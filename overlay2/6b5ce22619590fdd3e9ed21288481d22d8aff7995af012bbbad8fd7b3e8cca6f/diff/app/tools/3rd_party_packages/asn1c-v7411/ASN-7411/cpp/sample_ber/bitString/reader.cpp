// This test driver program reads an encoded record from a file         
// and decodes it and displays the results..                            

#include <stdio.h>
#include <stdlib.h>
#include "BitString.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int          i, stat;
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

   // Read input file and decode 

   ASN1BERDecodeBuffer decodeBuffer;
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      printf ("Error reading message file %s\n", filename);
      decodeBuffer.printErrorInfo();
      return stat;
   }
   decodeBuffer.setDiag (verbose);
   ASN1T_BSSeq msgData;
   ASN1C_BSSeq bsSeq (decodeBuffer, msgData);

   stat = bsSeq.Decode ();

   if (stat == 0) {
      if (trace) {
         printf ("Decode of BSSeq was successful\n");
         printf ("Decoded record:\n");
         bsSeq.Print ("bsSeq");

         // check bit strings
         ASN1CBitStr bs1 (decodeBuffer, msgData.bs1);
         if(bs1.isSet(64) && bs1.cardinality() == 1) {
            printf ("Bit 64 of bs1 is ok!\n");
         }
         else {
            printf ("ERROR: Only bit 64 of bs1 should be set!\n");
            exit(-1);
         }

         ASN1CBitStr bs2(decodeBuffer, msgData.bs2.data, msgData.bs2.numbits, 16);
         if(bs2.isSet(9) && bs2.cardinality() == 1) {
            printf ("Bit 9 of bs2 is ok!\n");
         }
         else {
            printf ("ERROR: Only bit 9 of bs2 should be set!\n");
            exit(-1);
         }

         ASN1CBitStr bs3(decodeBuffer, msgData.bs3.data, msgData.bs3.numbits, 8);
         if(bs3.isSet(ASN1C_BS3::a) && bs3.isSet(ASN1C_BS3::c) &&
            bs3.cardinality() == 2)
         {
            printf ("Bits a and c of bs3 are ok!\n");
         }
         else {
            printf ("ERROR: Only bits a and b of bs3 should be set!\n");
            exit(-1);
         }
      }
   }
   else {
      printf ("decode of BS3 failed\n");
      decodeBuffer.printErrorInfo ();
      exit(-1);
   }
   return 0;
}
