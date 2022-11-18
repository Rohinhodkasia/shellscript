// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   ASN1TAG      tag;
   int          i, stat;
   OSSIZE       len;
   const char*  filename = "message.dat";
   OSBOOL       indefLen, verbose = FALSE, trace = TRUE;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Read input file and decode 

   ASN1BERDecodeBuffer decodeBuffer;
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      printf ("Error reading message file %s\n", filename);
      decodeBuffer.printErrorInfo();
      return stat;
   }
   decodeBuffer.setDiag (verbose);

   stat = decodeBuffer.parseTagLen (tag, len, &indefLen);

   if (stat != 0) {
      printf ("decodeBuffer.parseTagLen failed\n");
      decodeBuffer.PrintErrorInfo ();
      return -1;
   }

   // Verify record is a personnel record

   if (tag == TV_PersonnelRecord) {

      // Decode

      ASN1T_PersonnelRecord msgData;
      ASN1C_PersonnelRecord employee (decodeBuffer, msgData);

      stat = employee.Decode ();

      if (stat == 0) {
         if (trace) {
            printf ("Decode of PersonnelRecord was successful\n");
            printf ("Decoded record:\n");
				employee.Print("Employee");
         }
      }
      else {
         printf ("decode of PersonnelRecord failed\n");
         decodeBuffer.PrintErrorInfo ();
         return -1;
      }
   }
   else {
      printf ("unexpected tag %hx received\n", tag);
      return -1;
   }

   return 0;
}
