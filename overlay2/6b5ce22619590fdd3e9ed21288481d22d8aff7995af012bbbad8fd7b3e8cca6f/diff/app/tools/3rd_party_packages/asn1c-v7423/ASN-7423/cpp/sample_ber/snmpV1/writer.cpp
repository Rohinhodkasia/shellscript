/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "RFC1157-SNMP.h"
#include "RFC1213-MIB.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define COMMUNITY "public"
#define MAXMSGLEN 1024

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET	msgbuf[MAXMSGLEN];
   int		i, len;
   FILE*        fp;
   const char*  filename = "message.dat";
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
   ASN1T_SimpleSyntax simpleSyntax;
   ASN1T_VarBind* pVarBind;
   ASN1T_GetRequest_PDU pdu;
   ASN1C_VarBindList varBindList (encodeBuffer, pdu.variable_bindings); 

   /* Populate variable bindings structure:                     */
   /* Set up to retrieve sysDescr object..                      */

   simpleSyntax.t = T_SimpleSyntax_empty;
   pVarBind = rtxMemAllocType (snmpMessage.getCtxtPtr(), ASN1T_VarBind);
   rtSetOID (&pVarBind->name, &sysDescr);
   pVarBind->name.subid[pVarBind->name.numids++] = 0; /* append index */
   pVarBind->value.t = T_ObjectSyntax_simple;
   pVarBind->value.u.simple = &simpleSyntax;

   /* Populate get_request PDU structure */

   pdu.request_id = 1;
   pdu.error_status = 0;
   pdu.error_index  = 0;
   varBindList.append (pVarBind);

   DECLARE_MEMLEAK_DETECTOR;

   /* Populate main message structure */

   msgData.version = Message_version::version_1;
   msgData.community.numocts = strlen (COMMUNITY);
   msgData.community.data = (OSOCTET*) COMMUNITY;
   msgData.data.t = T_PDUs_get_request;
   msgData.data.u.get_request = &pdu;

   /* Encode */

   if ((len = snmpMessage.Encode ()) >= 0) {
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
      exit (-1);
   }

   // Write the encoded message out to the output file 

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
