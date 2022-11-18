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
   TS24008Msg_CMServiceRequest data;
   TS24008Msg_CMServiceRequest* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_CMServiceRequest;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_CMServiceRequest;
   pdu.data.u.obj_CMServiceRequest = pvalue;

   asn1Init_TS24008Msg_CMServiceRequest (pvalue);
   pvalue->cmServiceType = TS24008IE_CMServiceType_mobOrigCallEstab;
   pvalue->ciphKeySeqNum.spare = 0;
   pvalue->ciphKeySeqNum.value = 1;
   pvalue->mobileStationClassmark2.m.cm1Present = 1;
   pvalue->mobileStationClassmark2.cm1.spare = 0;
   pvalue->mobileStationClassmark2.cm1.revLevel = 2;
   pvalue->mobileStationClassmark2.cm1.esInd = 1;
   pvalue->mobileStationClassmark2.cm1.a5_1_alg = 1;
   pvalue->mobileStationClassmark2.cm1.rfPowerCap = TS24008IE_RFPowerCapValues_class5;
   pvalue->mobileStationClassmark2.m.octet4Present = 1;
   pvalue->mobileStationClassmark2.octet4.spare = 0;
   pvalue->mobileStationClassmark2.octet4.psCapability = 0;
   pvalue->mobileStationClassmark2.octet4.ssScreeningInd = 1;
   pvalue->mobileStationClassmark2.octet4.smCapability = 1;
   pvalue->mobileStationClassmark2.octet4.vbsNotifRecept = 1;
   pvalue->mobileStationClassmark2.octet4.vgcsNotifRecept = 1;
   pvalue->mobileStationClassmark2.octet4.fcFreqCap = 1;
   pvalue->mobileStationClassmark2.m.octet5Present = 1;
   pvalue->mobileStationClassmark2.octet5.cm3 = 0;
   pvalue->mobileStationClassmark2.octet5.spare = 0;
   pvalue->mobileStationClassmark2.octet5.lcsvaCap = 1;
   pvalue->mobileStationClassmark2.octet5.ucs2Treatment = 1;
   pvalue->mobileStationClassmark2.octet5.soLSA = 0;
   pvalue->mobileStationClassmark2.octet5.cmsp = 0;
   pvalue->mobileStationClassmark2.octet5.a5_3_alg = 0;
   pvalue->mobileStationClassmark2.octet5.a5_2_alg = 1;
   pvalue->mobileIdentity.t =  T_TS24008IE_MobileIdentity_imsi;
   rtxStrncpy(pvalue->mobileIdentity.u.imsi,
              sizeof(pvalue->mobileIdentity.u.imsi), "78735684699984", 15);
   pvalue->m.priorityLevelPresent = 1;
   pvalue->priorityLevel.spare = 0;
   pvalue->priorityLevel.callPriority = 6;

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
