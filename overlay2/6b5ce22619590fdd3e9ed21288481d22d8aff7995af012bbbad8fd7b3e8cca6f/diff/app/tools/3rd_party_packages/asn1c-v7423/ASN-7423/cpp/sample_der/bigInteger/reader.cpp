// This test driver program reads an encoded record from a file
// and decodes it and displays the results..                            

#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int          i, stat;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Decode 

   ASN1BERDecodeBuffer decodeBuffer;
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      printf ("Error reading message file %s\n", filename);
      decodeBuffer.printErrorInfo();
      return stat;
   }
   ASN1T_Dss_Parms dss;
   ASN1C_Dss_Parms dssC (decodeBuffer, dss);

   stat = dssC.Decode ();

   if (stat == 0) {
      if (trace) {
         printf ("Decode of BigIntType was successful\n");
         printf ("Decoded record:\n");
         dssC.Print ("bigInteger");
      }
   }
   else {
      printf ("decode of BigIntType failed\n");
      decodeBuffer.PrintErrorInfo ();
      exit (-1);
   }

   return 0;
}
