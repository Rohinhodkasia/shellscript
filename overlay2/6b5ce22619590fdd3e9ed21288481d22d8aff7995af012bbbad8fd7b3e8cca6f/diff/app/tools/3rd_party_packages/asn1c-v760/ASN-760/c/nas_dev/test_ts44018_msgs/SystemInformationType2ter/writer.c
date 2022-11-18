#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType2ter*
    asn1Test_TS44018Msg_SystemInformationType2ter (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType2ter* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType2ter);
   asn1Init_TS44018Msg_SystemInformationType2ter (pvalue);

   pvalue->extendedBCCHFrequencyList.t =  2;

   pvalue->extendedBCCHFrequencyList.u.choice_2.multiband_reporting = 1;

   pvalue->extendedBCCHFrequencyList.u.choice_2.ba_ind = 0;

   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.t =  4;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[0] = 0x95;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[1] = 0x16;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[2] = 0xba;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[3] = 0x8b;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[4] = 0x69;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[5] = 0x98;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[6] = 0xf3;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[7] = 0x40;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[8] = 0x6e;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[9] = 0x7e;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[10] = 0xb6;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[11] = 0x5d;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[12] = 0xa1;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[13] = 0x21;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[14] = 0x1c;
   pvalue->extendedBCCHFrequencyList.u.choice_2.component_3.u.range_128[15] = 0x69;
   return (pvalue);
}


TS44018IE_SI2ter_Rest_Octets*
    asn1Test_TS44018IE_SI2ter_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI2ter_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI2ter_Rest_Octets);
   asn1Init_TS44018IE_SI2ter_Rest_Octets (pvalue);

   pvalue->m.component_1Present = 1;

   pvalue->component_1.si2ter_MP_CHANGE_MARK = 0;

   pvalue->component_1.si2ter_3G_CHANGE_MARK = 0;

   pvalue->component_1.si2ter_INDEX = 4;

   pvalue->component_1.si2ter_COUNT = 0;

   pvalue->component_1.m.utran_FDD_DescriptionPresent = 1;

   pvalue->component_1.utran_FDD_Description.component_1 = 1;

   pvalue->component_1.utran_FDD_Description.fdd_arfcn = 7487;

   pvalue->component_1.utran_FDD_Description.m.bandwidth_FDDPresent = 1;
   pvalue->component_1.utran_FDD_Description.bandwidth_FDD = 3;

   pvalue->component_1.m.utran_TDD_DescriptionPresent = 1;

   pvalue->component_1.utran_TDD_Description.component_1 = 1;

   pvalue->component_1.utran_TDD_Description.tdd_arfcn = 8891;

   pvalue->component_1.utran_TDD_Description.m.bandwidth_TDDPresent = 1;
   pvalue->component_1.utran_TDD_Description.bandwidth_TDD = 0;

   pvalue->component_1.m.a3G_MEASUREMENT_Parameters_DescriptionPresent = 1;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.qsearch_I = 14;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.m.component_2Present = 1;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.component_2.fdd_Qoffset = 9;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.component_2.fdd_Qmin = 6;

   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.m.tdd_QoffsetPresent = 1;
   pvalue->component_1.a3G_MEASUREMENT_Parameters_Description.tdd_Qoffset = 2;

   pvalue->component_1.m.component_8Present = 1;

   pvalue->component_1.component_8.m.a3G_Additional_Measurement_Parameters_DescriptionPresent = 1;

   pvalue->component_1.component_8.a3G_Additional_Measurement_Parameters_Description.fdd_Qmin_Offset = 0;

   pvalue->component_1.component_8.a3G_Additional_Measurement_Parameters_Description.fdd_RSCPmin = 13;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType2ter;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2ter;
   pdu.data.u.obj_SystemInformationType2ter =
      asn1Test_TS44018Msg_SystemInformationType2ter(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType2ter;
   pdu.restOctets.u.obj_SystemInformationType2ter =
      asn1Test_TS44018IE_SI2ter_Rest_Octets(pctxt);


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
