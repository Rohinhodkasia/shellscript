/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "SNMPv2-PDU.h"
#include "UDP-MIB.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define COMMUNITY "public"
#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET*	msgptr;
   OSOCTET	msgbuf[MAXMSGLEN];
   int		i, len;
   FILE*        fp;
   const char*        filename = "message.dat";
   OSBOOL       verbose = FALSE, dump = FALSE, trace = TRUE;

   /* Process command line arguments */

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
            return 0;
         }
      }
   }

   ASN1BEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   encodeBuffer.setDiag (verbose);

   ASN1T_Message msgData;
   ASN1C_Message snmpMessage (encodeBuffer, msgData);
   ASN1T_VarBind* pVarBind;
   ASN1T_Response_PDU pdu;
   ASN1T_IpAddress ipAddress;
   ASN1C_VarBindList varBindList (encodeBuffer, pdu.variable_bindings); 

   pVarBind = rtxMemAllocType (snmpMessage.getCtxtPtr(), ASN1T_VarBind);
   rtSetOID (&pVarBind->name, &udpLocalAddress);
   /* append index identifiers onto the end of the base OID */
   pVarBind->name.subid[pVarBind->name.numids++] = 192;
   pVarBind->name.subid[pVarBind->name.numids++] = 180;
   pVarBind->name.subid[pVarBind->name.numids++] = 140;
   pVarBind->name.subid[pVarBind->name.numids++] = 202;
   pVarBind->name.subid[pVarBind->name.numids++] = 520;

   pVarBind->aChoice.t = T_VarBind_aChoice_value;
   pVarBind->aChoice.u.value = 
      rtxMemAllocType (snmpMessage.getCtxtPtr(), ASN1T_ObjectSyntax);
   pVarBind->aChoice.u.value->t = T_ObjectSyntax_application_wide;
   pVarBind->aChoice.u.value->u.application_wide = 
   
   rtxMemAllocType (snmpMessage.getCtxtPtr(), ASN1T_ApplicationSyntax);

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

   pdu.request_id = 1827802204;
   pdu.error_status = 0;
   pdu.error_index  = 0;
   varBindList.append (pVarBind);

DECLARE_MEMLEAK_DETECTOR;

   /* Populate main message structure */

   msgData.version = Message_version::version_1;
   msgData.community.numocts = strlen (COMMUNITY);
   msgData.community.data = (OSOCTET*) COMMUNITY;
   msgData.data.t = T_PDUs_response;
   msgData.data.u.response = &pdu;

   /* Encode */

   if ((len = snmpMessage.Encode ()) >= 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded message:\n");
         encodeBuffer.hexDump (len);
         printf ("\n");
         printf ("Binary dump:\n");
         encodeBuffer.binDump ();
      }
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return -1;
   }

   /* Write the encoded message out to the output file */

   if (fp = fopen (filename, "wb")) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   // Create a dump file

   if (dump) {
      printf("Writing to .dmp file\n");
      if (fp = fopen ("message.dmp", "w")) {
         rtxHexDumpToFile (fp, msgptr, len);
         fclose (fp);
         printf("closing .dmp file\n");
      }
      else {
         printf ("Error opening message.dmp for write access\n");
         return -1;
      }
   }

   return 0;
}
