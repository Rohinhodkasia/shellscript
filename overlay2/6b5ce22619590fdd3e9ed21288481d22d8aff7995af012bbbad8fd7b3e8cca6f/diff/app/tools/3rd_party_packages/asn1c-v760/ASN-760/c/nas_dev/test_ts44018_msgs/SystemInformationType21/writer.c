#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018IE_SI21_Rest_Octets* asn1Test_TS44018IE_SI21_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI21_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI21_Rest_Octets);
   asn1Init_TS44018IE_SI21_Rest_Octets (pvalue);

   pvalue->si_21_change_mark = 2;

   pvalue->si_21_index = 3;

   pvalue->si_21_count = 0;

   pvalue->m.component_4Present = 1;

   pvalue->component_4.eab_Authorization_Mask = 627;

   pvalue->component_4.eab_Subcategory = 1;

   pvalue->component_5.m.network_Sharing_EAB_InformationPresent = 1;

   pvalue->component_5.network_Sharing_EAB_Information.m.component_1Present = 1;

   pvalue->component_5.network_Sharing_EAB_Information.component_1.common_PLMN_PS_EAB_Authorization_Mask = 124;

   pvalue->component_5.network_Sharing_EAB_Information.component_1.common_PLMN_PS_EAB_Subcategory = 1;

   pvalue->component_5.network_Sharing_EAB_Information.nb_Additional_PLMNs = 0;

   pvalue->component_5.network_Sharing_EAB_Information.component_3.n = 1;

   pvalue->component_5.network_Sharing_EAB_Information.component_3.elem[0].m.component_1Present = 1;

   pvalue->component_5.network_Sharing_EAB_Information.component_3.elem[0].component_1.additional_EAB_Authorization_Mask = 329;

   pvalue->component_5.network_Sharing_EAB_Information.component_3.elem[0].component_1.additional_EAB_Subcategory = 1;

   pvalue->component_5.network_Sharing_EAB_Information.component_3.elem[0].m.component_2Present = 1;

   pvalue->component_5.network_Sharing_EAB_Information.component_3.elem[0].component_2.m.component_1Present = 1;

   pvalue->component_5.network_Sharing_EAB_Information.component_3.elem[0].component_2.component_1.ps_EAB_Authorization_Mask = 261;

   pvalue->component_5.network_Sharing_EAB_Information.component_3.elem[0].component_2.component_1.ps_EAB_Subcategory = 1;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType21;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType21;

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType21;
   pdu.restOctets.u.obj_SystemInformationType21 =
      asn1Test_TS44018IE_SI21_Rest_Octets(pctxt);


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
