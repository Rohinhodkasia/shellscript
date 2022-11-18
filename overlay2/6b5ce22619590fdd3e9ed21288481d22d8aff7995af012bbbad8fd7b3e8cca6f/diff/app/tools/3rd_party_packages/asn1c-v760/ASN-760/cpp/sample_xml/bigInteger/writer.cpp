// This test driver program encodes a data record and writes the        
// encoded result to an output file..                                   

#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

#define MAXMSGLEN 4096

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSOCTET      msgbuf[MAXMSGLEN];
   int          i, stat;
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -v             verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace       do not display trace info\n");
            return 0;
         }
      }
   }

   // Populate structure of generated type 

   ASN1T_Dss_Parms dss;
   dss.p = "0x112233445566778899aabbccddeeff";
   dss.q = "-1234567890123456789012345678901234567890";
   dss.g = "1234567890123456789012345678901234567890";

   // Encode 

   OSXMLEncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   ASN1C_Dss_Parms dssC (encodeBuffer, dss);

   if ((stat = dssC.Encode ()) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((const char*)msgbuf);
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return stat;
   }
  
   // Write the encoded message out to the output file 

   stat = encodeBuffer.write (filename);
   if (stat < 0) {
      printf ("Write to output file failed.\n");
      encodeBuffer.printErrorInfo ();
      return stat;
   }

   return 0;

}
