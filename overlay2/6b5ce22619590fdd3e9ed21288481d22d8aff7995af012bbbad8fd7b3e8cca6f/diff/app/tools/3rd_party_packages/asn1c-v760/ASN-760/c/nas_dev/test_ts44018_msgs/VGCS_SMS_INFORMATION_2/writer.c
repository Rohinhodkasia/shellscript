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
   TS44018Msg_VGCS_SMS_INFORMATION vsiData;
   TS44018Msg_VGCS_SMS_INFORMATION* pvalue = &vsiData;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_vgcs_sms_information;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_vgcs_sms_information;
   pdu.data.u.obj_vgcs_sms_information = pvalue;


   asn1Init_TS44018Msg_VGCS_SMS_INFORMATION (pvalue);

   pvalue->t =  2;

   pvalue->u.segmented_SMS_Description.sms_Reference_Number = 10;
   pvalue->u.segmented_SMS_Description.segment_Number  = 2;
   pvalue->u.segmented_SMS_Description.component_3.t = 1;
   pvalue->u.segmented_SMS_Description.component_3.u.sms_Content.numbits = 150;
   {
      OSOCTET* data = rtxMemAlloc(&ctxt, 19);
      pvalue->u.segmented_SMS_Description.component_3.u.sms_Content.data = data;   
      data[0] = 0x42;
      data[1] = 0x3e;
      data[2] = 0x46;
      data[3] = 0x42;
      data[4] = 0x40;
      data[5] = 0x50;
      data[6] = 0x39;
      data[7] = 0x31;
      data[8] = 0x47;
      data[9] = 0x60;
      data[10] = 0x30;
      data[11] = 0x48;
      data[12] = 0x45;
      data[13] = 0x47;
      data[14] = 0x6d;
      data[15] = 0x3f;
      data[16] = 0x43;
      data[17] = 0x66;
      data[18] = 0x40;
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

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
