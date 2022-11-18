// This test driver program reads an encoded record from a file 
// and decodes it and displays the results.

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtbersrc/ASN1BERDecodeStream.h"
#include "rtxsrc/OSRTFileInputStream.h"
#include "rtxsrc/rtxMemLeakCheck.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   ASN1TAG	tag;
   int		i, len;
   const char*  filename = "message.dat";
   OSBOOL       trace = TRUE;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) rtxSetGlobalDiag (1);
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Decode 

   ASN1BERDecodeStream in (new OSRTFileInputStream (filename));

   if (in.getStatus () != 0) {
      in.printErrorInfo ();
      return -1;
   }

   if (in.peekTagAndLen (tag, len) != 0) {
      printf ("peekTagAndLen failed\n");
      in.printErrorInfo ();
      return -1;
   }

   // Verify record is a personnel record

   if (tag == TV_PersonnelRecord) {

      // Decode
      
      ASN1T_PersonnelRecord msgData;
      ASN1C_PersonnelRecord employee (in, msgData);

      in >> employee;
      if (in.getStatus () != 0) {
         printf ("decode of PersonnelRecord failed\n");
         in.printErrorInfo ();
         return -1;
      }

      if (trace) {
         printf ("Decode of PersonnelRecord was successful\n");
         printf ("Decoded record:\n");
         employee.Print("Employee");
      }
   }
   else {
      printf ("unexpected tag %hx received\n", tag);
      return -1;
   }

   return 0;
}
