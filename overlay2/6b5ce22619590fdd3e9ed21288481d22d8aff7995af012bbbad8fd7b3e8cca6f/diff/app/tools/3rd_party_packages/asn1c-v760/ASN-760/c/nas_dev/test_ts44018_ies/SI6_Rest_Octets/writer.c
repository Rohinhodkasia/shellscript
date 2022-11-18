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
   TS44018IE_SI6_Rest_Octets value;
   TS44018IE_SI6_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_SI6_Rest_Octets (pvalue);

   pvalue->m.pch_and_NCH_infoPresent = 1;

   pvalue->pch_and_NCH_info.paging_channel_restructuring.t =  2;

   pvalue->pch_and_NCH_info.nln_sacch = 2;

   pvalue->pch_and_NCH_info.m.call_priorityPresent = 1;
   pvalue->pch_and_NCH_info.call_priority = 0;

   pvalue->pch_and_NCH_info.nln_status_SACCH = 0;

   pvalue->m.vbs_VGCS_optionsPresent = 1;
   pvalue->vbs_VGCS_options = 1;

   pvalue->m.component_3Present = 1;

   pvalue->component_3.rac = 44;

   pvalue->component_3.max_LAPDm = 3;

   pvalue->band_indicator = TS44018IE_LHType_lbit;

   pvalue->m.gprs_ms_txpwr_max_cchPresent = 1;
   pvalue->gprs_ms_txpwr_max_cch = 29;

   pvalue->m.component_6Present = 1;

   pvalue->component_6.dedicated_mode_mbms_notification_support = 0;

   pvalue->component_6.mnci_support = 0;

   pvalue->m.component_7Present = 1;

   pvalue->component_7.m.amr_ConfigPresent = 0;


   pvalue->m.random_bit_streamPresent = 1;

   /* random_bit_stream should be populated to achieve byte-alignment.
   First, I will encode with 0 bits.  I'll detect the error and use the 
   buffer bit offset to determine how many bits I should use.
   */
      
   pvalue->random_bit_stream.numbits = 0;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI6_Rest_Octets (&ctxt, pvalue);
   if ( ret == ASN_E_BAD_ALIGN ) {
      printf("Bad alignment detected as expected.\n");
      /* pctxt->buffer.bitOffset % 8 gives me the number of bits needed */
      pvalue->random_bit_stream.numbits = pctxt->buffer.bitOffset % 8;      
      {
         OSOCTET* bitData = (OSOCTET*) rtxMemAlloc (pctxt,1);
         bitData[0] = 0x58;
         pvalue->random_bit_stream.data = (const OSOCTET*)bitData;
      }
      if (verbose) {
         rtxDiagCtxtBitFieldListInit (&ctxt);
      }

      rtxErrReset(&ctxt);
      rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

      ret = NASEnc_TS44018IE_SI6_Rest_Octets (&ctxt, pvalue);
   }
   else {
      printf ("Bad alignment error not encountered as expected; status = %d\n",
         ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   if (0 != ret) {
      printf ("encode SI6_Rest_Octets failed; status = %d\n", ret);
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
