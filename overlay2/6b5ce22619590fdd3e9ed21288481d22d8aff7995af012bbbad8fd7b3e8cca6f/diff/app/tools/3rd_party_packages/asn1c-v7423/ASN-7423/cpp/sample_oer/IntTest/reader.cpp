#include "Test.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   OSCTXT      ctxt;
   OSBOOL      verbose = FALSE;
   const char* filename;
   int         i, stat;

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

   ASN1OERDecodeBuffer decodeBuffer;
   decodeBuffer.setDiag (verbose);

   /* Decode INTEGER sample */
   { 
      ASN1T_Int data;
      ASN1C_Int pdu( decodeBuffer, data);;
      filename = "INTEGER.dat";

      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_Int ("INTEGER", &data);
   }

   /* Decode INTEGER_2 sample */
   { 
      ASN1T_Int data;
      ASN1C_Int pdu( decodeBuffer, data);;
      filename = "INTEGER_2.dat";

      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_Int ("INTEGER_2", &data);
   }


   /* Decode UInt32 samples */
   { 
      ASN1T_UInt32 data;
      ASN1C_UInt32 pdu( decodeBuffer, data);
      filename = "UInt32_1.dat";

      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UInt32 ("UInt32_1", &data);

      filename = "UInt32_2.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UInt32 ("UInt32_2", &data);
   }

   /* Decode INTEGER (0..MAX) sample */
   { 
      ASN1T_UIntMax data;
      ASN1C_UIntMax pdu( decodeBuffer, data);
      filename = "UIntMax.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UIntMax ("UIntMax", &data);
   }

   /* Decode INTEGER (0..255) sample */
   { 
      ASN1T_UInt8 data;
      ASN1C_UInt8 pdu( decodeBuffer, data);
      filename = "UInt8.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UInt8 ("UInt8", &data);
   }

   /* Decode INTEGER (0..255) sample */
   { 
      ASN1T_ConstrUInt32 data;
      ASN1C_ConstrUInt32 pdu( decodeBuffer, data);
      filename = "ConstrUInt32.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_ConstrUInt32 ("ConstrUInt32", &data);
   }

   /* Decode INTEGER (0..2000) sample */
   { 
      ASN1T_UInt_0_2000 data;
      ASN1C_UInt_0_2000 pdu( decodeBuffer, data);
      filename = "UInt_0_2000.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UInt_0_2000 ("UInt_0_2000", &data);
   }

   /* Decode INTEGER (1999..2000) sample */
   { 
      ASN1T_UInt_1999_2000 data;
      ASN1C_UInt_1999_2000 pdu( decodeBuffer, data);
      filename = "UInt_1999_2000.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UInt_1999_2000 ("UInt_1999_2000", &data);
   }

   /* Decode INTEGER (1200..1250) sample */
   { 
      ASN1T_UInt32_1200_1250 data;
      ASN1C_UInt32_1200_1250 pdu( decodeBuffer, data);
      filename = "UInt32_1200_1250.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UInt32_1200_1250 ("UInt32_1200_1250", &data);
   }

   /* Decode INTEGER (0..255,...) sample */
   { 
      ASN1T_UInt8Ext data;
      ASN1C_UInt8Ext pdu( decodeBuffer, data);
      filename = "UInt8Ext.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UInt8Ext ("UInt8Ext", &data);
   }

   /* Decode INTEGER (0..255,...) sample */
   { 
      ASN1T_UInt8Ext data;
      ASN1C_UInt8Ext pdu( decodeBuffer, data);
      filename = "UInt8Ext_2.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_UInt8Ext ("UInt8Ext_2", &data);
   }

   /* Decode INTEGER (-127..127) sample */
   { 
      ASN1T_Int8 data;
      ASN1C_Int8 pdu( decodeBuffer, data);
      filename = "Int8.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_Int8 ("Int8", &data);
   }

   /* Decode INTEGER (-1000..1000) sample */
   { 
      ASN1T_Int_Neg1000_1000 data;
      ASN1C_Int_Neg1000_1000 pdu( decodeBuffer, data);
      filename = "Int_Neg1000_1000.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_Int_Neg1000_1000 ("Int_Neg1000_1000", &data);
   }

   /* Decode INTEGER {a(1),b(2)} sample */
   { 
      ASN1T_IntWithNamedNumbers data;
      ASN1C_IntWithNamedNumbers pdu( decodeBuffer, data);
      filename = "IntWithNamedNumbers.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_IntWithNamedNumbers ("IntWithNamedNumbers", &data);
   }

   /* Decode INTEGER {a(1),b(2)} (0..65535) sample */
   { 
      ASN1T_ConstrIntWithNamedNumbers data;
      ASN1C_ConstrIntWithNamedNumbers pdu( decodeBuffer, data);
      filename = "ConstrIntWithNamedNumbers.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }
      asn1Print_ConstrIntWithNamedNumbers ("ConstrIntWithNamedNumbers", &data);
   }

   /* Decode INTEGER (-128..127)(0..MAX) sample */
   { 
      ASN1T_IntWith2Ranges data;
      ASN1C_IntWith2Ranges pdu( decodeBuffer, data);
      filename = "IntWith2Ranges.dat";
      decodeBuffer.readBinaryFile (filename);
      if (decodeBuffer.getStatus() != 0) {
         printf("Error opening %s for read access\n", filename);
         decodeBuffer.printErrorInfo();
         return -1;
      }

      stat = pdu.Decode ();
      if (stat != 0) {
         printf ("decode of data failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }

      asn1Print_IntWith2Ranges ("IntWith2Ranges", &data);
   }

   rtFreeContext (&ctxt);

   return 0;
}
