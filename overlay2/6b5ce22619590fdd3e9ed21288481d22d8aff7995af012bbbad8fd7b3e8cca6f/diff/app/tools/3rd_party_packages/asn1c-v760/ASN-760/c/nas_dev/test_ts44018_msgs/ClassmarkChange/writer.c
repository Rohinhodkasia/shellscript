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
   TS44018Msg_ClassmarkChange data;
   TS44018Msg_ClassmarkChange* pvalue = &data;

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

   asn1Init_TS44018Msg_UL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_ClassmarkChange;
   pdu.data.t = T_TS44018Msgs_UL_DCCH_Messages_obj_ClassmarkChange;
   pdu.data.u.obj_ClassmarkChange = pvalue;


   asn1Init_TS44018Msg_ClassmarkChange (pvalue);

   pvalue->mobileStationClassmark.m.cm1Present = 1;

   pvalue->mobileStationClassmark.cm1.spare = 0;

   pvalue->mobileStationClassmark.cm1.revLevel = 2;

   pvalue->mobileStationClassmark.cm1.esInd = 0;

   pvalue->mobileStationClassmark.cm1.a5_1_alg = 1;

   pvalue->mobileStationClassmark.cm1.rfPowerCap = TS24008IE_RFPowerCapValues_class5;

   pvalue->mobileStationClassmark.m.octet4Present = 1;

   pvalue->mobileStationClassmark.octet4.spare = 0;

   pvalue->mobileStationClassmark.octet4.psCapability = 1;

   pvalue->mobileStationClassmark.octet4.ssScreeningInd = 1;

   pvalue->mobileStationClassmark.octet4.smCapability = 0;

   pvalue->mobileStationClassmark.octet4.vbsNotifRecept = 0;

   pvalue->mobileStationClassmark.octet4.vgcsNotifRecept = 0;

   pvalue->mobileStationClassmark.octet4.fcFreqCap = 1;

   pvalue->mobileStationClassmark.m.octet5Present = 1;

   pvalue->mobileStationClassmark.octet5.cm3 = 0;

   pvalue->mobileStationClassmark.octet5.spare = 0;

   pvalue->mobileStationClassmark.octet5.lcsvaCap = 1;

   pvalue->mobileStationClassmark.octet5.ucs2Treatment = 0;

   pvalue->mobileStationClassmark.octet5.soLSA = 1;

   pvalue->mobileStationClassmark.octet5.cmsp = 0;

   pvalue->mobileStationClassmark.octet5.a5_3_alg = 0;

   pvalue->mobileStationClassmark.octet5.a5_2_alg = 0;

   pvalue->m.addlMobileStationClassmarkInfoPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.length = 0; /* length will be calculated */

   pvalue->addlMobileStationClassmarkInfo.spare = 0;

   pvalue->addlMobileStationClassmarkInfo.multiband.supported = TS24008IE_MBSEnum_mbs0;

   pvalue->addlMobileStationClassmarkInfo.multiband.a5bits.a5_7 = 0;

   pvalue->addlMobileStationClassmarkInfo.multiband.a5bits.a5_6 = 0;

   pvalue->addlMobileStationClassmarkInfo.multiband.a5bits.a5_5 = 1;

   pvalue->addlMobileStationClassmarkInfo.multiband.a5bits.a5_4 = 0;

   pvalue->addlMobileStationClassmarkInfo.m.rSupportPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.rSupport = 4;

   pvalue->addlMobileStationClassmarkInfo.m.hscsdMultiSlotCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.hscsdMultiSlotCap = 15;

   pvalue->addlMobileStationClassmarkInfo.ucs2Treatment = 0;

   pvalue->addlMobileStationClassmarkInfo.extMeasurementCap = 0;

   pvalue->addlMobileStationClassmarkInfo.m.msMeasurementCapPresent = 1;

   pvalue->addlMobileStationClassmarkInfo.msMeasurementCap.smsValue = 11;

   pvalue->addlMobileStationClassmarkInfo.msMeasurementCap.smValue = 4;

   pvalue->addlMobileStationClassmarkInfo.m.msPositioningMethodCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.msPositioningMethodCap = 16;

   pvalue->addlMobileStationClassmarkInfo.m.ecsdMultiSlotCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.ecsdMultiSlotCap = 13;

   pvalue->addlMobileStationClassmarkInfo.m.an_8_PSKStructPresent = 1;

   pvalue->addlMobileStationClassmarkInfo.an_8_PSKStruct.modulationCap = 1;

   pvalue->addlMobileStationClassmarkInfo.an_8_PSKStruct.m.rfPowerCap1Present = 1;
   pvalue->addlMobileStationClassmarkInfo.an_8_PSKStruct.rfPowerCap1 = 2;

   pvalue->addlMobileStationClassmarkInfo.an_8_PSKStruct.m.rfPowerCap2Present = 1;
   pvalue->addlMobileStationClassmarkInfo.an_8_PSKStruct.rfPowerCap2 = 1;

   pvalue->addlMobileStationClassmarkInfo.m.gsm400StructPresent = 1;

   pvalue->addlMobileStationClassmarkInfo.gsm400Struct.bandsSupported = TS24008IE_GSM400Struct_bandsSupported_band1;

   pvalue->addlMobileStationClassmarkInfo.gsm400Struct.assocRadioCap = 8;

   pvalue->addlMobileStationClassmarkInfo.m.gsm850AssocRadioCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.gsm850AssocRadioCap = 9;

   pvalue->addlMobileStationClassmarkInfo.m.gsm1900AssocRadioCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.gsm1900AssocRadioCap = 6;

   pvalue->addlMobileStationClassmarkInfo.umtsFDDRadioAccessTechCap = 0;

   pvalue->addlMobileStationClassmarkInfo.umts384McpsTDDRadioAccessTechCap = 1;

   pvalue->addlMobileStationClassmarkInfo.cdma2000RadioAccessTechCap = 1;

   pvalue->addlMobileStationClassmarkInfo.m.dtmGPRSStructPresent = 1;

   pvalue->addlMobileStationClassmarkInfo.dtmGPRSStruct.dtmGPRSMultiSlotClass = 1;

   pvalue->addlMobileStationClassmarkInfo.dtmGPRSStruct.singleSlotDTM = 0;

   pvalue->addlMobileStationClassmarkInfo.dtmGPRSStruct.m.dtmEGPRSMultiSlotClassPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.dtmGPRSStruct.dtmEGPRSMultiSlotClass = 1;

   pvalue->addlMobileStationClassmarkInfo.m.singleBandSupportPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.singleBandSupport = 8;

   pvalue->addlMobileStationClassmarkInfo.m.gsm750AssocRadioCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.gsm750AssocRadioCap = 5;

   pvalue->addlMobileStationClassmarkInfo.umts1_28McpsTDDRadioAccessTechCap = 1;

   pvalue->addlMobileStationClassmarkInfo.geranFeaturePackage1 = 1;

   pvalue->addlMobileStationClassmarkInfo.m.extDtmGPRSStructPresent = 1;

   pvalue->addlMobileStationClassmarkInfo.extDtmGPRSStruct.extDtmGPRSMultiSlotClass = 1;

   pvalue->addlMobileStationClassmarkInfo.extDtmGPRSStruct.extDtmEGPRSMultiSlotClass = 2;

   pvalue->addlMobileStationClassmarkInfo.m.highMultislotCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.highMultislotCap = 0;

   pvalue->addlMobileStationClassmarkInfo.m.geranIuModeCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.geranIuModeCap.length = 0; /* length will be calculated */

   pvalue->addlMobileStationClassmarkInfo.geranIuModeCap.floIuCap = 1;

   pvalue->addlMobileStationClassmarkInfo.geranIuModeCap.spareBits.numbits = 4;
   pvalue->addlMobileStationClassmarkInfo.geranIuModeCap.spareBits.data[0] = 0x49;

   pvalue->addlMobileStationClassmarkInfo.geranFeaturePackage2 = 1;

   pvalue->addlMobileStationClassmarkInfo.gmskMultislotPowerProfile = 0;

   pvalue->addlMobileStationClassmarkInfo.multislotPowerProfile8PSK = 0;

   pvalue->addlMobileStationClassmarkInfo.m.tgsm400StructPresent = 1;

   pvalue->addlMobileStationClassmarkInfo.tgsm400Struct.bandsSupported = TS24008IE_GSM400Struct_bandsSupported_band1;

   pvalue->addlMobileStationClassmarkInfo.tgsm400Struct.assocRadioCap = 8;

   pvalue->addlMobileStationClassmarkInfo.zerobit = 0;

   pvalue->addlMobileStationClassmarkInfo.downlinkAdvancedRcvrPerf = 2;

   pvalue->addlMobileStationClassmarkInfo.dtmEnhancementsCap = 0;

   pvalue->addlMobileStationClassmarkInfo.m.dtmGPRSStruct2Present = 1;

   pvalue->addlMobileStationClassmarkInfo.dtmGPRSStruct2.dtmGPRSHighMultiSlotClass = 3;

   pvalue->addlMobileStationClassmarkInfo.dtmGPRSStruct2.offsetRequired = 1;

   pvalue->addlMobileStationClassmarkInfo.dtmGPRSStruct2.m.dtmEGPRSHighMultiSlotClassPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.dtmGPRSStruct2.dtmEGPRSHighMultiSlotClass = 4;

   pvalue->addlMobileStationClassmarkInfo.repeatedACCHCap = 0;

   pvalue->addlMobileStationClassmarkInfo.m.gsm710AssocRadioCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.gsm710AssocRadioCap = 6;

   pvalue->addlMobileStationClassmarkInfo.m.tgsm810AssocRadioCapPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.tgsm810AssocRadioCap = 8;

   pvalue->addlMobileStationClassmarkInfo.cipheringModeSettingCap = 1;

   pvalue->addlMobileStationClassmarkInfo.additionalPositioningCap = 0;

   pvalue->addlMobileStationClassmarkInfo.e_UTRA_FDD_support = 0;

   pvalue->addlMobileStationClassmarkInfo.e_UTRA_TDD_support = 0;

   pvalue->addlMobileStationClassmarkInfo.e_UTRA_MeasAndReportSupport = 1;

   pvalue->addlMobileStationClassmarkInfo.priorityBasedReselectionSupport = 0;

   pvalue->addlMobileStationClassmarkInfo.m._v9ExtPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.uTRA_CSG_Cells_Reporting = 1;

   pvalue->addlMobileStationClassmarkInfo.m._v9ExtPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.vAMOS_Level = 1;

   pvalue->addlMobileStationClassmarkInfo.m._v10ExtPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.tighterCapability = 2;

   pvalue->addlMobileStationClassmarkInfo.m._v10ExtPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.selCiphOf_DL_SACCH = 0;

   pvalue->addlMobileStationClassmarkInfo.m.spareBitsPresent = 1;
   pvalue->addlMobileStationClassmarkInfo.spareBits.numbits = 10;
   {
      OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,2);
      bitData[0] = 0x50;
      bitData[1] = 0x48;
      pvalue->addlMobileStationClassmarkInfo.spareBits.data = (const OSOCTET*)bitData;
   }

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
