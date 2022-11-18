/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "SNMPv3MessageSyntax.h"
#include "SNMPv2-PDU.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   SNMPv3Message snmpMessage;
   PDUs         pdu;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSSIZE       len;
   int		i, stat;
   FILE*        fp;
   const char*  filename = "message.dat";
   OSBOOL       trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Read input file into a memory buffer */

   if (fp = fopen (filename, "rb")) {
      len = fread (msgbuf, 1, sizeof(msgbuf), fp);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   /* Init context structure */

   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   stat = xd_setp64 (&ctxt, msgbuf, len, 0, 0, 0);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Decode outer message wrapper */

   stat = asn1D_SNMPv3Message (&ctxt, &snmpMessage, ASN1EXPL, 0);
   if (stat == 0) {
      if (trace) {
         printf ("Decode of SNMPv3Message was successful\n");
         printf ("Decoded record:\n");
         asn1Print_SNMPv3Message ("snmpMessage", &snmpMessage);
      }
   }
   else {
      printf ("decode of SNMP message failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }

   /* Decode PDU's */

   if (snmpMessage.msgData.t == T_ScopedPduData_plaintext) {
      stat = xd_setp64 
         (&ctxt, snmpMessage.msgData.u.plaintext->data.data, 
          snmpMessage.msgData.u.plaintext->data.numocts, 0, 0, 0);

      if (stat != 0) {
         printf ("xd_setp plaintext data failed\n");
         rtxErrPrint (&ctxt);
         return -1;
      }

      stat = asn1D_PDUs (&ctxt, &pdu, ASN1EXPL, 0);
      if (stat == 0) {
         if (trace) {
            printf ("Decode of PDUs was successful\n");
            printf ("Decoded record:\n");
            asn1Print_PDUs ("pdu", &pdu);
         }
      }
      else {
         printf ("decode of SNMP message failed\n");
         rtxErrPrint (&ctxt);
         return -1;
      }
   }
   else
      printf ("unexpected msgData field type = %d\n", snmpMessage.msgData.t);

   rtFreeContext (&ctxt);
   return 0;
}

