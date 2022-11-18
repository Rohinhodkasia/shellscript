// This test driver program reads an encoded record from a file 
// and decodes it and displays the results.  This demonstrates how 
// to make a copy of a decoded PDU structure for use in other parts 
// of an application after the control class and message buffer 
// objects go out of scope..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

ASN1T_PersonnelRecord* decodePDU 
(const OSOCTET* msgbuf, OSSIZE len, OSBOOL verbose);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSOCTET      msgbuf[MAXMSGLEN];
   int          i;
   OSSIZE       len;
   FILE*        fp;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Read input file into a memory buffer

   if (fp = fopen (filename, "rb")) {
      len = fread (msgbuf, 1, sizeof(msgbuf), fp);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   // decodePDU decodes the message and returns a copy of the 
   // decode structure..

   ASN1T_PersonnelRecord* pPR = decodePDU (msgbuf, len, verbose);

   if (0 != pPR) {
      if (trace) {
         printf ("Decode of PersonnelRecord was successful\n");
         printf ("Decoded record:\n");
         asn1Print_PersonnelRecord ("employee", pPR);
      }
   }

   // should be OK to delete since we got record using newCopy..

   delete pPR;

   return 0;
}

ASN1T_PersonnelRecord* decodePDU 
(const OSOCTET* msgbuf, OSSIZE len, OSBOOL verbose)
{
   ASN1TAG      tag;
   int          stat;
   OSBOOL       indefLen;

   ASN1BERDecodeBuffer decodeBuffer (msgbuf, len);
   decodeBuffer.setDiag (verbose);

   stat = decodeBuffer.parseTagLen (tag, len, &indefLen);

   if (stat != 0) {
      printf ("decodeBuffer.parseTagLen failed\n");
      decodeBuffer.PrintErrorInfo ();
      return 0;
   }

   // Verify record is a personnel record

   if (tag == TV_PersonnelRecord) {
      ASN1T_PersonnelRecord msgData;
      ASN1C_PersonnelRecord employee (decodeBuffer, msgData);

      stat = employee.Decode ();

      if (stat != 0) {
         printf ("decode of PersonnelRecord failed\n");
         decodeBuffer.PrintErrorInfo ();
         return 0;
      }
      else 
         return employee.newCopy();
   }
   else {
      printf ("unexpected tag %hx received\n", tag);
      return 0;
   }

   return 0;
}


