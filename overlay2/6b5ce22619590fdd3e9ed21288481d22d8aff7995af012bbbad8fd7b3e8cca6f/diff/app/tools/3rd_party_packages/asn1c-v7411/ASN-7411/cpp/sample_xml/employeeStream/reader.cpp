#include "Employee.h"
#include "rtxmlsrc/OSXMLDecodeBuffer.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

int main (int argc, char** argv)
{
   OSBOOL       trace = TRUE, verbose = FALSE;
   const char*  filename = "message.xml";
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

   // Create ASN.1 message objects
   OSXMLDecodeBuffer decodeBuffer (filename);
   decodeBuffer.setDiag (verbose);
   ASN1T_PersonnelRecord data;
   ASN1C_PersonnelRecord PersonnelRecordPDU (decodeBuffer, data);

   stat = PersonnelRecordPDU.Decode ();
   if (0 != stat) {
      decodeBuffer.printErrorInfo ();
      return stat;
   }
   printf ("Decode of data was successful\n");
   printf ("Decoded record:\n");
   PersonnelRecordPDU.Print ("PersonnelRecord");

   return (stat);
}
