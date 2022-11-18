// This test driver program reads an encoded record from a file         
// and decodes it and displays the results..                            

#include <stdio.h>
#include <stdlib.h>
#include "rtsrc/ASN1CGeneralizedTime.h"
#include "rtsrc/ASN1CUTCTime.h"
#include "TimeString.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int          i, stat;
   const char*  filename = "message.json";
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

   // Decode 

   OSJSONDecodeBuffer decodeBuffer (filename);
   if (0 != decodeBuffer.getStatus()) {
      printf ("Error opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   decodeBuffer.setDiag (verbose);
   ASN1T_TimesSeq msgData;
   ASN1C_TimesSeq tmSeq (decodeBuffer, msgData);

   stat = tmSeq.Decode ();

   if (stat == 0) {
      if (trace) {
         printf ("Decode of TimesSeq was successful\n");
         printf ("Decoded record:\n");
         tmSeq.Print ("tmSeq");

         ASN1CGeneralizedTime genTime (decodeBuffer, msgData.genTime);
         printf("\ntmSeq.genTime\n");
      
         stat = genTime.getYear(); // check is format ok or not
         if (stat < 0) {
            decodeBuffer.printErrorInfo ();
            exit(-1);
         }

         printf("Year: %.4i, ", genTime.getYear());
         printf("Month: %.2i, ", genTime.getMonth());
         printf("Day: %.2i, ", genTime.getDay());
         printf("Hours: %.2i, ", genTime.getHour());
         printf("Mins: %.2i, ", genTime.getMinute());
         printf("Secs: %.2i, ", genTime.getSecond());
         printf("Frac: %.2i,\n", genTime.getFraction());
         printf("DiffH: %.2i, ", genTime.getDiffHour());
         printf("DiffM: %.2i, ", genTime.getDiffMinute());
         printf("Z: %i\n", genTime.getUTC());

         ASN1CUTCTime utcTime(decodeBuffer, msgData.utcTime);

         stat = genTime.getYear(); // check is format ok or not
         if (stat < 0) {
            decodeBuffer.printErrorInfo ();
            exit(-1);
         }

         printf("\ntmSeq.utcTime\n");
         printf("Year: %.4i, ", utcTime.getYear());
         printf("Month: %.2i, ", utcTime.getMonth());
         printf("Day: %.2i, ", utcTime.getDay());
         printf("Hours: %.2i, ", utcTime.getHour());
         printf("Mins: %.2i, ", utcTime.getMinute());
         printf("Secs: %.2i, ", utcTime.getSecond());
         printf("DiffH: %.2i, ", utcTime.getDiffHour());
         printf("DiffM: %.2i, ", utcTime.getDiffMinute());
         printf("Z: %i\n", utcTime.getUTC());
      }
   }
   else {
      printf ("decode of TimesSeq failed\n");
      decodeBuffer.printErrorInfo ();
      return -1;
   }

   return 0;
}
