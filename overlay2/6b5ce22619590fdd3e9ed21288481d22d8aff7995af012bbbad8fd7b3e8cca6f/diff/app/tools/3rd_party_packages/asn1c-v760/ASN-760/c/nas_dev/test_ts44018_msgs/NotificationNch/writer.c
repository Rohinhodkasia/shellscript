#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300


TS44018IE_NT_N_Rest_Octets* asn1Test_TS44018IE_NT_N_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_NT_N_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_NT_N_Rest_Octets);
   asn1Init_TS44018IE_NT_N_Rest_Octets (pvalue);

   pvalue->m.nln_nchPresent = 1;
   pvalue->nln_nch = 0;

   /* zero elements */

   pvalue->m.component_3Present = 1;

   pvalue->component_3.m.cell_global_countPresent = 1;
   pvalue->component_3.cell_global_count = 0;

   pvalue->component_3.list_of_Reduced_GCR.n = 6;
   pvalue->component_3.list_of_Reduced_GCR.elem = rtxMemAllocArrayZ (pctxt, 6, OSUINT32);
   pvalue->component_3.list_of_Reduced_GCR.elem[0] = 3805651;

   pvalue->component_3.list_of_Reduced_GCR.elem[1] = 178278596;

   pvalue->component_3.list_of_Reduced_GCR.elem[2] = 197353708;

   pvalue->component_3.list_of_Reduced_GCR.elem[3] = 142504499;

   pvalue->component_3.list_of_Reduced_GCR.elem[4] = 51290552;

   pvalue->component_3.list_of_Reduced_GCR.elem[5] = 35038866;

   /* zero elements */

   pvalue->m.component_4Present = 1;

   pvalue->component_4.list_of_Emergency_information.n = 3;
   pvalue->component_4.list_of_Emergency_information.elem = rtxMemAllocArrayZ (pctxt, 3, OSUINT8);
   pvalue->component_4.list_of_Emergency_information.elem[0] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[1] = 0;

   pvalue->component_4.list_of_Emergency_information.elem[2] = 0;

   pvalue->component_4.m.priority_Uplink_accessPresent = 1;
   pvalue->component_4.priority_Uplink_access = 0;

   pvalue->component_4.m.component_3Present = 1;

   pvalue->component_4.component_3.m.fr_AMR_ConfigPresent = 1;
   pvalue->component_4.component_3.fr_AMR_Config = 10;

   pvalue->component_4.component_3.m.hr_AMR_ConfigPresent = 1;
   pvalue->component_4.component_3.hr_AMR_Config = 6;

   pvalue->component_4.m.component_4Present = 1;

   pvalue->component_4.component_4.sms_Data_Confidentiality_Ind = 0;

   pvalue->component_4.component_4.sms_Guaranteed_Privacy_Ind = 0;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_NotificationNch;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_NotificationNch;

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_NotificationNch;
   pdu.restOctets.u.obj_NotificationNch =
      asn1Test_TS44018IE_NT_N_Rest_Octets(pctxt);


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
