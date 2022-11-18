/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "SNMPv3MessageSyntax.h"
#include "SNMPv2-PDU.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

ASN1OBJID sysDescr = {
   8,
   { 1, 3, 6, 1, 2, 1, 1, 1 }
} ;

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET *msgptr;
   OSOCTET msgbuf[MAXMSGLEN];
   int		i, len;
   FILE*        fp;
   const char*        filename = "message.dat";
   OSBOOL       verbose = FALSE, dump = FALSE, trace = TRUE;

   /* Dummy security data */
   const OSOCTET secdata[] = { 
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09
   };

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

   ASN1T_SNMPv3Message msgV3Data;
   ASN1C_SNMPv3Message snmpMessage (encodeBuffer, msgV3Data);
   ASN1T_VarBind* pVarBind;
   ASN1T_GetRequest_PDU getReqPDU;
   ASN1T_ScopedPDU scopedPDU;
   ASN1T_PDUs pduData;
   ASN1C_PDUs pdus(encodeBuffer, pduData);
   ASN1C_VarBindList varBindList (encodeBuffer, getReqPDU.variable_bindings); 

   // Populate variable bindings structure:
   // Set up to retrieve sysDescr object..

   pVarBind = rtxMemAllocType (snmpMessage.getCtxtPtr(), ASN1T_VarBind);
   rtSetOID (&pVarBind->name, &sysDescr);
   pVarBind->name.subid[pVarBind->name.numids++] = 0; /* append index */
   pVarBind->aChoice.t = T_VarBind_aChoice_unSpecified;

   /* Populate get_request PDU structure */

   getReqPDU.request_id = 1;
   getReqPDU.error_status = 0;
   getReqPDU.error_index  = 0;
   varBindList.append (pVarBind);

   pduData.t = T_PDUs_get_request;
   pduData.u.response = &getReqPDU;

   /* Need to encode PDU separately to include as a scoped PDU in the   */
   /* v3 message.                                           */

   if ((len = pdus.Encode ()) >= 0) {
      msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return -1;
   }

DECLARE_MEMLEAK_DETECTOR;

   /* Populate main message structure */

   msgV3Data.msgVersion = 3;
   msgV3Data.msgGlobalData.msgID = 1;
   msgV3Data.msgGlobalData.msgMaxSize = 1024;
   msgV3Data.msgGlobalData.msgFlags.numocts = 1;
   msgV3Data.msgGlobalData.msgFlags.data[0] = 0xaa;
   msgV3Data.msgGlobalData.msgSecurityModel = 1;
   msgV3Data.msgSecurityParameters.numocts = 10;
   msgV3Data.msgSecurityParameters.data = (OSOCTET*)secdata;

   scopedPDU.contextEngineID.data = (OSOCTET*)"aContextEngineID";
   scopedPDU.contextEngineID.numocts = 
      strlen((const char*)scopedPDU.contextEngineID.data) + 1;
   scopedPDU.contextName.data = (OSOCTET*)"aContextName";
   scopedPDU.contextName.numocts = 
      strlen((const char*)scopedPDU.contextName.data) + 1;

   scopedPDU.data.numocts = len;
   scopedPDU.data.data = msgptr;

   msgV3Data.msgData.t = T_ScopedPduData_plaintext;
   msgV3Data.msgData.u.plaintext = &scopedPDU;

   /* Encode */

   if ((len = snmpMessage.Encode ()) >= 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded message:\n");
         encodeBuffer.hexDump (len);
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
