/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static void fill_jSmith (OSCTXT* pctxt, PersonnelRecord* pPR);

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT       ctxt;
   OSOCTET      msgbuf[MAXMSGLEN];
   int          i, stat;
   const char*  filename = "message.xml";
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

   stat = rtXmlInitContext (&ctxt);
   if (0 != stat) {
      printf ("context initialization failed\n");
      rtxErrPrint (&ctxt);
      return stat;
   }

   rtxSetDiag (&ctxt, verbose);

   asn1Init_PersonnelRecord (&employee);
   
   /* Populate structure of generated type */

   fill_jSmith (&ctxt, &employee);

   /* Encode */

   stat = rtXmlSetEncBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   if (0 == stat)
      stat = XmlEnc_PersonnelRecord_PDU (&ctxt, &employee);

   if (0 == stat) {
      if (trace) {
         printf ("encoded XML message:\n");
         puts ((char*)msgbuf);
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return stat;
   }
  
   /* Write the encoded message out to the output file */

   stat = rtXmlWriteToFile (&ctxt, filename);
   if (0 != stat) {
      printf ("Error opening %s for write access\n", filename);
      rtxErrPrint (&ctxt);
   }
   rtxFreeContext (&ctxt);

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

   /* fill first child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);
   asn1Init_ChildInformation (pChildInfo);

   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = "19571111";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);

   /* fill second child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);
   asn1Init_ChildInformation (pChildInfo);

   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = "19590717";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);

   pPR->privateData.numocts = 4;
   pPR->privateData.data = (OSOCTET*) rtxMemAlloc (pctxt, 4);
   {
      static const OSOCTET testdata[] = {
      244, 14, 127, 128 };
      OSCRTLMEMCPY ((void*) pPR->privateData.data, testdata, 4);
   }
}

/* Routine to fill a name structure */

static void fill_Name (Name* pName, char* fn, char* mi, char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->familyName = ln;
}
