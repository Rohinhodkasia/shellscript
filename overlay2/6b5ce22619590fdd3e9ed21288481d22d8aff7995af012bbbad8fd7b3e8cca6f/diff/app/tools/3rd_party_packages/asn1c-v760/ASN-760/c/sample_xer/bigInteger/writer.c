/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 4096

int main (int argc, char** argv)
{
   Dss_Parms    dss;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN];
   int		i, stat;
   const char* filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;
   FILE *fp;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

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

   /* Init */

   if (rtXmlInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   rtXmlSetEncBufPtr(&ctxt, msgbuf, sizeof(msgbuf));
   if (cxer) rtxCtxtSetFlag(&ctxt, OSXMLC14N);

   /* Populate structure of generated type */
   
   memset (&dss, 0, sizeof (dss));
   dss.p = "0x112233445566778899aabbccddeeff";
   dss.q = "-1234567890123456789012345678901234567890";
   dss.g = "1234567890123456789012345678901234567890";

   /* Encode */

   stat = XmlEnc_Dss_Parms_PDU (&ctxt, &dss);

   if (stat == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((char*)msgbuf);
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      exit (-1);
   }
  
   /* Write the encoded message out to the output file */

   if (fp = fopen (filename, "w")) {
      fputs ((char*)msgbuf, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }
   rtFreeContext (&ctxt);
   return 0;

}

