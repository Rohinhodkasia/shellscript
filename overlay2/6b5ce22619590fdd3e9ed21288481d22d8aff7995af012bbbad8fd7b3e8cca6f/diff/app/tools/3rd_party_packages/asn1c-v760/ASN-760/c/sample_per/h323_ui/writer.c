/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "H323-MESSAGES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static ASN1OBJID gProtocolID = {
   6, { 0, 0, 8, 2250, 0, 2 }
} ;

int main (int argc, char** argv)
{
   H225H323_UserInformation userInfo;
   H225Setup_UUIE setup;

   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int		i, len, stat, tvalue = 2;

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
   pu_setBuffer (&ctxt, msgbuf, sizeof(msgbuf), aligned);
   pu_setTrace (&ctxt, trace);

   /* Populate structure */

   asn1Init_H225Setup_UUIE (&setup);
   rtSetOID (&setup.protocolIdentifier, &gProtocolID);
   for (i = 0; i < 16; i++)
      setup.conferenceID.data[i] = i + 1;
   setup.conferenceGoal.t = T_H225Setup_UUIE_conferenceGoal_create;
   setup.callType.t = T_H225CallType_pointToPoint;

   /* extension fields */
   setup.m.callIdentifierPresent = TRUE;
   setup.m.mediaWaitForConnectPresent = TRUE;
   setup.m.canOverlapSendPresent = TRUE;
   for (i = 0; i < 16; i++)
       setup.callIdentifier.guid.data[i] = i + 1;
   setup.mediaWaitForConnect = FALSE;
   setup.canOverlapSend = FALSE;

   asn1Init_H225H323_UserInformation (&userInfo);
   userInfo.h323_uu_pdu.h323_message_body.t = 
      T_H225H323_UU_PDU_h323_message_body_setup;
   userInfo.h323_uu_pdu.h323_message_body.u.setup = &setup;

   /* Encode */

   if ((stat = asn1PE_H225H323_UserInformation (&ctxt, &userInfo)) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt, "userInfo");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&ctxt, &len);

   /* Write the encoded message out to the output file */

   if (fp = fopen (filename, "wb")) {
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
