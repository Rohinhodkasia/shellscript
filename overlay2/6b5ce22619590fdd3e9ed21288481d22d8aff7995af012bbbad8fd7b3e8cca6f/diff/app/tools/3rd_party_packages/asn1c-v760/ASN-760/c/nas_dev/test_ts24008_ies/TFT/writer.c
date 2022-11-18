#include "TS24008IES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300
TS24008IE_TFT* test_TS24008IE_TFT (OSCTXT* pctxt);
TS24008IE_TFTParam* test_TS24008IE_TFTParam (OSCTXT* pctxt, size_t n);
TS24008IE_TFTPacketFilterItem*
    test_TS24008IE_TFTPacketFilterItem (OSCTXT* pctxt, size_t n);

int main (int argc, char** argv)
{
   TS24008IE_TFT* pvalue;
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

   pvalue = test_TS24008IE_TFT (&ctxt);

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008IE_TFT (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode TFT failed; status = %d\n", ret);
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

TS24008IE_TFT* test_TS24008IE_TFT (OSCTXT* pctxt)
{
   TS24008IE_TFT* pvalue = rtxMemAllocType (pctxt, TS24008IE_TFT);
   asn1Init_TS24008IE_TFT (pvalue);

   pvalue->octet1.tftOperationCode = 1; /* Create new TFT */
   pvalue->octet1.eBit = 1; /* include parameters list */
   pvalue->octet1.numPacketFilters = 2;

   pvalue->packetFilterList.u.filterItems.n = 2;
   pvalue->packetFilterList.u.filterItems.elem =
      test_TS24008IE_TFTPacketFilterItem (pctxt, 2);

   pvalue->paramList.n = 3;
   pvalue->paramList.elem = test_TS24008IE_TFTParam (pctxt, 3);

   return (pvalue);
}

TS24008IE_TFTParam* test_TS24008IE_TFTParam (OSCTXT* pctxt, size_t n)
{
   size_t i;

   TS24008IE_TFTParam* pvalue =
      rtxMemAllocArrayZ (pctxt, n, TS24008IE_TFTParam);

   for (i = 0; i < n; i++) {
      pvalue[i].paramIdentifier = TS24008IE_TFTParamId_flowId;
      pvalue[i].contents.u.flowId.mediaComponentNum = 362;
      pvalue[i].contents.u.flowId.ipFlowNum = 9746;
   }

   return (pvalue);
}

TS24008IE_TFTPacketFilterItem*
    test_TS24008IE_TFTPacketFilterItem (OSCTXT* pctxt, size_t n)
{
   size_t i;

   TS24008IE_TFTPacketFilterItem* pvalue =
      rtxMemAllocArrayZ (pctxt, n, TS24008IE_TFTPacketFilterItem);

   for (i = 0; i < n; i++) {
      pvalue[i].pfDirection = 3;
      pvalue[i].pfIdentifier = 14;
      pvalue[i].pfEvaluationPrecedence = 134;

      pvalue[i].contents.components.n = 2;
      pvalue[i].contents.components.elem  = rtxMemAllocArray(pctxt, 2, TS24008IE_TFTPacketFilterComponent);
      pvalue[i].contents.components.elem[0].id = TS24008IE_TFTPacketFilterComponentType_ipv4Remote;
      pvalue[i].contents.components.elem[0].value.u.ipv4Remote.addr[0] = 46;
      pvalue[i].contents.components.elem[0].value.u.ipv4Remote.addr[1] = 16;
      pvalue[i].contents.components.elem[0].value.u.ipv4Remote.addr[2] = 18;
      pvalue[i].contents.components.elem[0].value.u.ipv4Remote.addr[3] = 99;
      pvalue[i].contents.components.elem[0].value.u.ipv4Remote.mask[0] = 101;
      pvalue[i].contents.components.elem[0].value.u.ipv4Remote.mask[1] = 102;
      pvalue[i].contents.components.elem[0].value.u.ipv4Remote.mask[2] = 201;
      pvalue[i].contents.components.elem[0].value.u.ipv4Remote.mask[3] = 203;
      pvalue[i].contents.components.elem[1].id = TS24008IE_TFTPacketFilterComponentType_flowLabel;
      pvalue[i].contents.components.elem[1].value.u.flowLabel.spare = 0;
      pvalue[i].contents.components.elem[1].value.u.flowLabel.label = 27;      
   }
   return (pvalue);
}
