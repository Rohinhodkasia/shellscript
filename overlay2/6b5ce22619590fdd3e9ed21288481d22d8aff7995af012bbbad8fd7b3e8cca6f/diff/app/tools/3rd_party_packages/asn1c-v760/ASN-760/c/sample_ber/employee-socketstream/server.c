/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results.                             */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamSocket.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024
#define MAX_CONNECT_ATTEMPTS 3

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT	ctxt;
   int		i, len, stat, port = 9000, destPort;
   const char*  ipAddressStr = "127.0.0.1";
   OSBOOL       trace = TRUE, verbose = FALSE;
   OSIPADDR     ipAddr = OSIPADDR_LOCAL, destIP;
   OSRTSOCKET   socket, listenSocket;
   ASN1TAG      tag;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-l")) {
            char* portStr;
            ipAddressStr = argv[++i];
            portStr = strchr (ipAddressStr, ':');
            if (portStr != 0) {
               *portStr = 0;
               portStr++;
               port = atoi (portStr);
            }
         }
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: server [ -v ] [ -l <ip-address:port> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -l <ip-address:port>  bind local <ip-address:port>.\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context for stream first */

   if ((stat = berStrmInitContext (&ctxt)) != 0) {
      printf ("Initialization failed, status %d\n", stat);
      rtxErrPrint (&ctxt);
      return stat;
   }
   if (verbose) rtxSetDiag (&ctxt, TRUE);

   /* One-time socket package initialization (required for Windows only) */

   stat = rtxSocketsInit();
   if (0 != stat) {
      printf ("Socket initialization failed.\n");
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   stat = rtxSocketCreate (&listenSocket);
   if (0 != stat) {
      printf ("Socket creation failed.\n");
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Bind the socket */
   stat = rtxSocketStrToAddr (ipAddressStr, &ipAddr);
   if (0 != stat) {
      printf ("Address translation failed.\n");
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   stat = rtxSocketBind (listenSocket, ipAddr, port);
   if (0 != stat) {
      printf ("Socket binding failed.\n");
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Wait for a connection from a remote side... */

   stat = rtxSocketListen (listenSocket, 1);
   if (0 != stat) {
      printf ("Socket listening failed.\n");
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   if (trace) printf ("Wait for connection...\n");

   stat = rtxSocketAccept (listenSocket, &socket, &destIP, &destPort); 
   if (0 != stat) {
      printf ("Socket accept failed.\n");
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   if (trace) {
      char addr[100];

      if (rtxSocketAddrToStr (destIP, addr, sizeof (addr)) != 0)
         strcpy (addr, "<unknown>");
      printf ("Connection is established with %s:%d\n", addr, destPort);
   }


   stat = rtxStreamSocketAttach 
      (&ctxt, socket, OSRTSTRMF_INPUT);

   if (0 != stat) {
      printf ("Stream initialization failed.\n");
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Decode */

   if ((stat = berDecStrmPeekTagAndLen (&ctxt, &tag, &len)) != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   if (tag == TV_PersonnelRecord) {

      /* Call compiler generated decode function */

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
         return -1;
      }
   }
   else {
      printf ("unexpected tag %hx received\n", tag);
   }

   rtxSocketClose (socket);

   berStrmFreeContext (&ctxt);
   return 0;
}
