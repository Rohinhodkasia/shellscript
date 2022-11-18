/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include "TS44018Msgs.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrintStream.h"

/**
 * Decodes the SI 3 Rest Octets from an SI Type 3 message.
 * @param pmsg Pointer to the SI Type 3 message.
 * @param pdata Pointer to the SI 3 Rest Octets data, represented as octets.
 * @param pRestOctets object to receive the decoded SI 3 Rest Octets data.
 */
int Dec_SI3_Rest_Octets( OSCTXT* pctxt, 
   TS44018Msg_SystemInformationType3* pmsg,
   TS44018IE_SI3_Rest_Octets_Data* pdata,
   TS44018IE_SI3_Rest_Octets* pRestOctets )
{
   int ret;
   OSBOOL iuModeSupported;

   /* cast away the const-ness of data; decoding from it won't modify it anyway.
   */
   ret = rtxCtxtSetBufPtr(pctxt, (OSOCTET*)pdata->data.data, 
                           pdata->data.numocts);
   if ( ret < 0 ) return LOG_RTERR(pctxt, ret);

   /* set iuModeSupported.  I am not sure whether cbq3 == 1 
      ("Iu mode capable MSs barred") counts as Iu mode supported or not.
      We're just assuming here that it does.
   */
   iuModeSupported = pmsg->controlChannelDescription.cbq3 != 0;

   return NASDec_TS44018IE_SI3_Rest_Octets(pctxt, pRestOctets, iuModeSupported);
}

int main (int argc, char** argv)
{
   TS44018Msg_L2_PSEUDO_LEN_PDU data;
   OSCTXT	ctxt;
   OSOCTET*     msgbuf;
   const char*  filename = "message.dat";
   int          i, ret;
   OSSIZE       len;
   OSBOOL       verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: reader [-v]\n");
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

   if (verbose) {
      printf ("\nReading message file %s..\n", filename);
   }
   /* Read input file into a memory buffer */

   ret = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
   if (0 != ret) {
      printf ("Error opening %s for read access\n", filename);
      rtxErrPrint (&ctxt);
      return ret;
   }

   /* Set message buffer pointer */

   ret = rtxCtxtSetBufPtr (&ctxt, msgbuf, len);
   if (0 != ret) {
      printf ("rtxCtxtSetBufPtr failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Call decode function */

   ret = NASDec_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, &data);

   if (verbose) {
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   if (0 != ret) {
      printf ("decode PDU failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
   }

   /* Print fields */

   if (verbose) {
      /* Register print-to-stream callback function */
      rtxSetPrintStream (&ctxt, &rtxPrintStreamToStdoutCB, 0);

      /* Invoke generated print-to-stream function */
      asn1PrtToStrm_TS44018Msg_L2_PSEUDO_LEN_PDU (&ctxt, "PDU", &data);
   }

   {
      /* now decode the SI 3 Rest Octets */

      TS44018IE_SI3_Rest_Octets si3;     

      ret = Dec_SI3_Rest_Octets(&ctxt, data.data.u.obj_SystemInformationType3, 
            data.restOctets.u.obj_SystemInformationType3, &si3);
      if ( ret != 0 ) {
         printf ("decode SI 3 Rest Octets failed; status = %d\n", ret);
         rtxErrPrint (&ctxt);
      }
      if ( verbose )
         asn1PrtToStrm_TS44018IE_SI3_Rest_Octets(&ctxt, "SI 3 Rest Octets", &si3);
   }

   rtxFreeContext (&ctxt);

   return 0;
}
