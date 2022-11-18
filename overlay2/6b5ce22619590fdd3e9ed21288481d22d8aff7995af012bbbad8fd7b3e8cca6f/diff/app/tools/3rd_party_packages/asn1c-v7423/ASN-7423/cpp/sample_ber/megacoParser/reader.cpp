// This test driver program parses a BER-encoded file and uses a print 
// event handler to display the contents on stdout..

#include <stdio.h>
#include <stdlib.h>
#include "MEDIA-GATEWAY-CONTROL.h"
#include "printHandler.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int          i, stat;
   const char*  filename = "msg25.bin";
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

   // Read input file and parse

   ASN1BERDecodeBuffer decodeBuffer;
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      printf ("Error reading message file %s\n", filename);
      decodeBuffer.printErrorInfo();
      return stat;
   }
   decodeBuffer.setDiag (verbose);

   ASN1C_MegacoMessage mmPDU (decodeBuffer);

   // Create and register an event handler object

   PrintHandler* pHandler = new PrintHandler ("megaco");
   pHandler->setTrace (trace);
   decodeBuffer.addEventHandler (pHandler);

   // Decode

   stat = mmPDU.Parse (decodeBuffer);

   // Delete the event handler object

   delete pHandler;

   if (stat != 0) {
      printf ("parse of MegacoMessage failed\n");
      decodeBuffer.printErrorInfo ();
      return -1;
   }

   return 0;
}
