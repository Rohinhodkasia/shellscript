#include "NBAP-PDU-Descriptions.h"
#include "NBAP-Constants.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   /* ASN1C compiler generated variables */
   NBAP_PDU   pduData;
   InitiatingMessage initMsg;
   RadioLinkSetupRequestFDD radioLinkSetupFDD;
   RadioLinkSetupRequestFDD_protocolIEs_element protocolIEs[1];
   RL_InformationList_RL_SetupRqstFDD setupRqstFDD;
   RL_InformationList_RL_SetupRqstFDD_element setupRqstFDD_element;
   DL_CodeInformationItem_RL_SetupRqstFDD dl_CodeInformationItem;

   /* Common run-time variables */
   OSCTXT     ctxt;
   OSOCTET*   msgptr;
   FILE*      fp;
   int        i, len, stat;
   OSBOOL     aligned = TRUE;
   OSBOOL     trace = TRUE;
   OSBOOL     verbose = FALSE;
   const char* filename = "message.dat";

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [ -v ] [ -o <filename>\n");
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

   /* Populate RL_InformationList_RL_SetupRqstFDD_element */

   asn1Init_RL_InformationList_RL_SetupRqstFDD_element (&setupRqstFDD_element);
   setupRqstFDD_element.id = ASN1V_id_RL_InformationItem_RL_SetupRqstFDD;
   setupRqstFDD_element.criticality = Criticality_notify;
   setupRqstFDD_element.value.rL_ID = 25;           /*  INTEGER (0..31) */
   setupRqstFDD_element.value.c_ID = 1000;          /*  INTEGER (0..65535) */
   setupRqstFDD_element.value.
      firstRLS_indicator = FirstRLS_Indicator_first_RLS;
   setupRqstFDD_element.value.frameOffset = 99;     /*  INTEGER (0..255) */
   setupRqstFDD_element.value.chipOffset = 224;     /*  INTEGER (0..38399) */
   setupRqstFDD_element.value.m.propagationDelayPresent = 1;
   setupRqstFDD_element.value.propagationDelay = 22; /* INTEGER (0..255) */
   setupRqstFDD_element.value.m.diversityControlFieldPresent = 1;
   setupRqstFDD_element.value.
      diversityControlField = DiversityControlField_must_not;

   asn1Init_DL_CodeInformationItem_RL_SetupRqstFDD (&dl_CodeInformationItem);
   dl_CodeInformationItem.m.
      transmissionGapPatternSequenceCodeInformationPresent = 1;
   dl_CodeInformationItem.dl_ScramblingCode = 0;
   dl_CodeInformationItem.fdd_DL_ChannelisationCodeNumber = 255;
   dl_CodeInformationItem.transmissionGapPatternSequenceCodeInformation = 
      TransmissionGapPatternSequenceCodeInformation_nocode_change;

   rtxDListAppend 
      (&ctxt, &setupRqstFDD_element.value.dl_CodeInformationList, 
       &dl_CodeInformationItem);

   setupRqstFDD_element.value.initialDL_transmissionPower = -22;
   setupRqstFDD_element.value.maximumDL_power = 100;
   setupRqstFDD_element.value.minimumDL_power = -100;
   setupRqstFDD_element.value.m.sSDT_Cell_IdentityPresent = 0;
   setupRqstFDD_element.value.m.transmitDiversityIndicatorPresent = 0;
   setupRqstFDD_element.value.m.iE_ExtensionsPresent = 0;

   /* Populate RadioLinkSetupRequestFDD structure */

   asn1Init_RL_InformationList_RL_SetupRqstFDD (&setupRqstFDD);
   rtxDListAppend (&ctxt, &setupRqstFDD, &setupRqstFDD_element);

   asn1Init_RadioLinkSetupRequestFDD_protocolIEs_element (&protocolIEs[0]);
   protocolIEs[0].id = ASN1V_id_RL_InformationList_RL_SetupRqstFDD;
   protocolIEs[0].criticality = Criticality_notify;
   protocolIEs[0].value.t = 
      T_NBPDUCont_RLSReqFDD_id_RL_InformationList_RL_SetupRqstFDD;
   protocolIEs[0].value.u.
      _RLSReqFDD_id_RL_InformationList_RL_SetupRqstFDD = &setupRqstFDD;

   asn1Init_RadioLinkSetupRequestFDD (&radioLinkSetupFDD);
   rtxDListAppend (&ctxt, &radioLinkSetupFDD.protocolIEs, &protocolIEs[0]);

   /* Populate NBAP-PDU structure */

   initMsg.procedureID.procedureCode = ASN1V_id_radioLinkSetup;
   initMsg.procedureID.ddMode = ProcedureID_ddMode_fdd;
   initMsg.criticality = Criticality_reject;
   initMsg.messageDiscriminator = MessageDiscriminator_common;
   initMsg.transactionID.t = T_TransactionID_shortTransActionId;
   initMsg.transactionID.u.shortTransActionId = 1;
   initMsg.value.t = T_NBPDUDescr_NBAPEP_radioLinkSetupFDD;
   initMsg.value.u.radioLinkSetupFDD = &radioLinkSetupFDD;

   pduData.t = T_NBAP_PDU_initiatingMessage;
   pduData.u.initiatingMessage = &initMsg;

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_NBAP_PDU ("NBAP_PDU", &pduData);
      printf ("\n");
   }

   /* Encode */
   if ((stat = asn1PE_NBAP_PDU (&ctxt, &pduData))== 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt, "data");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }
   msgptr = pe_GetMsgPtr (&ctxt, &len);
   /* Write the encoded message out to the output file */
   if ((fp = fopen (filename, "wb"))) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      rtFreeContext (&ctxt);
      return -1;
   }

   rtFreeContext (&ctxt);
   return 0;
}
