// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "printHandler.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.dat";
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
   ASN1T_PersonnelRecord employee;
   ASN1C_PersonnelRecord employeePDU (decodeBuffer, employee);

   // Create and register an event handler object

   Asn1NamedEventHandler* pHandler;
   if (trace)
      pHandler = new PrintHandler ("employee");
   else
      pHandler = new Asn1NullEventHandler64();

   decodeBuffer.addEventHandler (pHandler);

   // Decode

   decodeBuffer.setTrace (trace);

   stat = employeePDU.Decode ();

   // Delete the event handler object

   delete pHandler;

   if (trace) {
      printf ("\n");
      printf ("Dump of decoded bit fields:\n");
      decodeBuffer.binDump ("employee");
      printf ("\n");
   }

   if (stat != 0) {
      printf ("decode of PersonnelRecord failed\n");
      decodeBuffer.printErrorInfo ();
      exit (-1);
   }

   return 0;
}
