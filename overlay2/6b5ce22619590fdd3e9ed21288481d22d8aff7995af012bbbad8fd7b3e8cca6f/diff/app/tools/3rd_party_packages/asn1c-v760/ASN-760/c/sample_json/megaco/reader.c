/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "MEDIA-GATEWAY-CONTROL.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   MegacoMessage megacoMessage;
   OSCTXT	ctxt, outctxt;
   OSOCTET*     msgbuf;
   ASN1TAG	tag;
   OSSIZE       len, len2; 
   OSBOOL       indefLen;
   int		i, stat;
   const char*  filename = "msg05.bin",
         *outfile = "message.json";
   OSBOOL       trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context structure */

   if (rtInitContext (&ctxt) != 0) {
      printf ("Error initializing context\n");
      return -1;
   }

   rtxSetDiag (&ctxt, verbose);

   /* Read input file into a memory buffer */

   stat = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
   if (0 != stat) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   stat = xd_setp64 (&ctxt, msgbuf, len, &tag, &len2, &indefLen);
   if (0 != stat) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Decode */

   stat = asn1D_MegacoMessage (&ctxt, &megacoMessage, ASN1EXPL, 0);
   if (stat == 0) {
      if (trace) {
         printf ("Decode was successful\n");
         printf ("Decoded record:\n");
         asn1Print_MegacoMessage ("megacoMessage", &megacoMessage);
      }
   }
   else {
      printf ("decode failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }

   rtInitContext (&outctxt);
   stat = rtxStreamFileCreateWriter (&outctxt, outfile);

   if (stat != 0) {
      printf ("Unable to open '%s' for writing.\n", outfile);
      rtxErrPrint (&outctxt);
      rtFreeContext (&ctxt);
      rtFreeContext (&outctxt);
      return stat;
   }

   stat = asn1JsonEnc_MegacoMessage (&outctxt, &megacoMessage);
   
   if (stat == 0) {
      printf ("Message encoded successfully.\n");
   }
   else {
      rtxErrPrint (&outctxt);
      rtFreeContext (&ctxt);
      rtFreeContext (&outctxt);
      return stat;
   }

   rtFreeContext (&ctxt);
   rtFreeContext (&outctxt);
   return 0;
}
