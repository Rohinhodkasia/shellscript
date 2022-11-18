#include "TAP-0302.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

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
   ASN1T_DataInterChange tap3;
   OSXMLDecodeBuffer decodeBuffer (filename);
   ASN1C_DataInterChange tap3C (decodeBuffer, tap3);

   stat = tap3C.Decode ();

   if (0 == stat) {
      if (trace) tap3C.Print ("tap3");
   }
   else {
      decodeBuffer.printErrorInfo ();
   }

   return (stat);

}
