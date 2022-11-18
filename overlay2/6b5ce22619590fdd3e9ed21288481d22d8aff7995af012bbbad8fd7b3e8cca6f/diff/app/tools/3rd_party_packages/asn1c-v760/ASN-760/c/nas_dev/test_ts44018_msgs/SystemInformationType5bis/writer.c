#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType5bis*
    asn1Test_TS44018Msg_SystemInformationType5bis (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType5bis* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType5bis);
   asn1Init_TS44018Msg_SystemInformationType5bis (pvalue);

   pvalue->extensionBCCHFrequencyListDescription.t =  1;

   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.ext_ind = 0;

   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.ba_ind = 0;

   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[0] = 0x6b;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[1] = 0x82;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[2] = 0x10;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[3] = 0xa7;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[4] = 0x41;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[5] = 0x9;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[6] = 0x19;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[7] = 0x5f;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[8] = 0xe5;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[9] = 0xc2;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[10] = 0xa;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[11] = 0xcb;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[12] = 0xc8;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[13] = 0x7a;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[14] = 0xaf;
   pvalue->extensionBCCHFrequencyListDescription.u.bitmap0.bitmap0[15] = 0xad;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType5bis;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5bis;
   pdu.data.u.obj_SystemInformationType5bis =
      asn1Test_TS44018Msg_SystemInformationType5bis(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5bis;

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
