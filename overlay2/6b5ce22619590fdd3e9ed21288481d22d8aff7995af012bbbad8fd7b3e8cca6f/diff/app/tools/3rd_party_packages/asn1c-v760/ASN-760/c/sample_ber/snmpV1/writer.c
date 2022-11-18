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

int main (int argc, char** argv)
{
   Message      snmpMessage;
   GetRequest_PDU pdu;
   VarBind*     pVarBind;
   SimpleSyntax simpleSyntax;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   int		i, len;
   FILE*        fp;
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
   /* Set up to retrieve sysDescr object..                      */

   simpleSyntax.t = T_SimpleSyntax_empty;
   pVarBind = rtxMemAllocType (&ctxt, VarBind);
   asn1Init_VarBind (pVarBind);

   rtSetOID (&pVarBind->name, &sysDescr);
   pVarBind->name.subid[pVarBind->name.numids++] = 0; /* append index */
   pVarBind->value.t = T_ObjectSyntax_simple;
   pVarBind->value.u.simple = &simpleSyntax;

   /* Populate get_request PDU structure */
   asn1Init_GetRequest_PDU (&pdu);
   pdu.request_id = 1;
   pdu.error_status = 0;
   pdu.error_index  = 0;
   rtxDListAppend (&ctxt, &pdu.variable_bindings, pVarBind);

   /* Populate main message structure */

   snmpMessage.version = version_1;
   snmpMessage.community.numocts = strlen (COMMUNITY);
   snmpMessage.community.data = (OSOCTET*) COMMUNITY;
   snmpMessage.data.t = T_PDUs_get_request;
   snmpMessage.data.u.get_request = &pdu;

   /* Encode */

   xe_setp (&ctxt, msgbuf, sizeof(msgbuf));

   if ((len = asn1E_Message (&ctxt, &snmpMessage, ASN1EXPL)) > 0) {
      msgptr = xe_getp (&ctxt);
      if (trace) {
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
