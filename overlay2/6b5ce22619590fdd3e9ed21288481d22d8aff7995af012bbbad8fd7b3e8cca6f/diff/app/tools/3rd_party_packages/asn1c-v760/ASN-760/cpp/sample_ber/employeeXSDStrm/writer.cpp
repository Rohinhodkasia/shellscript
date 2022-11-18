// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtbersrc/ASN1BEREncodeStream.h"
#include "rtxsrc/osMacros.h"
#include "rtxsrc/OSRTFileOutputStream.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln);

int main (int argc, char** argv)
{
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments 

   if (argc > 1) {
      for (int i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   ASN1BEREncodeStream out (new OSRTFileOutputStream (filename));

   if (out.getStatus () != 0) {
      out.printErrorInfo ();
      return -1;
   }
   out.setDiag (verbose);

   // Create an instance of the compiler generated class.  This
   // example uses a static message buffer..

   ASN1T_PersonnelRecord msgData;
   ASN1C_PersonnelRecord employee (out, msgData);

   // Populate structure of generated type

   ASN1T_ChildInformation* pChildInfo;

   fill_Name (&msgData.name, "John", "P", "Smith");

   msgData.title  = OSUTF8("Director");
   msgData.number = 51;
   msgData.dateOfHire = OSUTF8("19710917");

   fill_Name (&msgData.nameOfSpouse, "Mary", "T", "Smith");

   // fill first child record

   void* pdata = employee.memAlloc (sizeof(ASN1T_ChildInformation));
   pChildInfo = new (pdata) ASN1T_ChildInformation();
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = OSUTF8("19571111");
   employee.append (msgData.children, pChildInfo);

   // fill second child record

   pdata = employee.memAlloc (sizeof(ASN1T_ChildInformation));
   pChildInfo = new (pdata) ASN1T_ChildInformation();
   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = OSUTF8("19590717");
   employee.append (msgData.children, pChildInfo);

   // Encode

   out << employee;
   if (out.getStatus () != 0) {
      printf ("Encoding failed. Status = %i\n", out.getStatus());
      out.printErrorInfo ();
      return -1;
   }

   out.close ();

   if (trace) {
      printf ("Encoding was successful\n");
      ASN1BERDecodeBuffer decodeBuffer;

      // Read encoded data into a memory buffer

      int stat = decodeBuffer.readBinaryFile (filename);
      if (0 != stat) {
         out.printErrorInfo ();
      }
      else {
         // Dump message in readable format
         decodeBuffer.binDump();
      }
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

