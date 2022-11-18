#include "TS24301IES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

int main (int argc, char** argv)
{
   TS24301IE_TrackingAreaIdentListItem* pvalue;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   OSSIZE       len;
   int		i, ret;
   OSBOOL       verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: writer [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            return 0;
         }
      }
   }

   /* Initialize context structure */

   ret = rtInitContext (&ctxt);
   if (0 != ret) {
      printf ("rtInitContext failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Populate data structure */

   pvalue = rtxMemAllocType (&ctxt, TS24301IE_TrackingAreaIdentListItem);
   asn1Init_TS24301IE_TrackingAreaIdentListItem (pvalue);

   pvalue->spare = 0;
   pvalue->typeOfList = 0;
   pvalue->numElements = 1;
   rtxStrncpy(pvalue->elements.u.partTrkIdentList0.mcc_mnc.mcc,
              sizeof(pvalue->elements.u.partTrkIdentList0.mcc_mnc.mcc),
			  "110", 4);
   rtxStrncpy(pvalue->elements.u.partTrkIdentList0.mcc_mnc.mnc,
              sizeof(pvalue->elements.u.partTrkIdentList0.mcc_mnc.mnc),
			  "684", 4);

   pvalue->elements.u.partTrkIdentList0.tacs.n = 2;
   {
      static const OSOCTET testdata[] = {
      0x51, 0xcb };
      OSCRTLMEMCPY ((void*)pvalue->elements.u.partTrkIdentList0.tacs.elem[0].data, testdata, 2);
   }

   {
      static const OSOCTET testdata[] = {
      0x4b, 0xc4 };
      OSCRTLMEMCPY ((void*)pvalue->elements.u.partTrkIdentList0.tacs.elem[1].data, testdata, 2);
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24301IE_TrackingAreaIdentListItem (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode TrackingAreaIdentListItem failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   msgptr = rtxCtxtGetMsgPtr (&ctxt);
   len = rtxCtxtGetMsgLen (&ctxt);

   if (verbose) {
      printf ("Encoding was successful\n");
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
      printf ("\n");
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   /* Write encoded message to output file */

   ret = rtxFileWriteBinary (filename, msgptr, len);
   if (0 != ret) {
      printf ("rtxFileWriteBinary failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   rtxFreeContext (&ctxt);

   return 0;
}