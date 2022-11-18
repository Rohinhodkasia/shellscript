/*
This reader program uses a stream approach to decode a file with TS 32.297
headers and CDRs.
*/

#include "IMS-R8-2009-03.h"

#include "rtxsrc/rtxCommon.h"
#include "rtsrc/rt3GPPTS32297.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxPrintStream.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtbersrc/asn1berStream.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   TS32297CDRFileHeader fileHeader;
   TS32297CDRHeader cdrHeader;
   IMSRecord data;
   OSCTXT      ctxt;
   OSBOOL     trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int        i, stat;
   unsigned int ui;

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

   /* Create a new context structure */
   if ((stat = berStrmInitContext (&ctxt)) != 0) {
      printf ("Context initialization failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Set print stream to stdout */
   rtxSetPrintStream (&ctxt, rtxPrintStreamToStdoutCB, 0);

   /* Open file stream for reading */
   stat = rtxStreamFileCreateReader (&ctxt, filename);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Decode TS 32.297 file header */
   rtInitTS32297FileHdr(&fileHeader);
   stat = rtDecTS32297FileHdr (&ctxt, &fileHeader);
   if (stat < 0) {
      printf ("decode of file header failed\n");
      rtxErrPrint (&ctxt);
      berStrmFreeContext (&ctxt);
      return stat;
   }
   if (trace) {
      rtPrtToStrmTS32297FileHdr (&ctxt, &fileHeader);
   }

   for (ui = 1; ui <= fileHeader.cdrCount; ui++) {

      /* Decode TS 32.297 record header */
      rtInitTS32297Hdr(&cdrHeader);
      stat = rtDecTS32297Hdr (&ctxt, &cdrHeader);
      if (stat < 0) {
         printf ("decode of CDR header failed\n");
         rtxErrPrint (&ctxt);
         berStrmFreeContext (&ctxt);
         return stat;
      }
      if (trace) {
         rtPrtToStrmTS32297Hdr (&ctxt, &cdrHeader);
      }

      asn1Init_IMSRecord (&data);

      /* Call compiler generated decode function */
      stat = asn1BSD_IMSRecord (&ctxt, &data, ASN1EXPL, 0);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         berStrmFreeContext (&ctxt);
         return stat;
      }
      if (trace) {
         asn1Print_IMSRecord ("Data", &data);
      }

      rtxMemReset (&ctxt);
   }

   rtxStreamClose (&ctxt);
   berStrmFreeContext (&ctxt);
   return 0;
}