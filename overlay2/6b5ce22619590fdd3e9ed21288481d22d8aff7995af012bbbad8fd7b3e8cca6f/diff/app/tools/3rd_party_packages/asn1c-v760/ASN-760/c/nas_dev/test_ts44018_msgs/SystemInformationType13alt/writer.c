#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018IE_SI13alt_Rest_Octets*
    asn1Test_TS44018IE_SI13alt_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_SI13alt_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI13alt_Rest_Octets);
   asn1Init_TS44018IE_SI13alt_Rest_Octets (pvalue);

   pvalue->pbcch_Description.psi1_repeat_period = 14;

   pvalue->pbcch_Description.pb = 12;

   pvalue->pbcch_Description.tn = 2;

   pvalue->pbcch_Description.pbcch_Frequency_Description.tsc = 4;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.t =  4;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_2.maio = 57;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_2.hsn = 6;

   pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_2.length_of_MA_Frequency_List_contents = 2;

   {
      static const OSOCTET testdata[] = { 
      0xbd, 0x80, 0x81, 0xab, 0x1e };
      pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_2.ma_Frequency_List_contents.numocts = 5;
      OSCRTLSAFEMEMCPY ((void*)pvalue->pbcch_Description.pbcch_Frequency_Description.component_2.u.direct_encoding_2.ma_Frequency_List_contents.data, 5, testdata, 5);
   }
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
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType13alt;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType13alt;

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType13alt;
   pdu.restOctets.u.obj_SystemInformationType13alt =
      asn1Test_TS44018IE_SI13alt_Rest_Octets(pctxt);


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
