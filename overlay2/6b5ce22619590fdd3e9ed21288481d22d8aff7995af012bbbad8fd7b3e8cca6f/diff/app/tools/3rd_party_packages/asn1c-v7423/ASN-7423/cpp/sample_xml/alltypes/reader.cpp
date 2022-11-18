#include "Test.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char* argv[])
{
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE;
   int          i, stat;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename> ] [ -notrace ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read XML doc from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Create ASN.1 message objects
   ASN1T_TestType testData;
   OSXMLDecodeBuffer decodeBuffer (filename);
   decodeBuffer.setDiag (verbose);
   ASN1C_TestType testC (decodeBuffer, testData);

   stat = testC.Decode ();

   if (0 == stat) {
      if (trace) testC.Print ("testData");
   }
   else {
      decodeBuffer.printErrorInfo ();
   }

   return (stat);

}
