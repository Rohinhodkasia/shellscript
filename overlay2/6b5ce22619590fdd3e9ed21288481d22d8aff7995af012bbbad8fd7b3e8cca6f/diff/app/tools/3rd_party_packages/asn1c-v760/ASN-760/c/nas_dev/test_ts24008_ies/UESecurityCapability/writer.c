#include "TS24301IES.h"
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
   TS24301IE_UESecurityCapability* pvalue;
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

   pvalue = rtxMemAllocType (&ctxt, TS24301IE_UESecurityCapability);
   asn1Init_TS24301IE_UESecurityCapability (pvalue);

   pvalue->length = 10;

   pvalue->epsEncryptAlgs.eea0 = 1;
   pvalue->epsEncryptAlgs.x128_eea1 = 1;
   pvalue->epsEncryptAlgs.x128_eea2 = 1;
   pvalue->epsEncryptAlgs.eea3 = 0;
   pvalue->epsEncryptAlgs.eea4 = 0;
   pvalue->epsEncryptAlgs.eea5 = 0;
   pvalue->epsEncryptAlgs.eea6 = 1;
   pvalue->epsEncryptAlgs.eea7 = 0;

   pvalue->epsIntegAlgs.eia0 = 1;
   pvalue->epsIntegAlgs.eia1 = 1;
   pvalue->epsIntegAlgs.eia2 = 0;
   pvalue->epsIntegAlgs.eia3 = 0;
   pvalue->epsIntegAlgs.eia4 = 1;
   pvalue->epsIntegAlgs.eia5 = 1;
   pvalue->epsIntegAlgs.eia6 = 0;
   pvalue->epsIntegAlgs.eia7 = 0;

   pvalue->m.umtsEncryptAlgsPresent = 1;
   pvalue->umtsEncryptAlgs.uea0 = 1;
   pvalue->umtsEncryptAlgs.uea1 = 0;
   pvalue->umtsEncryptAlgs.uea2 = 0;
   pvalue->umtsEncryptAlgs.uea3 = 0;
   pvalue->umtsEncryptAlgs.uea4 = 1;
   pvalue->umtsEncryptAlgs.uea5 = 1;
   pvalue->umtsEncryptAlgs.uea6 = 0;
   pvalue->umtsEncryptAlgs.uea7 = 0;

   pvalue->m.octet6Present = 1;
   pvalue->octet6.spare = 1;
   pvalue->octet6.umtsIntegAlgs.uia1 = 0;
   pvalue->octet6.umtsIntegAlgs.uia2 = 1;
   pvalue->octet6.umtsIntegAlgs.uia3 = 0;
   pvalue->octet6.umtsIntegAlgs.uia4 = 0;
   pvalue->octet6.umtsIntegAlgs.uia5 = 0;
   pvalue->octet6.umtsIntegAlgs.uia6 = 1;
   pvalue->octet6.umtsIntegAlgs.uia7 = 0;

   pvalue->m.octet7Present = 1;
   pvalue->octet7.spare = 1;
   pvalue->octet7.gprsIntegAlgs.gea1 = 1;
   pvalue->octet7.gprsIntegAlgs.gea2 = 1;
   pvalue->octet7.gprsIntegAlgs.gea3 = 0;
   pvalue->octet7.gprsIntegAlgs.gea4 = 1;
   pvalue->octet7.gprsIntegAlgs.gea5 = 0;
   pvalue->octet7.gprsIntegAlgs.gea6 = 0;
   pvalue->octet7.gprsIntegAlgs.gea7 = 1;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24301IE_UESecurityCapability (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode UESecurityCapability failed; status = %d\n", ret);
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

   rtxFreeContext (&ctxt);

   return 0;
}
