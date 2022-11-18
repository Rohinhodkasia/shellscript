// This test driver program encodes a data record and writes the        
// encoded result to an output file..                                   

#include <stdio.h>
#include <stdlib.h>
#include "BitString.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   int		i, len;
   FILE*        fp;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments 

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

   // Populate structure of generated type 

   ASN1BEREncodeBuffer encodeBuffer;
   encodeBuffer.setDiag (verbose);
   ASN1T_BSSeq msgData;
   ASN1C_BSSeq bsSeq (encodeBuffer, msgData);

   ASN1CBitStr bs3 (encodeBuffer, msgData.bs3.data, msgData.bs3.numbits, 8);
   int stat;
   stat = bs3.set (ASN1C_BS3::a);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   stat = bs3.clear (ASN1C_BS3::b);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   stat = bs3.set (ASN1C_BS3::c);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   ASN1CBitStr bs2 (encodeBuffer, msgData.bs2.data, msgData.bs2.numbits, 10);
   ASN1CBitStr bs2a (encodeBuffer, 0u);
   stat = bs2.set (1, 10);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = bs2a.invert (1, 10);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = bs2a.clear (9);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = bs2.doXor (bs2a);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   ASN1CBitStr bs1 (encodeBuffer, msgData.bs1);
   stat = bs1.set (2, 612);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = bs1.clear (611);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = bs1.invert (2, 611);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = bs1.invert (68);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = bs1.shiftLeft (10);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = bs1.shiftRight (6);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   // Encode in a dynamic buffer 
   if ((len = bsSeq.Encode ()) > 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.HexDump (len);
         printf ("Binary dump:\n");
         encodeBuffer.BinDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      exit (-1);
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
