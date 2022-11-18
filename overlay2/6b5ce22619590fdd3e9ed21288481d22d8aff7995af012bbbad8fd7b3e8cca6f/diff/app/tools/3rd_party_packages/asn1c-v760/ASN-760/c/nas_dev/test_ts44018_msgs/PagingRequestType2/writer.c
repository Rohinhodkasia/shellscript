#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_PagingRequestType2*
    asn1Test_TS44018Msg_PagingRequestType2 (OSCTXT* pctxt)
{
   TS44018Msg_PagingRequestType2* pvalue = rtxMemAllocType (pctxt, TS44018Msg_PagingRequestType2);
   asn1Init_TS44018Msg_PagingRequestType2 (pvalue);

   pvalue->channelsNeededForMobiles1And2.channel_second = 2;

   pvalue->channelsNeededForMobiles1And2.channel_first = 1;

   pvalue->pageMode.spare_bit = 0;

   pvalue->pageMode.pm = 2;

   pvalue->mobileIdentity1.t =  2;
   rtxStrncpy(pvalue->mobileIdentity1.u.imei,
              sizeof(pvalue->mobileIdentity1.u.imei),
			  "5000b9c72#20*#5", 16);

   pvalue->mobileIdentity2.t =  1;
   rtxStrncpy (pvalue->mobileIdentity2.u.imsi, sizeof(pvalue->mobileIdentity2.u.imsi), "64801123456789", 15);

   pvalue->m.mobileIdentity3Present = 1;
   pvalue->mobileIdentity3.t =  5;

   pvalue->mobileIdentity3.u.tmgi.mbmsSessIdInd = 1;

   pvalue->mobileIdentity3.u.tmgi.mccMncInd = 1;

   {
      static const OSOCTET testdata[] = { 
      0xb4, 0x21, 0x4e };
      OSCRTLSAFEMEMCPY ((void*)pvalue->mobileIdentity3.u.tmgi.mbmsServiceID, 3, testdata, 3);
   }

   rtxStrncpy (pvalue->mobileIdentity3.u.tmgi.mcc_mnc.mcc, 4, "238", 3);
   rtxStrncpy (pvalue->mobileIdentity3.u.tmgi.mcc_mnc.mnc, 4, "02", 3);

   pvalue->mobileIdentity3.u.tmgi.mbmsSessionID = 253;
   return (pvalue);
}


TS44018IE_P2_Rest_Octets* asn1Test_TS44018IE_P2_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_P2_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_P2_Rest_Octets);
   asn1Init_TS44018IE_P2_Rest_Octets (pvalue);

   pvalue->m.cn3Present = 1;
   pvalue->cn3 = 2;

   pvalue->m.component_2Present = 1;

   pvalue->component_2.nln_pch = 1;

   pvalue->component_2.nln_status_PCH = 0;

   pvalue->m.priority1Present = 1;
   pvalue->priority1 = 6;

   pvalue->m.priority2Present = 1;
   pvalue->priority2 = 3;

   pvalue->m.priority3Present = 1;
   pvalue->priority3 = 3;

   pvalue->m.packet_Page_Indication_3Present = 1;
   pvalue->packet_Page_Indication_3 = TS44018IE_LHType_lbit;

   pvalue->m.component_7Present = 1;

   pvalue->component_7.m.component_1Present = 1;

   pvalue->component_7.component_1.m.mbms_Notification_3Present = 1;
   pvalue->component_7.component_1.mbms_Notification_3.t =  1;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.m.component_1Present = 1;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.m.frequency_ParametersPresent = 1;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.tsc = 5;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.t =  1;
   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.frequency_Parameters.component_2.u.arfcn = 462;

   pvalue->component_7.component_1.mbms_Notification_3.u.choice_1.component_1.mbms_p_t_m_channel_description.dl_timeslot_allocation = 55;

   /* zero elements */

   pvalue->component_7.component_1.m.p2_MBMS_InformationPresent = 1;

   /* zero elements */

   pvalue->component_7.component_1.p2_MBMS_Information.m.mbms_Sessions_List_2Present = 1;
   /* zero elements */

   /* zero elements */

   pvalue->m.component_8Present = 1;

   pvalue->component_8.implicit_Reject_CS = 0;

   pvalue->component_8.implicit_Reject_PS = 0;

   pvalue->m.ipa_SupportPresent = 1;
   pvalue->ipa_Support = 0;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_PagingRequestType2;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_PagingRequestType2;
   pdu.data.u.obj_PagingRequestType2 =
      asn1Test_TS44018Msg_PagingRequestType2(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_PagingRequestType2;
   pdu.restOctets.u.obj_PagingRequestType2 =
      asn1Test_TS44018IE_P2_Rest_Octets(pctxt);


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

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
