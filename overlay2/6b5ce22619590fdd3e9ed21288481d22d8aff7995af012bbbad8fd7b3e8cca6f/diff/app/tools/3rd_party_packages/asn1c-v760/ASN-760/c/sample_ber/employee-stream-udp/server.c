/* This test driver program reads an encoded record from a UDP socket   */
/* and decodes it and displays the results.                             */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamMemory.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxSocket.h"

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT	ctxt;
   OSOCTET  buf[4096];
   int		i, len, stat;
   OSBOOL       trace = TRUE, verbose = FALSE;
   ASN1TAG      tag;

   OSRTSOCKET listenSocket;
   const char *ipAddress = "127.0.0.1";
   OSIPADDR   ipAddr;
   int        port = 9000, msglen = 0;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-p")) port = atoi(argv[++i]);
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -p <port> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -p <port> read from <port>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context for stream first */

   if ((stat = berStrmInitContext (&ctxt)) != 0) {
      printf ("Initialization failed, status %d\n", stat);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Initialize the socket layer and wait for input */
   if ((stat = rtxSocketsInit()) != 0) {
      printf ("Error:  unable to initialize socket layer.\n");
      return -1;
   }

   if ((stat = rtxSocketCreateUDP (&listenSocket)) != 0) {
      printf ("Error:  unable to create a listening socket.\n");
      return -1;
   }

   if ((stat = rtxSocketStrToAddr (ipAddress, &ipAddr)) != 0) {
      printf ("Error:  %s is not a valid address string.\n", ipAddress);
      return -1;
   }

   if ((stat = rtxSocketBind (listenSocket, ipAddr, port)) != 0) {
      printf ("Error:  unable to listen on %s:%d.\n", ipAddress, port);
      return -1;
   }

   /* Wait for input on the socket and decode. */
   while (1) {
      msglen = rtxSocketRecvTimed(listenSocket, buf, 4096, 30);

      if (msglen < 0) { /* There was a receiving error. */
         printf ("Error: unable to receive data on %s:%d.\n", ipAddress, 
               port);
         stat = msglen;
         break;
      }

      else if (msglen > 0) { /* Data was received that needs to be decoded. */
         /* Open the input stream to read data */
         stat = rtxStreamMemoryCreateReader (&ctxt, buf, 4096);
         if (stat != 0) {
            rtxErrPrint (&ctxt);
            break;
         }

         if ((stat = berDecStrmPeekTagAndLen (&ctxt, &tag, &len)) != 0) {
            rtxErrPrint (&ctxt);
            break;
         }

         /* Decode */

         stat = asn1BSD_PersonnelRecord (&ctxt, &employee, ASN1EXPL, 0);
         if (stat == 0) {
            if (trace) {
               printf ("Decode of PersonnelRecord was successful\n");
               printf ("Decoded record:\n");
               asn1Print_PersonnelRecord ("Employee", &employee);
            }
         }
         else {
            printf ("decode of PersonnelRecord failed\n");
            rtxErrPrint (&ctxt);
            break;
         }

         break; /* We've finished reading, so break out of the loop. */
      }
   }

   rtxSocketClose (listenSocket);
   berStrmFreeContext (&ctxt);

   return stat;
}
