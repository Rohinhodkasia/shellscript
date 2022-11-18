// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.bin";
   int          i, stat;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-a")) ; /* just skip */
         else if (!strcmp (argv[i], "-u")) ; /* just skip */
         else {
            printf ("usage: reader [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Decode

   ASN1PERDecodeBuffer decodeBuffer (aligned);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus() != 0) {
      printf("Error opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   ASN1T_PersonnelRecord employee;
   ASN1C_PersonnelRecord employeePDU (decodeBuffer, employee);

   decodeBuffer.SetTrace (trace);

   stat = employeePDU.Decode ();

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      decodeBuffer.BinDump ("employee");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("Decode of PersonnelRecord was successful\n");
         printf ("Decoded record:\n");
         employeePDU.Print("Employee");
         printf ("\n");
      }
   }
   else {
      printf ("decode of PersonnelRecord failed\n");
      decodeBuffer.PrintErrorInfo ();
      exit (-1);
   }

   // Encode XML

   OSOCTET xmlbuf[10240];
   OSXMLEncodeBuffer encodeBuffer (xmlbuf, sizeof(xmlbuf));
   ASN1C_PersonnelRecord employeePDU2 (encodeBuffer, employee);

   if ((stat = employeePDU2.EncodeTo (encodeBuffer)) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((const char*)xmlbuf);
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      exit (-1);
   }
  
   // Write the encoded message out to the output file

   if (encodeBuffer.write ("message.xml") < 0) {
      printf ("Error writing XML document to file '%s'\n", filename);
      return -1;
   }

   return 0;
}
