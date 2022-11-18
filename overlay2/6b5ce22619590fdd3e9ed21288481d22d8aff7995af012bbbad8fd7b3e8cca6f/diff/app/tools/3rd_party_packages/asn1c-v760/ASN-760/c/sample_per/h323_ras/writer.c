/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "H323RAS.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamFile.h"

static ASN1OBJID gProtocolID = {
   6, { 0, 0, 8, 2250, 0, 2 }
} ;

int main (int argc, char** argv)
{
   AliasAddress aliasAddress;
   TransportAddress_ipAddress ipAddress;
   TransportAddress transportAddress;
   RegistrationConfirm registrationConfirm;
   RasMessage rasMessage;
   OSCTXT	ctxt;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.dat";
   int		i, stat, tvalue = 2;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-t")) tvalue = atoi(argv[++i]);
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [ -v ] [ -o <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -t  choice tag value to encode\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Create a new context structure */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   stat = rtxStreamFileCreateWriter (&ctxt, filename);
   if (0 != stat) {
      printf ("Stream initialization failed.\n");
      rtxErrPrint (&ctxt);
      return stat;
   }
   pu_setAligned (&ctxt, aligned);
   pu_setTrace (&ctxt, trace);

   /* Populate structure */

   asn1Init_RegistrationConfirm (&registrationConfirm);
   registrationConfirm.m.terminalAliasPresent = 1;
   registrationConfirm.m.gatekeeperIdentifierPresent = 1;

   registrationConfirm.requestSeqNum = 1;
   rtSetOID (&registrationConfirm.protocolIdentifier, &gProtocolID);

   /* Call signal address */

   ipAddress.ip[0] = 0xc0;
   ipAddress.ip[1] = 0xa8;
   ipAddress.ip[2] = 0x00;
   ipAddress.ip[3] = 0x01;
   ipAddress.port = 1720;

   asn1Init_TransportAddress (&transportAddress);
   transportAddress.t = T_TransportAddress_ipAddress;
   transportAddress.u.ipAddress = &ipAddress;
   rtxDListAppend 
      (&ctxt, &registrationConfirm.callSignalAddress, &transportAddress);

   /* Terminal alias */

   asn1Init_AliasAddress (&aliasAddress);
   aliasAddress.t = T_AliasAddress_h323_ID;
   rtCToBMPString (&ctxt, "anH323ID", &aliasAddress.u.h323_ID, 0);
   rtxDListAppend (&ctxt, &registrationConfirm.terminalAlias, &aliasAddress);

   /* Gatekeeper identifier */

   rtCToBMPString (&ctxt, "aGatekeeperID", 
                   &registrationConfirm.gatekeeperIdentifier, 0);

   /* Endpoint identifier */

   rtCToBMPString (&ctxt, "anEndpointID", 
                   &registrationConfirm.endpointIdentifier, 0);

   asn1Init_RasMessage (&rasMessage);
   rasMessage.t = T_RasMessage_registrationConfirm;
   rasMessage.u.registrationConfirm = &registrationConfirm;

   /* Encode */

   stat = asn1PE_RasMessage (&ctxt, &rasMessage);

   if (stat == 0) {
      stat = rtxStreamFlush (&ctxt);
   }

   if (stat == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt, "rasMessage");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }
  
   rtFreeContext (&ctxt);

   return 0;

}
