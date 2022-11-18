#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_SystemInformationType1*
    asn1Test_TS44018Msg_SystemInformationType1 (OSCTXT* pctxt)
{
   TS44018Msg_SystemInformationType1* pvalue = rtxMemAllocType (pctxt, TS44018Msg_SystemInformationType1);
   asn1Init_TS44018Msg_SystemInformationType1 (pvalue);

   pvalue->cellChannelDescription.t =  2;

   pvalue->cellChannelDescription.u.choice_2.spare_bit = 0;

   pvalue->cellChannelDescription.u.choice_2.component_2.t =  5;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[0] = 0xa9;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[1] = 0x61;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[2] = 0x45;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[3] = 0x84;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[4] = 0x64;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[5] = 0x4b;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[6] = 0x2c;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[7] = 0x24;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[8] = 0x76;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[9] = 0xd;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[10] = 0xbb;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[11] = 0xa4;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[12] = 0x35;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[13] = 0xa4;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[14] = 0x9e;
   pvalue->cellChannelDescription.u.choice_2.component_2.u.variable_bitmap[15] = 0xc9;

   pvalue->rachControlParameter.max_retrans = 0;

   pvalue->rachControlParameter.tx_integer = 1;

   pvalue->rachControlParameter.cell_bar_access = 0;

   pvalue->rachControlParameter.re = 0;

   pvalue->rachControlParameter.acc = 49345;
   return (pvalue);
}


TS44018IE_SI1_Rest_Octets* asn1Test_TS44018IE_SI1_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI1_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI1_Rest_Octets);
   asn1Init_TS44018IE_SI1_Rest_Octets (pvalue);

   pvalue->m.nch_PositionPresent = 1;
   pvalue->nch_Position = 10;

   pvalue->band_indicator = TS44018IE_LHType_lbit;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType1;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType1;
   pdu.data.u.obj_SystemInformationType1 =
      asn1Test_TS44018Msg_SystemInformationType1(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType1;
   pdu.restOctets.u.obj_SystemInformationType1 =
      asn1Test_TS44018IE_SI1_Rest_Octets(pctxt);


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
