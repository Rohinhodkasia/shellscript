/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "H323-MESSAGES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

extern "C"
void writeToFile(void* pPrntStrmInfo, const char* fmtspec, 
                 va_list arglist);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.dat";
   int          i, stat;
   FILE*        fpLog;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader -a | -u [ -v ] [ -i <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Set up logging */
   if(fpLog = fopen("reader.log", "w"))
   {
      /* Here the callback function is registered as a global
         print handler. This means all print/debug streams
         will be passed to this handler.
      */
      rtxSetGlobalPrintStream(&writeToFile, (void *) fpLog);
   }
   else
   {
      printf("Failed to setup logging\n");
      return -1;
   }
   
   /* Call compiler generated decode function */

   ASN1PERDecodeBuffer decodeBuffer (aligned);
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      printf ("Error reading message file %s\n", filename);
      decodeBuffer.printErrorInfo();
      return stat;
   }
   ASN1T_H225H323_UserInformation msgData;
   ASN1C_H225H323_UserInformation userInfo (decodeBuffer, msgData);
   
   decodeBuffer.setTrace (trace);

   stat = userInfo.Decode ();

   if (trace) {
      decodeBuffer.binDump ("userInfo");
   }

   if (stat == 0) {
      if (trace) {
         printf ("Decoding was successful. See reader.log for details.\n");
         userInfo.toStream ("userInfo");
      }
   }
   else {
       decodeBuffer.printErrorInfo ();
       return -1;
   }

   return 0;
}

/*
   This is a callback function, which is called for handling all
   the run time logging/printing. The callback function can be 
   registered at the context level, which means it is used for
   logging/printing debug messages related to a particular context.
   It can also be registered at a global level, which applies
   to all contexts.
*/
void writeToFile(void* pPrntStrmInfo, const char* fmtspec, 
                 va_list arglist)
{
   FILE * fp = (FILE*) pPrntStrmInfo;
   vfprintf(fp, fmtspec, arglist);
   return;
}
