#include "TS24008IES.h"
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
   TS24008IE_MobileIdentity data;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr, ub;
   const char*  filename;
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

   /* Populate and encode each IE alternative and write to file */
   for (i = 1; i < 6; i++) {
      asn1Init_TS24008IE_MobileIdentity (&data);

      data.t = i;

      switch (i) {
      case T_TS24008IE_MobileIdentity_imsi:
         /* IMSI */
         rtxStrcpy (data.u.imsi, sizeof(data.u.imsi), "0123456789*#abc");
         filename = "message_imsi.dat";
         break;

      case T_TS24008IE_MobileIdentity_imei:
         /* IMEI */
         rtxStrcpy (data.u.imei, sizeof(data.u.imei), "123456789*#abc0");
         filename = "message_imei.dat";
         break;

      case T_TS24008IE_MobileIdentity_imeisv:
         /* IMEISV */
         rtxStrcpy (data.u.imeisv, sizeof(data.u.imeisv), "123456789*#abc01");
         filename = "message_imeisv.dat";
         break;

      case T_TS24008IE_MobileIdentity_tmsi:
         /* TMSI */
         for (ub = 0; ub < 4; ub++) {
            data.u.tmsi[ub] = ub + 1;
         }
         filename = "message_tmsi.dat";
         break;

      case T_TS24008IE_MobileIdentity_tmgi:
         /* TMGI */
         data.u.tmgi.mbmsSessIdInd = TRUE;
         data.u.tmgi.mccMncInd = TRUE;
         for (ub = 0; ub < 3; ub++) {
            data.u.tmgi.mbmsServiceID[ub] = ub + 1;
         }
         rtxStrcpy (data.u.tmgi.mcc_mnc.mcc,
                    sizeof(data.u.tmgi.mcc_mnc.mcc), "123");
         rtxStrcpy (data.u.tmgi.mcc_mnc.mnc,
                    sizeof(data.u.tmgi.mcc_mnc.mnc), "321");
         data.u.tmgi.mbmsSessionID = 127;
         filename = "message_tmgi.dat";
         break;

      default:;
      }

      /* Enable bit tracing */

      if (verbose) {
         rtxDiagCtxtBitFieldListInit (&ctxt);
      }

      /* Ecnode data */

      rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

      ret = NASEnc_TS24008IE_MobileIdentity (&ctxt, &data);
      if (0 != ret) {
         printf ("encode MobileIdentity failed; status = %d\n", ret);
         rtxErrPrint (&ctxt);
         return ret;
      }

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
   }

   rtxFreeContext (&ctxt);

   return 0;
}
