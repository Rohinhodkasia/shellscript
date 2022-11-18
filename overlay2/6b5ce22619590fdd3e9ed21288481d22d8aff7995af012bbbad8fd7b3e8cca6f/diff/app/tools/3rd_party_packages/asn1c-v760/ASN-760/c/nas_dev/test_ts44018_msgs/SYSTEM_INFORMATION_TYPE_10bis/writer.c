#include "TS44018Msgs.h"
#include "TS44018IES.h"
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
   TS44018Msg_SYSTEM_INFORMATION_TYPE_10bis sitData;
   TS44018Msg_SYSTEM_INFORMATION_TYPE_10bis* pvalue = &sitData;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_system_information_type_10bis;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_system_information_type_10bis;
   pdu.data.u.obj_system_information_type_10bis = pvalue;


   asn1Init_TS44018Msg_SYSTEM_INFORMATION_TYPE_10bis (pvalue);

   pvalue->si10bis_Sequence = 1;
   pvalue->component_2.n = 1;
   pvalue->component_2.elem = 
      rtxMemAlloc(&ctxt,
      sizeof(TS44018IE_SI10bis_Rest_Octets_component_2_element) * 
      pvalue->component_2.n);
   
   pvalue->component_2.elem[0].m.bcch_arfcnPresent = 1;
   pvalue->component_2.elem[0].m.bsicPresent = 1;
   pvalue->component_2.elem[0].position_in_SI5_list = 4;
   pvalue->component_2.elem[0].bcch_arfcn = 15;
   pvalue->component_2.elem[0].bsic = 31;   

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.channel_Description = 22008;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.m.component_2Present = 1;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.t =  2;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.u.frequency_Short_List[0] = 0xa0;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.u.frequency_Short_List[1] = 0x51;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.u.frequency_Short_List[2] = 0x20;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.u.frequency_Short_List[3] = 0x1f;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.u.frequency_Short_List[4] = 0xf6;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.u.frequency_Short_List[5] = 0xed;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.u.frequency_Short_List[6] = 0xe0;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.group_Channel_Description.component_2.u.frequency_Short_List[7] = 0xd1;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.m.component_2Present = 1;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_2.t =  2;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_2.u.frequency_List.length = 0;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_2.u.frequency_List.component_2.t = 2;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_2.u.frequency_List.component_2.u.choice_2.spare_bit = 0;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_2.u.frequency_List.component_2.u.choice_2.component_2.t = 1;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_2.u.frequency_List.component_2.u.choice_2.component_2.u.range_1024.numbits = 83;
   {
      OSOCTET* data = rtxMemAlloc(&ctxt, 11);
      data[0] = 0x41;
      data[1] = 0x37;
      data[2] = 0x52;
      data[3] = 0x6b;
      data[4] = 0x4e;
      data[5] = 0x61;
      data[6] = 0x6d;
      data[7] = 0x46;
      data[8] = 0x60;
      data[9] = 0x64;
      data[10] = 0x6b;

      pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_2.u.frequency_List.component_2.u.choice_2.component_2.u.range_1024.data = data;
   }
   
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.cell_global_count = 1;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.b22_count = 0;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.m.component_5Present = 1;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.m.priority_Uplink_accessPresent = 1;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.priority_Uplink_access = 0;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.m.component_2Present = 1;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.component_2.m.fr_AMR_ConfigPresent = 1;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.component_2.fr_AMR_Config = 7;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.component_2.m.hr_AMR_ConfigPresent = 1;
   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.component_2.hr_AMR_Config = 9;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.m.component_3Present = 1;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.component_3.sms_Data_Confidentiality_Ind = 0;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.component_3.sms_Guaranteed_Privacy_Ind = 0;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.m.component_4Present = 1;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.component_4.max_retrans = 0;

   pvalue->component_2.elem[0].si10bis_Neighbour_Cell_Info.component_5.component_4.tx_Integer = 5;
   

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
