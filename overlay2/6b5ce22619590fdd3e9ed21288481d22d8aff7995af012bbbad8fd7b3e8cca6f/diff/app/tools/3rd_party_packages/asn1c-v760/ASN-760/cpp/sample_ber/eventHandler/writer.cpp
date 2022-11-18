// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static void fill_jSmith (ASN1C_PersonnelRecord& ccobj);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSBOOL       verbose = FALSE, trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int		i, len;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print detailed trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Populate the employee structure

   ASN1BEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   encodeBuffer.setDiag (verbose);
   ASN1T_PersonnelRecord employee;
   ASN1C_PersonnelRecord employeePDU (encodeBuffer, employee);

   fill_jSmith (employeePDU);

   // Encode

   if ((len = employeePDU.Encode ()) >= 0)
   {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump (len);
         printf ("Binary dump:\n");
         encodeBuffer.binDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else
   {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      exit (0);
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


// Routine to fill the employee record with test data 

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln);

static void fill_jSmith (ASN1C_PersonnelRecord& ccobj)
{
   ASN1T_PersonnelRecord& employee = ccobj.getData();
   ASN1T_ChildInformation* pChildInfo;
   ASN1C__SeqOfChildInformation seqOfChildInfo (ccobj, employee.children);

   fill_Name (&employee.name, "John", "P", "Smith");

   employee.title  = "Director";
   employee.number = 51;
   employee.dateOfHire = "19710917";

   fill_Name (&employee.nameOfSpouse, "Mary", "T", "Smith");

   employee.m.childrenPresent = TRUE;

   // fill first child record

   pChildInfo = seqOfChildInfo.NewElement();
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = "19571111";
   seqOfChildInfo.Append (pChildInfo);

   // fill second child record

   pChildInfo = seqOfChildInfo.NewElement();
   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = "19590717";
   seqOfChildInfo.Append (pChildInfo);
}

// Routine to fill a name structure

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->familyName = ln;
}
