// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "InfoObject.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.dat";
   int          i, stat;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader -a | -u [ -v ] [ -i <filename> ]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Decode

   ASN1PERDecodeBuffer decodeBuffer (aligned);
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      decodeBuffer.printErrorInfo();
      return stat;
   }
   ASN1T_Iu_ReleaseCommand releaseCommand;
   ASN1C_Iu_ReleaseCommand releaseCommandC (decodeBuffer, releaseCommand);

   decodeBuffer.setTrace (trace);

   stat = releaseCommandC.Decode ();

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      decodeBuffer.binDump ("releaseCommand");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode was successful\n");
         releaseCommandC.Print ("releaseCommand");
      }
   }
   else {
       printf ("decode failed\n");
       decodeBuffer.printErrorInfo ();
       return -1;
   }

   // Decode the open type

   ASN1T_ProtocolIE_Field* pField = 
      (ASN1T_ProtocolIE_Field*) releaseCommand.protocolIEs.head->data;

   ASN1PERDecodeBuffer decodeBuffer2 
      (pField->value.data, pField->value.numocts, aligned);

   ASN1T_Cause cause;
   ASN1C_Cause causeC (decodeBuffer2, cause);

   decodeBuffer.setTrace (trace);

   stat = causeC.Decode ();

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      decodeBuffer.binDump ("cause");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode was successful\n");
         causeC.Print ("cause");
      }
   }
   else {
       printf ("decode failed\n");
       decodeBuffer.printErrorInfo ();
       return -1;
   }

   return 0;
}
