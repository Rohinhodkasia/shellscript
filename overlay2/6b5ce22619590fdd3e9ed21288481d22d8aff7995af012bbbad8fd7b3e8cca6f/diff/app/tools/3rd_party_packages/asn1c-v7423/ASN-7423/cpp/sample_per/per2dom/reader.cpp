// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "domHandler.h"
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
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-a")) ; /* just skip */
         else if (!strcmp (argv[i], "-u")) ; /* just skip */
         else {
            printf ("usage: reader [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Read input file into a memory buffer

   ASN1PERDecodeBuffer decodeBuffer (aligned);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus() != 0) {
      printf("Error opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   ASN1C_PersonnelRecord employeePDU (decodeBuffer);

   // Create and register an event handler object

   DOMHandler* pHandler = 
      new DOMHandler (decodeBuffer.getCtxtPtr(), "employee");

   decodeBuffer.addEventHandler (pHandler);

   // Decode

   decodeBuffer.SetTrace (trace);

   stat = employeePDU.Parse ();

   const char* firstNameOfSpouse =
      pHandler->getTree().getValue ("employee.nameOfSpouse.givenName");

   if (0 != firstNameOfSpouse && trace) {
      printf ("First name of employee's spouse is %s\n", firstNameOfSpouse);
   }

   delete pHandler;

   if (stat != 0) {
      printf ("decode of PersonnelRecord failed\n");
      decodeBuffer.PrintErrorInfo ();
      exit (-1);
   }

   return 0;
}
