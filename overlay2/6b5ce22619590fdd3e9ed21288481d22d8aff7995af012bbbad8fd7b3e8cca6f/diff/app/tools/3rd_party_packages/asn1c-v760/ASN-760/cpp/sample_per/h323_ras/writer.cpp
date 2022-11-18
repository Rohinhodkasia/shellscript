// This test driver program encodes a data record and writes the 
// encoded result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "H323RAS.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static ASN1OBJID gProtocolID = {
   6, { 0, 0, 8, 2250, 0, 2 }
} ;

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int		i, stat;
   OSSIZE       len;

   // Process command line arguments 

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
            return 0;
         }
      }
   }

   // Create an instance of the compiler generated class.  This
   // example uses a static message buffer..

   ASN1PEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf), aligned);
   ASN1T_RasMessage msgData;
   ASN1C_RasMessage rasMessage (encodeBuffer, msgData);

   // Populate the msgData structure

   ASN1T_AliasAddress aliasAddress;
   ASN1T_TransportAddress_ipAddress ipAddress;
   ASN1T_TransportAddress transportAddress;
   ASN1T_RegistrationConfirm registrationConfirm;
   ASN1TBMPString h323ID;

   registrationConfirm.m.terminalAliasPresent = 1;
   registrationConfirm.m.gatekeeperIdentifierPresent = 1;
   registrationConfirm.requestSeqNum = 1;
   registrationConfirm.protocolIdentifier = gProtocolID;

   // Call signal address

   ipAddress.ip[0] = 0xc0;
   ipAddress.ip[1] = 0xa8;
   ipAddress.ip[2] = 0x00;
   ipAddress.ip[3] = 0x01;
   ipAddress.port = 1720;

   transportAddress.t = T_TransportAddress_ipAddress;
   transportAddress.u.ipAddress = &ipAddress;
   ASN1CSeqOfList callSigList 
      (encodeBuffer, registrationConfirm.callSignalAddress);
   callSigList.append (&transportAddress);

   // Terminal alias

   aliasAddress.t = T_AliasAddress_h323_ID;
   aliasAddress.u.h323_ID = &h323ID;
   encodeBuffer.CStringToBMPString ("anH323ID", aliasAddress.u.h323_ID);
   ASN1CSeqOfList termList (encodeBuffer, registrationConfirm.terminalAlias);
   termList.append (&aliasAddress);

   // Gatekeeper identifier

   encodeBuffer.CStringToBMPString ("aGatekeeperID", 
                                    &registrationConfirm.gatekeeperIdentifier);

   // Endpoint identifier

   encodeBuffer.CStringToBMPString ("anEndpointID", 
                                    &registrationConfirm.endpointIdentifier);

   msgData.t = T_RasMessage_registrationConfirm;
   msgData.u.registrationConfirm = &registrationConfirm;

   // Encode 

   encodeBuffer.setTrace (trace);

   if ((stat = rasMessage.Encode ()) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
         printf ("Binary dump:\n");
         encodeBuffer.binDump ("aliasAddress");
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.getMsgLen ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return -1;
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

   return 0;

}
