#include "TS44018Msgs.h"
#include "TS44018IES.h"
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
   TS44018Msg_SYSTEM_INFORMATION_TYPE_10ter data;
   TS44018Msg_SYSTEM_INFORMATION_TYPE_10ter* pvalue = &data;

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
   pdu.msgType = ASN1V_ts44018Msg_mt_system_information_type_10ter;
   pdu.short_layer_2_header = 0;
   pdu.data.t = T_TS44018Msgs_RR_Short_PD_Messages_obj_system_information_type_10ter;
   pdu.data.u.obj_system_information_type_10ter = pvalue;


   asn1Init_TS44018Msg_SYSTEM_INFORMATION_TYPE_10ter (pvalue);

   pvalue->cell_Channel_Description[0] = 0x80;
   pvalue->cell_Channel_Description[1] = 0xe4;
   pvalue->cell_Channel_Description[2] = 0x30;
   pvalue->cell_Channel_Description[3] = 0x91;
   pvalue->cell_Channel_Description[4] = 0xd9;
   pvalue->cell_Channel_Description[5] = 0xd9;
   pvalue->cell_Channel_Description[6] = 0xc7;
   pvalue->cell_Channel_Description[7] = 0x10;
   pvalue->cell_Channel_Description[8] = 0x1d;
   pvalue->cell_Channel_Description[9] = 0x29;
   pvalue->cell_Channel_Description[10] = 0x80;
   pvalue->cell_Channel_Description[11] = 0x12;
   pvalue->cell_Channel_Description[12] = 0x49;
   pvalue->cell_Channel_Description[13] = 0x7c;
   pvalue->cell_Channel_Description[14] = 0xba;
   pvalue->cell_Channel_Description[15] = 0xe;

   pvalue->si10ter_Rest_Octets.si10bis_Sequence = 0;

   pvalue->si10ter_Rest_Octets.component_2.t =  2;
   pvalue->si10ter_Rest_Octets.component_2.u.bcch_arfcn = 317;

   pvalue->si10ter_Rest_Octets.m.bsicPresent = 1;
   pvalue->si10ter_Rest_Octets.bsic = 4;

   pvalue->si10ter_Rest_Octets.nch_Position = 3;

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
