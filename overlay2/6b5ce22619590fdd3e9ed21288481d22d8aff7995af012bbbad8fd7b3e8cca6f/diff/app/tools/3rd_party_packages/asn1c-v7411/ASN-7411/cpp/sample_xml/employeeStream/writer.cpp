// Example of encoding an XML message directly to a file output stream

#include "Employee.h"
#include "rtxsrc/OSRTFileOutputStream.h"
#include "rtxmlsrc/OSXMLEncodeStream.h"

static void fill_Name 
(ASN1T_Name* pName, const char* fn, const char* mi, const char* ln);

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
            return 1;
         }
      }
   }

   // Create an instance of the compiler generated class.
   // This example uses a dynamic message buffer..

   OSRTFileOutputStream fos (filename);
   OSXMLEncodeStream xmlfos (fos);
   xmlfos.setDiag (verbose);
   ASN1T_PersonnelRecord msgData;
   ASN1C_PersonnelRecord PersonnelRecordPDU (xmlfos, msgData);

   // Populate structure of generated type

   ASN1T_ChildInformation* pChildInfo;
   ASN1C__SeqOfChildInformation listHelper (xmlfos, msgData.children);

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

   if ((stat = PersonnelRecordPDU.Encode()) == 0) {
      if (trace) {
         fos.close();
         OSOCTET* pXmlText;
         size_t fileLength;

         stat = rtxFileReadText 
            (xmlfos.getCtxtPtr(), filename, &pXmlText, &fileLength);

         if (0 == stat) {
            printf ("encoded XML message:\n");
            printf ((const char*)pXmlText);
            printf ("\n");
         }
         else {
            printf ("ERROR: read XML text file failed\n");
            xmlfos.printErrorInfo ();
            return (-1);
         }
      }
   }
   else {
      printf ("Encoding failed\n");
      xmlfos.printErrorInfo ();
      return (-1);
   }

   return 0;
}

// Routine to fill a name structure

static void fill_Name 
(ASN1T_Name* pName, const char* fn, const char* mi, const char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->familyName = ln;
}
