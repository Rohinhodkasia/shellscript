// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "ExtChoice.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const char*  filename = "message.xml";
   int          i, stat;
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename> ] [ -notrace ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read XML doc from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Create ASN.1 message objects
   OSXMLDecodeBuffer decodeBuffer (filename);
   decodeBuffer.setDiag (verbose);
   ASN1T_AliasAddressList msgData;
   ASN1C_AliasAddressList aliasAddressList (decodeBuffer, msgData);

   stat = aliasAddressList.Decode ();

   if (stat == 0) {
      if (trace) {
         printf ("decode was successful\n");
         aliasAddressList.Print ("aliasAddressList");
      }
   }
   else {
      printf ("decode of AliasAddressList failed\n");
      decodeBuffer.printErrorInfo ();
   }

   return (stat);

}
