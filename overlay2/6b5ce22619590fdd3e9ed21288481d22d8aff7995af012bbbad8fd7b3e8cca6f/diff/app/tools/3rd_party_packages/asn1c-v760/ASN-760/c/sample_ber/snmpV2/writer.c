/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include "SNMPv2-PDU.h"
#include "UDP-MIB.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define COMMUNITY "public"
#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   Message      snmpMessage;
   Response_PDU pdu;
   VarBind*     pVarBind;
   IpAddress    ipAddress;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   int		i, len;
   char*        filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

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
   /* This is a GetResponse for the UDB MIB returning the       */
   /* the udpLocalAddress and udpLocalPort fields               */

   pVarBind = rtxMemAllocType (&ctxt, VarBind);
   asn1Init_VarBind (pVarBind);

   rtSetOID (&pVarBind->name, &udpLocalAddress);
   /* append index identifiers onto the end of the base OID */
   pVarBind->name.subid[pVarBind->name.numids++] = 192;
   pVarBind->name.subid[pVarBind->name.numids++] = 180;
   pVarBind->name.subid[pVarBind->name.numids++] = 140;
   pVarBind->name.subid[pVarBind->name.numids++] = 202;
   pVarBind->name.subid[pVarBind->name.numids++] = 520;

   pVarBind->aChoice.t = T_VarBind_aChoice_value;
   pVarBind->aChoice.u.value = rtxMemAllocType (&ctxt, ObjectSyntax);
   pVarBind->aChoice.u.value->t = T_ObjectSyntax_application_wide;
   pVarBind->aChoice.u.value->u.application_wide = 
      rtxMemAllocType (&ctxt, ApplicationSyntax);

   pVarBind->aChoice.u.value->u.application_wide->t = 
      T_ApplicationSyntax_ipAddress_value;

   ipAddress.numocts = 4;
   ipAddress.data[0] = 135;
   ipAddress.data[1] = 180;
   ipAddress.data[2] = 140;
   ipAddress.data[3] = 202;

   pVarBind->aChoice.u.value->u.application_wide->u.ipAddress_value = 
      &ipAddress;

   /* Populate response PDU structure */

   asn1Init_Response_PDU (&pdu);
   pdu.request_id = 1827802204;
   pdu.error_status = 0;
   pdu.error_index  = 0;
   rtxDListAppend (&ctxt, &pdu.variable_bindings, pVarBind);

   /* Populate main message structure */

   snmpMessage.version = version_1;
   snmpMessage.community.numocts = strlen (COMMUNITY);
   snmpMessage.community.data = (OSOCTET*) COMMUNITY;
   snmpMessage.data.t = T_PDUs_response;
   snmpMessage.data.u.response = &pdu;

   /* Encode */

   xe_setp (&ctxt, msgbuf, sizeof(msgbuf));

   if ((len = asn1E_Message (&ctxt, &snmpMessage, ASN1EXPL)) > 0) {
      msgptr = xe_getp (&ctxt);
      if (trace) {
         printf ("Hex dump of encoded message:\n");
         rtxHexDump (msgptr, len);
         printf ("\n");
         printf ("BER dump of encoded message:\n");
         if (XU_DUMP (msgptr) != 0) 
            printf ("dump of ASN.1 message failed.");
      }

      /* Write the encoded message out to the output file */
      if (0 != rtxFileWriteBinary (filename, msgptr, len)) {
         printf ("Error writing encoded message to %s\n", filename);
         return -1;
      }
   }
   else {
      rtxErrPrint (&ctxt);
      return -1;
   }
  
   rtFreeContext (&ctxt);
   return 0;

}
