#include "CAP-datatypes.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   Component  pdu;
   LegType    legType;
   CallResult callResult;
   ReturnResult result;
   TimeDurationChargingResult timeDurationChargingResult;
   OSCTXT     ctxt;
   int        i, len, stat;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   OSOCTET    msgbuf[1024];
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

   /* Populate variable to be encoded */
   callResult.t = T_CAMEL_CallResult_timeDurationChargingResult;
   callResult.u.timeDurationChargingResult = &timeDurationChargingResult;
   asn1Init_TimeDurationChargingResult (&timeDurationChargingResult);
   timeDurationChargingResult.partyToCharge.t = 
      T_ReceivingSideID_receivingSideID;
   timeDurationChargingResult.partyToCharge.u.receivingSideID = &legType;
   legType.data[0] = 0x22;
   timeDurationChargingResult.timeInformation.t = 
      T_TimeInformation_timeIfNoTariffSwitch;
   timeDurationChargingResult.timeInformation.u.timeIfNoTariffSwitch = 111;
   timeDurationChargingResult.m.callLegReleasedAtTcpExpiryPresent = TRUE;

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_CallResult ("CallResult", &callResult);
      printf ("\n");
   }

   /* Encode - uses static encode buffer*/
   xe_setp (&ctxt, msgbuf, sizeof(msgbuf));

   len = asn1E_CallResult (&ctxt, &callResult, ASN1EXPL);
   if (len > 0) {
      msgptr = xe_getp (&ctxt);
      if (trace) {
         printf ("Hex dump of encoded CallResult:\n");
         rtxHexDump (msgptr, len);
         
         printf ("Binary dump:\n");
         xu_dump2 (&ctxt, msgptr);

         printf ("\n***\n");
      }
   }
   else {
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return (-1);
   }

   /* Populate and encode Component header */
   pdu.t = T_Component_returnResultLast;
   pdu.u.returnResultLast = &result;
   asn1Init_ReturnResult (&result);
   result.invokeID = 2;
   result.m.resultretresPresent = TRUE;
   result.resultretres.opCode.t = T_OPERATION_localValue;
   result.resultretres.opCode.u.localValue = initiateCallAttempt;
   result.resultretres.m.returnparameterPresent = TRUE;
   result.resultretres.returnparameter.numocts = len;
   result.resultretres.returnparameter.data = msgptr;

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_Component ("Component", &pdu);
      printf ("\n");
   }

   len = asn1E_Component (&ctxt, &pdu, ASN1EXPL);
   if (len > 0) {
      msgptr = xe_getp (&ctxt);
      if (trace) {
         printf ("Hex dump of encoded Component:\n");
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
