/* This test driver program encodes a data record and writes the	*/
/* result to an output file..						*/

#include <stdio.h>
#include <stdlib.h>
#include "InfoObject.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

#define MAXMSGLEN 1024

static OSBOOL trace = TRUE;

static OSSIZE encodeCause 
(OSOCTET* pbuf, int bufsiz, OSBOOL aligned, OSBOOL verbose);

int main (int argc, char** argv)
{
   Iu_ReleaseCommand releaseCommand;
   ProtocolIE_Field protocolIEs[1];
   OSCTXT	ctxt;
   OSOCTET	buf1[100], msgbuf[MAXMSGLEN], *msgptr;
   OSBOOL       verbose = FALSE, aligned = TRUE;
   const char*  filename = "message.dat";
   int		i, stat, count = 1;
   OSSIZE       len;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-count")) count = atoi (argv[++i]);
         else {
            printf ("usage: writer -a|-u [-v] [-o <filename>] "
                    "[-count <count>]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            printf ("   -count <count> number of messages to encode\n");
            return 0;
         }
      }
   }

   /* Encode a message to insert as open type */

   len = encodeCause (buf1, sizeof(buf1), aligned, verbose);
   if (len == OSNULLINDEX) return -1;

   /* Populate final message structure with data from encoded open type */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   asn1Init_ProtocolIE_Field (&protocolIEs[0]);
   protocolIEs[0].id = 12345;
   protocolIEs[0].criticality = notify;
   protocolIEs[0].value.numocts = len;	/* from encoded open type */
   protocolIEs[0].value.data = buf1;    /* from encoded open type */

   asn1Init_Iu_ReleaseCommand (&releaseCommand);
   rtxDListAppend (&ctxt, &releaseCommand.protocolIEs, &protocolIEs[0]);

   /* Encode up to count messages to demonstrate encoding in a loop.  
      Note that the context can be reused, it is only necessary to call 
      pe_resetBuffer before each call. */

   pu_setBuffer (&ctxt, msgbuf, sizeof(msgbuf), aligned);
   pu_setTrace (&ctxt, trace);

   for (i = 0;; ) {
      if (trace) {
         printf ("The following record will be encoded:\n");
         asn1Print_Iu_ReleaseCommand ("releaseCommand", &releaseCommand);
         printf ("\n");
      }

      if ((stat = asn1PE_Iu_ReleaseCommand (&ctxt, &releaseCommand)) == 0) {
         if (trace) {
            printf ("Encoding was successful\n");
            printf ("Hex dump of encoded record:\n");
            pu_hexdump (&ctxt);
            printf ("Binary dump:\n");
            pu_bindump (&ctxt, "releaseCommand");
         }
      }
      else {
         printf ("Encoding failed\n");
         rtxErrPrint (&ctxt);
         return -1;
      }

      /* update protocol ID in next message */
      if (++i < count) {
         protocolIEs[0].id++;
         pe_resetBuffer (&ctxt);
      }
      else break;
   }

   msgptr = pe_GetMsgPtr64 (&ctxt, &len);

   /* Write the encoded message out to the output file */

   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (0 != stat) {
      printf ("Error writing data to file %s; status = %d\n", 
              filename, stat);
      return stat;
   }

   rtFreeContext (&ctxt);

   return 0;

}


/* Encode message for use in open type field */

static OSSIZE encodeCause 
(OSOCTET* pbuf, int bufsiz, OSBOOL aligned, OSBOOL verbose)
{
   OSCTXT ctxt;
   Cause  cause;
   OSSIZE len;

   cause.t = T_Cause_radioNetwork;
   cause.u.radioNetwork = relocation_triggered;

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return OSNULLINDEX;
   }
   rtxSetDiag (&ctxt, verbose);
   pu_setBuffer (&ctxt, pbuf, bufsiz, aligned);
   pu_setTrace (&ctxt, trace);

   if (asn1PE_Cause (&ctxt, &cause) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt, "releaseCommand");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return OSNULLINDEX;
   }
  
   len = pu_getMsgLen (&ctxt);

   rtFreeContext (&ctxt);

   return len;
}
