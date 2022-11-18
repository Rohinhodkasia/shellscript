#include "S1AP-PDU-Descriptions.h"
#include "S1AP-Constants.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxPrint.h"

int main (int argc, char** argv)
{
   /* PDU: S1AP-PDU-Descriptions.S1AP_PDU */
   S1AP_PDU*  pdata;
   Cause      cause;
   TargetID   targetID;
   TargeteNB_ID eNodeBID;
   ASN1BitStr32 homeENB_ID;
   InitiatingMessage initMsg;
   HandoverRequired handoverRequired;

   OSCTXT     ctxt;
   int        i, len, stat;
   OSBOOL     aligned = !FALSE;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";
   const OSOCTET* msgptr;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [-v] [-o <filename>]  [-notrace]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
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
   pu_setBuffer (&ctxt, 0, 0, aligned);
   pu_setTrace (&ctxt, trace);

   /* Populate PDU structure */
   pdata = rtxMemAllocType (&ctxt, S1AP_PDU);
   asn1Init_S1AP_PDU (pdata);

   pdata->t = T_S1AP_PDU_initiatingMessage;
   pdata->u.initiatingMessage = &initMsg;

   initMsg.procedureCode = ASN1V_id_HandoverPreparation;
   initMsg.criticality = reject;
   initMsg.value.t = 
      T_S1AP_PDU_Descriptions_S1AP_ELEMENTARY_PROCEDURES_handoverPreparation;
   initMsg.value.u.handoverPreparation = &handoverRequired;

   asn1Init_HandoverRequired (&handoverRequired);
   asn1Append_HandoverRequired_protocolIEs_HandoverRequiredIEs_id_MME_UE_S1AP_ID
      (&ctxt, &handoverRequired.protocolIEs, 123456);

   asn1Append_HandoverRequired_protocolIEs_HandoverRequiredIEs_id_HandoverType
      (&ctxt, &handoverRequired.protocolIEs, ltetogeran);

   cause.t = T_Cause_transport;
   cause.u.transport = transport_resource_unavailable;
   asn1Append_HandoverRequired_protocolIEs_HandoverRequiredIEs_id_Cause 
      (&ctxt, &handoverRequired.protocolIEs, &cause);

   OSCRTLMEMSET (&homeENB_ID, 0, sizeof(ASN1BitStr32));
   homeENB_ID.numbits = 28;
   homeENB_ID.data[0] = 0xAA;
   homeENB_ID.data[1] = 0xAA;
   homeENB_ID.data[2] = 0xAA;
   homeENB_ID.data[3] = 0xAA;

   asn1Init_TargeteNB_ID (&eNodeBID);
   stat = rtStringToBCD
      ("123456", eNodeBID.global_ENB_ID.pLMNidentity.data, 3, TRUE);
   if (stat < 0) {
      printf ("rtStringToBCD failed, status = %d\n", stat);
      return stat;
   }

   eNodeBID.global_ENB_ID.eNB_ID.t = T_ENB_ID_homeENB_ID;
   eNodeBID.global_ENB_ID.eNB_ID.u.homeENB_ID = &homeENB_ID;

   stat = rtStringToBCD
      ("2234", eNodeBID.selected_TAI.pLMNidentity.data, 3, TRUE);
   if (stat < 0) {
      printf ("rtStringToBCD failed, status = %d\n", stat);
      return stat;
   }
   eNodeBID.selected_TAI.tAC.data[0] = 0x01;
   eNodeBID.selected_TAI.tAC.data[1] = 0x23;

   asn1Init_TargetID (&targetID);
   targetID.t = T_TargetID_targeteNB_ID;
   targetID.u.targeteNB_ID = &eNodeBID;

   asn1Append_HandoverRequired_protocolIEs_HandoverRequiredIEs_id_TargetID 
      (&ctxt, &handoverRequired.protocolIEs, &targetID);

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_S1AP_PDU ("data", pdata);
      printf ("\n");
   }

   /* Encode */
   stat = asn1PE_S1AP_PDU (&ctxt, pdata);

   msgptr = pe_GetMsgPtr (&ctxt, &len);

   if (trace) {
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
      
      printf ("Binary dump:\n");
      pu_bindump (&ctxt, "data");
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
