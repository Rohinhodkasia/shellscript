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
   TS44018Msg_NOTIFICATION_FACCH data;
   TS44018Msg_NOTIFICATION_FACCH* pvalue = &data;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_notification_facch;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_notification_facch;
   pdu.data.u.obj_notification_facch = pvalue;
   
   
   asn1Init_TS44018Msg_NOTIFICATION_FACCH (pvalue);

   pvalue->component_1.t =  1;

   pvalue->component_1.u.group_Call_information.group_Call_Reference[0] = 0xfe;
   pvalue->component_1.u.group_Call_information.group_Call_Reference[1] = 0xed;
   pvalue->component_1.u.group_Call_information.group_Call_Reference[2] = 0xbe;
   pvalue->component_1.u.group_Call_information.group_Call_Reference[3] = 0xef;
   pvalue->component_1.u.group_Call_information.group_Call_Reference[4] = 0x03;

   pvalue->component_1.u.group_Call_information.m.group_Channel_DescriptionPresent = 1;

   pvalue->component_1.u.group_Call_information.group_Channel_Description.channel_Description = 18746;

   pvalue->component_1.u.group_Call_information.group_Channel_Description.m.component_2Present = 1;
   pvalue->component_1.u.group_Call_information.group_Channel_Description.component_2.t =  1;
   pvalue->component_1.u.group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.length = 1;
   pvalue->component_1.u.group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.numbits = 8;
   pvalue->component_1.u.group_Call_information.group_Channel_Description.component_2.u.mobile_Allocation.mac.data[0] = 0xED;

   pvalue->m.component_2Present = 1;

   pvalue->component_2.m.component_1Present = 1;

   pvalue->component_2.component_1.cell_global_count = 2;

   pvalue->component_2.component_1.b22_count = 0;

   pvalue->component_2.m.vstk_randPresent = 1;
   pvalue->component_2.vstk_rand[0] = 0xc5;
   pvalue->component_2.vstk_rand[1] = 0xd1;
   pvalue->component_2.vstk_rand[2] = 0x98;
   pvalue->component_2.vstk_rand[3] = 0xb3;
   pvalue->component_2.vstk_rand[4] = 0xcf;

   pvalue->m.component_3Present = 1;

   pvalue->component_3.priority_Uplink_Access = TS44018Msg_LHType_lbit;

   pvalue->component_3.emergency_Ind = TS44018Msg_LHType_lbit;

   pvalue->component_3.m.amr_ConfigPresent = 1;
   pvalue->component_3.amr_Config = 3;

   pvalue->component_3.m.paging_CausePresent = 1;
   pvalue->component_3.paging_Cause = 2;

   pvalue->component_3.m.component_5Present = 1;

   pvalue->component_3.component_5.sms_Data_Confidentiality_Ind = 0;

   pvalue->component_3.component_5.sms_Guaranteed_Privacy_Ind = 0;

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
