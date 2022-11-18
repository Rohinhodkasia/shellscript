#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType6*
    asn1Test_TS44018Msg_SystemInformationType6 (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType6* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType6);
   asn1Init_TS44018Msg_SystemInformationType6 (pvalue);

   pvalue->cellIdentity = 62850;

   rtxStrncpy (pvalue->locationAreaIdentification.mcc_mnc.mcc, 4, "310", 3);
   rtxStrncpy (pvalue->locationAreaIdentification.mcc_mnc.mnc, 4, "94", 3);

   pvalue->locationAreaIdentification.lac = 28189;

   pvalue->cellOptions.dtx_high = 0;

   pvalue->cellOptions.pwrc = 0;

   pvalue->cellOptions.dtx_low = 0;

   pvalue->cellOptions.radio_link_timeout = 11;

   pvalue->nccPermitted = 136;
   return (pvalue);
}


TS44018IE_SI6_Rest_Octets* asn1Test_TS44018IE_SI6_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI6_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI6_Rest_Octets);
   asn1Init_TS44018IE_SI6_Rest_Octets (pvalue);

   pvalue->m.pch_and_NCH_infoPresent = 1;

   pvalue->pch_and_NCH_info.paging_channel_restructuring.t =  1;

   pvalue->pch_and_NCH_info.nln_sacch = 1;

   pvalue->pch_and_NCH_info.m.call_priorityPresent = 1;
   pvalue->pch_and_NCH_info.call_priority = 5;

   pvalue->pch_and_NCH_info.nln_status_SACCH = 0;

   pvalue->m.vbs_VGCS_optionsPresent = 1;
   pvalue->vbs_VGCS_options = 0;

   pvalue->m.component_3Present = 1;

   pvalue->component_3.rac = 203;

   pvalue->component_3.max_LAPDm = 0;

   pvalue->band_indicator = TS44018IE_LHType_lbit;

   pvalue->m.gprs_ms_txpwr_max_cchPresent = 1;
   pvalue->gprs_ms_txpwr_max_cch = 11;

   pvalue->m.component_6Present = 1;

   pvalue->component_6.dedicated_mode_mbms_notification_support = 0;

   pvalue->component_6.mnci_support = 0;

   pvalue->m.component_7Present = 1;

   pvalue->component_7.m.amr_ConfigPresent = 1;
   pvalue->component_7.amr_Config = 1;

   pvalue->m.random_bit_streamPresent = 1;
   pvalue->random_bit_stream.numbits = 15;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,2);
      bitData[0] = 0x3a;
      bitData[1] = 0x41;
      pvalue->random_bit_stream.data = (const OSOCTET*)bitData;
   }
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType6;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType6;
   pdu.data.u.obj_SystemInformationType6 =
      asn1Test_TS44018Msg_SystemInformationType6(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType6;
   pdu.restOctets.u.obj_SystemInformationType6 =
      asn1Test_TS44018IE_SI6_Rest_Octets(pctxt);


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
