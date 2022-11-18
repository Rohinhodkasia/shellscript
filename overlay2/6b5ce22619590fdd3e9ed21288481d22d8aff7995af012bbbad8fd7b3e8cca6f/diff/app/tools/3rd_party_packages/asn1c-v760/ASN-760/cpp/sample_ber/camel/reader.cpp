#include "CAP-datatypes.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>
#include "rtPrintStream.h" 

static void writeToStdout
(void* pPrntStrmInfo, const char* fmtspec, va_list arglist) 
{
   vprintf (fmtspec, arglist);
   return;
}

#define MAXREADLEN 1024

int main (int argc, char** argv)
{
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int         i, stat;

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

   ASN1BERDecodeBuffer decodeBuffer;
   ASN1T_Component component;
   ASN1C_Component ComponentPDU (decodeBuffer, component);

   // Read from input file

   decodeBuffer.setDiag (verbose);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus () != 0) {
      printf("Failed opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   ComponentPDU.setPrintStream (&writeToStdout, (void*)0);

   // Decode Component 

   stat = ComponentPDU.Decode ();
   if (stat != 0) {
      printf ("decode failed\n");
      decodeBuffer.PrintErrorInfo ();
      return stat;
   }
   printf ("Decode of Component was successful\n");
   printf ("Decoded record:\n");
   ComponentPDU.Print ("Component");
   printf ("\n***\n");

   // Decode CallResult

   const OSOCTET* pConstData = 
      component.u.returnResultLast->resultretres.returnparameter.data;
   OSSIZE len = 
      component.u.returnResultLast->resultretres.returnparameter.numocts;
   ASN1BERDecodeBuffer decodeBuffer2 (pConstData, len);
   ASN1T_CallResult callResult;
   ASN1C_CallResult callResultC (decodeBuffer2, callResult);

   stat = callResultC.Decode ();
   if (stat != 0) {
      printf ("decode failed\n");
      decodeBuffer2.PrintErrorInfo ();
      return stat;
   }
   printf ("Decode of CallResult was successful\n");
   printf ("Decoded record:\n");
   callResultC.Print ("CallResult");
   
   return 0;
}
