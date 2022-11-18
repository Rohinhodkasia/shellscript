/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.8.A, Date: 19-Dec-2014.
 */
#include "CryptographicMessageSyntax-2009.h"
#include "PKIXAttributeCertificate-2009.h"
#include "AttributeCertificateVersion1-2009.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>
#include "rtPrintStream.h" 

void writeToStdout(void* pPrntStrmInfo, const char* fmtspec, va_list arglist) {
   vprintf(fmtspec, arglist);
   return;
}

#define MAXREADLEN 1024

int main (int argc, char** argv)
{
   ContentInfo data;
   OSCTXT      ctxt, xmlCtxt;
   OSOCTET     msgbuf[] = {
      0x30, 0x82, 0x01, 0xFE, 0x06, 0x09, 0x2A, 0x86,
      0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x02, 0xA0,
      0x82, 0x01, 0xEF, 0x30, 0x82, 0x01, 0xEB, 0x02,
      0x01, 0x01, 0x31, 0x0F, 0x30, 0x0D, 0x06, 0x09,
      0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01,
      0x05, 0x05, 0x00, 0x30, 0x45, 0x06, 0x09, 0x2A,
      0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x01,
      0xA0, 0x38, 0x04, 0x36, 0x54, 0x68, 0x65, 0x20,
      0x56, 0x65, 0x6E, 0x74, 0x75, 0x72, 0x65, 0x73,
      0x20, 0x61, 0x72, 0x65, 0x20, 0x74, 0x68, 0x65,
      0x20, 0x62, 0x65, 0x73, 0x74, 0x20, 0x73, 0x75,
      0x72, 0x66, 0x2D, 0x69, 0x6E, 0x73, 0x74, 0x72,
      0x75, 0x6D, 0x65, 0x6E, 0x74, 0x61, 0x6C, 0x20,
      0x62, 0x61, 0x6E, 0x64, 0x20, 0x65, 0x76, 0x65,
      0x72, 0x21, 0x31, 0x82, 0x01, 0x8C, 0x30, 0x82,
      0x01, 0x88, 0x02, 0x01, 0x01, 0x30, 0x81, 0xE1,
      0x30, 0x81, 0xCC, 0x31, 0x17, 0x30, 0x15, 0x06,
      0x03, 0x55, 0x04, 0x0A, 0x13, 0x0E, 0x56, 0x65,
      0x72, 0x69, 0x53, 0x69, 0x67, 0x6E, 0x2C, 0x20,
      0x49, 0x6E, 0x63, 0x2E, 0x31, 0x1F, 0x30, 0x1D,
      0x06, 0x03, 0x55, 0x04, 0x0B, 0x13, 0x16, 0x56,
      0x65, 0x72, 0x69, 0x53, 0x69, 0x67, 0x6E, 0x20,
      0x54, 0x72, 0x75, 0x73, 0x74, 0x20, 0x4E, 0x65,
      0x74, 0x77, 0x6F, 0x72, 0x6B, 0x31, 0x46, 0x30,
      0x44, 0x06, 0x03, 0x55, 0x04, 0x0B, 0x13, 0x3D,
      0x77, 0x77, 0x77, 0x2E, 0x76, 0x65, 0x72, 0x69,
      0x73, 0x69, 0x67, 0x6E, 0x2E, 0x63, 0x6F, 0x6D,
      0x2F, 0x72, 0x65, 0x70, 0x6F, 0x73, 0x69, 0x74,
      0x6F, 0x72, 0x79, 0x2F, 0x52, 0x50, 0x41, 0x20,
      0x49, 0x6E, 0x63, 0x6F, 0x72, 0x70, 0x2E, 0x20,
      0x42, 0x79, 0x20, 0x52, 0x65, 0x66, 0x2E, 0x2C,
      0x4C, 0x49, 0x41, 0x42, 0x2E, 0x4C, 0x54, 0x44,
      0x28, 0x63, 0x29, 0x39, 0x38, 0x31, 0x48, 0x30,
      0x46, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x3F,
      0x56, 0x65, 0x72, 0x69, 0x53, 0x69, 0x67, 0x6E,
      0x20, 0x43, 0x6C, 0x61, 0x73, 0x73, 0x20, 0x31,
      0x20, 0x43, 0x41, 0x20, 0x49, 0x6E, 0x64, 0x69,
      0x76, 0x69, 0x64, 0x75, 0x61, 0x6C, 0x20, 0x53,
      0x75, 0x62, 0x73, 0x63, 0x72, 0x69, 0x62, 0x65,
      0x72, 0x2D, 0x50, 0x65, 0x72, 0x73, 0x6F, 0x6E,
      0x61, 0x20, 0x4E, 0x6F, 0x74, 0x20, 0x56, 0x61,
      0x6C, 0x69, 0x64, 0x61, 0x74, 0x65, 0x64, 0x02,
      0x10, 0x01, 0x47, 0x8A, 0xE1, 0xE3, 0xBF, 0xE9,
      0x99, 0xFB, 0xC0, 0xAA, 0x9D, 0x92, 0xD9, 0xED,
      0x38, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48,
      0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05, 0x05, 0x00,
      0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86,
      0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x04,
      0x81, 0x80, 0x08, 0x4F, 0x8F, 0xC8, 0x0E, 0x15,
      0x62, 0x91, 0x4F, 0xF8, 0xA7, 0x38, 0x95, 0x88,
      0xC3, 0x83, 0x90, 0x09, 0xD5, 0xAE, 0xB3, 0x3D,
      0xBD, 0x22, 0x2D, 0xFC, 0xAE, 0x18, 0x91, 0xCF,
      0xDC, 0xCC, 0xF6, 0xB8, 0x7B, 0x18, 0x8B, 0x90,
      0xB6, 0xFC, 0xD3, 0xA5, 0x2A, 0x00, 0x12, 0x7F,
      0x30, 0xCC, 0xB1, 0x2E, 0x1F, 0x32, 0x77, 0x1C,
      0x10, 0xF2, 0xFF, 0xC8, 0xE5, 0x16, 0xD2, 0x16,
      0xE2, 0xD4, 0xDD, 0xF2, 0x32, 0xB9, 0x87, 0x46,
      0xB2, 0xF1, 0x08, 0xEC, 0x26, 0x31, 0x85, 0x21,
      0x56, 0x75, 0x71, 0xEA, 0x91, 0x4D, 0x60, 0xF1,
      0x82, 0xB6, 0x9D, 0x3F, 0x21, 0x4D, 0xE1, 0x59,
      0x3C, 0x1D, 0xD1, 0xB2, 0x10, 0xE6, 0x90, 0xEE,
      0xB2, 0x09, 0xF6, 0x11, 0x8C, 0x21, 0x5B, 0x38,
      0xF2, 0x96, 0x21, 0xDD, 0xFF, 0x46, 0xF6, 0x8C,
      0xD7, 0x61, 0x44, 0x00, 0x5B, 0x2E, 0x21, 0x7E,
      0x8E, 0x3B   
   } ;
   OSOCTET*    pMsgBuf = msgbuf;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.xml";
   int         i, stat;
   OSSIZE      len = sizeof(msgbuf);

   /* Process command line arguments */
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

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   rtxSetPrintStream(&ctxt, &writeToStdout, (void *) 0);

   stat = xd_setp64 (&ctxt, pMsgBuf, len, 0, 0, 0);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   asn1Init_ContentInfo (&data);

   /* Call compiler generated decode function */
   stat = asn1D_ContentInfo (&ctxt, &data, ASN1EXPL, 0);
   if (stat != 0) {
      printf ("decode of data failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }
   if (trace) {
      asn1PrtToStrm_ContentInfo (&ctxt, "ContentInfo", &data);
   }

   /* Encode to XML */

   stat = rtXmlInitContext (&xmlCtxt);
   if (0 != stat) {
      printf ("context initialization failed\n");
      rtxErrPrint (&xmlCtxt);
      return stat;
   }

   rtxSetDiag (&xmlCtxt, verbose);

   stat = rtXmlSetEncBufPtr (&xmlCtxt, 0, 0);

   if (0 == stat) {
      stat = XmlEnc_ContentInfo_PDU (&xmlCtxt, &data);
   }
   if (0 == stat) {
      if (trace) {
         printf ("encoded XML message:\n");
         puts ((char*)rtXmlGetEncBufPtr(&xmlCtxt));
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&xmlCtxt);
      return stat;
   }
  
   /* Write the encoded message out to the output file */

   stat = rtXmlWriteToFile (&xmlCtxt, filename);
   if (0 != stat) {
      printf ("Error opening %s for write access\n", filename);
      rtxErrPrint (&xmlCtxt);
   }

   rtFreeContext (&ctxt);
   rtFreeContext (&xmlCtxt);

   return 0;
}