#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType3*
    asn1Test_TS44018Msg_SystemInformationType3 (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType3* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType3);
   asn1Init_TS44018Msg_SystemInformationType3 (pvalue);

   pvalue->cellIdentity = 31932;

   rtxStrncpy (pvalue->locationAreaIdentification.mcc_mnc.mcc, 4, "310", 3);
   rtxStrncpy (pvalue->locationAreaIdentification.mcc_mnc.mnc, 4, "03", 3);

   pvalue->locationAreaIdentification.lac = 10741;

   pvalue->controlChannelDescription.mscr = 0;

   pvalue->controlChannelDescription.att = 0;

   pvalue->controlChannelDescription.bs_ag_blks_res = 2;

   pvalue->controlChannelDescription.ccch_conf = 2;

   pvalue->controlChannelDescription.si22ind = 0;

   pvalue->controlChannelDescription.cbq3 = 0;

   pvalue->controlChannelDescription.spare_bit = 0;

   pvalue->controlChannelDescription.bs_pa_mfrms = 2;

   pvalue->controlChannelDescription.t3212 = 85;

   pvalue->cellOptions.dn_ind = 0;

   pvalue->cellOptions.pwrc = 0;

   pvalue->cellOptions.dtx = 1;

   pvalue->cellOptions.radio_link_timeout = 12;

   pvalue->cellSelectionParameters.cell_reselect_hysteresis = 3;

   pvalue->cellSelectionParameters.ms_txpwr_max_cch = 4;

   pvalue->cellSelectionParameters.acs = 0;

   pvalue->cellSelectionParameters.neci = 0;

   pvalue->cellSelectionParameters.rxlev_access_min = 23;

   pvalue->rachControlParameters.max_retrans = 0;

   pvalue->rachControlParameters.tx_integer = 11;

   pvalue->rachControlParameters.cell_bar_access = 0;

   pvalue->rachControlParameters.re = 0;

   pvalue->rachControlParameters.acc = 19944;

   return (pvalue);
}

TS44018IE_SI3_Rest_Octets* asn1Test_TS44018IE_SI3_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI3_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI3_Rest_Octets);
   asn1Init_TS44018IE_SI3_Rest_Octets (pvalue);

   pvalue->optional_Selection_Parameters.m.selection_ParametersPresent = 1;

   pvalue->optional_Selection_Parameters.selection_Parameters.cbq = 0;

   pvalue->optional_Selection_Parameters.selection_Parameters.cell_reselect_offset = 20;

   pvalue->optional_Selection_Parameters.selection_Parameters.temporary_offset = 3;

   pvalue->optional_Selection_Parameters.selection_Parameters.penalty_time = 5;

   pvalue->optional_Power_Offset.m.power_OffsetPresent = 1;
   pvalue->optional_Power_Offset.power_Offset = 2;

   pvalue->system_Information_2ter_Indicator = TS44018IE_LHType_lbit;

   pvalue->early_Classmark_Sending_Control = TS44018IE_LHType_lbit;

   pvalue->scheduling_if_and_where.m.wherePresent = 1;
   pvalue->scheduling_if_and_where.where = 5;

   pvalue->m.gprs_IndicatorPresent = 1;

   pvalue->gprs_Indicator.ra_colour = 0;

   pvalue->gprs_Indicator.si13_position = 0;

   pvalue->a3G_Early_Classmark_Sending_Restriction = TS44018IE_LHType_lbit;

   pvalue->m.si2quater_IndicatorPresent = 1;

   pvalue->si2quater_Indicator.si2quater_POSITION = 0;

   /* GPRS is supported so iu-Indicator must be absent */
   pvalue->m.iu_IndicatorPresent = 0;

   pvalue->iu_Indicator.si13alt_POSITION = 0;

   /* WHERE is present so System Information 21 Indicator must be absent */
   pvalue->m.system_Information_21_IndicatorPresent = 0;

   return (pvalue);
}

TS44018IE_SI3_Rest_Octets_Data* asn1Test_TS44018IE_SI3_Rest_Octets_Data (OSCTXT* pctxt)
{
   OSCTXT ctxt2;
   int ret;
   TS44018IE_SI3_Rest_Octets* pSI3;
   TS44018IE_SI3_Rest_Octets_Data* pvalue;
   OSOCTET*	msgbuf;

   ret = rtInitContext (&ctxt2);
   if (0 != ret) {
      printf ("Init ctxt2 failed; status = %d\n", ret);      
      return 0;
   }

   pSI3 = asn1Test_TS44018IE_SI3_Rest_Octets (&ctxt2);

   /* encode the SI 3 Rest Octet data in pSI3.  
      Allocate a buffer for the data using pctxt and not the temp context ctxt2.
      The encoded result becomes the octet data that is populated into
      TS44018IE_SI3_Rest_Octets_Data.
   */
   msgbuf = rtxMemAlloc(pctxt, MAXMSGLEN);
   rtxCtxtSetBufPtr (&ctxt2, msgbuf, MAXMSGLEN);
   ret = NASEnc_TS44018IE_SI3_Rest_Octets(&ctxt2, pSI3);

   if ( ret < 0 ) {
      printf ("encode SI 3 Rest Octets failed; status = %d\n", ret);
      rtxErrPrint (&ctxt2);
      return 0;
   }

   pvalue = rtxMemAllocType (pctxt, TS44018IE_SI3_Rest_Octets_Data);
   asn1Init_TS44018IE_SI3_Rest_Octets_Data (pvalue);
   pvalue->data.data = rtxCtxtGetMsgPtr(&ctxt2);
   pvalue->data.numocts = rtxCtxtGetMsgLen(&ctxt2);

   rtxFreeContext (&ctxt2);

   return pvalue;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType3;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType3;
   pdu.data.u.obj_SystemInformationType3 =
      asn1Test_TS44018Msg_SystemInformationType3(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType3;
   pdu.restOctets.u.obj_SystemInformationType3 =
      asn1Test_TS44018IE_SI3_Rest_Octets_Data(pctxt);

   if ( pdu.restOctets.u.obj_SystemInformationType3 == 0 ) {
      /* should already have reported error */
      return -1;
   }

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
