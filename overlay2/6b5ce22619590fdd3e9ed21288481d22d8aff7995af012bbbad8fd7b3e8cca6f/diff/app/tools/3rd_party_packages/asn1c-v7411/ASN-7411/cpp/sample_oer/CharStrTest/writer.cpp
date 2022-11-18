/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.2.A, Date: 13-Jun-2017.
 */
#include "Test.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   int        i, stat;
   OSSIZE     len;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";
   const OSOCTET* msgptr;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [-v] [-o <filename>]  [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Create an instance of the compiler generated class.
      This example uses a dynamic message buffer..*/
   ASN1OEREncodeBuffer encodeBuffer;
   ASN1T_MyString data;
   ASN1C_MyString MyStringPDU (encodeBuffer, data);

   data = "test str";

   /* Encode */

   if ((stat = MyStringPDU.Encode ()) == 0)
   {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.getMsgLen ();
   }
   else
   {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }
   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      encodeBuffer.printErrorInfo();
      return stat;
   }

   return 0;
}