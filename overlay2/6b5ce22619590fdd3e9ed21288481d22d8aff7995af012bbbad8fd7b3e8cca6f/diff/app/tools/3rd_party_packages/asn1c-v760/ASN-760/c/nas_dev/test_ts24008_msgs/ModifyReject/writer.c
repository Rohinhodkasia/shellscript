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
   TS24008Msg_ModifyReject data;
   TS24008Msg_ModifyReject* pvalue = &data;
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
   pdu.protoDiscr = TS24007L3_ProtoDiscr_callCtrl;
   pdu.msgType = ASN1V_mt_ModifyReject;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_ModifyReject;
   pdu.data.u.obj_ModifyReject = pvalue;

   asn1Init_TS24008Msg_ModifyReject (pvalue);


   pvalue->bearerCap.octet3.radioChannelRequirement = 1;
   pvalue->bearerCap.octet3.nonstandardCoding = 0;
   pvalue->bearerCap.octet3.packetXferMode = 0;
   pvalue->bearerCap.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;

   pvalue->cause.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->cause.octet3.spare = 0;
   pvalue->cause.octet3.location = TS24008IE_Location_user;
   pvalue->cause.m.recommendationPresent = 1;
   pvalue->cause.recommendation = 48;
   pvalue->cause.causeValue = 52;

   pvalue->m.lowLayerCompPresent = 1;
   {
      pvalue->lowLayerComp.numocts = 0;
   }

   pvalue->m.highLayerCompPresent = 1;
   pvalue->highLayerComp.length = 81;

   pvalue->highLayerComp.m.octet3Present = 1;
   pvalue->highLayerComp.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->highLayerComp.octet3.interpretation = 3;
   pvalue->highLayerComp.octet3.presentMethOfProtoProf = 2;

   pvalue->highLayerComp.m.highLayerCharacteristicsIDPresent = 1;
   pvalue->highLayerComp.highLayerCharacteristicsID = 4;

   pvalue->highLayerComp.m.extHighLayerCharacteristicsIDPresent = 1;
   pvalue->highLayerComp.extHighLayerCharacteristicsID = 87;

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
