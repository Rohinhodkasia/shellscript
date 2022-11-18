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
   TS24008Msg_Modify data;
   TS24008Msg_Modify* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_Modify;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_Modify;
   pdu.data.u.obj_Modify = pvalue;

   asn1Init_TS24008Msg_Modify (pvalue);

   pvalue->bearerCap.octet3.radioChannelRequirement = 0;
   pvalue->bearerCap.octet3.nonstandardCoding = 0;
   pvalue->bearerCap.octet3.packetXferMode = 1;
   pvalue->bearerCap.octet3.infoXferCap = TS24008IE_InfoXferCap_speech;

   pvalue->m.lowLayerCompPresent = 1;
   {
      pvalue->lowLayerComp.numocts = 0;
   }
   pvalue->m.highLayerCompPresent = 1;
   pvalue->highLayerComp.length = 175;
   pvalue->highLayerComp.m.octet3Present = 1;
   pvalue->highLayerComp.octet3.codingStandard = TS24008IE_CodingStandard_q931;
   pvalue->highLayerComp.octet3.interpretation = 4;
   pvalue->highLayerComp.octet3.presentMethOfProtoProf = 0;
   pvalue->highLayerComp.m.highLayerCharacteristicsIDPresent = 1;
   pvalue->highLayerComp.highLayerCharacteristicsID = 80;
   pvalue->highLayerComp.m.extHighLayerCharacteristicsIDPresent = 1;
   pvalue->highLayerComp.extHighLayerCharacteristicsID = 63;
   pvalue->m.revCallSetupDirectionPresent = 1;
   pvalue->m.netInitServUpgrdIndPresent = 1;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

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
