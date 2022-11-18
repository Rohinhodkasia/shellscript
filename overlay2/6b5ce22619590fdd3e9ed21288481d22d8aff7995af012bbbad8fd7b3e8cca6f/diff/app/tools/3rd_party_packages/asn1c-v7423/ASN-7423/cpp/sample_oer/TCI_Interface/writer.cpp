/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 7.3.B, Date: 04-Jan-2019.
 */
#include "TCI-Dispatcher.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxDiagBitTrace.h"

#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   int        i, stat;
   OSSIZE     len;
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

   /* Create an instance of the compiler generated class.
      This example uses a dynamic message buffer..*/
   ASN1OEREncodeBuffer encodeBuffer;
   ASN1T_TCIMsg data;
   ASN1C_TCIMsg TCIMsgPDU (encodeBuffer, data);

   // Populate structure of generated type
   OSCTXT* pctxt = TCIMsgPDU.getCtxtPtr();
   ASN1T_TCIMsg* pvalue = &data;
   //asn1Init_TCIMsg (pvalue, FALSE, pctxt);

   pvalue->version = 1;

   pvalue->time_ = OSUI64CONST(886110268624495200);

   pvalue->frame.t =  1;
   pvalue->frame.u.d16093 = rtxMemAllocTypeZ (pctxt, ASN1T_TCI16093);
   pvalue->frame.u.d16093->t =  2;
   pvalue->frame.u.d16093->u.response = rtxMemAllocTypeZ (pctxt, ASN1T_Response);

   pvalue->frame.u.d16093->u.response->msgID = 217;

   pvalue->frame.u.d16093->u.response->resultCode = ResultCode::rcSuccess;

   pvalue->frame.u.d16093->u.response->m.exceptionPresent = 1;

   pvalue->frame.u.d16093->u.response->exception.type = ExceptionType::info;

   pvalue->frame.u.d16093->u.response->exception.m.idPresent = 1;
   pvalue->frame.u.d16093->u.response->exception.id = ExceptionId::critical_error;

   pvalue->frame.u.d16093->u.response->exception.m.modulePresent = 1;
   pvalue->frame.u.d16093->u.response->exception.module = OSUTF8("cOdObR:MLCX8hJH@5b@SE4Z6u3uklp_7dnfW8pr:9suUMLKlnkqJD2sLkUVOsI7I2C8M");

   pvalue->frame.u.d16093->u.response->exception.m.descriptionPresent = 1;
   pvalue->frame.u.d16093->u.response->exception.description = OSUTF8("0VX");

   /* Encode */

   if ((stat = TCIMsgPDU.Encode ()) == 0)
   {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.getMsgLen ();
   }
   else
   {
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

   return 0;
}