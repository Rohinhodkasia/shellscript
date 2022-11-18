#include "SS-Protocol.h"
#include "MAP-MobileServiceOperations.h"
#include "rtxsrc/rtxCommon.h"

#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   SS_Operations_ROSE_PDU pdu;
   SS_Operations_ROSE_PDU_invoke invoke;
   SS_ForBS_Code forBSCode;
   BearerServiceCode bearerService;
   OSCTXT     ctxt;
   int        i, len, stat;
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

   /* Populate PDU data structure */
   asn1Init_SS_Operations_ROSE_PDU (&pdu);
   pdu.t = T_SS_Operations_ROSE_PDU_invoke;
   pdu.u.invoke = &invoke;

   asn1Init_SS_Operations_ROSE_PDU_invoke (&invoke);
   invoke.m.argumentPresent = 1;
   invoke.invokeId.t = T_InvokeId_present;
   invoke.invokeId.u.present = 1;
   asn1SetTC_SS_Operations_ROSE_PDU_invoke_activateSS (&ctxt, &invoke, &forBSCode);

   asn1Init_SS_ForBS_Code (&forBSCode);
   forBSCode.ss_Code.data[0] = 0x12;
   forBSCode.m.basicServicePresent = 1;
   forBSCode.basicService.t = T_BasicServiceCode_bearerService;
   forBSCode.basicService.u.bearerService = &bearerService;
   bearerService.data[0] = 0x34;

   /* Encode - uses dynamic encode buffer*/
   xe_setp (&ctxt, 0, 0);

   len = asn1E_SS_Operations_ROSE_PDU (&ctxt, &pdu, ASN1EXPL);
   if (len > 0) {
      msgptr = xe_getp (&ctxt);
      if (trace) {
         printf ("Hex dump of encoded record:\n");
         rtxHexDump (msgptr, len);
         
         printf ("Binary dump:\n");
         xu_dump2 (&ctxt, msgptr);
      }
   }
   else {
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return (-1);
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
