/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "rtsrc/rtPrint.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

int decodedateOfHire (ASN1OpenType *pOpenType, OSBOOL trace, OSBOOL verbose);
int decodenameOfSpouse (ASN1OpenType *pOpenType, OSBOOL trace, OSBOOL verbose);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int          i, stat;
   const char*  filename = "message.bin";
   OSBOOL       verbose = FALSE, trace = TRUE;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Read input file into a memory buffer */

   ASN1BERDecodeBuffer decodeBuffer;
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      printf ("Error reading message file %s\n", filename);
      decodeBuffer.printErrorInfo();
      return stat;
   }
   decodeBuffer.setDiag (verbose);

   ASN1T_PersonnelRecord msgData;
   ASN1C_PersonnelRecord employee (decodeBuffer, msgData);

   stat = employee.Decode ();

   if (stat == 0) {
      if (trace) {
         printf ("Decode of PersonnelRecord was successful\n");
         printf ("Decoded record:\n");
         employee.Print("Employee");
      }
   }
   else {
      printf ("decode of PersonnelRecord failed\n");
      decodeBuffer.PrintErrorInfo ();
      return -1;
   }

   decodedateOfHire (&msgData.dateOfHire, trace, verbose);
   decodenameOfSpouse (&msgData.nameOfSpouse, trace, verbose);
   
   return 0;
}

int decodedateOfHire (ASN1OpenType *pOpenType, OSBOOL trace, OSBOOL verbose)
{
   OSCTXT	ctxt;
   ASN1TAG	tag;
   OSSIZE       len;
   int		stat;
   ASN1T_Date dateOfHire;

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   xd_setp64 (&ctxt, pOpenType->data, pOpenType->numocts, &tag, &len, 0);

   stat = asn1D_PersonnelRecord_dateOfHire_OpenType (&ctxt, &dateOfHire);
   if (stat != 0) {
      printf("Decode of dateOfHire failed\n");
      return stat;
   }

   if (trace) {
      printf("\n");
      printf("Defer Decoded element: dateOfHire\n");
      asn1Print_Date("PR.dateOfHire", dateOfHire);
   }
   rtFreeContext (&ctxt);
   return stat;
}

int decodenameOfSpouse (ASN1OpenType *pOpenType, OSBOOL trace, OSBOOL verbose)
{
   OSCTXT       ctxt;
   ASN1TAG      tag;
   OSSIZE       len;
   int          stat;
   ASN1T_Name   nameOfSpouse;

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   xd_setp64 (&ctxt, pOpenType->data, pOpenType->numocts, &tag, &len, 0);

   stat = asn1D_PersonnelRecord_nameOfSpouse_OpenType (&ctxt, &nameOfSpouse);
   if (stat != 0) {
      printf("Decode of nameOfSpouse failed\n");
      return stat;
   }

   if (trace) {
      printf("\n");
      printf("Defer Decoded element: nameOfSpouse\n");
      asn1Print_Name("PR.nameOfSpouse", &nameOfSpouse);
   }
   rtFreeContext (&ctxt);
   return stat;
}

