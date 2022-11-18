/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "SNMPv3MessageSyntax.h"
#include "SNMPv2-PDU.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 1024

ASN1OBJID sysDescr = {
   8,
   { 1, 3, 6, 1, 2, 1, 1, 1 }
} ;

int main (int argc, char** argv)
{
   SNMPv3Message snmpMessage;
   PDUs         pdu;
   GetRequest_PDU getReqPDU;
   ScopedPDU    scopedPDU;
   VarBind*     pVarBind;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   int		i, len;
   FILE*        fp;
   char*        filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   /* Dummy security data */
   const OSOCTET secdata[] = { 
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09
   };

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = (1);
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Populate variable bindings structure:                     */
   /* Set up to retrieve sysDescr object..                      */

   pVarBind = rtxMemAllocType (&ctxt, VarBind);
   asn1Init_VarBind (pVarBind);

   rtSetOID (&pVarBind->name, &sysDescr);
   pVarBind->name.subid[pVarBind->name.numids++] = 0; /* append index */
   pVarBind->aChoice.t = T_VarBind_aChoice_unSpecified;

   /* Populate get_request PDU structure */

   asn1Init_GetRequest_PDU (&getReqPDU);
   getReqPDU.request_id = 1;
   getReqPDU.error_status = 0;
   getReqPDU.error_index  = 0;
   rtxDListAppend (&ctxt, &getReqPDU.variable_bindings, pVarBind);

   pdu.t = T_PDUs_get_request;
   pdu.u.response = &getReqPDU;

   /* Need to encode PDU separately to include as a scoped PDU in the   */
   /* v3 message..                                                      */

   xe_setp (&ctxt, msgbuf, sizeof(msgbuf));

   if ((len = asn1E_PDUs (&ctxt, &pdu, ASN1EXPL)) > 0) {
      msgptr = xe_getp (&ctxt);
   }
   else {
      rtxErrPrint (&ctxt);
      return -1;
   }

   /* Populate main message structure */

   asn1Init_SNMPv3Message (&snmpMessage);
   snmpMessage.msgVersion = 3;
   snmpMessage.msgGlobalData.msgID = 1;
   snmpMessage.msgGlobalData.msgMaxSize = 1024;
   snmpMessage.msgGlobalData.msgFlags.numocts = 1;
   snmpMessage.msgGlobalData.msgFlags.data[0] = 0xaa;
   snmpMessage.msgGlobalData.msgSecurityModel = 1;
   snmpMessage.msgSecurityParameters.numocts = 10;
   snmpMessage.msgSecurityParameters.data = (OSOCTET*)secdata;

   scopedPDU.contextEngineID.data = (OSOCTET*)"aContextEngineID";
   scopedPDU.contextEngineID.numocts = 
     strlen((const char*)scopedPDU.contextEngineID.data) + 1;

   scopedPDU.contextName.data = (OSOCTET*)"aContextName";
   scopedPDU.contextName.numocts = 
     strlen((const char*)scopedPDU.contextName.data) + 1;

   scopedPDU.data.numocts = len;
   scopedPDU.data.data = msgptr;

   snmpMessage.msgData.t = T_ScopedPduData_plaintext;
   snmpMessage.msgData.u.plaintext = &scopedPDU;

   /* Encode */

   xe_setp (&ctxt, msgbuf, sizeof(msgbuf));

   if ((len = asn1E_SNMPv3Message (&ctxt, &snmpMessage, ASN1EXPL)) > 0) {
      msgptr = xe_getp (&ctxt);
      if (trace) {
         printf ("Hex dump of encoded message:\n");
         rtxHexDump (msgptr, len);
         printf ("\n");
         printf ("BER dump of encoded message:\n");
         if (XU_DUMP (msgptr) != 0) 
            printf ("dump of ASN.1 message failed.");
      }
   }
   else {
      rtxErrPrint (&ctxt);
      return -1;
   }
  
   /* Write the encoded message out to the output file */

   if (0 != (fp = fopen (filename, "wb"))) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   rtFreeContext (&ctxt);
   return 0;

}
