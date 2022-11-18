#include "TS44018Msgs.h"
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
   TS44018Msg_DL_DCCH_PDU pdu;
   TS44018Msg_UplinkBusy data;
   TS44018Msg_UplinkBusy* pvalue = &data;

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

   asn1Init_TS44018Msg_DL_DCCH_PDU (&pdu);
   pdu.l3HdrOpts.t = 1;
   pdu.l3HdrOpts.u.skipInd = 0;
   pdu.protoDiscr = TS24007L3_ProtoDiscr_rrMgmt;
   pdu.msgType = ASN1V_ts44018Msg_mt_UplinkBusy;
   pdu.data.t = T_TS44018Msgs_DL_DCCH_Messages_obj_UplinkBusy;
   pdu.data.u.obj_UplinkBusy = pvalue;


   asn1Init_TS44018Msg_UplinkBusy (pvalue);

   pvalue->m.talkerPriorityEmergencyIndPresent = 1;
   pvalue->talkerPriorityEmergencyInd.length = 0; /* length will be calculated */

   pvalue->talkerPriorityEmergencyInd.es = 0;

   pvalue->talkerPriorityEmergencyInd.spare_bit = 0;

   pvalue->talkerPriorityEmergencyInd.uai = 0;

   pvalue->talkerPriorityEmergencyInd.priority = 2;

   pvalue->m.tokenPresent = 1;

   pvalue->token.identification = 11174;

   pvalue->m.talkerIdentityPresent = 1;
   pvalue->talkerIdentity.length = 0; /* length will be calculated */

   pvalue->talkerIdentity.spare_bit = 0;

   pvalue->talkerIdentity.filler = 0;

   pvalue->talkerIdentity.talker_id_field.numocts = 5;
   pvalue->talkerIdentity.talker_id_field.data = (OSOCTET*) rtxMemAlloc (pctxt, 5);
   {
      static const OSOCTET testdata[] = {
      0x17, 0xfb, 0xa8, 0xcc, 0x66 };
      OSCRTLSAFEMEMCPY ((void*)pvalue->talkerIdentity.talker_id_field.data, 5, testdata, 5);
   }

   pvalue->m.uplinkAccessIndicationPresent = 1;

   pvalue->uplinkAccessIndication.spare_bit = 0;

   pvalue->uplinkAccessIndication.ua_ind = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_DL_DCCH_PDU (&ctxt, &pdu);
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
