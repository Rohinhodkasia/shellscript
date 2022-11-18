// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#include "rtjsonsrc/rtJsonCppMsgBuf.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int		i, stat;
   const char*  filename = "message.json";
   OSBOOL       verbose = FALSE, trace = TRUE;

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

   // Create ASN.1 message objects
   OSJSONDecodeBuffer decodeBuffer (filename);
   decodeBuffer.setDiag (verbose);

   ASN1T_PersonnelRecord data;
   ASN1C_PersonnelRecord PersonnelRecordPDU (decodeBuffer, data);

   // Decode
   stat = PersonnelRecordPDU.Decode ();
   if (0 != stat) {
      decodeBuffer.printErrorInfo ();
      return stat;
   }

   // Print results
   printf ("Decode of data was successful\n");
   printf ("Decoded record:\n");
   PersonnelRecordPDU.Print ("PersonnelRecord");

   return stat;
}
