#include "Test.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   OSCTXT      ctxt;
   OSOCTET*    pMsgBuf;
   OSBOOL      verbose = FALSE;
   const char* filename;
   int         i, stat;
   size_t      len;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: reader [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            return 1;
         }
      }
   }

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Decode INTEGER sample */
   { 
      Int data;
      filename = "INTEGER.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_Int (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_Int ("INTEGER", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode UInt32 samples */
   { 
      UInt32 data;
      filename = "UInt32_1.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_UInt32 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_UInt32 ("UInt32_1", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);

      filename = "UInt32_2.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_UInt32 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_UInt32 ("UInt32_2", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER (0..MAX) sample */
   { 
      UIntMax data;
      filename = "UIntMax.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_UIntMax (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_UIntMax ("UIntMax", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER (0..255) sample */
   { 
      ConstrUInt32 data;
      filename = "ConstrUInt32.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_ConstrUInt32 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_ConstrUInt32 ("ConstrUInt32", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER (0..2000) sample */
   { 
      UInt_0_2000 data;
      filename = "UInt_0_2000.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_UInt_0_2000 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_UInt_0_2000 ("UInt_0_2000", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER (1999..2000) sample */
   { 
      UInt_1999_2000 data;
      filename = "UInt_1999_2000.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_UInt_1999_2000 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_UInt_1999_2000 ("UInt_1999_2000", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER (0..255,...) sample */
   { 
      UInt8Ext data;
      filename = "UInt8Ext.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_UInt8Ext (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_UInt8Ext ("UInt8Ext", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER (-127..127) sample */
   { 
      Int8 data;
      filename = "Int8.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_Int8 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_Int8 ("Int8", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER (-1000..1000) sample */
   { 
      Int_Neg1000_1000 data;
      filename = "Int_Neg1000_1000.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_Int_Neg1000_1000 (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_Int_Neg1000_1000 ("Int_Neg1000_1000", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER {a(1),b(2)} sample */
   { 
      IntWithNamedNumbers data;
      filename = "IntWithNamedNumbers.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_IntWithNamedNumbers (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_IntWithNamedNumbers ("IntWithNamedNumbers", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER {a(1),b(2)} (0..65535) sample */
   { 
      ConstrIntWithNamedNumbers data;
      filename = "ConstrIntWithNamedNumbers.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_ConstrIntWithNamedNumbers (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_ConstrIntWithNamedNumbers ("ConstrIntWithNamedNumbers", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   /* Decode INTEGER (-128..127)(0..MAX) sample */
   { 
      IntWith2Ranges data;
      filename = "IntWith2Ranges.dat";
      if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }

      OSCRTLMEMSET (&data, 0, sizeof(data));
      rtxInitContextBuffer (&ctxt, pMsgBuf, len);

      stat = OERDec_IntWith2Ranges (&ctxt, &data);
      if (stat != 0) {
         printf ("decode of data failed\n");
         rtxErrPrint (&ctxt);
         rtFreeContext (&ctxt);
         return -1;
      }

      asn1Print_IntWith2Ranges ("IntWith2Ranges", &data);
      rtxMemFreePtr (&ctxt, pMsgBuf);
   }

   rtFreeContext (&ctxt);

   return 0;
}
