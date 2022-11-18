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
   TS44018IE_SI18_Rest_Octets value;
   TS44018IE_SI18_Rest_Octets* pvalue = &value;
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

   asn1Init_TS44018IE_SI18_Rest_Octets (pvalue);
   pvalue->si18_change_mark = 2;

   pvalue->si18_index = 4;

   pvalue->si18_last = 0;

   pvalue->non_GSM_Message.non_GSM_Protocol_Discriminator = 4;
   pvalue->non_GSM_Message.nr_of_container_octets = 3;
   pvalue->non_GSM_Message.component_3.u.choice_2.container.n = 3;
   pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[0] = 236;
   pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[1] = 19;
   pvalue->non_GSM_Message.component_3.u.choice_2.container.elem[2] = 66;

   pvalue->non_GSM_Message.component_3.u.choice_2.m.non_GSM_Message_structPresent = 1;
   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct = rtxMemAllocTypeZ (pctxt, TS44018IE_Non_GSM_Message_struct);

   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->non_GSM_Protocol_Discriminator = 2;

   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets = 2;
   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.n = 2;
   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[0] = 146;
   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[1] = 253;
   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.container.elem[2] = 106;

   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.m.non_GSM_Message_structPresent = 1;
   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct = rtxMemAllocTypeZ (pctxt, TS44018IE_Non_GSM_Message_struct);

   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->non_GSM_Protocol_Discriminator = 1;

   pvalue->non_GSM_Message.component_3.u.choice_2.non_GSM_Message_struct->component_3.u.choice_2.non_GSM_Message_struct->nr_of_container_octets = 0;


   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Ecnode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS44018IE_SI18_Rest_Octets (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode SI18_Rest_Octets failed; status = %d\n", ret);
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
