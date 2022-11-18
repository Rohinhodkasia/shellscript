// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "InfoObject.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static OSBOOL trace = TRUE, verbose = FALSE;

static OSSIZE encodeCause (OSOCTET* pbuf, OSSIZE bufsiz, OSBOOL aligned);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET	buf1[100], msgbuf[MAXMSGLEN];
   OSBOOL       aligned = TRUE;
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

   // Encode a message to insert as open type

   len = encodeCause (buf1, sizeof(buf1), aligned);
   if (len == OSNULLINDEX) return -1;

   // Create an instance of the compiler generated class and populate

   ASN1PEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf), aligned);
   ASN1T_Iu_ReleaseCommand msgData;
   ASN1C_Iu_ReleaseCommand releaseCommand (encodeBuffer, msgData);
   ASN1T_ProtocolIE_Field protocolIEs[1];

   memset (protocolIEs, 0, sizeof(protocolIEs));
   protocolIEs[0].id = 12345;
   protocolIEs[0].criticality = Criticality::notify;
   protocolIEs[0].value.numocts = len;
   protocolIEs[0].value.data = buf1;

   ASN1CSeqOfList protocolIEsList (encodeBuffer, msgData.protocolIEs);
   protocolIEsList.append (&protocolIEs[0]);

   // Encode

   encodeBuffer.setTrace (trace);

   if ((stat = releaseCommand.Encode ()) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
         printf ("Binary dump:\n");
         encodeBuffer.binDump ("cause");
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


// Encode message for use in open type field

static OSSIZE encodeCause (OSOCTET* pbuf, OSSIZE bufsiz, OSBOOL aligned)
{
   int stat;

   ASN1PEREncodeBuffer encodeBuffer (pbuf, bufsiz, aligned);
   ASN1T_Cause msgData;
   ASN1C_Cause cause (encodeBuffer, msgData);

   msgData.t = T_Cause_radioNetwork;
   msgData.u.radioNetwork = CauseRadioNetwork::relocation_triggered;

   encodeBuffer.setDiag (verbose);
   encodeBuffer.setTrace (trace);

   if ((stat = cause.Encode ()) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.hexDump ();
         printf ("Binary dump:\n");
         encodeBuffer.binDump ("cause");
      }
      return encodeBuffer.getMsgLen ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return OSNULLINDEX;
   }
}
