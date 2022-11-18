/**
 * Sample program to read multiple ASN.1 records in Abstract Value Notation.
 */
#include "Employee.h"
#include "rtxsrc/rtxCommon.h"

#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT      ctxt;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.txt";
   int         i, stat;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>]\n");
            printf ("   [-notrace] \n");           
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
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


   for(;;) {
      
      /* Decode a record. */
      asn1Init_PersonnelRecord (&employee);

      /* Call compiler generated decode function */
      stat = asn1AvnDec_PersonnelRecord (&ctxt, &employee);
      if ( stat != 0 ) break;
      
      if (trace) {
         asn1Print_PersonnelRecord ("employee", &employee);
      }    
   
       /* Skip any whitespace */
      stat = rtxTxtSkipWhitespace(&ctxt);
      if (stat != 0) break;

      /* If any input remains, decode another record, otherwise break.
         We look for RTERR_ENDOFFILE because we're using a stream.  If
         we were just using a buffer, we'd look for RTERR_ENDOFBUF instead. */
      stat = rtxCheckInputBuffer(&ctxt, 1);
      if (stat == RTERR_ENDOFFILE) { stat = 0;  break; }
      else if ( stat != 0 ) break;      
      
      /* Release memory used by current record */
      rtxMemReset(&ctxt);
   }
         
   if (stat != 0) {
      printf ("Error.\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }

   rtxStreamClose(&ctxt);
   
   rtFreeContext (&ctxt);

   return 0;
}
