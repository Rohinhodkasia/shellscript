// This reader program uses a buffer approach to decode a file with TS 32.297
// headers and CDRs.#include "IMS-R8-2009-03.h"

#include "IMS-R8-2009-03.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxMemLeakCheck.h"

#include <stdio.h>
#include <stdlib.h>

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int         i, stat;
   unsigned int ui;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   ASN1BERDecodeBuffer decodeBuffer;
   ASN1T_IMSRecord msgData;
   ASN1C_IMSRecord IMSRecordPDU (decodeBuffer, msgData);

   // Read from input file
   decodeBuffer.setDiag (verbose);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus () != 0) {
      printf("Failed opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   ASN1BERTS32297CDRFileHeader fileHeader(&decodeBuffer);

   // Decode TS 32.297 file header
   stat = fileHeader.decode();
   if (stat < 0) {
      printf ("decode of file header failed\n");
      fileHeader.printErrorInfo();
      return stat;
   }
   if (trace) {
      fileHeader.print();
   }
   ASN1BERTS32297CDRHeader cdrHeader(fileHeader);

   for (ui = 1; ui <= fileHeader.getFileHeaderData()->cdrCount; ui++) {

      // Decode TS 32.297 record header
      cdrHeader.init();
      stat = cdrHeader.decode();
      if (stat < 0) {
         printf ("decode of CDR header failed\n");
         cdrHeader.printErrorInfo();
         return stat;
      }
      if (trace) {
         cdrHeader.print();
      }

      // Call compiler generated decode function
      stat = IMSRecordPDU.Decode ();
      if (stat != 0) {
         printf ("decode failed\n");
         decodeBuffer.PrintErrorInfo ();
         return stat;
      }
      IMSRecordPDU.Print ("IMSRecord");
      stat = cdrHeader.nextCdrHeader();
      if (stat != 0) {
         cdrHeader.printErrorInfo();
         return stat;
      }
      IMSRecordPDU.memReset();
   }
   return 0;
}
