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
   TS44018Msg_RR_Short_PD_PDU pdu;
   TS44018Msg_VGCS_ADDITIONAL_INFO data;
   TS44018Msg_VGCS_ADDITIONAL_INFO* pvalue = &data;

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

   asn1Init_TS44018Msg_RR_Short_PD_PDU (&pdu);
   pdu.rr_short_PD = 0;
   pdu.msgType = ASN1V_ts44018Msg_mt_vgcs_additional_info;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_vgcs_additional_info;
   pdu.data.u.obj_vgcs_additional_info = pvalue;
   
   asn1Init_TS44018Msg_VGCS_ADDITIONAL_INFO (pvalue);

   pvalue->talker_identity_length = 184 / 8;

   pvalue->filler_bits = 1;

   pvalue->talker_identity.numbits = 184;
   pvalue->talker_identity.data[0] = 0x42;
   pvalue->talker_identity.data[1] = 0x72;
   pvalue->talker_identity.data[2] = 0x5a;
   pvalue->talker_identity.data[3] = 0x39;
   pvalue->talker_identity.data[4] = 0x68;
   pvalue->talker_identity.data[5] = 0x4e;
   pvalue->talker_identity.data[6] = 0x38;
   pvalue->talker_identity.data[7] = 0x43;
   pvalue->talker_identity.data[8] = 0x55;
   pvalue->talker_identity.data[9] = 0x6e;
   pvalue->talker_identity.data[10] = 0x35;
   pvalue->talker_identity.data[11] = 0x6e;
   pvalue->talker_identity.data[12] = 0x45;
   pvalue->talker_identity.data[13] = 0x43;
   pvalue->talker_identity.data[14] = 0x38;
   pvalue->talker_identity.data[15] = 0x58;
   pvalue->talker_identity.data[16] = 0x40;
   pvalue->talker_identity.data[17] = 0x3c;
   pvalue->talker_identity.data[18] = 0x68;
   pvalue->talker_identity.data[19] = 0x3b;
   pvalue->talker_identity.data[20] = 0x59;
   pvalue->talker_identity.data[21] = 0x72;
   pvalue->talker_identity.data[22] = 0x3e;

   //These bits are extraneous and should not appear in the encoding
   pvalue->talker_identity.data[23] = 0xEE;
   pvalue->talker_identity.data[24] = 0xEE;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_RR_Short_PD_PDU (&ctxt, &pdu);
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
