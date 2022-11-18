/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxStreamSocket.h"

#define DEFAULT_URL "http://127.0.0.1:9124"

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT       ctxt;
   int          i, stat, numMsgs = 2, port, destPort;
   const char*  url = DEFAULT_URL;
   char buf[100];
   OSIPADDR     ipAddr = OSIPADDR_LOCAL, destIP;
   OSRTSOCKET   listenSocket, socket;
   OSBOOL       aligned = TRUE, trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-url")) url = argv[++i];
         else {
            printf ("usage: server -a | -u [ -v ] [ -url ]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -url  bind URL http://host:port\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   {
      char* portStr;

      strcpy (buf, url);
      portStr = strstr (buf, "://");
      if (portStr != 0) {
         url = portStr + 3;
      }
      else
         url = buf;

      portStr = strchr (url, ':');
      if (portStr != 0) {
         *portStr = 0;
         portStr++;
         port = atoi (portStr);
      }
   }

   /* Init context structure */

   if (rtInitContext (&ctxt) != 0) {
      printf ("Error initializing context\n");
      return -1;
   }

   rtxSetDiag (&ctxt, verbose);

   /* One-time socket package initialization (required for Windows only) */

   stat = rtxSocketsInit();
   if (0 != stat) {
      printf ("Socket initialization failed.\n");
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Create listener socket */

   if ((stat = rtxSocketCreate (&listenSocket)) != 0) {
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Bind the socket */

   if ((stat = rtxSocketStrToAddr (url, &ipAddr)) != 0) {
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }
   if ((stat = rtxSocketBind (listenSocket, ipAddr, port)) != 0) {
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Wait for connection */

   if ((stat = rtxSocketListen (listenSocket, 1)) != 0) {
      rtxErrSetData (&ctxt, stat, __FILE__, __LINE__);
      rtxErrPrint (&ctxt);
      return stat;
   }

   if (trace) printf ("Wait for connection...\n");

   if ((stat = rtxSocketAccept 
                  (listenSocket, &socket, &destIP, &destPort)) != 0) 
   {
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

   /* Create input source object */
   stat = rtxStreamSocketAttach (&ctxt, socket, OSRTSTRMF_INPUT);
   printf ("decoding %d messages..\n", numMsgs);

   ctxt.buffer.aligned = aligned;
   pu_setTrace (&ctxt, trace);
   
   for (i = 0; i < numMsgs; i++) {
      /* Call compiler generated decode function */

      stat = asn1PD_PersonnelRecord (&ctxt, &employee);
      rtxByteAlign (&ctxt);

      if (trace) {
         printf ("Dump of decoded bit fields:\n");
         pu_bindump (&ctxt, "employee");
         printf ("\n");
      }

      if (stat == 0) {
         if (trace) {
            printf ("decode of PersonnelRecord was successful\n");
            asn1Print_PersonnelRecord ("Employee", &employee);
         }
      }
      else {
         printf ("decode of PersonnelRecord failed\n");
         rtxErrPrint (&ctxt);
         return -1;
      }

      /* rtxMemReset (&ctxt); */
   }

   rtxStreamClose (&ctxt);
   rtFreeContext (&ctxt);
   return 0;
}
