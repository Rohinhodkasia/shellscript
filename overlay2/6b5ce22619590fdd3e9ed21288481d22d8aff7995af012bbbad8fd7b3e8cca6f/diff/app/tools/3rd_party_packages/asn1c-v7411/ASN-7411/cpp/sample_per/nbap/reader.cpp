/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.2.A, Date: 18-Sep-2008.
 */
#include "NBAP-PDU-Descriptions.h"
#include "NBAP-Constants.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

#include <stdio.h>
#include <stdlib.h>

#define MAXREADLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       aligned = TRUE, trace = TRUE, verbose = FALSE;
   const char*  filename = "message.dat";
   int          i, stat;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-a|-u] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   ASN1PERDecodeBuffer decodeBuffer (aligned);
   ASN1T_NBAP_PDU data;
   ASN1C_NBAP_PDU NBAP_PDUPDU (decodeBuffer, data);
   decodeBuffer.setDiag (verbose);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus() != 0) {
      printf("Error opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   decodeBuffer.SetTrace (trace);
   stat = NBAP_PDUPDU.Decode ();
   if (stat != 0) {
      printf ("decode of PersonnelRecord failed\n");
      decodeBuffer.PrintErrorInfo ();
      return stat;
   }

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      decodeBuffer.BinDump ("Data");
      printf ("\n");
      printf ("Decode of data was successful\n");
      printf ("Decoded record:\n");
      NBAP_PDUPDU.Print ("NBAP_PDU");
   }
   return 0;
}
