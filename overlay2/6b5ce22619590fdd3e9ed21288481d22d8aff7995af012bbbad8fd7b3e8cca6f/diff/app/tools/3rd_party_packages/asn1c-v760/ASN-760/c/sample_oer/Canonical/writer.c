/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.1.A, Date: 10-Nov-2016.
 */
#include "Canonical.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxDiagBitTrace.h"

#include "rtxsrc/rtxPrint.h"
#include "rtxsrc/rtxStreamMemory.h"

int main (int argc, char** argv)
{
   PDU* pdata;
   OSCTXT     ctxt;
   int        i, stat;
   size_t     len;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";
   const OSOCTET* msgptr;

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

   pdata = rtxMemAllocType (&ctxt, PDU);
   asn1Init_PDU (pdata);

   /* should not be encoded */
   pdata->valueWithDefault = "okay";

   /* should be encoded as 14 bits */
   pdata->bitStringNamedRange.numbits = 18;
   pdata->bitStringNamedRange.data[0] = 0x63;
   pdata->bitStringNamedRange.data[1] = 0x64;
   pdata->bitStringNamedRange.data[2] = 0x00;

   {
      OSRTDList* plist2 = &pdata->seqOfOctStrings;
      OSDynOctStr* poctstr;
      rtxDListInit (plist2);

      poctstr = rtxMemAllocTypeZ (&ctxt, OSDynOctStr);
      poctstr->numocts = 0;
      poctstr->data = 0;
      poctstr->numocts = 4;
      poctstr->data = (OSOCTET*) rtxMemAlloc (&ctxt, 4);
      {
         static const OSOCTET testdata[] = {
         0x12, 0x34, 0x56, 0x78
         };
         OSCRTLSAFEMEMCPY ((void*)poctstr->data, 4, testdata, 4);
      }

      rtxDListAppend (&ctxt, plist2, (void*)poctstr);

      poctstr = rtxMemAllocTypeZ (&ctxt, OSDynOctStr);
      poctstr->numocts = 0;
      poctstr->data = 0;
      poctstr->numocts = 2;
      poctstr->data = (OSOCTET*) rtxMemAlloc (&ctxt, 2);
      {
         static const OSOCTET testdata[] = {
         0xab, 0xcd };
         OSCRTLSAFEMEMCPY ((void*)poctstr->data, 2, testdata, 2);
      }

      rtxDListAppend (&ctxt, plist2, (void*)poctstr);

      poctstr = rtxMemAllocTypeZ (&ctxt, OSDynOctStr);
      poctstr->numocts = 0;
      poctstr->data = 0;
      poctstr->numocts = 3;
      poctstr->data = (OSOCTET*) rtxMemAlloc (&ctxt, 3);
      {
         static const OSOCTET testdata[] = {
         0x45, 0x67, 0x89 };
         OSCRTLSAFEMEMCPY ((void*)poctstr->data, 3, testdata, 3);
      }

      rtxDListAppend (&ctxt, plist2, (void*)poctstr);

      poctstr = rtxMemAllocTypeZ (&ctxt, OSDynOctStr);
      poctstr->numocts = 0;
      poctstr->data = 0;
      poctstr->numocts = 2;
      poctstr->data = (OSOCTET*) rtxMemAlloc (&ctxt, 2);
      {
         static const OSOCTET testdata[] = {
         0x41, 0x67 };
         OSCRTLSAFEMEMCPY ((void*)poctstr->data, 2, testdata, 2);
      }

      rtxDListAppend (&ctxt, plist2, (void*)poctstr);
   }

   {
      OSRTDList* plist2 = &pdata->setOfOctStrings;
      OSDynOctStr* poctstr;
      rtxDListInit (plist2);

      poctstr = rtxMemAllocTypeZ (&ctxt, OSDynOctStr);
      poctstr->numocts = 0;
      poctstr->data = 0;
      poctstr->numocts = 4;
      poctstr->data = (OSOCTET*) rtxMemAlloc (&ctxt, 4);
      {
         static const OSOCTET testdata[] = {
         0x12, 0x34, 0x56, 0x78
         };
         OSCRTLSAFEMEMCPY ((void*)poctstr->data, 4, testdata, 4);
      }

      rtxDListAppend (&ctxt, plist2, (void*)poctstr);

      poctstr = rtxMemAllocTypeZ (&ctxt, OSDynOctStr);
      poctstr->numocts = 0;
      poctstr->data = 0;
      poctstr->numocts = 2;
      poctstr->data = (OSOCTET*) rtxMemAlloc (&ctxt, 2);
      {
         static const OSOCTET testdata[] = {
         0xab, 0xcd };
         OSCRTLSAFEMEMCPY ((void*)poctstr->data, 2, testdata, 2);
      }

      rtxDListAppend (&ctxt, plist2, (void*)poctstr);

      poctstr = rtxMemAllocTypeZ (&ctxt, OSDynOctStr);
      poctstr->numocts = 0;
      poctstr->data = 0;
      poctstr->numocts = 3;
      poctstr->data = (OSOCTET*) rtxMemAlloc (&ctxt, 3);
      {
         static const OSOCTET testdata[] = {
         0x45, 0x67, 0x89 };
         OSCRTLSAFEMEMCPY ((void*)poctstr->data, 3, testdata, 3);
      }

      rtxDListAppend (&ctxt, plist2, (void*)poctstr);

      poctstr = rtxMemAllocTypeZ (&ctxt, OSDynOctStr);
      poctstr->numocts = 0;
      poctstr->data = 0;
      poctstr->numocts = 2;
      poctstr->data = (OSOCTET*) rtxMemAlloc (&ctxt, 2);
      {
         static const OSOCTET testdata[] = {
         0x41, 0x67 };
         OSCRTLSAFEMEMCPY ((void*)poctstr->data, 2, testdata, 2);
      }

      rtxDListAppend (&ctxt, plist2, (void*)poctstr);
   }

   pdata->generalizedTime = "19861127100756.314Z";

   pdata->utcTime = "050128100020Z";

   pdata->trueOrFalse = 5;    /* should be encoded as 0xFF */
   pdata->unsignedint = 3452816845;
   pdata->signedint = -842150451;
   pdata->animal = cow;
   pdata->color = white;


   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_PDU ("data", pdata);
      printf ("\n");
   }

   /* Create memory output stream */
   stat = rtxStreamMemoryCreateWriter (&ctxt, 0, 0);
   if (stat < 0) {
      printf ("Create memory output stream failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Encode */
   stat = OEREnc_PDU (&ctxt, pdata);

   msgptr = rtxStreamMemoryGetBuffer (&ctxt, &len);

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
   }
   if (stat < 0) {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }
   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return stat;
   }

   rtFreeContext (&ctxt);

   return 0;
}
