// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "TAP-0311.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxMemory.h"

#define MAXMSGLEN 1024

// DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int		i, stat;
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
   rtxMemSetDefBlkSize (500*1024); // set block size to 500K

   ASN1BERDecodeBuffer decodeBuffer;
   decodeBuffer.setDiag (verbose);

   // Read input file into a memory buffer

   stat = decodeBuffer.readBinaryFile (filename);
   if (stat != 0) {
      printf ("read data file failed\n");
      return stat;
   }

   // Decode

   ASN1T_DataInterChange msgData;
   ASN1C_DataInterChange dataInterChange (decodeBuffer, msgData);

   stat = dataInterChange.Decode ();

   if (stat == 0) {
      if (trace) {
         printf ("Decode of DataInterChange was successful\n");
         printf ("Decoded record:\n");
         asn1Print_DataInterChange ("dataInterChange", &msgData);
      }
   }
   else {
      printf ("decode failed\n");
      decodeBuffer.printErrorInfo ();
      return -1;
   }

   dataInterChange.memFreeAll ();

   return 0;
}
