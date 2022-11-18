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
   TS24008Msg_GMMInformation data;
   TS24008Msg_GMMInformation* pvalue = &data;
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
   pdu.protoDiscr = TS24007L3_ProtoDiscr_gprsMobMgmt;
   pdu.msgType = ASN1V_mt_GMMInformation;
   pdu.data.t = T_TS24008Msgs_TS24008_IE_OBJECTSET_obj_GMMInformation;
   pdu.data.u.obj_GMMInformation = pvalue;

   asn1Init_TS24008Msg_GMMInformation (pvalue);
   pvalue->m.fullNetNamePresent = 1;
   pvalue->fullNetName.length = 3;
   pvalue->fullNetName.ext = 1;
   pvalue->fullNetName.codingScheme =
      TS24008IE_NetworkName_codingScheme_callBcastData;
   pvalue->fullNetName.addCI = 1;
   pvalue->fullNetName.textString.u.callBcastData = "51l";
   {
      OSSIZE nchars = OSCRTLSTRLEN
         (pvalue->fullNetName.textString.u.callBcastData);

      pvalue->fullNetName.numSpareBitsInLastOct = nchars % 8;
  }
   pvalue->m.shortNetNamePresent = 1;
   pvalue->shortNetName.length = 224;
   pvalue->shortNetName.ext = 0;
   pvalue->shortNetName.codingScheme =
      TS24008IE_NetworkName_codingScheme_callBcastData;
   pvalue->shortNetName.addCI = 0;
   pvalue->shortNetName.textString.u.callBcastData = "Ff@_4l3l";
   {
      OSSIZE nchars = OSCRTLSTRLEN
         (pvalue->shortNetName.textString.u.callBcastData);

      pvalue->shortNetName.numSpareBitsInLastOct = nchars % 8;
  }
   pvalue->m.localTimeZonePresent = 1;
   pvalue->localTimeZone = 142;
   pvalue->m.universalAndLocalTimeZonePresent = 1;
   pvalue->universalAndLocalTimeZone.year = 22;
   pvalue->universalAndLocalTimeZone.month = 148;
   pvalue->universalAndLocalTimeZone.day = 191;
   pvalue->universalAndLocalTimeZone.hour = 232;
   pvalue->universalAndLocalTimeZone.minute = 204;
   pvalue->universalAndLocalTimeZone.second = 151;
   pvalue->universalAndLocalTimeZone.timezone = 66;
   pvalue->m.lsaIdentityPresent = 1;
   {
      pvalue->lsaIdentity.numocts = 0;
   }
   pvalue->m.networkDSTPresent = 1;
   pvalue->networkDST.spare = 60;
   pvalue->networkDST.dst = TS24008IE_DaylightSavingTime_dst_dstNoAdjust;

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
