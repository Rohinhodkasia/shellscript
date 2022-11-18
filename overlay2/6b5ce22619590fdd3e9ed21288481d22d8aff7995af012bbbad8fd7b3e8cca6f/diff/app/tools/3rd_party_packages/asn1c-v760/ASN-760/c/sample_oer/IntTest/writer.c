/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.4.A, Date: 07-Nov-2010.
 */
#include "Test.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxPrint.h"

static int processResult (OSCTXT* pctxt, int stat, const char* filename)
{
   const OSOCTET* msgptr = pctxt->buffer.data;
   size_t len = pctxt->buffer.byteIndex;

   printf ("Hex dump of encoded record:\n");
   rtxHexDump (msgptr, len);

   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (pctxt);
      return stat;
   }

   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      rtxErrPrint (pctxt);
   }

   return stat;
}

int main (int argc, char** argv)
{
   OSCTXT     ctxt;
   int        i, stat;
   OSBOOL     verbose = FALSE;
   OSOCTET    buffer[100];

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: writer [-v]\n");
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

   /* Encode INTEGER sample */
   printf ("encode INTEGER value 120..\n");
   rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
   stat = OEREnc_Int (&ctxt, 120L);
   stat = processResult (&ctxt, stat, "INTEGER.dat");

   /* Encode Counter, TimeTicks, Gauge (UInt32) samples */
   if (stat >= 0) {
      printf ("encode UInt32 value 120..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_UInt32 (&ctxt, 120L);
      stat = processResult (&ctxt, stat, "UInt32_1.dat");
   }
   if (stat >= 0) {
      printf ("encode UInt32 value 12345678..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_UInt32 (&ctxt, 12345678L);
      stat = processResult (&ctxt, stat, "UInt32_2.dat");
   }

   /* Encode INTEGER (0..MAX) sample */
   if (stat >= 0) {
      printf ("encode UIntMax value 120..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_UIntMax (&ctxt, 120L);
      stat = processResult (&ctxt, stat, "UIntMax.dat");
   }

   /* Encode INTEGER (0..255) sample */
   if (stat >= 0) {
      printf ("encode UInt8 value 120..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_UInt8 (&ctxt, 120L);
      stat = processResult (&ctxt, stat, "UInt8.dat");
   }

   /* Encode Counter (0..255) sample */
   if (stat >= 0) {
      printf ("encode ConstrUInt32 value 120..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_ConstrUInt32 (&ctxt, 120L);
      stat = processResult (&ctxt, stat, "ConstrUInt32.dat");
   }

   /* Encode INTEGER (0..2000) sample */
   if (stat >= 0) {
      printf ("encode UInt_0_2000 value 120..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_UInt_0_2000 (&ctxt, 120L);
      stat = processResult (&ctxt, stat, "UInt_0_2000.dat");
   }

   /* Encode INTEGER (1999..2000) sample */
   if (stat >= 0) {
      printf ("encode UInt_1999_2000 value 2000..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_UInt_0_2000 (&ctxt, 2000L);
      stat = processResult (&ctxt, stat, "UInt_1999_2000.dat");
   }

   /* Encode Gauge (1200..1250) sample */
   if (stat >= 0) {
      printf ("encode UInt32_1200_1250 value 1200..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_UInt32_1200_1250 (&ctxt, 1200L);
      stat = processResult (&ctxt, stat, "UInt32_1200_1250.dat");
   }

   /* Encode INTEGER (0..255,...) sample */
   if (stat >= 0) {
      printf ("encode UInt8Ext value 120..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_UInt8Ext (&ctxt, 120L);
      stat = processResult (&ctxt, stat, "UInt8Ext.dat");
   }

   /* Encode INTEGER (-128..127) sample */
   if (stat >= 0) {
      printf ("encode Int8 value 120..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_Int8 (&ctxt, 120L);
      stat = processResult (&ctxt, stat, "Int8.dat");
   }

   /* Encode INTEGER (-1000..1000) sample */
   if (stat >= 0) {
      printf ("encode Int_Neg1000_1000 value -129..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_Int_Neg1000_1000 (&ctxt, -129L);
      stat = processResult (&ctxt, stat, "Int_Neg1000_1000.dat");
   }

   /* Encode INTEGER {a(1),b(2)} sample */
   if (stat >= 0) {
      printf ("encode IntWithNamedNumbers value 3..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_IntWithNamedNumbers (&ctxt, 3L);
      stat = processResult (&ctxt, stat, "IntWithNamedNumbers.dat");
   }

   /* Encode INTEGER {a(1),b(2)} (0..65535) sample */
   if (stat >= 0) {
      printf ("encode ConstrIntWithNamedNumbers value 3..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_ConstrIntWithNamedNumbers (&ctxt, 3L);
      stat = processResult (&ctxt, stat, "ConstrIntWithNamedNumbers.dat");
   }

   /* Encode INTEGER (-128..127)(0..MAX) samples */
   if (stat >= 0) {
      printf ("encode IntWith2Ranges value 12..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_IntWith2Ranges (&ctxt, 12L);
      stat = processResult (&ctxt, stat, "IntWith2Ranges.dat");
   }
   if (stat >= 0) {
      printf ("encode IntWith2Ranges value -128..\n");
      rtxInitContextBuffer (&ctxt, buffer, sizeof(buffer));
      stat = OEREnc_IntWith2Ranges (&ctxt, -128L);
      /* expected result is constraint violation error */
      if (stat == RTERR_CONSVIO) stat = 0;
      else { printf ("ERROR: unexpected status %d returned\n", stat); }
   }

   rtFreeContext (&ctxt);

   return stat;
}
