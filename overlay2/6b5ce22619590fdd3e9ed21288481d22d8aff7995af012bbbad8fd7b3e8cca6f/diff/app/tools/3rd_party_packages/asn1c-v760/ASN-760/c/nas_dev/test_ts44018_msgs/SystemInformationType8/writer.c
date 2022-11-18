#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300


TS44018IE_SI8_Rest_Octets* asn1Test_TS44018IE_SI8_Rest_Octets (OSCTXT* pctxt)
{
   /* We are assuming "SI4 Rest Octets O" should be present.  The reader will
      have to know to expect it.
   */
   TS44018IE_SI8_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_SI8_Rest_Octets);
   asn1Init_TS44018IE_SI8_Rest_Octets (pvalue);

   pvalue->m.si4_Rest_Octets_OPresent = 1;

   pvalue->si4_Rest_Octets_O.m.optional_Selection_ParametersPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.m.selection_ParametersPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.cbq = 0;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.cell_reselect_offset = 6;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.temporary_offset = 1;

   pvalue->si4_Rest_Octets_O.optional_Selection_Parameters.selection_Parameters.penalty_time = 24;

   pvalue->si4_Rest_Octets_O.m.optional_Power_OffsetPresent = 1;

   pvalue->si4_Rest_Octets_O.optional_Power_Offset.m.power_OffsetPresent = 1;
   pvalue->si4_Rest_Octets_O.optional_Power_Offset.power_Offset = 1;

   pvalue->si4_Rest_Octets_O.m.gprs_IndicatorPresent = 1;

   pvalue->si4_Rest_Octets_O.gprs_Indicator.ra_colour = 6;

   pvalue->si4_Rest_Octets_O.gprs_Indicator.si13_position = 0;

   pvalue->si4_Rest_Octets_S.m.si4_LSA_ParametersPresent = 1;

   pvalue->si4_Rest_Octets_S.si4_LSA_Parameters.prio_thr = 0;

   pvalue->si4_Rest_Octets_S.si4_LSA_Parameters.lsa_offset = 3;

   pvalue->si4_Rest_Octets_S.si4_LSA_Parameters.m.component_3Present = 1;

   pvalue->si4_Rest_Octets_S.si4_LSA_Parameters.component_3.mcc = 2335;

   pvalue->si4_Rest_Octets_S.si4_LSA_Parameters.component_3.mnc = 1569;

   pvalue->si4_Rest_Octets_S.m.cell_IdentityPresent = 1;
   pvalue->si4_Rest_Octets_S.cell_Identity = 25666;

   pvalue->si4_Rest_Octets_S.m.lsa_ID_informationPresent = 1;

   pvalue->si4_Rest_Octets_S.lsa_ID_information.first.t =  2;
   pvalue->si4_Rest_Octets_S.lsa_ID_information.first.u.shortLSA_ID = 710;

   pvalue->si4_Rest_Octets_S.lsa_ID_information.additional.n = 2;
   pvalue->si4_Rest_Octets_S.lsa_ID_information.additional.elem = rtxMemAllocArrayZ (pctxt, 2, TS44018IE_LSA_identity);
   pvalue->si4_Rest_Octets_S.lsa_ID_information.additional.elem[0].t =  1;
   pvalue->si4_Rest_Octets_S.lsa_ID_information.additional.elem[0].u.lsa_id = 28892;

   pvalue->si4_Rest_Octets_S.lsa_ID_information.additional.elem[1].t =  2;
   pvalue->si4_Rest_Octets_S.lsa_ID_information.additional.elem[1].u.shortLSA_ID = 603;

   pvalue->si4_Rest_Octets_S.m.component_4Present = 1;

   pvalue->si4_Rest_Octets_S.component_4.cbq3 = 0;

   pvalue->si4_Rest_Octets_S.component_4.m.si13alt_PositionPresent = 1;
   pvalue->si4_Rest_Octets_S.component_4.si13alt_Position = 0;
   return (pvalue);
}



/**
 * Encode given SI 8 Rest Octets into given buffer.
 * @param pvalue
 * @param msgbuf The message buffer
 * @param plen The length of message buffer on input; length of msg on output
 * @param verbose TRUE if verbose output should be generated
 * @return error code
 */
int EncodeSI8 (TS44018IE_SI8_Rest_Octets* pvalue, OSOCTET* msgbuf, OSSIZE* plen, OSBOOL verbose)
{
   OSCTXT ctxt;
   int ret;

   /* Initialize context structure */

   ret = rtInitContext (&ctxt);
   if (0 != ret) {
      printf ("rtInitContext failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, *plen);

   ret = NASEnc_TS44018IE_SI8_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI8 Rest Octets failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   /* Verify buffer is byte-aligned */
   OSRTASSERT (ctxt.buffer.bitOffset == 8 || ctxt.buffer.bitOffset == 0);

   *plen = rtxCtxtGetMsgLen (&ctxt);

   if (verbose) {
      printf ("Encoding of SI 8 Rest Octets was successful\n");
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgbuf, *plen);
      printf ("\n");
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   rtxFreeContext (&ctxt);

   return 0;
}


int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU pdu;
   TS44018IE_SI8_Rest_Octets* pSI8;
   TS44018IE_SI8_Rest_Octets_Data si8data;
   OSCTXT	ctxt;
   OSCTXT*  pctxt = &ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   OSOCTET  si8msgbuf[MAXMSGLEN];
   OSSIZE   si8len;
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

   /* Populate an SI 8 Rest Octets IE, encode it to a buffer, and set the
      encoding into an TS44018IE_SI8_Rest_Octets_Data object.
   */
   pSI8 = asn1Test_TS44018IE_SI8_Rest_Octets(pctxt);
   si8len = sizeof(si8msgbuf);
   ret = EncodeSI8 (pSI8, si8msgbuf, &si8len, verbose);
   if (0 != ret) return ret;  /* error already will have been printed */

   asn1Init_TS44018IE_SI8_Rest_Octets_Data (&si8data);
   si8data.numocts = si8len;
   si8data.data = si8msgbuf;
  
   /* Populate PDU data structure */
   asn1Init_TS44018Msg_L2_PSEUDO_LEN_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_SystemInformationType8;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType8;

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_SystemInformationType8;
   pdu.restOctets.u.obj_SystemInformationType8 = &si8data;

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
