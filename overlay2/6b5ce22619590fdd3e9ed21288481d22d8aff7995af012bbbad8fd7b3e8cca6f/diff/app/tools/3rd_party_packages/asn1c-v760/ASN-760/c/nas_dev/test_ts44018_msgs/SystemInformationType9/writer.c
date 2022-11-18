#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType9*
    asn1Test_TS44018Msg_SystemInformationType9 (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType9* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType9);

   pvalue->rachControlParameter.max_retrans = 2;

   pvalue->rachControlParameter.tx_integer = 7;

   pvalue->rachControlParameter.cell_bar_access = 0;

   pvalue->rachControlParameter.re = 0;

   pvalue->rachControlParameter.acc = 4358;
   return (pvalue);
}


TS44018IE_SI9_Rest_Octets* asn1Test_TS44018IE_SI9_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI9_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI9_Rest_Octets);
   asn1Init_TS44018IE_SI9_Rest_Octets (pvalue);

   pvalue->m.scheduling_info_listPresent = 1;

   pvalue->scheduling_info_list.scheduling_info.info_type.t =  2;
   pvalue->scheduling_info_list.scheduling_info.info_type.u.info_type_5 = 26;

   pvalue->scheduling_info_list.scheduling_info.positions.position.modulus = 12;

   switch (pvalue->scheduling_info_list.scheduling_info.positions.position.modulus) {
      /* bcch-type */
      case 0:
         pvalue->scheduling_info_list.scheduling_info.positions.position.component_1.u.bcch_type = 0;
         break;

      /* choice-2 */
      default:

         pvalue->scheduling_info_list.scheduling_info.positions.position.component_1.u.choice_2.relative_position.numbits = 13;
         pvalue->scheduling_info_list.scheduling_info.positions.position.component_1.u.choice_2.relative_position.data[0] = 0x6e;
         pvalue->scheduling_info_list.scheduling_info.positions.position.component_1.u.choice_2.relative_position.data[1] = 0x51;

         pvalue->scheduling_info_list.scheduling_info.positions.position.component_1.u.choice_2.bcch_type = 0;
         break;

   }

   pvalue->scheduling_info_list.scheduling_info.positions.m.position2Present = 1;

   pvalue->scheduling_info_list.scheduling_info.positions.position2.modulus = 3;

   switch (pvalue->scheduling_info_list.scheduling_info.positions.position2.modulus) {
      /* bcch-type */
      case 0:
         pvalue->scheduling_info_list.scheduling_info.positions.position2.component_1.u.bcch_type = 0;
         break;

      /* choice-2 */
      default:

         pvalue->scheduling_info_list.scheduling_info.positions.position2.component_1.u.choice_2.relative_position.numbits = 4;
         pvalue->scheduling_info_list.scheduling_info.positions.position2.component_1.u.choice_2.relative_position.data[0] = 0x61;

         pvalue->scheduling_info_list.scheduling_info.positions.position2.component_1.u.choice_2.bcch_type = 0;
         break;

   }

   /* zero elements */
   return (pvalue);
}


int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU pdu;

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

   asn1Init_TS44018Msg_L2_PSEUDO_LEN_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType9;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType9;
   pdu.data.u.obj_SystemInformationType9 =
      asn1Test_TS44018Msg_SystemInformationType9(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType9;
   pdu.restOctets.u.obj_SystemInformationType9 =
      asn1Test_TS44018IE_SI9_Rest_Octets(pctxt);


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, &pdu);
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
