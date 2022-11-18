#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_ImmediateAssignmentReject*
    asn1Test_TS44018Msg_ImmediateAssignmentReject (OSCTXT* pctxt)
{
   TS44018Msg_ImmediateAssignmentReject* pvalue = rtxMemAllocType (pctxt, TS44018Msg_ImmediateAssignmentReject);
   asn1Init_TS44018Msg_ImmediateAssignmentReject (pvalue);

   pvalue->featureIndicator.spare_bit = 0;

   pvalue->featureIndicator.cs_ir = 0;

   pvalue->featureIndicator.ps_ir = 0;

   pvalue->pageMode.spare_bit = 1;

   pvalue->pageMode.pm = 0;

   pvalue->requestReference1.ra = 151;

   pvalue->requestReference1.t1prime = 8;

   pvalue->requestReference1.t3 = 25;

   pvalue->requestReference1.t2 = 0;

   pvalue->waitIndication1.t3122_T3142_timeout = 189;

   pvalue->requestReference2.ra = 165;

   pvalue->requestReference2.t1prime = 29;

   pvalue->requestReference2.t3 = 39;

   pvalue->requestReference2.t2 = 9;

   pvalue->waitIndication2.t3122_T3142_timeout = 88;

   pvalue->requestReference3.ra = 181;

   pvalue->requestReference3.t1prime = 27;

   pvalue->requestReference3.t3 = 12;

   pvalue->requestReference3.t2 = 21;

   pvalue->waitIndication3.t3122_T3142_timeout = 44;

   pvalue->requestReference4.ra = 140;

   pvalue->requestReference4.t1prime = 13;

   pvalue->requestReference4.t3 = 18;

   pvalue->requestReference4.t2 = 25;

   pvalue->waitIndication4.t3122_T3142_timeout = 235;
   return (pvalue);
}


TS44018IE_IAR_Rest_Octets* asn1Test_TS44018IE_IAR_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_IAR_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_IAR_Rest_Octets);
   asn1Init_TS44018IE_IAR_Rest_Octets (pvalue);

   pvalue->m.extended_RA_1Present = 1;
   pvalue->extended_RA_1 = 25;

   pvalue->m.extended_RA_2Present = 1;
   pvalue->extended_RA_2 = 25;

   pvalue->m.extended_RA_3Present = 1;
   pvalue->extended_RA_3 = 13;

   pvalue->m.extended_RA_4Present = 1;
   pvalue->extended_RA_4 = 23;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_ImmediateAssignmentReject;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ImmediateAssignmentReject;
   pdu.data.u.obj_ImmediateAssignmentReject =
      asn1Test_TS44018Msg_ImmediateAssignmentReject(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_ImmediateAssignmentReject;
   pdu.restOctets.u.obj_ImmediateAssignmentReject =
      asn1Test_TS44018IE_IAR_Rest_Octets(pctxt);


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
