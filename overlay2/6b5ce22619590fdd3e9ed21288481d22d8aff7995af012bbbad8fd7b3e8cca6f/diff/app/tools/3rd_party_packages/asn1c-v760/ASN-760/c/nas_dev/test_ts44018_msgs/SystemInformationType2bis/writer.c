#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType2bis*
    asn1Test_TS44018Msg_SystemInformationType2bis (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType2bis* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType2bis);
   asn1Init_TS44018Msg_SystemInformationType2bis (pvalue);

   pvalue->extendedBCCHFrequencyList.t =  1;

   pvalue->extendedBCCHFrequencyList.u.bitmap0.ext_ind = 0;

   pvalue->extendedBCCHFrequencyList.u.bitmap0.ba_ind = 0;

   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[0] = 0x68;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[1] = 0x57;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[2] = 0x56;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[3] = 0x8a;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[4] = 0x76;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[5] = 0x6f;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[6] = 0xa3;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[7] = 0xea;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[8] = 0x3e;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[9] = 0xc6;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[10] = 0x87;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[11] = 0xa9;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[12] = 0x15;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[13] = 0x6;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[14] = 0x5b;
   pvalue->extendedBCCHFrequencyList.u.bitmap0.bitmap0[15] = 0xe6;

   pvalue->rachControlParameter.max_retrans = 2;

   pvalue->rachControlParameter.tx_integer = 12;

   pvalue->rachControlParameter.cell_bar_access = 0;

   pvalue->rachControlParameter.re = 0;

   pvalue->rachControlParameter.acc = 59999;
   return (pvalue);
}


TS44018IE_SI2bis_Rest_Octets*
    asn1Test_TS44018IE_SI2bis_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI2bis_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI2bis_Rest_Octets);
   asn1Init_TS44018IE_SI2bis_Rest_Octets (pvalue);

   pvalue->m.paddingPresent = 1;
   pvalue->padding.t =  2;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType2bis;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2bis;
   pdu.data.u.obj_SystemInformationType2bis =
      asn1Test_TS44018Msg_SystemInformationType2bis(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2bis;
   pdu.restOctets.u.obj_SystemInformationType2bis =
      asn1Test_TS44018IE_SI2bis_Rest_Octets(pctxt);


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
