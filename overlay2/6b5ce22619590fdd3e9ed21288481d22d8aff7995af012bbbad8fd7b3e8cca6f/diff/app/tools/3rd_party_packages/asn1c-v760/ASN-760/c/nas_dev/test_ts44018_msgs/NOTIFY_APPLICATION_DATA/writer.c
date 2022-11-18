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
   TS44018Msg_RR_Short_PD_PDU pdu;
   TS44018Msg_NOTIFY_APPLICATION_DATA data;
   TS44018Msg_NOTIFY_APPLICATION_DATA* pvalue = &data;

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

   asn1Init_TS44018Msg_RR_Short_PD_PDU (&pdu);
   pdu.rr_short_PD = 0;
   pdu.msgType = ASN1V_ts44018Msg_mt_notify_application_data;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_notify_application_data;
   pdu.data.u.obj_notify_application_data = pvalue;


   asn1Init_TS44018Msg_NOTIFY_APPLICATION_DATA (pvalue);

   pvalue->application_data[0] = 0xea;
   pvalue->application_data[1] = 0xf7;
   pvalue->application_data[2] = 0x19;
   pvalue->application_data[3] = 0x4;
   pvalue->application_data[4] = 0x2b;
   pvalue->application_data[5] = 0xc1;
   pvalue->application_data[6] = 0xc3;
   pvalue->application_data[7] = 0xe0;
   pvalue->application_data[8] = 0x6;

   pvalue->data_identity = 167;

   pvalue->m.component_3Present = 1;

   pvalue->component_3.msisdn_length = 8;

   pvalue->component_3.msisdn.numbits = 64;
   pvalue->component_3.msisdn.data[0] = 0x30;
   pvalue->component_3.msisdn.data[1] = 0x37;
   pvalue->component_3.msisdn.data[2] = 0x69;
   pvalue->component_3.msisdn.data[3] = 0x58;
   pvalue->component_3.msisdn.data[4] = 0x39;
   pvalue->component_3.msisdn.data[5] = 0x69;
   pvalue->component_3.msisdn.data[6] = 0x30;
   pvalue->component_3.msisdn.data[7] = 0x61;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018Msg_RR_Short_PD_PDU (&ctxt, &pdu);
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
