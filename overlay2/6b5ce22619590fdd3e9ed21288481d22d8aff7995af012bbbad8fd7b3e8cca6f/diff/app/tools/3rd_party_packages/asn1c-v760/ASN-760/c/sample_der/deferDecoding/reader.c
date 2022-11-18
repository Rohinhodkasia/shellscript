/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include "rtsrc/rtPrint.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static int decodeDateOfHire (ASN1OpenType *pOpenType, OSBOOL trace);
static int decodeNameOfSpouse (ASN1OpenType *pOpenType, OSBOOL trace);

int main (int argc, char** argv)
{
   PersonnelRecord msgData;
   OSCTXT       ctxt;
   OSOCTET      msgbuf[MAXMSGLEN];
   int          i, stat;
   OSSIZE       len;
   FILE*        fp;
   const char*  filename = "message.bin";
   OSBOOL       trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

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

   if (fp = fopen (filename, "rb")) {
      len = fread (msgbuf, 1, sizeof(msgbuf), fp);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   /* Init context structure */

   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   stat = xd_setp64 (&ctxt, msgbuf, len, 0, 0, 0);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   stat = asn1D_PersonnelRecord (&ctxt, &msgData, ASN1EXPL, 0);

   if (stat == 0) {
      if (trace) {
         printf ("Decode of PersonnelRecord was successful\n");
         printf ("Decoded record:\n");
         asn1Print_PersonnelRecord("Employee", &msgData);
      }
   }
   else {
      printf ("decode of PersonnelRecord failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }

   decodeDateOfHire (&msgData.dateOfHire, trace);
   decodeNameOfSpouse (&msgData.nameOfSpouse, trace);
   
   rtFreeContext (&ctxt);
   return 0;
}

static int decodeDateOfHire (ASN1OpenType *pOpenType, OSBOOL trace)
{
   OSCTXT ctxt;
   int    stat;
   Date   dateOfHire;

   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   stat = xd_setp64 (&ctxt, pOpenType->data, pOpenType->numocts, 0, 0, 0);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

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

static int decodeNameOfSpouse (ASN1OpenType *pOpenType, OSBOOL trace)
{
   OSCTXT ctxt;
   int    stat;
   Name   nameOfSpouse;

   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   stat = xd_setp64 (&ctxt, pOpenType->data, pOpenType->numocts, 0, 0, 0);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

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
