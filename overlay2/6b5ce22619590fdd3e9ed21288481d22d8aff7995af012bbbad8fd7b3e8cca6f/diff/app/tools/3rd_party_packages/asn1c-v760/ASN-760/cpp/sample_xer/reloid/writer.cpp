/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "TestPrint.cpp"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   FILE         *fp;
   OSOCTET	msgbuf[MAXMSGLEN];
   const char*  filename = "message.xml";
   int		i, len;
   unsigned char a[] = { 0xA0 };
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-cxer")) cxer = TRUE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -cxer          use canonical XER rules (CXER)\n");
            printf ("   -v             verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace       do not display trace info\n");
            return 0;
         }
      }
   }

   // Populate structure of generated type 

   OSXMLEncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   if (cxer) rtxCtxtSetFlag (encodeBuffer.getCtxtPtr(), OSXMLC14N);

   ASN1T_TestSeq seq;
   ASN1C_TestSeq tsSeq (encodeBuffer, seq);

   /* Populate TestSeq structure (note: this is the structure that was */
   /* generated by the compiler)..					*/
   seq.date = date;
   seq.time_ = time_;
   seq.number = number;
   seq.phone = phone;
   seq.account = account;
   seq.white = white;

   /* Encode */
   if ((len = tsSeq.Encode ()) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((const char*)msgbuf);
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      exit (-1);
   }

   // Write the encoded message out to the output file

   if (fp = fopen (filename, "w")) {
      fwrite (msgbuf, 1, encodeBuffer.getMsgLen(), fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   return 0;
}