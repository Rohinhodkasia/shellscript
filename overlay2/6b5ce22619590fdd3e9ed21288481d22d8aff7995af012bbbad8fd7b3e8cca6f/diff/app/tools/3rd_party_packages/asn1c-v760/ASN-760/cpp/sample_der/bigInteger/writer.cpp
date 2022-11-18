// This test driver program encodes a data record and writes the
// encoded result to an output file..                                   

#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   int		i, len;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Populate structure of generated type 

   ASN1T_Dss_Parms dss;
   dss.p = "0x112233445566778899aabbccddeeff";
   dss.q = "-1234567890123456789012345678901234567890";
   dss.g = "1234567890123456789012345678901234567890";

   // Encode in a dynamic buffer 

   ASN1BEREncodeBuffer encodeBuffer;
   encodeBuffer.setDiag (verbose);
   ASN1C_Dss_Parms dssC (encodeBuffer, dss);

   if ((len = dssC.Encode ()) > 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.HexDump (len);
         printf ("Binary dump:\n");
         encodeBuffer.BinDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.PrintErrorInfo ();
      return (-1);
   }
  
   // Write the encoded message out to the output file 

   int ret = rtxFileWriteBinary (filename, msgptr, len);
   if (ret < 0) {
      printf ("Write to file %s failed\n", filename);
      return ret;
   }

   return 0;

}
