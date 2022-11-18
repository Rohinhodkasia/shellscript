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
   TS44018Msg_UL_DCCH_PDU pdu;
   TS44018Msg_NotificationResponse data;
   TS44018Msg_NotificationResponse* pvalue = &data;

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

   asn1Init_TS44018Msg_UL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_NotificationResponse;
   pdu.data.t = T_TS44018Msgs_UL_DCCH_Messages_obj_NotificationResponse;
   pdu.data.u.obj_NotificationResponse = pvalue;


   asn1Init_TS44018Msg_NotificationResponse (pvalue);

   pvalue->mobileStationClassmark.m.cm1Present = 1;

   pvalue->mobileStationClassmark.cm1.spare = 0;

   pvalue->mobileStationClassmark.cm1.revLevel = 2;

   pvalue->mobileStationClassmark.cm1.esInd = 1;

   pvalue->mobileStationClassmark.cm1.a5_1_alg = 1;

   pvalue->mobileStationClassmark.cm1.rfPowerCap = TS24008IE_RFPowerCapValues_class4;

   pvalue->mobileStationClassmark.m.octet4Present = 1;

   pvalue->mobileStationClassmark.octet4.spare = 0;

   pvalue->mobileStationClassmark.octet4.psCapability = 1;

   pvalue->mobileStationClassmark.octet4.ssScreeningInd = 2;

   pvalue->mobileStationClassmark.octet4.smCapability = 1;

   pvalue->mobileStationClassmark.octet4.vbsNotifRecept = 0;

   pvalue->mobileStationClassmark.octet4.vgcsNotifRecept = 0;

   pvalue->mobileStationClassmark.octet4.fcFreqCap = 0;

   pvalue->mobileStationClassmark.m.octet5Present = 1;

   pvalue->mobileStationClassmark.octet5.cm3 = 0;

   pvalue->mobileStationClassmark.octet5.spare = 0;

   pvalue->mobileStationClassmark.octet5.lcsvaCap = 0;

   pvalue->mobileStationClassmark.octet5.ucs2Treatment = 1;

   pvalue->mobileStationClassmark.octet5.soLSA = 1;

   pvalue->mobileStationClassmark.octet5.cmsp = 1;

   pvalue->mobileStationClassmark.octet5.a5_3_alg = 0;

   pvalue->mobileStationClassmark.octet5.a5_2_alg = 0;

   pvalue->mobileIdentity.t =  3;
   rtxStrncpy(pvalue->mobileIdentity.u.imeisv,
              sizeof(pvalue->mobileIdentity.u.imeisv),
			  "1a30*8#*850b5372", 17);

   pvalue->groupOrBroadcastCallReference.bc = 20265;

   pvalue->groupOrBroadcastCallReference.sf = 0;

   pvalue->groupOrBroadcastCallReference.af = 1;

   pvalue->groupOrBroadcastCallReference.callPriority = 4;

   pvalue->groupOrBroadcastCallReference.cipheringInformation = 4;

   pvalue->groupOrBroadcastCallReference.spare = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_UL_DCCH_PDU (&ctxt, &pdu);
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
