/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/OSRTFileOutputStream.h"
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int          i;
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-cxer")) cxer = TRUE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -cxer          use canonical XER rules (CXER)\n");
            printf ("   -v             verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace       do not display trace info\n");
            return 0;
         }
      }
   }

   // Create an instance of the compiler generated class.  
   OSRTFileOutputStream fstream (filename);

   OSXMLEncodeStream os (&fstream, FALSE);
   if ( cxer) rtxCtxtSetFlag(os.getCtxtPtr(), OSXMLC14N);

   if (os.getStatus () != 0) {
      os.printErrorInfo ();
      return -1;
   }

   ASN1T_PersonnelRecord msgData;
   ASN1C_PersonnelRecord employee (os, msgData);

   // Populate structure of generated type

   ASN1T_ChildInformation* pChildInfo;
   ASN1C__SeqOfChildInformation listHelper (os, msgData.children);

   fill_Name (&msgData.name, "John", "P", "Smith");

   msgData.title  = "Director";
   msgData.number = 51;
   msgData.dateOfHire = "19710917";

   fill_Name (&msgData.nameOfSpouse, "Mary", "T", "Smith");

   // fill first child record

   pChildInfo = listHelper.NewElement();
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = "19571111";
   listHelper.Append (pChildInfo);

   // fill second child record

   pChildInfo = listHelper.NewElement();
   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = "19590717";
   listHelper.Append (pChildInfo);

   // Encode

   employee.EncodeTo(os);
   if (os.getStatus () != 0) {
      printf ("Encoding failed\n");
      os.printErrorInfo ();
      return -1;
   }
   if (trace) {
      printf ("XML message has been created.\n");
   }

   return 0;
}

// Routine to fill a name structure

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->familyName = ln;
}

