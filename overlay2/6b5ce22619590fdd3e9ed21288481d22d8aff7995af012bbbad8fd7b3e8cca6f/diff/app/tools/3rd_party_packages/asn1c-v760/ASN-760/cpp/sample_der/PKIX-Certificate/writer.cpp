/**
 * This sample writer program writes a binary-encoded DER certificate
 * using the PKIX standard.
 */
#include "PKIX1Explicit-2009.h"
#include "PKIX-CommonTypes-2009.h"
#include "AlgorithmInformation-2009.h"
#include "PKIX1Implicit-2009.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"


int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSBOOL       dump = FALSE;
   OSBOOL       trace = TRUE;
   OSBOOL       verbose = FALSE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int          i, len, stat;

   /* Process Command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-dump")) dump = TRUE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            printf ("   -dump     generate a hex dump file\n");
            return 1;
         }
      }
   }

   /* Create an instance of the compiler generated class.
      This example uses a dynamic message buffer..*/
   ASN1BEREncodeBuffer encodeBuffer (0,0);
   encodeBuffer.setDiag(verbose);
   OSCTXT* pctxt = encodeBuffer.getCtxtPtr();
   ASN1T_Certificate msgData;

   /* Populate Certificate structure to be encoded */
   asn1Init_Certificate (&msgData, TRUE, pctxt);
   msgData.toBeSigned.version = 2;

   msgData.toBeSigned.serialNumber =
      (const char*)"160118841221132149945952828414366461591";

   {
      msgData.toBeSigned.signature_.algorithm.numids = 7;
      msgData.toBeSigned.signature_.algorithm.subid[0] = 1;
      msgData.toBeSigned.signature_.algorithm.subid[1] = 2;
      msgData.toBeSigned.signature_.algorithm.subid[2] = 840;
      msgData.toBeSigned.signature_.algorithm.subid[3] = 113549;
      msgData.toBeSigned.signature_.algorithm.subid[4] = 1;
      msgData.toBeSigned.signature_.algorithm.subid[5] = 1;
      msgData.toBeSigned.signature_.algorithm.subid[6] = 2;
   }

   msgData.toBeSigned.signature_.m.parametersPresent = 1;
   /* Populate open type with encoded string
      - example uses arbitray string, users 
      should populate the encoded string of 
      appropriate type. The "-tables" option
      of compiler supports appropriate type 
      encoded string generation. */
   {
      static const OSOCTET testdata[] = {0x05, 0x00};
      msgData.toBeSigned.signature_.parameters.data = (const OSOCTET*)rtxMemAllocZ(pctxt, 2);
      msgData.toBeSigned.signature_.parameters.numocts = 2;
      OSCRTLSAFEMEMCPY ((void*)msgData.toBeSigned.signature_.parameters.data, 2, testdata, 2);
   }

   msgData.toBeSigned.issuer.t =  1;
   msgData.toBeSigned.issuer.u.rdnSequence = rtxMemAllocTypeZ (pctxt, ASN1T_RDNSequence);
   {
      ASN1T_RelativeDistinguishedName* rdn = rtxMemAllocTypeZ (pctxt, ASN1T_RelativeDistinguishedName);
      ASN1T_SingleAttribute* sa = rtxMemAllocTypeZ (pctxt, ASN1T_SingleAttribute);
      static const OSOCTET testdata[] = { 0x13, 0x02, 0x43, 0x41 };

      sa->type.numids = 4;
      sa->type.subid[0] = 2;
      sa->type.subid[1] = 5;
      sa->type.subid[2] = 4;
      sa->type.subid[3] = 6;
      sa->value.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 4);
      sa->value.numocts = 4;
      OSCRTLSAFEMEMCPY ((void*)sa->value.data, 4, testdata, 4);
      rtxDListAppend (pctxt, rdn, sa);
      rtxDListAppend (pctxt, msgData.toBeSigned.issuer.u.rdnSequence, rdn);
   }
   {
      ASN1T_RelativeDistinguishedName* rdn = rtxMemAllocTypeZ (pctxt, ASN1T_RelativeDistinguishedName);
      ASN1T_SingleAttribute* sa = rtxMemAllocTypeZ (pctxt, ASN1T_SingleAttribute);
      static const OSOCTET testdata[] = { 
         0x13, 0x16, 0x42, 0x6F, 0x76, 0x69, 0x6E, 0x65, 0x20, 0x42,
         0x61, 0x6C, 0x6C, 0x69, 0x73, 0x74, 0x69, 0x63, 0x73, 0x2C,
         0x20, 0x49, 0x6E, 0x63 };

      sa->type.numids = 4;
      sa->type.subid[0] = 2;
      sa->type.subid[1] = 5;
      sa->type.subid[2] = 4;
      sa->type.subid[3] = 10;
      sa->value.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 24);
      sa->value.numocts = 24;
      OSCRTLSAFEMEMCPY ((void*)sa->value.data, 24, testdata, 24);
      rtxDListAppend (pctxt, rdn, sa);
      rtxDListAppend (pctxt, msgData.toBeSigned.issuer.u.rdnSequence, rdn);
   }
   {
      ASN1T_RelativeDistinguishedName* rdn = rtxMemAllocTypeZ (pctxt, ASN1T_RelativeDistinguishedName);
      ASN1T_SingleAttribute* sa = rtxMemAllocTypeZ (pctxt, ASN1T_SingleAttribute);
      static const OSOCTET testdata[] = { 
         0x13, 0x17, 0x54, 0x65, 0x73, 0x74, 0x20, 0x53, 0x65, 0x63,
         0x75, 0x72, 0x69, 0x74, 0x79, 0x20, 0x41, 0x75, 0x74, 0x68,
         0x6F, 0x72, 0x69, 0x74, 0x79 };

      sa->type.numids = 4;
      sa->type.subid[0] = 2;
      sa->type.subid[1] = 5;
      sa->type.subid[2] = 4;
      sa->type.subid[3] = 3;
      sa->value.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 25);
      sa->value.numocts = 25;
      OSCRTLSAFEMEMCPY ((void*)sa->value.data, 25, testdata, 25);
      rtxDListAppend (pctxt, rdn, sa);
      rtxDListAppend (pctxt, msgData.toBeSigned.issuer.u.rdnSequence, rdn);
   }

   msgData.toBeSigned.validity.notBefore.t =  1;
   msgData.toBeSigned.validity.notBefore.u.utcTime = "970123050000Z";

   msgData.toBeSigned.validity.notAfter.t =  1;
   msgData.toBeSigned.validity.notAfter.u.utcTime = "010123045959Z";

   msgData.toBeSigned.subject.t =  1;
   msgData.toBeSigned.subject.u.rdnSequence = rtxMemAllocTypeZ (pctxt, ASN1T_RDNSequence);
   {
      ASN1T_RelativeDistinguishedName* rdn = rtxMemAllocTypeZ (pctxt, ASN1T_RelativeDistinguishedName);
      ASN1T_SingleAttribute* sa = rtxMemAllocTypeZ (pctxt, ASN1T_SingleAttribute);
      static const OSOCTET testdata[] = { 0x13, 0x02, 0x43, 0x41 };

      sa->type.numids = 4;
      sa->type.subid[0] = 2;
      sa->type.subid[1] = 5;
      sa->type.subid[2] = 4;
      sa->type.subid[3] = 6;
      sa->value.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 4);
      sa->value.numocts = 4;
      OSCRTLSAFEMEMCPY ((void*)sa->value.data, 4, testdata, 4);
      rtxDListAppend (pctxt, rdn, sa);
      rtxDListAppend (pctxt, msgData.toBeSigned.subject.u.rdnSequence, rdn);
   }
   {
      ASN1T_RelativeDistinguishedName* rdn = rtxMemAllocTypeZ (pctxt, ASN1T_RelativeDistinguishedName);
      ASN1T_SingleAttribute* sa = rtxMemAllocTypeZ (pctxt, ASN1T_SingleAttribute);
      static const OSOCTET testdata[] = { 
         0x13, 0x16, 0x42, 0x6F, 0x76, 0x69, 0x6E, 0x65, 0x20, 0x42,
         0x61, 0x6C, 0x6C, 0x69, 0x73, 0x74, 0x69, 0x63, 0x73, 0x2C,
         0x20, 0x49, 0x6E, 0x63 };

      sa->type.numids = 4;
      sa->type.subid[0] = 2;
      sa->type.subid[1] = 5;
      sa->type.subid[2] = 4;
      sa->type.subid[3] = 10;
      sa->value.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 24);
      sa->value.numocts = 24;
      OSCRTLSAFEMEMCPY ((void*)sa->value.data, 24, testdata, 24);
      rtxDListAppend (pctxt, rdn, sa);
      rtxDListAppend (pctxt, msgData.toBeSigned.subject.u.rdnSequence, rdn);
   }
   {
      ASN1T_RelativeDistinguishedName* rdn = rtxMemAllocTypeZ (pctxt, ASN1T_RelativeDistinguishedName);
      ASN1T_SingleAttribute* sa = rtxMemAllocTypeZ (pctxt, ASN1T_SingleAttribute);
      static const OSOCTET testdata[] = { 
         0x13, 0x17, 0x54, 0x65, 0x73, 0x74, 0x20, 0x53, 0x65, 0x63,
         0x75, 0x72, 0x69, 0x74, 0x79, 0x20, 0x41, 0x75, 0x74, 0x68,
         0x6F, 0x72, 0x69, 0x74, 0x79 };

      sa->type.numids = 4;
      sa->type.subid[0] = 2;
      sa->type.subid[1] = 5;
      sa->type.subid[2] = 4;
      sa->type.subid[3] = 3;
      sa->value.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 25);
      sa->value.numocts = 25;
      OSCRTLSAFEMEMCPY ((void*)sa->value.data, 25, testdata, 25);
      rtxDListAppend (pctxt, rdn, sa);
      rtxDListAppend (pctxt, msgData.toBeSigned.subject.u.rdnSequence, rdn);
   }

   {
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm.numids = 7;
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm.subid[0] = 1;
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm.subid[1] = 2;
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm.subid[2] = 840;
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm.subid[3] = 113549;
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm.subid[4] = 1;
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm.subid[5] = 1;
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm.subid[6] = 1;
   }

   msgData.toBeSigned.subjectPublicKeyInfo.algorithm.m.parametersPresent = 1;
   /* Populate open type with encoded string
      - example uses arbitray string, users 
      should populate the encoded string of 
      appropriate type. The "-tables" option
      of compiler supports appropriate type 
      encoded string generation. */
   {
      static const OSOCTET testdata[] = {0x05, 0x00 };
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.parameters.data = (const OSOCTET*)rtxMemAllocZ(pctxt, 2);
      msgData.toBeSigned.subjectPublicKeyInfo.algorithm.parameters.numocts = 2;
      OSCRTLSAFEMEMCPY ((void*)msgData.toBeSigned.subjectPublicKeyInfo.algorithm.parameters.data, 2, testdata, 2);
   }

   msgData.toBeSigned.subjectPublicKeyInfo.subjectPublicKey.numbits = 1632;
   {
      static const OSOCTET testdata[] = {
         0x30, 0x81, 0xC9, 0x02, 0x81, 0xC1, 0x00, 0xF2, 0x93, 0x35, 0x62,
         0x9E, 0x5B, 0x5F, 0x53, 0xCB, 0xCF, 0x27, 0x6D, 0x6A, 0x30, 0xD9,
         0x9B, 0xE7, 0x92, 0xD4, 0x6E, 0xB3, 0x52, 0x20, 0x1A, 0x25, 0x50,
         0xFB, 0x4F, 0x61, 0x92, 0x2B, 0xA7, 0x9E, 0x9C, 0x67, 0xD2, 0xED,
         0x1F, 0x54, 0x88, 0xC6, 0xC2, 0xAE, 0x82, 0x76, 0xF1, 0xBF, 0x44,
         0xE1, 0x06, 0xE0, 0xB2, 0xAC, 0x93, 0x28, 0x11, 0xDF, 0xF3, 0xC2,
         0xB2, 0x65, 0x3A, 0xB6, 0x77, 0x9E, 0x06, 0x0C, 0x50, 0xC8, 0x1A,
         0x3E, 0x33, 0xA1, 0x37, 0x73, 0x72, 0xAE, 0x48, 0xC9, 0x45, 0x36,
         0xA6, 0xF0, 0xC7, 0x2F, 0xB3, 0xE6, 0x32, 0xC6, 0xEB, 0xF7, 0x8E,
         0x2F, 0x56, 0x91, 0x38, 0x0D, 0x4C, 0xCD, 0x10, 0x31, 0xFD, 0xC3,
         0xF8, 0x86, 0x3E, 0xBD, 0x83, 0x22, 0xAD, 0x4A, 0x6E, 0x44, 0x59,
         0xA9, 0x8C, 0x74, 0x21, 0x63, 0x76, 0xB3, 0x07, 0x11, 0x3B, 0x9C,
         0x30, 0x83, 0xF0, 0x68, 0x61, 0x7E, 0x8B, 0xA3, 0xFC, 0x1B, 0x5F,
         0x59, 0x6E, 0x38, 0xEA, 0x6B, 0x6A, 0xDB, 0x7B, 0xC4, 0x76, 0xBA,
         0x55, 0xE3, 0xD9, 0xD5, 0x7B, 0xA8, 0x06, 0xCB, 0x23, 0xCA, 0x0F,
         0xD6, 0x81, 0xFA, 0xF0, 0xB5, 0x70, 0xD6, 0x06, 0xB3, 0x2E, 0x20,
         0xB8, 0xC0, 0xCA, 0xA5, 0x99, 0x08, 0xE0, 0xC6, 0x1A, 0xDB, 0x4D,
         0x95, 0xBB, 0x8D, 0x61, 0x97, 0xE4, 0x3F, 0x56, 0xEA, 0x83, 0xEE,
         0x75, 0x02, 0x03, 0x01, 0x00, 0x01 };
      msgData.toBeSigned.subjectPublicKeyInfo.subjectPublicKey.data = (const OSOCTET*)rtxMemAllocZ(pctxt, 204);
      OSCRTLSAFEMEMCPY ((void*)msgData.toBeSigned.subjectPublicKeyInfo.subjectPublicKey.data, 204, testdata, 204);
   }

   msgData.toBeSigned.m.issuerUniqueIDPresent = 1;
   msgData.toBeSigned.issuerUniqueID.numbits = 128;
   {
      static const OSOCTET testdata[] = {
         0x78, 0x75, 0xC4, 0x61, 0x75, 0x51, 0x11, 0xD0, 0x92, 0x43, 0x08,
         0x00, 0x09, 0x7A, 0x2E, 0x97 };
      msgData.toBeSigned.issuerUniqueID.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 16);
      OSCRTLSAFEMEMCPY ((void*)msgData.toBeSigned.issuerUniqueID.data, 16, testdata, 16);
   }

   msgData.toBeSigned.m.subjectUniqueIDPresent = 1;
   msgData.toBeSigned.subjectUniqueID.numbits = 128;
   {
      static const OSOCTET testdata[] = {
         0x78, 0x75, 0xC4, 0x61, 0x75, 0x51, 0x11, 0xD0, 0x92, 0x43, 0x08,
         0x00, 0x09, 0x7A, 0x2E, 0x97 };
      msgData.toBeSigned.subjectUniqueID.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 16);
      OSCRTLSAFEMEMCPY ((void*)msgData.toBeSigned.subjectUniqueID.data, 16, testdata, 16);
   }

   msgData.toBeSigned.m._v2ExtPresent = 1;
   msgData.toBeSigned.m.extensionsPresent = 1;
   msgData.toBeSigned.m._v3ExtPresent = 1;
   {
      OSRTDList* plist = &msgData.toBeSigned.extensions;
      ASN1T_Extension* pdata;
      rtxDListInit (plist);
      pdata = rtxMemAllocTypeZ (pctxt, ASN1T_Extension);
      static const OSOCTET testdata[] = {
         0x30, 0x06, 0x01, 0x01, 0xFF, 0x02, 0x01, 0xFF };
      pdata->extnID.numids = 4;
      pdata->extnID.subid[0] = 2;
      pdata->extnID.subid[1] = 5;
      pdata->extnID.subid[2] = 29;
      pdata->extnID.subid[3] = 19;
      pdata->critical = TRUE;
      pdata->extnValue.data = (const OSOCTET*)rtxMemAllocZ (pctxt, 8);
      pdata->extnValue.numocts = 8;
      OSCRTLSAFEMEMCPY ((void*)pdata->extnValue.data, 8, testdata, 8);
      rtxDListAppend (pctxt, plist, (void*)pdata);
   }

   {
      msgData.algorithm.algorithm.numids = 7;
      msgData.algorithm.algorithm.subid[0] = 1;
      msgData.algorithm.algorithm.subid[1] = 2;
      msgData.algorithm.algorithm.subid[2] = 840;
      msgData.algorithm.algorithm.subid[3] = 113549;
      msgData.algorithm.algorithm.subid[4] = 1;
      msgData.algorithm.algorithm.subid[5] = 1;
      msgData.algorithm.algorithm.subid[6] = 2;
   }

   msgData.algorithm.m.parametersPresent = 1;
   /* Populate open type with encoded string
      - example uses arbitray string, users 
      should populate the encoded string of 
      appropriate type. The "-tables" option
      of compiler supports appropriate type 
      encoded string generation. */
   {
      static const OSOCTET testdata[] = {0x05, 0x00 };
      msgData.algorithm.parameters.data = (const OSOCTET*)rtxMemAllocZ(pctxt, 2);
      msgData.algorithm.parameters.numocts = 2;
      OSCRTLSAFEMEMCPY ((void*)msgData.algorithm.parameters.data, 2, testdata, 2);
   }

   msgData.signature_.numbits = 1536;
   {
      static const OSOCTET testdata[] = {
         0x30, 0x81, 0xB6, 0xBD, 0x6C, 0xC8, 0xF9, 0xF6, 0xD8, 0x37, 0xBB,
         0xD5, 0x9B, 0x94, 0xA3, 0xA5, 0xCF, 0x74, 0xC9, 0xA1, 0xFE, 0x4D,
         0x90, 0xA0, 0xB4, 0x6F, 0x4E, 0x42, 0xAC, 0x1D, 0x84, 0x6D, 0xE9,
         0x87, 0xF9, 0x56, 0x08, 0xD8, 0x5E, 0xCB, 0xF0, 0x71, 0xA7, 0xC9,
         0x57, 0x32, 0x8A, 0x31, 0x86, 0xF5, 0x34, 0xA5, 0xD2, 0x6A, 0xC4,
         0xA0, 0x80, 0x8B, 0xCE, 0xF3, 0x7F, 0x9C, 0x96, 0xB1, 0x34, 0x66,
         0xC5, 0x41, 0x03, 0xD8, 0x6B, 0x76, 0xB9, 0x33, 0x41, 0x17, 0x6F,
         0xAE, 0x3F, 0xB8, 0x4A, 0x83, 0xC8, 0x16, 0xE5, 0xCC, 0x9A, 0x4B,
         0x2A, 0x56, 0x86, 0xD9, 0x95, 0xC6, 0xF2, 0x3D, 0xE2, 0x8F, 0x64,
         0x8C, 0xF1, 0xDE, 0x61, 0x7F, 0xDE, 0xCB, 0x95, 0x50, 0x80, 0xC3,
         0x4B, 0x0E, 0xF8, 0x7F, 0x1E, 0x45, 0xC6, 0xFE, 0x4F, 0x16, 0x98,
         0x25, 0x24, 0x59, 0x9D, 0x9A, 0xCD, 0xB6, 0xE0, 0xFD, 0xFE, 0x9B,
         0x37, 0x04, 0xB4, 0x7B, 0x58, 0x3D, 0x41, 0x94, 0x9B, 0x1B, 0x89,
         0x61, 0x18, 0x4B, 0x3C, 0x75, 0xF0, 0x16, 0x4B, 0xC6, 0xE1, 0x46,
         0xC2, 0x3A, 0x75, 0xDE, 0x09, 0x0C, 0x32, 0x92, 0x66, 0x79, 0x90,
         0x4F, 0x11, 0xD7, 0xFB, 0xB8, 0xBB, 0x7C, 0x43, 0xC5, 0xA8, 0xC8,
         0xBD, 0xD7, 0x42, 0x59, 0x5A, 0x54, 0xC0, 0xA2, 0xA9, 0x39, 0xB2,
         0xB5, 0x9D, 0x63, 0x65, 0xD8 };
      msgData.signature_.data = (const OSOCTET*)rtxMemAllocZ(pctxt, 192);
      OSCRTLSAFEMEMCPY ((void*)msgData.signature_.data, 192, testdata, 192);
   }

   ASN1C_Certificate CertificatePDU (encodeBuffer, msgData);

   // Populate structure of generated type
   //CertificatePDU.genTestInstance();

   /* Encode */
   if ((len = CertificatePDU.Encode ()) >= 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump (len);
         printf ("Binary dump:\n");
         encodeBuffer.binDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }
   /* Write the encoded message out to the output file */
   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Write to file failed\n");
      encodeBuffer.printErrorInfo();
      return stat;
   }

   /* Create a dump file */
   if (dump) {
      if ((fp = fopen ("message.dmp", "w"))) {
         rtxHexDumpToFile (fp, msgptr, len);
         fclose (fp);
      }
      else {
         printf ("Error opening message.dmp for write access\n");
         return -1;
      }
   }
   return 0;
}
