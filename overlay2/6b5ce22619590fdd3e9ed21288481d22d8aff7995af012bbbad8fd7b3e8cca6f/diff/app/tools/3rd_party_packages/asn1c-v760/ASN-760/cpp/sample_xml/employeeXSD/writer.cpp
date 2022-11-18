#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

DECLARE_MEMLEAK_DETECTOR;

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln);

int main (int argc, char** argv)
{
   const char* filename = "message.xml";
   int         stat, i;
   OSBOOL      trace = TRUE, verbose = FALSE;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] \n");
            printf ("   -v  verbose mode: print debug info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Create an instance of the compiler generated class.
   // This example uses a dynamic message buffer..

   OSXMLEncodeBuffer encodeBuffer (0, 0);
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

   if ((stat = employee.Encode()) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ("%s\n", (const char*)encodeBuffer.getMsgPtr());
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }

   // Write the encoded message out to the output file

   if (encodeBuffer.write (filename) < 0) {
      printf ("Error writing XML document to file '%s'\n", filename);
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
