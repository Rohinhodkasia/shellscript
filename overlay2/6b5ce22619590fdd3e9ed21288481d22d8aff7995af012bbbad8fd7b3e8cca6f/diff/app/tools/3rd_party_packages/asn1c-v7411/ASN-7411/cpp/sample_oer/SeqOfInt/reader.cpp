/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.2.A, Date: 13-Jun-2017.
 */
#include "Test.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

#define MAXREADLEN 1024

int main (int argc, char** argv)
{
   OSBOOL       trace = TRUE, verbose = FALSE;
   const char*  filename = "message.dat";
   int          i, stat;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   ASN1OERDecodeBuffer decodeBuffer;
   ASN1T_SeqOf10Ints data;
   ASN1C_SeqOf10Ints SeqOf10IntsPDU (decodeBuffer, data);
   decodeBuffer.setDiag (verbose);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus() != 0) {
      printf("Error opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   stat = SeqOf10IntsPDU.Decode ();
   if (stat != 0) {
      printf ("decode of PersonnelRecord failed\n");
      decodeBuffer.PrintErrorInfo ();
      return stat;
   }

   if (trace) {
      printf ("Decode of data was successful\n");
      printf ("Decoded record:\n");
      SeqOf10IntsPDU.Print ("SeqOf10Ints");
   }
   return 0;
}
