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
   TS44018Msg_SYSTEM_INFORMATION_TYPE_10 data;
   TS44018Msg_SYSTEM_INFORMATION_TYPE_10* pvalue = &data;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_system_information_type_10;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_system_information_type_10;
   pdu.data.u.obj_system_information_type_10 = pvalue;


   asn1Init_TS44018Msg_SYSTEM_INFORMATION_TYPE_10 (pvalue);

   pvalue->ba_ind = 0;

   pvalue->m.neighbour_informationPresent = 1;

   pvalue->neighbour_information.first_frequency = 16;

   pvalue->neighbour_information.cell_info.bsic = 42;

   pvalue->neighbour_information.cell_info.m.cell_parametersPresent = 1;

   pvalue->neighbour_information.cell_info.cell_parameters.t = 2;

   pvalue->neighbour_information.cell_info.cell_parameters.u.further_cell_info
      .la_different.m.cell_reselect_hysteresisPresent = 1;

   pvalue->neighbour_information.cell_info.cell_parameters.u.further_cell_info
      .la_different.cell_reselect_hysteresis = 7;

   pvalue->neighbour_information.cell_info.cell_parameters.u.further_cell_info
      .ms_txpwr_max_cch = 12;

   pvalue->neighbour_information.cell_info.cell_parameters.u.further_cell_info
      .rxlev_access_min = 21;

   pvalue->neighbour_information.cell_info.cell_parameters.u.further_cell_info
      .cell_reselect_offset = 15;

   pvalue->neighbour_information.cell_info.cell_parameters.u.further_cell_info
      .temporary_offset = 3;

   pvalue->neighbour_information.cell_info.cell_parameters.u.further_cell_info
      .penalty_time = 4;

   pvalue->neighbour_information.info_field_list.n = 1;

   pvalue->neighbour_information.info_field_list.elem = 
                        rtxMemAlloc(&ctxt, sizeof(TS44018IE_Info_field) * 1);

   pvalue->neighbour_information.info_field_list.elem[0].next_frequency = 5;

   pvalue->neighbour_information.info_field_list.elem[0].differential_cell_info
      .component_1.t = 1;
   pvalue->neighbour_information.info_field_list.elem[0].differential_cell_info
      .component_1.u.bcc = 3;
   pvalue->neighbour_information.info_field_list.elem[0].differential_cell_info
      .m.diff_cell_parsPresent = 0;

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
