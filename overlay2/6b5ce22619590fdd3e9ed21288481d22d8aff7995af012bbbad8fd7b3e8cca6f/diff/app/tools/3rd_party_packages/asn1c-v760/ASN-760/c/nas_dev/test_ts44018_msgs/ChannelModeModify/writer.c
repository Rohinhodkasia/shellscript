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
   TS44018Msg_DL_DCCH_PDU pdu;
   TS44018Msg_ChannelModeModify data;
   TS44018Msg_ChannelModeModify* pvalue = &data;

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

   asn1Init_TS44018Msg_DL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_ChannelModeModify;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_ChannelModeModify;
   pdu.data.u.obj_ChannelModeModify = pvalue;


   asn1Init_TS44018Msg_ChannelModeModify (pvalue);

   pvalue->channelDescription.channel_type_and_TDMA_offset = 17;

   pvalue->channelDescription.tn = 0;

   pvalue->channelDescription.tsc = 2;

   pvalue->channelDescription.component_4.t =  2;

   pvalue->channelDescription.component_4.u.choice_2.spare_bit = 0;

   pvalue->channelDescription.component_4.u.choice_2.arfcn = 685;

   pvalue->channelMode = 25;

   pvalue->m.vgcsTargetModeIndicationPresent = 1;
   pvalue->vgcsTargetModeIndication.length = 0; /* length will be calculated */

   pvalue->vgcsTargetModeIndication.target_mode = 0;

   pvalue->vgcsTargetModeIndication.group_cipher_key_num = 10;

   pvalue->vgcsTargetModeIndication.spare = 0;

   pvalue->m.multiRateConfigPresent = 1;

   pvalue->multiRateConfig.multirate_speech_version = 1;

   pvalue->multiRateConfig.nscb = 0;

   pvalue->multiRateConfig.icmi = 0;

   pvalue->multiRateConfig.start_mode = 2;

   /* two bits in amr_codec_modes are set so there should be 1 thr/hyst pair. */
   pvalue->multiRateConfig.amr_codec_modes = 0x03;
   pvalue->multiRateConfig.params.n = 1;
   pvalue->multiRateConfig.params.elem[0].threshold = 45;
   pvalue->multiRateConfig.params.elem[0].hysteresis = 7;

   pvalue->m.vgcsCipheringParamsPresent = 1;

   pvalue->vgcsCipheringParams.b22_count = 0;

   pvalue->vgcsCipheringParams.cell_global_count = 0;

   pvalue->vgcsCipheringParams.m.cell_identityPresent = 1;
   pvalue->vgcsCipheringParams.cell_identity = 163;

   pvalue->vgcsCipheringParams.m.location_area_identificationPresent = 1;
   pvalue->vgcsCipheringParams.location_area_identification[0] = 0x3c;
   pvalue->vgcsCipheringParams.location_area_identification[1] = 0x2a;
   pvalue->vgcsCipheringParams.location_area_identification[2] = 0x1f;
   pvalue->vgcsCipheringParams.location_area_identification[3] = 0xe7;
   pvalue->vgcsCipheringParams.location_area_identification[4] = 0x99;
 
   pvalue->vgcsCipheringParams.m.vstk_randPresent = 1;
   pvalue->vgcsCipheringParams.vstk_rand[0] = 0x46;
   pvalue->vgcsCipheringParams.vstk_rand[1] = 0x33;
   pvalue->vgcsCipheringParams.vstk_rand[2] = 0x49;
   pvalue->vgcsCipheringParams.vstk_rand[3] = 0x51;
   pvalue->vgcsCipheringParams.vstk_rand[4] = 0xE0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_DL_DCCH_PDU (&ctxt, &pdu);
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
