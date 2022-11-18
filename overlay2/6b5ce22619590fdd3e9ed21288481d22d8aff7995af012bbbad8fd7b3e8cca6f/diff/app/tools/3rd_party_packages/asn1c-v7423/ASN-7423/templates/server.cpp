#include <stdio.h>
#include <stdlib.h>
<include-files>
#include "<rtEncRulesSrcDir>/<cppTypesHdrFile>"
#include "rtxsrc/OSRTSocketInputStream.h"
#include "rtxsrc/OSRTSocketOutputStream.h"
#include "rtxsrc/OSRTString.h"
#include "rtxsrc/OSRTStringTokenizer.h"
#include "rtxsrc/rtxMemLeakCheck.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   int		port = 9000, destPort, stat;
   OSRTString   ipAddressStr = "127.0.0.1";
   OSIPADDR     destIP;

   // Process command line arguments

   if (argc > 1) {
      for (int i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-l")) {
            // parameter format is <ipaddress>:<port>
            OSRTStringTokenizer st (argv[++i], ":");
            ipAddressStr = st.nextToken();
            if (st.hasMoreTokens()) {
               OSRTString portStr = st.nextToken();
               if (!portStr.toInt (port)) {
                  printf ("conversion of port string '%s' to integer failed\n", 
                          portStr.data());
                  return -1;
               }
            }
         }
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -l <ip-address:port> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -l <ip-address:port>  bind local <ip-address:port>.\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   OSRTSocket listenSocket;

   if (listenSocket.bind (ipAddressStr, port) != 0) {
      printf ("listenSocket.bind failed, status %d\n", 
              listenSocket.getStatus ());
      return -1;
   }

   if (listenSocket.listen (1) != 0) {
      printf ("listenSocket.listen failed, status %d\n", 
              listenSocket.getStatus ());
      return -1;
   }

   if (trace) printf ("Wait for connection...\n");
   
   OSRTSocket* socket = listenSocket.accept (&destIP, &destPort);
   if (listenSocket.getStatus () != 0) {
      printf ("listenSocket.accept failed, status %d\n", 
              listenSocket.getStatus ());
      return -1;
   }

   if (trace) {
      char addr[100];

      printf ("Connection is established with %s:%d\n", 
         OSRTSocket::addrToString (destIP, addr, sizeof (addr)), destPort);
   }

   // Set up decoding objects

   OSRTSocketInputStream sockstrm (*socket);
   <decodeBufferClass> decbuf (sockstrm <alignedArg>);
   if (decbuf.getStatus() != 0) {
      decbuf.printErrorInfo ();
      return decbuf.getStatus();
   }
   decbuf.setDiag (verbose);

   ASN1T_<PDU-Type> data;
   ASN1C_<PDU-Type> decoder (decbuf, data);

   // Set up encoding objects

   OSRTSocketOutputStream sockstrm2 (*socket);
   <encodeBufferClass> encbuf (sockstrm2 <alignedArg>);
   if (encbuf.getStatus() != 0) {
      encbuf.printErrorInfo ();
      return encbuf.getStatus();
   }
   encbuf.setDiag (verbose);

   ASN1C_<PDU-Type> encoder (encbuf, data);

   for (;;) {
      // Read data from socket and decode
      stat = decoder.Decode();
      if (0 == stat) {
         if (trace) {
            printf ("Decode of <PDU-Type> was successful\n");
            printf ("Decoded record:\n");
            decoder.Print("<PDU-Type>");
         }
      }
      else {
         // EOF status is OK
         if (stat != RTERR_ENDOFFILE) {
            printf ("decode of <PDU-Type> failed\n");
            decbuf.printErrorInfo ();
         }
         else stat = 0;
         break;
      }

      // Encode and send response back to client
      stat = encoder.Encode();
      if (0 == stat) {
         sockstrm2.flush();
         if (trace) {
            printf ("Encode of <PDU-Type> was successful\n");
         }
      }
      else {
         printf ("Encode of <PDU-Type> failed\n");
         encbuf.printErrorInfo ();
         break;
      }
   }

   delete socket;

   return stat;
}
