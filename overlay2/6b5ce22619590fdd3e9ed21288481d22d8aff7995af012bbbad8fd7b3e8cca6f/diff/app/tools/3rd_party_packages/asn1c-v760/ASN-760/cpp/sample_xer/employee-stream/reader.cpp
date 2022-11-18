#include "rtxsrc/OSRTFileInputStream.h"
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char* argv[])
{
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE;
   int          stat = 0;

   /* Process command line arguments */

   if (argc > 1) {
      for (int i = 1; i < argc; i++) {
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

   OSRTFileInputStream fs (filename); 
   OSXMLDecodeBuffer is (fs);

   if (is.getStatus () != 0) {
      is.printErrorInfo ();
      return -1;
   }

   // Create ASN.1 message objects
   ASN1T_PersonnelRecord employee;
   ASN1C_PersonnelRecord employeeC (is, employee);

   employeeC.DecodeFrom(is);

   if (is.getStatus () == 0) {
      if (trace) employeeC.Print ("employee");
   }
   else {
      is.printErrorInfo ();
   }

   return (stat);
}
