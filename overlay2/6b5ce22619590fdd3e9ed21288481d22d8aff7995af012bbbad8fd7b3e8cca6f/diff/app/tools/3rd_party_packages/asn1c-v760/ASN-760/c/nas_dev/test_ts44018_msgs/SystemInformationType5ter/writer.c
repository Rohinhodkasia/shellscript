#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType5ter*
    asn1Test_TS44018Msg_SystemInformationType5ter (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType5ter* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType5ter);
   asn1Init_TS44018Msg_SystemInformationType5ter (pvalue);

   pvalue->extendedBCCHFrequencyList.t =  2;

   pvalue->extendedBCCHFrequencyList.u.choice_2.multiband_reporting = 0;

   pvalue->extendedBCCHFrequencyList.u.choice_2.ba_ind = 0;

   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.t =  4;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[0] = 0xe1;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[1] = 0x77;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[2] = 0x4e;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[3] = 0x33;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[4] = 0xca;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[5] = 0xee;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[6] = 0x1b;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[7] = 0x27;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[8] = 0xcf;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[9] = 0xe6;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[10] = 0x5e;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[11] = 0xbb;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[12] = 0xe9;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[13] = 0x6f;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[14] = 0x63;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[15] = 0x2b;
   return (pvalue);
}


int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU pdu;

   OSCTXT	ctxt;
   OSCTXT*  pctxt = &ctxt;
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

   asn1Init_TS44018Msg_L2_PSEUDO_LEN_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType5ter;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5ter;
   pdu.data.u.obj_SystemInformationType5ter =
      asn1Test_TS44018Msg_SystemInformationType5ter(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5ter;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, &pdu);
   if (0 != ret) {
      printf ("encode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

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
