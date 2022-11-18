/**
 * Sample program to read ASN.1 in Abstract Value Notation and encode it
 * to PER.
 */
#include "Employee.h"
#include "rtxsrc/rtxCommon.h"

#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT      ctxt;
   OSBOOL      trace = TRUE, verbose = FALSE;
   OSBOOL      aligned = TRUE;
   const char* filename = "message.txt";
   const char* ofilename = "message.dat";
   int         i, stat;
   OSOCTET*     msgptr;
   int         len;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-a")) aligned = 1;
         else if (!strcmp (argv[i], "-u")) aligned = 0;
         else if (!strcmp (argv[i], "-u")) aligned = 0;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-o")) ofilename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-o <filename>] \n");
            printf ("   [-notrace] [-a|-u]\n");           
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");            
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

   /* Create file input stream */
   stat = rtxStreamFileCreateReader (&ctxt, filename);
   if (0 != stat) {
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   asn1Init_PersonnelRecord (&employee);

   /* Call compiler generated decode function */
   stat = asn1AvnDec_PersonnelRecord (&ctxt, &employee);
   if (stat != 0) {
      printf ("decode of data failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }

   rtxStreamClose(&ctxt);

   if (trace) {
      asn1Print_PersonnelRecord ("employee", &employee);
   }

   /* Encode message to PER */
   rtxSetDiag (&ctxt, verbose);
   pu_setBuffer (&ctxt, 0, 0, aligned);
   pu_setTrace (&ctxt, trace);
   
   if ((stat = asn1PE_PersonnelRecord (&ctxt, &employee)) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt, "employee");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return stat;
   }
     
   msgptr = pe_GetMsgPtr (&ctxt, &len);

   /* Write the encoded message out to the output file */

   stat = rtxFileWriteBinary (ofilename, msgptr, len);
   if (0 != stat) {
      printf ("Error writing encoded data to file %s\n", filename);
   }
   
   rtFreeContext (&ctxt);

   return 0;
}
