// This test driver program reads an encoded record from a file         
// and decodes it and displays the results..                            

#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE;
   int          i, stat;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -i <filename> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Create ASN.1 message objects
   OSXMLDecodeBuffer decodeBuffer (filename);
   decodeBuffer.setDiag (verbose);
   ASN1T_Dss_Parms msgData;
   ASN1C_Dss_Parms dss (decodeBuffer, msgData);

   stat = dss.Decode ();

   if (0 == stat) {
      if (trace) dss.Print ("dss");
   }
   else {
      decodeBuffer.printErrorInfo ();
   }

   return (stat);

}
