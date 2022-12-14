/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.2.A, Date: 19-Feb-2009.
 */
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

   OSCTXT       ctxt;
   OSBOOL       trace = TRUE, verbose = FALSE;
   const char*  filename = "message.xml";
   int          i, stat;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Init context */

   stat = rtXmlInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Populate RL_InformationList_RL_SetupRqstFDD_element */

   asn1Init_RL_InformationList_RL_SetupRqstFDD_element (&setupRqstFDD_element);
   setupRqstFDD_element.id = ASN1V_id_RL_InformationItem_RL_SetupRqstFDD;
   setupRqstFDD_element.criticality = notify;
   setupRqstFDD_element.value.rL_ID = 25;           /*  INTEGER (0..31) */
   setupRqstFDD_element.value.c_ID = 1000;          /*  INTEGER (0..65535) */
   setupRqstFDD_element.value.firstRLS_indicator = first_RLS;
   setupRqstFDD_element.value.frameOffset = 99;     /*  INTEGER (0..255) */
   setupRqstFDD_element.value.chipOffset = 224;     /*  INTEGER (0..38399) */
   setupRqstFDD_element.value.m.propagationDelayPresent = 1;
   setupRqstFDD_element.value.propagationDelay = 22; /* INTEGER (0..255) */
   setupRqstFDD_element.value.m.diversityControlFieldPresent = 1;
   setupRqstFDD_element.value.diversityControlField = must_not;

   asn1Init_DL_CodeInformationItem_RL_SetupRqstFDD (&dl_CodeInformationItem);
   dl_CodeInformationItem.m.
      transmissionGapPatternSequenceCodeInformationPresent = 1;
   dl_CodeInformationItem.dl_ScramblingCode = 0;
   dl_CodeInformationItem.fdd_DL_ChannelisationCodeNumber = 255;
   dl_CodeInformationItem.
      transmissionGapPatternSequenceCodeInformation = nocode_change;

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
   protocolIEs[0].criticality = notify;
   protocolIEs[0].value.t = 
      T_NBAP_PDU_Contents_RadioLinkSetupRequestFDD_IEs_id_RL_InformationList_RL_SetupRqstFDD;
   protocolIEs[0].value.u.
      _RadioLinkSetupRequestFDD_IEs_id_RL_InformationList_RL_SetupRqstFDD = 
      &setupRqstFDD;

   asn1Init_RadioLinkSetupRequestFDD (&radioLinkSetupFDD);
   rtxDListAppend (&ctxt, &radioLinkSetupFDD.protocolIEs, &protocolIEs[0]);

   /* Populate NBAP-PDU structure */

   initMsg.procedureID.procedureCode = ASN1V_id_radioLinkSetup;
   initMsg.procedureID.ddMode = fdd;
   initMsg.criticality = reject;
   initMsg.messageDiscriminator = common;
   initMsg.transactionID.t = T_TransactionID_shortTransActionId;
   initMsg.transactionID.u.shortTransActionId = 1;
   initMsg.value.t = T_NBAP_PDU_Descriptions_NBAP_ELEMENTARY_PROCEDURES_radioLinkSetupFDD;
   initMsg.value.u.radioLinkSetupFDD = &radioLinkSetupFDD;

   pduData.t = T_NBAP_PDU_initiatingMessage;
   pduData.u.initiatingMessage = &initMsg;

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_NBAP_PDU ("NBAP_PDU", &pduData);
      printf ("\n");
   }

   /* Encode */

   stat = rtXmlSetEncBufPtr (&ctxt, 0, 0);

   if (stat == 0)
      stat = XmlEnc_NBAP_PDU_PDU (&ctxt, &pduData);

   if (stat == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         puts ((char*)rtXmlGetEncBufPtr(&ctxt));
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return (stat);
   }

   /* Write the encoded message out to the output file */

   stat = rtXmlWriteToFile (&ctxt, filename);
   if (0 != stat) {
      printf ("Error opening %s for write access\n", filename);
      rtxErrPrint (&ctxt);
   }
   rtxFreeContext (&ctxt);

   return 0;
}
