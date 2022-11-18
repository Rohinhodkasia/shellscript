// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "printHandler.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static void print_PersonnelRecord (ASN1T_PersonnelRecord* pPR);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSOCTET      msgbuf[MAXMSGLEN];
   OSBOOL       verbose = FALSE, trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int          i, stat;
   OSSIZE       len;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename> ] [ -notrace ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Read input file into a memory buffer

   if (fp = fopen (filename, "rb")) {
      len = fread (msgbuf, 1, sizeof(msgbuf), fp);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   ASN1BERDecodeBuffer decodeBuffer (msgbuf, len);
   decodeBuffer.setDiag (verbose);
   ASN1T_PersonnelRecord employee;
   ASN1C_PersonnelRecord employeePDU (decodeBuffer, employee);

   // Create and register an event handler object

   PrintHandler* pHandler = new PrintHandler ("employee");
   pHandler->setTrace (trace);
   decodeBuffer.addEventHandler (pHandler);

   // Decode

   stat = employeePDU.Decode ();

   // Delete the event handler object

   delete pHandler;

   if (stat != 0) {
      printf ("decode of PersonnelRecord failed\n");
      decodeBuffer.printErrorInfo ();
      return -1;
   }

   return 0;
}
