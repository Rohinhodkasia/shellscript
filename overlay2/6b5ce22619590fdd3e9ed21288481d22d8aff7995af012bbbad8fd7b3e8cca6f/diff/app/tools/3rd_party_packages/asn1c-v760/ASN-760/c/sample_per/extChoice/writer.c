/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "ExtChoice.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   AliasAddress aliasAddress;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
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

   switch (aliasAddress.t = tvalue) {
   case T_AliasAddress_e164:
      aliasAddress.u.e164 = "#12345";
      break;
   case T_AliasAddress_h323_ID:
      rtCToBMPString (&ctxt, "TESTSTRING", &aliasAddress.u.h323_ID, 0);
      break;
   case T_AliasAddress_url_ID:
      aliasAddress.u.url_ID = "http://www.obj-sys.com";
      break;
   case T_AliasAddress_transportID:
      aliasAddress.u.transportID = "Truck";
      break;
   case T_AliasAddress_email_ID:
      aliasAddress.u.email_ID = "objective@obj-sys.com";
      break;
   case T_AliasAddress_partyNumber:
      aliasAddress.u.partyNumber = 555;
      break;
   }

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_AliasAddress ("aliasAddress", &aliasAddress);
      printf ("\n");
   }

   /* Encode */

   if ((stat = asn1PE_AliasAddress (&ctxt, &aliasAddress)) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt, "aliasAddress");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&ctxt, &len);

   /* Write the encoded message out to the output file */

   stat = rtxFileWriteBinary(filename, msgptr, len);
   if (0 != stat) {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   rtFreeContext (&ctxt);

   return 0;

}
