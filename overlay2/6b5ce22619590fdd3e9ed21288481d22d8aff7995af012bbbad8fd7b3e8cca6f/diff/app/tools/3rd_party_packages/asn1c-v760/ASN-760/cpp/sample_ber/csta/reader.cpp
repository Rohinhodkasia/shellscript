/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.3.A, Date: 11-Nov-2009.
 */
#include "CSTA-ROSE-PDU-types.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

#define MAXREADLEN 1024

int main (int argc, char** argv)
{
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int         i, stat;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   ASN1BERDecodeBuffer decodeBuffer;
   ASN1T_CSTA_ROSE_PDU msgData;
   ASN1C_CSTA_ROSE_PDU CSTA_ROSE_PDUPDU (decodeBuffer, msgData);

   /* Read from input file */
   decodeBuffer.setDiag (verbose);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus () != 0) {
      printf("Failed opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }

   stat = CSTA_ROSE_PDUPDU.Decode ();
   if (stat != 0) {
      printf ("decode failed\n");
      decodeBuffer.PrintErrorInfo ();
   }
   else if (trace) {
      printf ("Decode of data was successful\n");
      printf ("Decoded record:\n");
      CSTA_ROSE_PDUPDU.Print ("CSTA_ROSE_PDU");
   }

   return stat;
}