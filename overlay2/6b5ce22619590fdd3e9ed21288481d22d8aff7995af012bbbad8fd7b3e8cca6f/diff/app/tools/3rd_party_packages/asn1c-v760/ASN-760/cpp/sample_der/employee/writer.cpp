// This test driver program encodes a data record and writes the encoded
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET	msgbuf[MAXMSGLEN];
   int		i, len;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
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

   // Create an instance of the compiler generated class.  This
   // example uses a static message buffer..

   ASN1BEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   encodeBuffer.setDiag (verbose);
   ASN1T_PersonnelRecord msgData;
   ASN1C_PersonnelRecord employee (encodeBuffer, msgData);

   // Populate structure of generated type

   ASN1T_ChildInformation* pChildInfo;
   ASN1C__SeqOfChildInformation listHelper (encodeBuffer, msgData.children);

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

   if ((len = employee.Encode ()) >= 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.HexDump (len);
         printf ("Binary dump:\n");
         encodeBuffer.BinDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }
  
   // Write the encoded message out to the output file 

   int ret = rtxFileWriteBinary (filename, msgptr, len);
   if (ret < 0) {
      printf ("Write to file %s failed\n", filename);
      return ret;
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

