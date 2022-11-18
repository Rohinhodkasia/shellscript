/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.4.A, Date: 18-Dec-2010.
 */
#include "Test.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxStreamFile.h"

int main (int argc, char** argv)
{
   TestSeq* pdata;
   OSCTXT     ctxt;
   OSOCTET*   msgptr;
   int        i, len, stat;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [-v] [-o <filename>]  [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
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

   /* Populate pdata with test data */
   pdata = rtxMemAllocType (&ctxt, TestSeq);
   asn1Init_TestSeq (pdata);
   pdata->m.objectName4Present = 1;
   pdata->m.objectName5Present = 1;

   pdata->objectName1.numocts = 5;
   memcpy ((char*)pdata->objectName1.data, "NTCIP", 5);

   pdata->objectName2 = 5;
   pdata->objectName3 = 120;

   pdata->objectName4.numbits = 8;
   pdata->objectName4.data[0] = 0x18;

   pdata->objectName5.numocts = 4;
   memcpy ((char*)pdata->objectName5.data, "TEST", 4);

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_TestSeq ("data", pdata);
      printf ("\n");
   }

   /* Create file output stream */
   stat = rtxStreamFileCreateWriter (&ctxt, filename);
   if (stat < 0) {
      printf ("Create file output stream failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Encode */
   stat = OEREnc_TestSeq (&ctxt, pdata);
   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   stat = rtxStreamClose (&ctxt);
   if (stat < 0) {
      printf ("Close stream failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Read message into memory */
   stat = rtxFileReadBinary (&ctxt, filename, &msgptr, &len);
   if (stat < 0) {
      printf ("rtxFileReadBinary failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
   }

   rtFreeContext (&ctxt);

   return 0;
}