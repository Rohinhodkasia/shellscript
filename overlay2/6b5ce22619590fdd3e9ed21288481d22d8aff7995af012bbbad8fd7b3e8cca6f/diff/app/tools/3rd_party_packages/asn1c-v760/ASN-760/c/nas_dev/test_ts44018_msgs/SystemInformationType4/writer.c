#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType4*
    asn1Test_TS44018Msg_SystemInformationType4 (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType4* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType4);
   asn1Init_TS44018Msg_SystemInformationType4 (pvalue);

   rtxStrncpy (pvalue->locationAreaIdentification.mcc_mnc.mcc, 4, "295", 3);
   rtxStrncpy (pvalue->locationAreaIdentification.mcc_mnc.mnc, 4, "01", 3);

   pvalue->locationAreaIdentification.lac = 27959;

   pvalue->cellSelectionParameters.cell_reselect_hysteresis = 5;

   pvalue->cellSelectionParameters.ms_txpwr_max_cch = 1;

   pvalue->cellSelectionParameters.acs = 0;

   pvalue->cellSelectionParameters.neci = 0;

   pvalue->cellSelectionParameters.rxlev_access_min = 27;

   pvalue->rachControlParameters.max_retrans = 2;

   pvalue->rachControlParameters.tx_integer = 6;

   pvalue->rachControlParameters.cell_bar_access = 0;

   pvalue->rachControlParameters.re = 0;

   pvalue->rachControlParameters.acc = 35093;

   pvalue->m.cbchChannelDescriptionPresent = 1;

   pvalue->cbchChannelDescription.channel_type_and_TDMA_offset = 17;

   pvalue->cbchChannelDescription.tn = 6;

   pvalue->cbchChannelDescription.tsc = 2;

   pvalue->cbchChannelDescription.component_4.t =  2;

   pvalue->cbchChannelDescription.component_4.u.choice_2.spare_bit = 1;

   pvalue->cbchChannelDescription.component_4.u.choice_2.arfcn = 824;

   pvalue->m.cbchMobileAllocationPresent = 1;

   pvalue->cbchMobileAllocation.length = 5;

   pvalue->cbchMobileAllocation.mac.numbits = 40;
   pvalue->cbchMobileAllocation.mac.data[0] = 0x4c;
   pvalue->cbchMobileAllocation.mac.data[1] = 0x37;
   pvalue->cbchMobileAllocation.mac.data[2] = 0x65;
   pvalue->cbchMobileAllocation.mac.data[3] = 0x4f;
   pvalue->cbchMobileAllocation.mac.data[4] = 0x34;
   return (pvalue);
}


TS44018IE_SI4_Rest_Octets* asn1Test_TS44018IE_SI4_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI4_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI4_Rest_Octets);
   asn1Init_TS44018IE_SI4_Rest_Octets (pvalue);

   pvalue->m.si4_Rest_Octets_OPresent = 1;

   pvalue->si4_Rest_Octets_O.m.optional_Selection_ParametersPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.m.selection_ParametersPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.cbq = 0;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.cell_reselect_offset = 5;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.temporary_offset = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.penalty_time = 9;

   pvalue->si4_Rest_Octets_O.m.optional_Power_OffsetPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Power_Offset.m.power_OffsetPresent = 1;
   pvalue->si4_Rest_Octets_O.optional_Power_Offset.power_Offset = 2;

   pvalue->si4_Rest_Octets_O.m.gprs_IndicatorPresent = 1;

   pvalue->si4_Rest_Octets_O.gprs_Indicator.ra_colour = 2;

   pvalue->si4_Rest_Octets_O.gprs_Indicator.si13_position = 0;

   pvalue->m.component_2Present = 1;
   pvalue->component_2.t =  2;

   pvalue->component_2.u.si4_Rest_Octets_S.m.si4_LSA_ParametersPresent = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.prio_thr = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.lsa_offset = 4;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.m.component_3Present = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.component_3.mcc = 1211;

   pvalue->component_2.u.si4_Rest_Octets_S.si4_LSA_Parameters.component_3.mnc = 1563;

   pvalue->component_2.u.si4_Rest_Octets_S.m.cell_IdentityPresent = 1;
   pvalue->component_2.u.si4_Rest_Octets_S.cell_Identity = 24057;

   pvalue->component_2.u.si4_Rest_Octets_S.m.lsa_ID_informationPresent = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.first.t =  2;
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.first.u.shortLSA_ID = 828;

   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.n = 2;
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem = rtxMemAllocArrayZ (pctxt, 2, TS44018IE_LSA_identity);
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem[0].t =  1;
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem[0].u.lsa_id = 1732544;

   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem[1].t =  2;
   pvalue->component_2.u.si4_Rest_Octets_S.lsa_ID_information.additional.elem[1].u.shortLSA_ID = 728;

   pvalue->component_2.u.si4_Rest_Octets_S.m.component_4Present = 1;

   pvalue->component_2.u.si4_Rest_Octets_S.component_4.cbq3 = 2;

   pvalue->component_2.u.si4_Rest_Octets_S.component_4.m.si13alt_PositionPresent = 1;
   pvalue->component_2.u.si4_Rest_Octets_S.component_4.si13alt_Position = 0;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType4;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType4;
   pdu.data.u.obj_SystemInformationType4 =
      asn1Test_TS44018Msg_SystemInformationType4(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType4;
   pdu.restOctets.u.obj_SystemInformationType4 =
      asn1Test_TS44018IE_SI4_Rest_Octets(pctxt);


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
