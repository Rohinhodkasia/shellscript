/**
* Sample program to read multiple ASN.1 records in Abstract Value Notation.
*/
#include "Employee.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/OSRTFileInputStream.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   OSBOOL       trace = TRUE, verbose = FALSE;
   const char*  filename = "message.txt";
   int          i, stat;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] \n");
            printf ("   [-notrace] \n");           
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");            
            return 1;
         }
      }
   }

   // Create ASN.1 message objects
   OSRTFileInputStream istream(filename);
   ASN1AVNDecodeBuffer decodeBuffer (istream);
   decodeBuffer.setDiag (verbose);
   ASN1T_PersonnelRecord data;
   ASN1C_PersonnelRecord personnelRecordPDU (decodeBuffer, data);

   for(;;) {
      stat = personnelRecordPDU.Decode ();
      if (0 != stat) {
         decodeBuffer.printErrorInfo ();
         return stat;
      }
         
      printf ("Decode of data was successful\n");
      printf ("Decoded record:\n");
      personnelRecordPDU.Print ("PersonnelRecord");
      
       /* Skip any whitespace */
      stat = rtxTxtSkipWhitespace(decodeBuffer.getCtxtPtr());
      if (stat != 0) break;

      /* If any input remains, decode another record, otherwise break.
         We look for RTERR_ENDOFFILE because we're using a stream.  If
         we were just using a buffer, we'd look for RTERR_ENDOFBUF instead. */
      stat = rtxCheckInputBuffer(decodeBuffer.getCtxtPtr(), 1);
      if (stat == RTERR_ENDOFFILE) { stat = 0;  break; }
      else if ( stat != 0 ) break;      
      
      /* Release memory used by current record */
      personnelRecordPDU.memReset();
   }  
   
   return (stat);
}
