// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
<include-files>
#include "<rtEncRulesSrcDir>/<cppTypesHdrFile>"
#include "rtxsrc/OSRTSocketInputStream.h"
#include "rtxsrc/OSRTSocketOutputStream.h"
#include "rtxsrc/OSRTString.h"
#include "rtxsrc/OSRTStringTokenizer.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxUTF8.h"

#define MAX_ATTEMPTS 10

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   OSRTString   ipAddress("127.0.0.1");
   OSSIZE       count = 2; // number of messages to send/recv
   int		i, ret, port = 9000;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) {
            // output string format is <ipaddress>:<port>
            OSRTStringTokenizer st (argv[++i], ":");
            ipAddress = st.nextToken();
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
         else if (!strcmp (argv[i], "-n")) {
            if (0 != rtxUTF8StrToSize (OSUTF8(argv[++i]), &count)) {
               printf ("Could not convert argument to size type\n");
               return -1;
            }
         }
         else {
            printf ("usage: client [-a|-u] [-v] [-o <ipaddr:port>] "
                    "[-n <count>] [-notrace]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <ip-address:port>  "
                    "send encoded msg to <ip-address:port>.\n");
            printf ("   -n <count>  iteration count\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   OSRTSocket socket;

   // Connect to the destination point

   if (trace) printf ("Connecting to %s:%i...", ipAddress.data(), port);
   socket.setRetryCount (MAX_ATTEMPTS);

   ret = socket.connect (ipAddress, port);
   if (0 != ret) {
      printf ("\nConnection failed, error code is %i\n", socket.getStatus());
      return socket.getStatus();
   }

   if (trace) printf ("\nConnection is established.\n");

   OSRTSocketOutputStream sockstrm (socket);

   // Set up encoding objects

   <encodeBufferClass> encbuf (sockstrm <alignedArg>);
   ASN1T_<PDU-Type> encdata;
   ASN1C_<PDU-Type> encoder (encbuf, encdata);

   // Set up decoding objects

   OSRTSocketInputStream sockistrm (socket);
   <decodeBufferClass> decbuf (sockistrm <alignedArg>);
   ASN1T_<PDU-Type> decdata;
   ASN1C_<PDU-Type> decoder (decbuf, decdata);

   // Loop to send requests and read responses

   // Populate structure of generated type
   // This assumes -test or -randtest was specified on asn1c command-line.

   encoder.genTestInstance();

   // Encode

   encbuf.setTrace (trace);
   encbuf.setDiag (verbose);

   for (size_t ii = 0; ii < count; ii++) {
      if ((ret = encoder.Encode()) == 0) {
         sockstrm.flush();
         if (trace) {
            printf ("Encoding was successful\n");
            printf ("Hex dump of encoded record:\n");
            encbuf.hexDump ();
            printf ("Binary dump:\n");
            encbuf.binDump ("employee");
         }
      }
      else {
         printf ("Encoding failed, status = %d\n", ret);
         encbuf.printErrorInfo ();
         return ret;
      }

      if ((ret = decoder.Decode()) == 0) {
         if (trace) {
            printf ("Decoding was successful\n");
            printf ("Binary dump:\n");
            decbuf.binDump ("employee");
            printf ("Decoded record:\n");
            decoder.Print();
         }
      }
      else {
         printf ("Decoding failed, status = %d\n", ret);
         decbuf.printErrorInfo ();
         return ret;
      }
   }

   if (trace) printf ("\nConnection is closed.\n");

   return ret;
}
