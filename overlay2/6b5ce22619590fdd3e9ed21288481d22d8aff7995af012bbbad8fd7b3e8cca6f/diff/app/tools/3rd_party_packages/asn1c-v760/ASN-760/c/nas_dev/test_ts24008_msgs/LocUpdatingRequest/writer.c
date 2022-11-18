#include "TS24008Msgs.h"
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
   TS24008Msg_PDU pdu;
   TS24008Msg_LocUpdatingRequest data;
   TS24008Msg_LocUpdatingRequest* pvalue = &data;
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

   asn1Init_TS24008Msg_PDU (&pdu);
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_mobMgmt;
   pdu.msgType = ASN1V_mt_LocUpdatingRequest;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_LocUpdatingRequest;
   pdu.data.u.obj_LocUpdatingRequest = pvalue;

   asn1Init_TS24008Msg_LocUpdatingRequest (pvalue);
   pvalue->locUpdatingType.for_ = 1;
   pvalue->locUpdatingType.spare = 0;
   pvalue->locUpdatingType.lut = TS24008IE_LocationUpdatingType_lut_normLocUpdate;
   pvalue->ciphKeySeqNum.spare = 0;
   pvalue->ciphKeySeqNum.value = 3;
   rtxStrncpy(pvalue->locAreaIdent.mcc_mnc.mcc,
              sizeof(pvalue->locAreaIdent.mcc_mnc.mcc), "a1c", 4);
   rtxStrncpy(pvalue->locAreaIdent.mcc_mnc.mnc,
              sizeof(pvalue->locAreaIdent.mcc_mnc.mnc), "66c", 4);
   pvalue->locAreaIdent.lac = 29663;
   pvalue->mobileStationClassmark1.spare = 0;
   pvalue->mobileStationClassmark1.revLevel = 1;
   pvalue->mobileStationClassmark1.esInd = 1;
   pvalue->mobileStationClassmark1.a5_1_alg = 1;
   pvalue->mobileStationClassmark1.rfPowerCap = TS24008IE_RFPowerCapValues_class1;
   pvalue->mobileIdentity.t =  T_TS24008IE_MobileIdentity_imei;
   rtxStrncpy(pvalue->mobileIdentity.u.imei,
              sizeof(pvalue->mobileIdentity.u.imei), "42145a62841c*c2", 16);
   pvalue->m.mobStatCmark4UMTSPresent = 1;
   pvalue->mobStatCmark4UMTS.m.cm1Present = 1;
   pvalue->mobStatCmark4UMTS.cm1.spare = 0;
   pvalue->mobStatCmark4UMTS.cm1.revLevel = 2;
   pvalue->mobStatCmark4UMTS.cm1.esInd = 0;
   pvalue->mobStatCmark4UMTS.cm1.a5_1_alg = 1;
   pvalue->mobStatCmark4UMTS.cm1.rfPowerCap = 0;
   pvalue->mobStatCmark4UMTS.m.octet4Present = 1;
   pvalue->mobStatCmark4UMTS.octet4.spare = 0;
   pvalue->mobStatCmark4UMTS.octet4.psCapability = 1;
   pvalue->mobStatCmark4UMTS.octet4.ssScreeningInd = 1;
   pvalue->mobStatCmark4UMTS.octet4.smCapability = 0;
   pvalue->mobStatCmark4UMTS.octet4.vbsNotifRecept = 0;
   pvalue->mobStatCmark4UMTS.octet4.vgcsNotifRecept = 1;
   pvalue->mobStatCmark4UMTS.octet4.fcFreqCap = 1;
   pvalue->mobStatCmark4UMTS.m.octet5Present = 1;
   pvalue->mobStatCmark4UMTS.octet5.cm3 = 0;
   pvalue->mobStatCmark4UMTS.octet5.spare = 0;
   pvalue->mobStatCmark4UMTS.octet5.lcsvaCap = 1;
   pvalue->mobStatCmark4UMTS.octet5.ucs2Treatment = 0;
   pvalue->mobStatCmark4UMTS.octet5.soLSA = 1;
   pvalue->mobStatCmark4UMTS.octet5.cmsp = 1;
   pvalue->mobStatCmark4UMTS.octet5.a5_3_alg = 1;
   pvalue->mobStatCmark4UMTS.octet5.a5_2_alg = 0;

   /* Add release 9 element */
   pvalue->m._v9ExtPresent = 1;
   pvalue->m.addnUpdateParamsPresent = 1;
   pvalue->addnUpdateParams.drvcc = TRUE;
   pvalue->addnUpdateParams.cmso = FALSE;
   pvalue->addnUpdateParams.cmst = TRUE;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008Msg_PDU (&ctxt, &pdu);
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
