/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "SeqOfTest.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int		i, len, stat;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [ -v ] [ -o <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Populate date structure */

   ASN1PEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf), aligned);
   encodeBuffer.SetTrace (trace);

   ASN1T_SeqOf10Ints msgData;
   ASN1C_SeqOf10Ints seqOf10Ints (encodeBuffer, msgData);
   OSINT32 ints[10];

   for (i = 0; i < 5; i++) {
      ints[i] = i - 2;
   }
   msgData.n = 5;
   msgData.elem = ints;

   /* Encode */

   if ((stat = seqOf10Ints.Encode ()) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.HexDump ();
         printf ("Binary dump:\n");
         encodeBuffer.BinDump ("seqOf10Ints");
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.GetMsgLen ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.PrintErrorInfo ();
      return -1;
   }
  
   /* Write the encoded message out to the output file */

   if (fp = fopen (filename, "wb")) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
      if (trace)
         printf ("Wrote %d bytes to file %s..\n", len, filename);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   return 0;

}
