/*
This reader program uses a buffer approach to decode a file with TS 32.297
headers and CDRs.
*/

#include "IMS-R8-2009-03.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtsrc/rt3GPPTS32297.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   TS32297CDRFileHeader fileHeader;
   TS32297CDRHeader cdrHeader;
   IMSRecord data;
   OSCTXT      ctxt;
   OSOCTET*    pMsgBuf;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int         i, stat;
   unsigned int ui;
   OSSIZE      msglen, offset = 0;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Read input file */
   if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &msglen)) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   stat = rtxCtxtSetBufPtr(&ctxt, pMsgBuf, msglen);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   rtInitTS32297FileHdr(&fileHeader);

   /* Decode TS 32.297 file header */
   stat = rtDecTS32297FileHdr (&ctxt, &fileHeader);
   if (stat < 0) {
      printf ("decode of file header failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }
   if (trace) {
      rtPrtToStrmTS32297FileHdr (&ctxt, &fileHeader);
   }

   offset = fileHeader.headerLength;
   for (ui = 1; ui <= fileHeader.cdrCount; ui++) {

      /* Decode TS 32.297 record header */
      rtInitTS32297Hdr(&cdrHeader);
      stat = rtDecTS32297Hdr (&ctxt, &cdrHeader);
      if (stat < 0) {
         printf ("decode of CDR header failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return stat;
      }
      else {
         offset += stat;
      }
      if (trace) {
         rtPrtToStrmTS32297Hdr (&ctxt, &cdrHeader);
      }

      asn1Init_IMSRecord (&data);

      /* Call compiler generated decode function */
      stat = asn1D_IMSRecord (&ctxt, &data, ASN1EXPL, 0);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }
      if (trace) {
         asn1Print_IMSRecord ("Data", &data);
      }

      offset += cdrHeader.cdrLength;
      stat = rtxCtxtSetBufPtr(&ctxt, pMsgBuf + offset, msglen - offset);
      if (stat != 0) {
         rtxErrPrint (&ctxt);
         return stat;
      }
   }

   rtFreeContext (&ctxt);

   return 0;
}
