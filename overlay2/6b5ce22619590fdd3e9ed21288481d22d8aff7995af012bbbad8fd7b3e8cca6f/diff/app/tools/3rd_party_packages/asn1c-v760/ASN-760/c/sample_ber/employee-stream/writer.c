/* This test driver program encodes a data record and writes the        */
/* encoded result to an output stream.                                  */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxDiag.h"
#include "rtbersrc/asn1berStream.h"

static void fill_jSmith (OSCTXT* pctxt, PersonnelRecord* pPR);

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT	ctxt;
   int		i, stat;
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
   rtxSetDiag (&ctxt, verbose);

   /* Open file stream for writing */

   stat = rtxStreamFileCreateWriter (&ctxt, filename);

   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Populate structure of generated type */

   fill_jSmith (&ctxt, &employee);

   /* Encode */

   if (asn1BSE_PersonnelRecord (&ctxt, &employee, ASN1EXPL) != 0) 
   {
      rtxErrPrint (&ctxt);
      berStrmFreeContext (&ctxt);
      exit (-1);
   }

   if (trace) {
      FILE* fp;
      size_t flen;

      /* Close the stream first */

      rtxStreamClose (&ctxt);
   
      /* Open the input file in read binary mode */

      if ((fp = fopen (filename, "rb")) == 0) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }
      fseek (fp, 0, SEEK_END);
      flen = (size_t) ftell (fp);
      fseek (fp, 0, SEEK_SET);

      if (flen > 0) {
         OSOCTET* msgptr =  (OSOCTET*)rtxMemAlloc (&ctxt, flen);
         if (fread (msgptr, 1, flen, fp) != flen) {
            printf ("Error reading %s\n", filename);
            return -1;
         }

         if (XU_DUMP (msgptr) != 0) 
            printf ("dump of ASN.1 message failed.");
      }

      fclose (fp);
   }
  
   berStrmFreeContext (&ctxt);
   return 0;
}


/* Routine to fill the employee record with test data */

static void fill_Name (Name* pName, char* fn, char* mi, char* ln);

static void fill_jSmith (OSCTXT* pctxt, PersonnelRecord* pPR)
{
   ChildInformation* pChildInfo;

   fill_Name (&pPR->name, "John", "P", "Smith");

   pPR->title  = "Director";
   pPR->number = 51;
   pPR->dateOfHire = "19710917";

   fill_Name (&pPR->nameOfSpouse, "Mary", "T", "Smith");
   pPR->m.nameOfSpousePresent = 1;
   pPR->m.childrenPresent = 1;
   pPR->m.dateOfFirePresent = 0;

   rtxDListInit (&pPR->children);

   /* fill first child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = "19571111";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);

   /* fill second child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);
   fill_Name (&pChildInfo->name, "Susan", 0, "Jones");
   pChildInfo->dateOfBirth = "19590717";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);
}

/* Routine to fill a name structure */

static void fill_Name (Name* pName, char* fn, char* mi, char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->m.initialPresent = (mi != 0) ? 1 : 0;
   pName->familyName = ln;
}

