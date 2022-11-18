#include "TS44018Msgs.h"
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
   TS44018Msg_DL_DCCH_PDU pdu;
   TS44018Msg_MbmsAnnouncement data;
   TS44018Msg_MbmsAnnouncement* pvalue = &data;

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

   asn1Init_TS44018Msg_DL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_MbmsAnnouncement;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_MbmsAnnouncement;
   pdu.data.u.obj_MbmsAnnouncement = pvalue;


   asn1Init_TS44018Msg_MbmsAnnouncement (pvalue);


   {
      static const OSOCTET testdata[] = { 
      0xeb, 0x4b, 0xb2 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->tempMobileGroupId.mbmsServiceID, 3, testdata, 3);
   }

   pvalue->tempMobileGroupId.m.mcc_mncPresent = 1;
   rtxStrncpy (pvalue->tempMobileGroupId.mcc_mnc.mcc, 4, "734", 3);
   rtxStrncpy (pvalue->tempMobileGroupId.mcc_mnc.mnc, 4, "03", 3);

   pvalue->m.mbmsSessionIdentityPresent = 1;
   pvalue->mbmsSessionIdentity.length = 0; /* length will be calculated */

   pvalue->mbmsSessionIdentity.mbms_Session_Identity = 192;

   pvalue->m.mbmsCountingChannelDescrPresent = 1;
   pvalue->mbmsCountingChannelDescr.length = 0; /* length will be calculated */

   pvalue->mbmsCountingChannelDescr.mprach_description.m.frequency_ParametersPresent = 1;

   pvalue->mbmsCountingChannelDescr.mprach_description.frequency_Parameters.tsc = 1;

   pvalue->mbmsCountingChannelDescr.mprach_description.frequency_Parameters.component_2.t =  1;
   pvalue->mbmsCountingChannelDescr.mprach_description.frequency_Parameters.component_2.u.arfcn = 530;

   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_timeslot_number = 3;

   pvalue->mbmsCountingChannelDescr.mprach_description.usf = 6;

   pvalue->mbmsCountingChannelDescr.mprach_description.m.mprach_Control_ParametersPresent = 1;

   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.m.acc_contr_classPresent = 1;
   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.acc_contr_class = 27417;

   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.m.max_retransPresent = 1;
   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.max_retrans = 1;

   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.s = 13;

   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.m.tx_intPresent = 1;
   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.tx_int = 13;

   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.m.persistence_levelPresent = 1;
   pvalue->mbmsCountingChannelDescr.mprach_description.mprach_Control_Parameters.persistence_level = 4;

   pvalue->m.mbmsPtmChannelDescrPresent = 1;
   pvalue->mbmsPtmChannelDescr.length = 0; /* length will be calculated */

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.m.frequency_ParametersPresent = 1;

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.frequency_Parameters.tsc = 3;

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.frequency_Parameters.component_2.t =  2;

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.frequency_Parameters.component_2.u.indirect_encoding.maio = 59;

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.frequency_Parameters.component_2.u.indirect_encoding.ma_number = 1;

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.frequency_Parameters.component_2.u.indirect_encoding.m.component_3Present = 1;

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.frequency_Parameters.component_2.u.indirect_encoding.component_3.change_mark_1 = 2;

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.frequency_Parameters.component_2.u.indirect_encoding.component_3.m.change_mark_2Present = 1;
   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.frequency_Parameters.component_2.u.indirect_encoding.component_3.change_mark_2 = 1;

   pvalue->mbmsPtmChannelDescr.mbms_p_t_m_Channel_Description.dl_timeslot_allocation = 176;

   pvalue->m.mbmsSessionParametersListPresent = 1;
   pvalue->mbmsSessionParametersList.length = 0; /* length will be calculated */

   /* zero elements */

   pvalue->m.restrictionTimerPresent = 1;

   pvalue->restrictionTimer.restriction_timer = 5;

   pvalue->restrictionTimer.spare_bit = 0;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_DL_DCCH_PDU (&ctxt, &pdu);
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
