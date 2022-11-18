#include "TS24008Msgs.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

int main (int argc, char** argv)
{
   TS24008Msg_PDU pdu;
   TS24008Msg_LocUpdatingAccept data;
   TS24008Msg_LocUpdatingAccept* pvalue = &data;
   OSCTXT	ctxt;
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

   asn1Init_TS24008Msg_PDU (&pdu);
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_mobMgmt;
   pdu.msgType = ASN1V_mt_LocUpdatingAccept;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_LocUpdatingAccept;
   pdu.data.u.obj_LocUpdatingAccept = pvalue;

   asn1Init_TS24008Msg_LocUpdatingAccept (pvalue);
   rtxStrncpy(pvalue->locAreaIdent.mcc_mnc.mcc,
              sizeof(pvalue->locAreaIdent.mcc_mnc.mcc), "bc0", 4);
   rtxStrncpy(pvalue->locAreaIdent.mcc_mnc.mnc,
              sizeof(pvalue->locAreaIdent.mcc_mnc.mnc), "527", 4);
   pvalue->locAreaIdent.lac = 21073;
   pvalue->m.mobileIdentityPresent = 1;
   pvalue->mobileIdentity.t =  T_TS24008IE_MobileIdentity_imsi;
   rtxStrncpy(pvalue->mobileIdentity.u.imsi,
              sizeof(pvalue->mobileIdentity.u.imsi), "789aa8*ac81959", 15);
   pvalue->m.followOnProceedPresent = 1;
   pvalue->m.ctsPermissionPresent = 1;
   pvalue->m.equivPLMNsPresent = 1;
   pvalue->equivPLMNs.n = 1;
   rtxStrncpy(pvalue->equivPLMNs.elem[0].mcc,
              sizeof(pvalue->equivPLMNs.elem[0].mcc), "558", 4);
   rtxStrncpy(pvalue->equivPLMNs.elem[0].mnc,
              sizeof(pvalue->equivPLMNs.elem[0].mnc), "405", 4);
   pvalue->m.emergNumListPresent = 1;
   pvalue->emergNumList.length = 0; /* will be calculated */
   pvalue->emergNumList.numbers.n = 1;
   pvalue->emergNumList.numbers.elem[0].length = 0; /* will be calculated */
   pvalue->emergNumList.numbers.elem[0].spare = 0;
   pvalue->emergNumList.numbers.elem[0].catValue = 22;
   pvalue->emergNumList.numbers.elem[0].digits = "2517";

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008Msg_PDU (&ctxt, &pdu);
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
