/**
 * Sample program to read ASN.1 in Abstract Value Notation and encode it
 * to PER.
 */
#include "Employee.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   OSBOOL     aligned = !FALSE;
   OSBOOL       trace = TRUE, verbose = FALSE;
   const char*  filename = "message.txt";
   const char*  ofilename = "message.dat";
   int          i, stat;
   int          len;
   const OSOCTET* msgptr;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-a")) aligned = 1;
         else if (!strcmp (argv[i], "-u")) aligned = 0;
         else if (!strcmp (argv[i], "-u")) aligned = 0;         
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-o")) ofilename = argv[++i];         
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-o <filename>] \n");
            printf ("   [-notrace] [-a|-u]\n");           
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");            
            printf ("   -notrace  do not display trace info\n");            
            return 1;
         }
      }
   }

   // Create ASN.1 message objects
   ASN1AVNDecodeBuffer decodeBuffer (filename);
   decodeBuffer.setDiag (verbose);
   ASN1T_PersonnelRecord data;
   ASN1C_PersonnelRecord personnelRecordPDU (decodeBuffer, data);

   stat = personnelRecordPDU.Decode ();
   if (0 != stat) {
      decodeBuffer.printErrorInfo ();
      return stat;
   }
   printf ("Decode of data was successful\n");
   printf ("Decoded record:\n");
   personnelRecordPDU.Print ("PersonnelRecord");

   ASN1PEREncodeBuffer encodeBuffer (aligned);
   ASN1C_PersonnelRecord personnelRecordPDU2 (encodeBuffer, data);   
   
   /* Encode to PER */
   encodeBuffer.setTrace (trace);
   encodeBuffer.setDiag (verbose);

   if ((stat = personnelRecordPDU2.Encode ()) == 0)
   {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
         printf ("Binary dump:\n");
         encodeBuffer.binDump ("Data");
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
   stat = rtxFileWriteBinary (ofilename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      encodeBuffer.printErrorInfo();
      return stat;
   }
   
   return (stat);
}
