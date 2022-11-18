/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.6.A, Date: 12-Nov-2012.
 */
#include "AllTypes.h"
#include "rtxsrc/rtxCommon.h"

int main (int argc, char** argv)
{
   const char* filename = "message.json";
   int         stat, i;
   OSBOOL      trace = TRUE, verbose = FALSE;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] \n");
            printf ("   -v  verbose mode: print debug info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   // Create an instance of the compiler generated class.
   // This example uses a dynamic message buffer..
   OSJSONEncodeBuffer encodeBuffer (0, 0);
   encodeBuffer.setDiag (verbose);
   /* PDU: AllTypes.PersonnelRecord */
   ASN1T_PersonnelRecord msgData;
   ASN1C_PersonnelRecord PersonnelRecordPDU (encodeBuffer, msgData);

   // Populate structure of generated type
   PersonnelRecordPDU.genTestInstance();

   // Encode
   if ((stat = PersonnelRecordPDU.Encode()) == 0) {
      encodeBuffer.nullTerminate();
   
      if (trace) {
         printf ("encoded JSON message:\n");
         printf ((const char*)encodeBuffer.getMsgPtr());
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }

   // Write the encoded message out to the output file
   if (encodeBuffer.write (filename) < 0) {
      printf ("Error writing JSON document to file '%s'\n", filename);
      return -1;
   }
   return 0;
}