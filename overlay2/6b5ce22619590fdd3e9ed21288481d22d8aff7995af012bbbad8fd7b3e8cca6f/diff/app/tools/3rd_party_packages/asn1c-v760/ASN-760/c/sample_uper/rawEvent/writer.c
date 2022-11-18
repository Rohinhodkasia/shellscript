#include "wr.h"
#include "rtsrc/rtPrint.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxCommon.h"

#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   /* PDU: RawEvents.PDU */
   PDU* pdata;
   OSCTXT     ctxt;
   int        i, len, stat;
   OSBOOL     aligned = TRUE;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.per";
   const OSOCTET* msgptr;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) {
            aligned = FALSE;
            filename = "message.uper";
         }
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [-v] [-o <filename>]  [-notrace]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);
   pu_setBuffer (&ctxt, 0, 0, aligned);
   pu_setTrace (&ctxt, trace);

   pdata = rtxMemAllocTypeZ (&ctxt, PDU);
   asn1Init_PDU(pdata);
   
   pdata->aseq.eeny = FALSE;
   pdata->aseq.meeny = TRUE;
   pdata->aseq.mineymoe.t = T_PDU_aseq_mineymoe_jane;
   pdata->aseq.mineymoe.u.jane = TRUE;
   

   pdata->record.a = TRUE;
   pdata->record.b = FALSE;
   
   
   rtxDListInit(&pdata->values);
   {
      ValueTable* pval;
      Record* prec;
      Record2* prec2;
      
      pval = rtxMemAllocType(&ctxt, ValueTable);
      rtxDListAppend(&ctxt, &pdata->values, pval);
      pval->id = 300;
      pval->data.t = T_RawEvents_Arguments_Arguments_3;
      pval->data.u._Arguments_3 = 5;
     
      pval = rtxMemAllocType(&ctxt, ValueTable);
      rtxDListAppend(&ctxt, &pdata->values, pval);
      pval->id = 200;
      pval->data.t = T_RawEvents_Arguments_Arguments_2;
      
      prec2 = rtxMemAllocType(&ctxt, Record2);
      pval->data.u._Arguments_2 = prec2;
      prec2->a = 1996;
      prec2->b = 2016;
      
      pval = rtxMemAllocType(&ctxt, ValueTable);
      rtxDListAppend(&ctxt, &pdata->values, pval);
      pval->id = 100;
      pval->data.t = T_RawEvents_Arguments_Arguments_1;
      
      prec = rtxMemAllocType(&ctxt, Record);
      pval->data.u._Arguments_1 = prec;
      prec2->a = TRUE;
      prec2->b = FALSE;     
   }
   
   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_PDU ("data", pdata);
      printf ("\n");
   }

   /* Encode */
   stat = asn1PE_PDU (&ctxt, pdata);

   msgptr = pe_GetMsgPtr (&ctxt, &len);

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
   }
   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }
   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   rtFreeContext (&ctxt);

   return 0;
}
