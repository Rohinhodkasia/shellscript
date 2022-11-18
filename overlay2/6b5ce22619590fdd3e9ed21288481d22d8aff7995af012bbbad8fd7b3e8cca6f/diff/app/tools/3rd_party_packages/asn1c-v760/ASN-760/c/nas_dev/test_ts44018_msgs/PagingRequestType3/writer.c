#include "TS44018Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

TS44018Msg_PagingRequestType3*
    asn1Test_TS44018Msg_PagingRequestType3 (OSCTXT* pctxt)
{
   TS44018Msg_PagingRequestType3* pvalue = rtxMemAllocType (pctxt, TS44018Msg_PagingRequestType3);
   asn1Init_TS44018Msg_PagingRequestType3 (pvalue);

   pvalue->channelsNeededForMobiles1And2.channel_second = 1;

   pvalue->channelsNeededForMobiles1And2.channel_first = 2;

   pvalue->pageMode.spare_bit = 2;

   pvalue->pageMode.pm = 1;

   pvalue->mobileIdentity1.t =  1;
   rtxStrncpy (pvalue->mobileIdentity1.u.imsi, sizeof(pvalue->mobileIdentity1.u.imsi), "61603123456789", 15);

   pvalue->mobileIdentity2.t =  2;
   rtxStrncpy(pvalue->mobileIdentity2.u.imei,
              sizeof(pvalue->mobileIdentity2.u.imei),
			  "393852228746632", 16);

   pvalue->mobileIdentity3.t =  3;
   rtxStrncpy(pvalue->mobileIdentity3.u.imei,
              sizeof(pvalue->mobileIdentity3.u.imei),
			  "946571452621968", 16);

   pvalue->mobileIdentity4.t =  4;
   {
      static const OSOCTET testdata[] = { 
      0x5e, 0x37, 0x03, 0xd6 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->mobileIdentity4.u.tmsi, 4, testdata, 4);
   }
   return (pvalue);
}


TS44018IE_P3_Rest_Octets* asn1Test_TS44018IE_P3_Rest_Octets (OSCTXT* pctxt)
{
   TS44018IE_P3_Rest_Octets* pvalue = rtxMemAllocType (pctxt, TS44018IE_P3_Rest_Octets);
   asn1Init_TS44018IE_P3_Rest_Octets (pvalue);

   pvalue->m.component_1Present = 1;

   pvalue->component_1.cn3 = 2;

   pvalue->component_1.cn4 = 0;

   pvalue->m.component_2Present = 1;

   pvalue->component_2.nln_pch = 1;

   pvalue->component_2.nln_status_PCH = 0;

   pvalue->m.priority1Present = 1;
   pvalue->priority1 = 1;

   pvalue->m.priority2Present = 1;
   pvalue->priority2 = 4;

   pvalue->m.priority3Present = 1;
   pvalue->priority3 = 4;

   pvalue->m.priority4Present = 1;
   pvalue->priority4 = 3;

   pvalue->m.component_7Present = 1;

   pvalue->component_7.implicit_Reject_CS = 0;

   pvalue->component_7.implicit_Reject_PS = 0;

   pvalue->m.ipa_SupportPresent = 1;
   pvalue->ipa_Support = 0;
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
   pdu.msgType = ASN1V_ts44018Msg_mt_PagingRequestType3;
   pdu.data.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_PagingRequestType3;
   pdu.data.u.obj_PagingRequestType3 =
      asn1Test_TS44018Msg_PagingRequestType3(pctxt);

   pdu.restOctets.t = T_TS44018Msgs_L2_PSEUDO_LEN_PDU_Messages_obj_PagingRequestType3;
   pdu.restOctets.u.obj_PagingRequestType3 =
      asn1Test_TS44018IE_P3_Rest_Octets(pctxt);


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

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
