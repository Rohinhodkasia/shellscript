/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include "TS44018Msgs.h"
#include "TS44018Misc.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrintStream.h"

int main (int argc, char** argv)
{
   TS44018Msg_DL_DCCH_PDU data;
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

   ret = NASDec_TS44018Msg_DL_DCCH_PDU (&ctxt, &data);

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
      asn1PrtToStrm_TS44018Msg_DL_DCCH_PDU (&ctxt, "PDU", &data);

      { 
         OSUINT16* arfcns;
         OSUINT16 arfcnCount;
         
         ret = TS44018IE_Frequency_List_decodeARFCN( 
                  &ctxt, &data.data.u.obj_AssignmentCommand->freqListAfterTime,
                  &arfcns, &arfcnCount);

         if ( ret < 0 ) {
            printf ("decode freqListAfterTime ARFCNs failed; status = %d\n", ret);
            rtxErrPrint (&ctxt);
         }
         else {
            printf("freqListAfterTime ARFCN list = ");
            TS44018IE_printArfcns(arfcns, arfcnCount);
            printf("\n");
         }
      }

      { 
         TS44018Msg_AssignmentCommand* pvalue;
         OSUINT16* arfcns;
         OSUINT16 arfcnCount;
         
         pvalue = data.data.u.obj_AssignmentCommand;

         ret = TS44018IE_Cell_Channel_Description_decodeARFCN( 
                  &ctxt, &pvalue->cellChannelDesc, &arfcns, &arfcnCount);

         if ( ret < 0 ) {
            printf ("decode cellChannelDesc ARFCNs failed; status = %d\n", ret);
            rtxErrPrint (&ctxt);
         }
         else {
            printf("cellChannelDesc ARFCN list = ");
            TS44018IE_printArfcns(arfcns, arfcnCount);
            printf("\n");
         }
      }

      { 
         OSUINT16* arfcns;
         OSUINT16 arfcnCount;
         
         ret = TS44018IE_Frequency_List_decodeARFCN( 
                  &ctxt, &data.data.u.obj_AssignmentCommand->frequencyListBeforeTime,
                  &arfcns, &arfcnCount);

         if ( ret < 0 ) {
            printf ("decode frequencyListBeforeTime ARFCNs failed; status = %d\n", ret);
            rtxErrPrint (&ctxt);
         }
         else {
            printf("frequencyListBeforeTime ARFCN list = ");
            TS44018IE_printArfcns(arfcns, arfcnCount);
            printf("\n");
         }
      }

   }

   rtxFreeContext (&ctxt);

   return 0;
}
