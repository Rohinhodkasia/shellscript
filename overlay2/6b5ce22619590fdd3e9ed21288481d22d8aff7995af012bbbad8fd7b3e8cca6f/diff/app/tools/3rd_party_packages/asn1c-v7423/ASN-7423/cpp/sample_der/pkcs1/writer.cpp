/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.3.A, Date: 14-Dec-2009.
 */
#include "PKCS-1.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSBOOL       dump = FALSE;
   OSBOOL       trace = TRUE;
   OSBOOL       verbose = FALSE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int          i, len;

   /* Process Command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-dump")) dump = TRUE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            printf ("   -dump     generate a hex dump file\n");
            return 1;
         }
      }
   }

   /* Create an instance of the compiler generated class.
      This example uses a dynamic message buffer..*/
   ASN1BEREncodeBuffer encodeBuffer (0,0);
   ASN1T_DigestInfo msgData;
   ASN1C_DigestInfo DigestInfoPDU (encodeBuffer, msgData);

   static const OSOCTET digest[] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
   };

   msgData.digestAlgorithm.algorithm = id_sha256;
   msgData.digestAlgorithm.m.parametersPresent = TRUE;
   msgData.digestAlgorithm.parameters.t = 
      PKCS1_v1_5DigestAlgorithms::T_id_sha256;
   msgData.digest.numocts = sizeof(digest);
   msgData.digest.data = (OSOCTET*) digest;

   if (trace) {
      printf ("The following record will be encoded:\n");
      DigestInfoPDU.Print ("msgData");
      printf ("\n");
   }

   /* Encode */
   if ((len = DigestInfoPDU.Encode ()) >= 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump (len);
         printf ("Binary dump:\n");
         encodeBuffer.binDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }
   /* Write the encoded message out to the output file */

   if ((fp = fopen (filename, "wb"))) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   /* Create a dump file */
   if (dump) {
      if ((fp = fopen ("message.dmp", "w"))) {
         rtxHexDumpToFile (fp, msgptr, len);
         fclose (fp);
      }
      else {
         printf ("Error opening message.dmp for write access\n");
         return -1;
      }
   }
   return 0;
}
