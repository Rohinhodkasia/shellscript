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

static int processResult (ASN1OEREncodeBuffer encodeBuffer, int stat, const char* filename)
{
   const OSOCTET* msgptr = encodeBuffer.getMsgPtr();
   size_t len = encodeBuffer.getMsgLen();

   printf ("Hex dump of encoded record:\n");
   rtxHexDump (msgptr, len);

   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (encodeBuffer.getCtxtPtr());
      return stat;
   }
   
   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      encodeBuffer.printErrorInfo();
      return stat;
   }

   return stat;
}

int main (int argc, char** argv)
{
   int        i, stat;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-notrace")) {}
         else {
            printf ("usage: writer [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Create an instance of the compiler generated class.
      This example uses a dynamic message buffer..*/
   ASN1OEREncodeBuffer encodeBuffer;

   {
      ASN1T_MyEnum data = MyEnum::b;
      ASN1C_MyEnum MyEnumPDU (encodeBuffer, data);

      /* Encode MyEnum sample */
      printf ("encode MyEnum value b(2)..\n");
      encodeBuffer.init();
      
      stat = MyEnumPDU.Encode();
      stat = processResult (encodeBuffer, stat, "MyEnum.dat");
   }

   if (stat >= 0) {
      ASN1T_MyExtEnum data = 128;
      ASN1C_MyExtEnum MyEnumPDU (encodeBuffer, data);

      /* Encode MyExtEnum sample */
      printf ("encode MyExtEnum value 128..\n");
      encodeBuffer.init();
      
      stat = MyEnumPDU.Encode();
      stat = processResult (encodeBuffer, stat, "MyExtEnum.dat");
   }

   return stat;
}