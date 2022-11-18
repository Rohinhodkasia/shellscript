// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/osMacros.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln);

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSSIZE       len;
   int          i, stat;
   FILE*        fp;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -a | -u ][ -v ] [ -o <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Create an instance of the compiler generated class.  This
   // example uses a static message buffer..

   ASN1PEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf), aligned);
   encodeBuffer.setDiag (verbose);
   ASN1T_PersonnelRecord msgData;
   ASN1C_PersonnelRecord employee (encodeBuffer, msgData);

   // Populate structure of generated type

   ASN1T_ChildInformation* pChildInfo;

   fill_Name (&msgData.name, "John", "P", "Smith");

   msgData.title  = OSUTF8("Director");
   msgData.number = 51;
   msgData.dateOfHire = OSUTF8("19710917");

   fill_Name (&msgData.nameOfSpouse, "Mary", "T", "Smith");

   // fill first child record

   pChildInfo = employee.new_children_element();
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = OSUTF8("19571111");
   employee.append_to_children (pChildInfo);

   // fill second child record

   pChildInfo = employee.new_children_element();
   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = OSUTF8("19590717");
   employee.append_to_children (pChildInfo);

   // Encode

   encodeBuffer.setTrace (trace);

   if ((stat = employee.Encode ()) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
         printf ("Binary dump:\n");
         encodeBuffer.binDump ("employee");
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.getMsgLen ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      exit (-1);
   }
  
   // Write the encoded message out to the output file 

   if (fp = fopen (filename, "wb")) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   return 0;
}

// Routine to fill a name structure

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln)
{
   pName->givenName = OSUTF8(fn);
   pName->initial = OSUTF8(mi);
   pName->familyName = OSUTF8(ln);
}

