/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.7.A, Date: 23-Oct-2013.
 */
#include "CAP-datatypes.h"
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

   // Populate and encode CallResult object

   ASN1BEREncodeBuffer encodeBuffer (0,0);
   ASN1T_CallResult callResult;
   ASN1C_CallResult callResultC (encodeBuffer, callResult);

   callResult.t = T_CAMEL_CallResult_timeDurationChargingResult;
   ASN1T_TimeDurationChargingResult* pTimeDurChargeRes =
      callResult.u.timeDurationChargingResult = 
      new_ASN1T_TimeDurationChargingResult (callResultC);

   pTimeDurChargeRes->partyToCharge.t = T_ReceivingSideID_receivingSideID;
   ASN1T_LegType legType;
   pTimeDurChargeRes->partyToCharge.u.receivingSideID = &legType;
   legType.data[0] = 0x22;
   pTimeDurChargeRes->timeInformation.t = 
      T_TimeInformation_timeIfNoTariffSwitch;
   pTimeDurChargeRes->timeInformation.u.timeIfNoTariffSwitch = 111;
   pTimeDurChargeRes->m.callLegReleasedAtTcpExpiryPresent = TRUE;

   if (trace) {
      printf ("The following record will be encoded:\n");
      callResultC.Print ("CallResult");
      printf ("\n");
   }

   if ((len = callResultC.Encode()) >= 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump (len);
         printf ("Binary dump:\n");
         encodeBuffer.binDump ();
         printf ("\n***\n");
      }
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }

   // Populate and encode Component object

   ASN1T_Component component;
   ASN1C_Component componentPDU (encodeBuffer, component);

   ASN1T_ReturnResult result;
   component.t = T_Component_returnResultLast;
   component.u.returnResultLast = &result;
   result.invokeID = 2;
   result.m.resultretresPresent = TRUE;
   result.resultretres.opCode.t = T_OPERATION_localValue;
   result.resultretres.opCode.u.localValue = 
      CAMELOperationLocalvalue::initiateCallAttempt;
   result.resultretres.m.returnparameterPresent = TRUE;
   result.resultretres.returnparameter.numocts = len;
   result.resultretres.returnparameter.data = msgptr;

   if (trace) {
      printf ("The following record will be encoded:\n");
      componentPDU.Print ("Component");
      printf ("\n");
   }

   if ((len = componentPDU.Encode ()) >= 0) {
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

   return 0;
}
