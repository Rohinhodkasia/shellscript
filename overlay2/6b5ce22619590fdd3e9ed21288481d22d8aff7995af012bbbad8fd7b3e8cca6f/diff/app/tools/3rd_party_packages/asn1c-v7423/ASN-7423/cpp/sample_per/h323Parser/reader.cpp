// This test driver program reads an encoded record from a file and 
// then invokes a compiler-generated parse function with a print handler 
// callback to print the contents of the message..

#include <stdio.h>
#include <stdlib.h>
#include "H323-MESSAGES.h"
#include "printHandler.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.bin";
   int          i, stat;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader -a | -u [ -v ] [ -i <filename> ]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Decode

   ASN1PERDecodeBuffer decodeBuffer (aligned);
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      decodeBuffer.printErrorInfo();
      return stat;
   }
   ASN1C_H225H323_UserInformation userInfo (decodeBuffer);

   // Create and register an event handler object

   Asn1NamedEventHandler* pHandler;
   if (trace)
      pHandler = new PrintHandler ("H323_UserInformation");
   else
      pHandler = new Asn1NullEventHandler64();

   decodeBuffer.addEventHandler (pHandler);

   // Call compiler generated parse function

   decodeBuffer.setTrace (trace);

   stat = userInfo.Parse ();

   delete pHandler;

   if (stat != 0) {
       printf ("parse failed\n");
       decodeBuffer.printErrorInfo ();
       return -1;
   }

   return 0;
}
