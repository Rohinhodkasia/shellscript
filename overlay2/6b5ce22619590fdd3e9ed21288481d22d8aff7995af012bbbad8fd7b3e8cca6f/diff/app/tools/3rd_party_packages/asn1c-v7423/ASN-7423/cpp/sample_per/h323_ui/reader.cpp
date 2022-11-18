/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "H323-MESSAGES.h"
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
   ASN1T_H225H323_UserInformation msgData;
   ASN1C_H225H323_UserInformation userInfo (decodeBuffer, msgData);

   decodeBuffer.setTrace (trace);

   stat = userInfo.Decode ();

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      decodeBuffer.binDump ("userInfo");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode was successful\n");
         userInfo.Print ("userInfo");
      }
   }
   else {
       printf ("decode failed\n");
       decodeBuffer.printErrorInfo ();
       return -1;
   }

   return 0;
}
