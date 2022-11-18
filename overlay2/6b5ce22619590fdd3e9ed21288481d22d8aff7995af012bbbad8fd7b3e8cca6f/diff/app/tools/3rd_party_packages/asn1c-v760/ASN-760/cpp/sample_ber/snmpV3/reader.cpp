/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "SNMPv3MessageSyntax.h"
#include "SNMPv2-PDU.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int          i, stat;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

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

   // Creating DecodeBuffer stream
   ASN1BERDecodeBuffer decodeBuffer;
   stat = decodeBuffer.readBinaryFile (filename);
   if (0 != stat) {
      printf ("Error reading message file %s\n", filename);
      decodeBuffer.printErrorInfo();
      return stat;
   }
   decodeBuffer.setDiag (verbose);

   ASN1T_SNMPv3Message msgV3Data;
   ASN1C_SNMPv3Message snmpMessage (decodeBuffer, msgV3Data);

   //Decode Message 
   stat = snmpMessage.Decode ();
   if (stat == 0) {
      if (trace) {
         printf ("Decode of SNMPv3Message was successful\n");
         printf ("Decoded record:\n");
         snmpMessage.Print("snmpMessage");
      }
   }
   else {
      printf ("decode of SNMP message failed\n");
      decodeBuffer.PrintErrorInfo ();
      return -1;
   }

   /* Decode PDU's */
   if (msgV3Data.msgData.t == T_ScopedPduData_plaintext) {
      decodeBuffer.setBuffer(msgV3Data.msgData.u.plaintext->data.data, 
                             msgV3Data.msgData.u.plaintext->data.numocts);
      ASN1T_PDUs pduData;
      ASN1C_PDUs pdus(decodeBuffer, pduData);
      stat = pdus.Decode();
      if (stat == 0) {
         if (trace) {
            printf ("Decode of PDUs was successful\n");
            printf ("Decoded record:\n");
            pdus.Print("pdus");
         }
      }
      else {
         printf ("decode of SNMP PDUs failed\n");
         decodeBuffer.PrintErrorInfo ();
         return -1;
      }
   }
   return 0;
}
