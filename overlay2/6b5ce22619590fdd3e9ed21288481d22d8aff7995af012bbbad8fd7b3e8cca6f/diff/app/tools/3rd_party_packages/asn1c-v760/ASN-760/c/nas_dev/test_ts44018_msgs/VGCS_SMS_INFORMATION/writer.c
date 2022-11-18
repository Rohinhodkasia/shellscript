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
   TS44018Msg_VGCS_SMS_INFORMATION data;
   TS44018Msg_VGCS_SMS_INFORMATION* pvalue = &data;

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

   pvalue->t =  1;

   pvalue->u.non_Segmented_SMS_Description.length = 146;

   pvalue->u.non_Segmented_SMS_Description.sms_Reference_Number = 10;

   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.numbits = 146;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[0] = 0x42;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[1] = 0x3e;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[2] = 0x46;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[3] = 0x42;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[4] = 0x40;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[5] = 0x50;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[6] = 0x39;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[7] = 0x31;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[8] = 0x47;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[9] = 0x60;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[10] = 0x30;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[11] = 0x48;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[12] = 0x45;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[13] = 0x47;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[14] = 0x6d;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[15] = 0x3f;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[16] = 0x43;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[17] = 0x66;
   pvalue->u.non_Segmented_SMS_Description.sms_Final_Content.data[18] = 0x40;

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
