#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType5*
    asn1Test_TS44018Msg_SystemInformationType5 (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType5* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType5);
   asn1Init_TS44018Msg_SystemInformationType5 (pvalue);

   pvalue->bcchFrequencyList.t =  2;

   pvalue->bcchFrequencyList.u.choice_2.ext_ind = 0;

   pvalue->bcchFrequencyList.u.choice_2.ba_ind = 0;

   pvalue->bcchFrequencyList.u.choice_2.component_3.t =  5;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[0] = 0x86;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[1] = 0x6f;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[2] = 0x64;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[3] = 0xe3;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[4] = 0x8e;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[5] = 0xe;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[6] = 0xdf;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[7] = 0xcd;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[8] = 0x23;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[9] = 0x6a;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[10] = 0x77;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[11] = 0xd1;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[12] = 0xd3;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[13] = 0xa0;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[14] = 0xe6;
   pvalue->bcchFrequencyList.u.choice_2.component_3.u.variable_bitmap[15] = 0x5c;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType5;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5;
   pdu.data.u.obj_SystemInformationType5 =
      asn1Test_TS44018Msg_SystemInformationType5(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType5;

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
