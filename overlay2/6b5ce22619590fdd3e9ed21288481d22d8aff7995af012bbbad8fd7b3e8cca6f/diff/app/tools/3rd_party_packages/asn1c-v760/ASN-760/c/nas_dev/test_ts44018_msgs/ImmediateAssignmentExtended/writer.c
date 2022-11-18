#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_ImmediateAssignmentExtended*
    asn1Test_TS44018Msg_ImmediateAssignmentExtended (OSCTXT* pctxt)
{
   TS44018Msg_ImmediateAssignmentExtended* pvalue = rtxMemAllocType (pctxt, TS44018Msg_ImmediateAssignmentExtended);
   asn1Init_TS44018Msg_ImmediateAssignmentExtended (pvalue);

   pvalue->featureIndicator.spare_bit = 2;

   pvalue->featureIndicator.cs_ir = 0;

   pvalue->featureIndicator.ps_ir = 0;

   pvalue->pageMode.spare_bit = 0;

   pvalue->pageMode.pm = 2;

   pvalue->channelDescr1.channel_type_and_TDMA_offset = 29;

   pvalue->channelDescr1.tn = 0;

   pvalue->channelDescr1.tsc = 6;

   pvalue->channelDescr1.component_4.t =  2;

   pvalue->channelDescr1.component_4.u.choice_2.spare_bit = 1;

   pvalue->channelDescr1.component_4.u.choice_2.arfcn = 518;

   pvalue->requestReference1.ra = 149;

   pvalue->requestReference1.t1prime = 18;

   pvalue->requestReference1.t3 = 55;

   pvalue->requestReference1.t2 = 22;

   pvalue->timingAdvance1 = 121;

   pvalue->channelDescr2.channel_type_and_TDMA_offset = 17;

   pvalue->channelDescr2.tn = 5;

   pvalue->channelDescr2.tsc = 0;

   pvalue->channelDescr2.component_4.t =  1;

   pvalue->channelDescr2.component_4.u.choice_1.maio = 11;

   pvalue->channelDescr2.component_4.u.choice_1.hsn = 21;

   pvalue->requestReference2.ra = 134;

   pvalue->requestReference2.t1prime = 24;

   pvalue->requestReference2.t3 = 30;

   pvalue->requestReference2.t2 = 28;

   pvalue->timingAdvance2 = 143;

   pvalue->mobileAllocation.length = 3;

   pvalue->mobileAllocation.mac.numbits = 24;
   pvalue->mobileAllocation.mac.data[0] = 0x71;
   pvalue->mobileAllocation.mac.data[1] = 0x4b;
   pvalue->mobileAllocation.mac.data[2] = 0x65;

   pvalue->m.startingTimePresent = 1;

   pvalue->startingTime.t1prime = 3;

   pvalue->startingTime.t3 = 15;

   pvalue->startingTime.spare_bit = 18;
   return (pvalue);
}


TS44018IE_IAX_Rest_Octets* asn1Test_TS44018IE_IAX_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_IAX_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_IAX_Rest_Octets);

   pvalue->compressed_Inter_RAT_HO_INFO_IND = 0;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_ImmediateAssignmentExtended;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ImmediateAssignmentExtended;
   pdu.data.u.obj_ImmediateAssignmentExtended =
      asn1Test_TS44018Msg_ImmediateAssignmentExtended(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ImmediateAssignmentExtended;
   pdu.restOctets.u.obj_ImmediateAssignmentExtended =
      asn1Test_TS44018IE_IAX_Rest_Octets(pctxt);


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
