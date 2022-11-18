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
   TS24008Msg_MMInformation data;
   TS24008Msg_MMInformation* pvalue = &data;
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
   pdu.msgType = ASN1V_mt_MMInformation;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_MMInformation;
   pdu.data.u.obj_MMInformation = pvalue;

   asn1Init_TS24008Msg_MMInformation (pvalue);
   pvalue->m.networkFullNamePresent = 1;
   pvalue->networkFullName.ext = 0;
   pvalue->networkFullName.codingScheme = TS24008IE_NetworkName_codingScheme_callBcastData;
   pvalue->networkFullName.addCI = 1;
   pvalue->networkFullName.numSpareBitsInLastOct = 3;
   pvalue->networkFullName.textString.u.callBcastData = "WH3";
   pvalue->m.networkShortNamePresent = 1;
   pvalue->networkShortName.ext = 1;
   pvalue->networkShortName.codingScheme = TS24008IE_NetworkName_codingScheme_callBcastData;
   pvalue->networkShortName.addCI = 1;
   pvalue->networkShortName.numSpareBitsInLastOct = 2;
   pvalue->networkShortName.textString.u.callBcastData = "aP";
   pvalue->m.localTimeZonePresent = 1;
   pvalue->localTimeZone = 213;
   pvalue->m.univAndLocalTimeZonePresent = 1;
   pvalue->univAndLocalTimeZone.year = 40;
   pvalue->univAndLocalTimeZone.month = 152;
   pvalue->univAndLocalTimeZone.day = 106;
   pvalue->univAndLocalTimeZone.hour = 51;
   pvalue->univAndLocalTimeZone.minute = 106;
   pvalue->univAndLocalTimeZone.second = 103;
   pvalue->univAndLocalTimeZone.timezone = 69;
   pvalue->m.lsaIdentityPresent = 1;
   {
      pvalue->lsaIdentity.numocts = 0;
   }
   pvalue->m.networkDaylightSavingTimePresent = 1;
   pvalue->networkDaylightSavingTime.spare = 12;
   pvalue->networkDaylightSavingTime.dst = TS24008IE_DaylightSavingTime_dst_dstNoAdjust;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

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
