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
   TS44018Msg_TalkerIndication data;
   TS44018Msg_TalkerIndication* pvalue = &data;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_TalkerIndication;
   pdu.data.t = T_TS44018Msgs_UL_DCCH_Messages_obj_TalkerIndication;
   pdu.data.u.obj_TalkerIndication = pvalue;


   asn1Init_TS44018Msg_TalkerIndication (pvalue);

   pvalue->mobileStationClassmark.m.cm1Present = 1;

   pvalue->mobileStationClassmark.cm1.spare = 0;

   pvalue->mobileStationClassmark.cm1.revLevel = 2;

   pvalue->mobileStationClassmark.cm1.esInd = 1;

   pvalue->mobileStationClassmark.cm1.a5_1_alg = 0;

   pvalue->mobileStationClassmark.cm1.rfPowerCap = TS24008IE_RFPowerCapValues_class4;

   pvalue->mobileStationClassmark.m.octet4Present = 1;

   pvalue->mobileStationClassmark.octet4.spare = 0;

   pvalue->mobileStationClassmark.octet4.psCapability = 0;

   pvalue->mobileStationClassmark.octet4.ssScreeningInd = 1;

   pvalue->mobileStationClassmark.octet4.smCapability = 0;

   pvalue->mobileStationClassmark.octet4.vbsNotifRecept = 1;

   pvalue->mobileStationClassmark.octet4.vgcsNotifRecept = 1;

   pvalue->mobileStationClassmark.octet4.fcFreqCap = 1;

   pvalue->mobileStationClassmark.m.octet5Present = 1;

   pvalue->mobileStationClassmark.octet5.cm3 = 1;

   pvalue->mobileStationClassmark.octet5.spare = 0;

   pvalue->mobileStationClassmark.octet5.lcsvaCap = 0;

   pvalue->mobileStationClassmark.octet5.ucs2Treatment = 0;

   pvalue->mobileStationClassmark.octet5.soLSA = 1;

   pvalue->mobileStationClassmark.octet5.cmsp = 1;

   pvalue->mobileStationClassmark.octet5.a5_3_alg = 0;

   pvalue->mobileStationClassmark.octet5.a5_2_alg = 1;

   pvalue->mobileIdentity.t =  5;

   pvalue->mobileIdentity.u.tmgi.mbmsSessIdInd = 1;

   pvalue->mobileIdentity.u.tmgi.mccMncInd = 1;

   {
      static const OSOCTET testdata[] = { 
      0xbd, 0xf4, 0x66 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->mobileIdentity.u.tmgi.mbmsServiceID, 3, testdata, 3);
   }

   rtxStrncpy (pvalue->mobileIdentity.u.tmgi.mcc_mnc.mcc, 4, "295", 3);
   rtxStrncpy (pvalue->mobileIdentity.u.tmgi.mcc_mnc.mnc, 4, "02", 3);

   pvalue->mobileIdentity.u.tmgi.mbmsSessionID = 5;

   pvalue->m.cipheringKeySequenceNumberPresent = 1;

   pvalue->cipheringKeySequenceNumber.spare = 0;

   pvalue->cipheringKeySequenceNumber.value = 2;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

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
