/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.2.A, Date: 13-Jun-2017.
 */
#include "Test.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

#define MAXREADLEN 1024

int main (int argc, char** argv)
{
   OSBOOL       trace = TRUE, verbose = FALSE;
   const char*  filename = "message.dat";
   int          i, stat;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-notrace")) {}
         else {
            printf ("usage: reader [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            return 1;
         }
      }
   }

   ASN1OERDecodeBuffer decodeBuffer;

   decodeBuffer.setDiag (verbose);

   /* Decode MyEnum sample */
   {      
      ASN1T_MyEnum data;
      ASN1C_MyEnum MyEnumPDU (decodeBuffer, data);
      filename = "MyEnum.dat";

      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));

      stat = MyEnumPDU.Decode ();
      if (stat != 0) {
         printf ("decode of PersonnelRecord failed\n");
         decodeBuffer.PrintErrorInfo ();
         return -1;
      }

      asn1Print_MyEnum ("MyEnum", &data);
   }

   /* Decode MyExtEnum sample */
   {
      ASN1T_MyExtEnum data;
      ASN1C_MyExtEnum MyEnumPDU (decodeBuffer, data);
      filename = "MyExtEnum.dat";

      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));

      stat = MyEnumPDU.Decode ();
      if (stat != 0) {
         printf ("decode of PersonnelRecord failed\n");
         decodeBuffer.PrintErrorInfo ();
         return -1;
      }

      asn1Print_MyExtEnum ("MyExtEnum", &data);
   }

   return 0;
}
