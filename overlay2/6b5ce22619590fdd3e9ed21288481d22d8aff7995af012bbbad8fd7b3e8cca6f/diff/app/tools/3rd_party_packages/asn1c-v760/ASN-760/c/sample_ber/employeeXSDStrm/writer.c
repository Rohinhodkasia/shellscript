/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamFile.h"

static void fill_jSmith (OSCTXT* pctxt, PersonnelRecord* pPR);

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT       ctxt;
   OSOCTET*     msgptr;
   int          i, stat;
   const char*  filename = "message.dat";
   OSBOOL       trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

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

   /* Init context for stream first */

   if ((stat = berStrmInitContext (&ctxt)) != 0) {
      printf ("Initialization failed, status %d\n", stat);
      return -1;
   }

   /* Open file stream for writing */

   stat = rtxStreamFileCreateWriter (&ctxt, filename);

   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   rtxSetDiag (&ctxt, verbose);

   asn1Init_PersonnelRecord (&employee);
   
   /* Populate structure of generated type */

   fill_jSmith (&ctxt, &employee);

   /* Encode */

   if (asn1BSE_PersonnelRecord (&ctxt, &employee, ASN1EXPL) != 0) 
   {
      rtxErrPrint (&ctxt);
      berStrmFreeContext (&ctxt);
      return (-1);
   }

   if (trace) {
      size_t flen;

      /* Close the stream first */

      rtxStreamClose (&ctxt);
   
      /* Read encoded data into a memory buffer */

      stat = rtxFileReadBinary (&ctxt, filename, &msgptr, &flen);
      if (0 != stat) {
         rtxErrPrint (&ctxt);
      }
      else {
         /* Dump message in readable format */
         if (XU_DUMP (msgptr) != 0) 
            printf ("dump of ASN.1 message failed.");
      }
   }
  
   berStrmFreeContext (&ctxt);
   return 0;
}

/* Routine to fill the employee record with test data */

static void fill_Name
(Name* pName, const char* fn, const char* mi, const char* ln);

static void fill_jSmith (OSCTXT* pctxt, PersonnelRecord* pPR)
{
   ChildInformation* pChildInfo;

   fill_Name (&pPR->name, "John", "P", "Smith");

   pPR->title  = (const OSUTF8CHAR*)"Director";
   pPR->number = 51;
   pPR->dateOfHire = (const OSUTF8CHAR*)"19710917";

   fill_Name (&pPR->nameOfSpouse, "Mary", "T", "Smith");

   /* fill first child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);

   asn1Init_ChildInformation (pChildInfo);

   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = (const OSUTF8CHAR*)"19571111";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);

   /* fill second child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);

   asn1Init_ChildInformation (pChildInfo);

   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = (const OSUTF8CHAR*)"19590717";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);
}

/* Routine to fill a name structure */

static void fill_Name
  (Name* pName, const char* fn, const char* mi, const char* ln)
{
   pName->givenName = (const OSUTF8CHAR*)fn;
   pName->initial = (const OSUTF8CHAR*)mi;
   pName->familyName = (const OSUTF8CHAR*)ln;
}
