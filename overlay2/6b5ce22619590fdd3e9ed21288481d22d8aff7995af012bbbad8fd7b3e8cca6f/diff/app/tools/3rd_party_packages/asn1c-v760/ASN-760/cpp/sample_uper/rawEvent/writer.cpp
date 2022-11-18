#include "wr.h"
#include "rtsrc/rtPrint.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   OSSIZE     len;
   int        i, stat;
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

   /* Create an instance of the compiler generated class.
      This example uses a dynamic message buffer. */
   ASN1PEREncodeBuffer encodeBuffer (aligned);

   ASN1T_PDU data;
   ASN1C_PDU PDUPDU (encodeBuffer, data);

   data.aseq.eeny = FALSE;
   data.aseq.meeny = TRUE;
   data.aseq.mineymoe.t = T_PDU_aseq_mineymoe_jane;
   data.aseq.mineymoe.u.jane = TRUE;
   
   data.record.a = TRUE;
   data.record.b = FALSE;
   
   {
      ASN1C__SeqOfValueTable helper (encodeBuffer, data.values);
      ASN1T_ValueTable* pval;
      
      pval = helper.AppendNewElement();
      pval->id = 300;
      pval->data.t = Arguments::T_Arguments_3;
      pval->data.u._Arguments_3 = 5;
      
      pval = helper.AppendNewElement();
      pval->id = 200;
      pval->data.t = Arguments::T_Arguments_2;
      pval->data.u._Arguments_2 = new_ASN1T_Record2(PDUPDU);
      pval->data.u._Arguments_2->a = 1996;
      pval->data.u._Arguments_2->b = 2016;
      
      pval = helper.AppendNewElement();
      pval->id = 100;
      pval->data.t = Arguments::T_Arguments_1;
      pval->data.u._Arguments_1 = new_ASN1T_Record(PDUPDU);
      pval->data.u._Arguments_1->a = TRUE;
      pval->data.u._Arguments_1->b = TRUE;
   }
   

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_PDU ("data", &data);
      printf ("\n");
   }
   
   /* Encode */
   encodeBuffer.setTrace (trace);
   encodeBuffer.setDiag (verbose);

   if ((stat = PDUPDU.Encode ()) == 0)
   {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.getMsgLen ();
   }
   else
   {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }
   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      encodeBuffer.printErrorInfo();
      return stat;
   }

   return 0;
}
