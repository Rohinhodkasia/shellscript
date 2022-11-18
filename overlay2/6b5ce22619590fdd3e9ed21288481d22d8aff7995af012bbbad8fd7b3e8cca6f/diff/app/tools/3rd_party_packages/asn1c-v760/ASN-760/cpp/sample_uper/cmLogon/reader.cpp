// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "ACSE-1.h"
#include "CMMessageSetVersion1.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, trace = TRUE;
   const char*  filename = "message.dat";
   int          i, stat;
   OSSIZE       len;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v][-i <filename>][-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // First, decode the ACSE header

   ASN1PERDecodeBuffer acseDecodeBuffer (filename, /*aligned*/FALSE);
   ASN1T_ACSE_apdu acse;
   ASN1C_ACSE_apdu acsePDU (acseDecodeBuffer, acse);

   acseDecodeBuffer.SetTrace (trace);  // enable bin trace of decode

   stat = acsePDU.Decode ();

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      acseDecodeBuffer.BinDump ("acse");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of ACSE_apdu was successful\n");
      }
   }
   else {
       printf ("decode of ACSE_apdu failed\n");
       acseDecodeBuffer.PrintErrorInfo ();
       return stat;
   }

   // Check fields for expected values

   if (acse.t != T_ACSE_apdu_aarq) {
      printf ("ERROR: expecting T_ACSE_apdu_aarq, got %d\n", acse.t);
      return (-1);
   }

   if (!acse.u.aarq->m.user_informationPresent) {
      printf ("ERROR: encoded aircraft message is not present.\n");
      return (-1);
   }

   if (acse.u.aarq->user_information.count != 1) {
      printf ("ERROR: expecting only 1 external element, got " OSSIZEFMT "\n",
              acse.u.aarq->user_information.count);
      return (-1);
   }

   ASN1C_Association_information uiList
      (acseDecodeBuffer, acse.u.aarq->user_information);
   ASN1T_External* ext = (ASN1T_External*) uiList.get(0);
   if (ext->encoding.t != 
       T_External_encoding_arbitrary) {
      printf ("ERROR: expecting arbitray encoding, got %d\n", ext->encoding.t);
      return (-1);
   }

   // Decode CM Aircraft Message 

   const OSOCTET* msgptr = ext->encoding.u.arbitrary->data;

   len = ext->encoding.u.arbitrary->numbits / 8;
   if (ext->encoding.u.arbitrary->numbits % 8 != 0) len++;

   ASN1PERDecodeBuffer cmDecodeBuffer (msgptr, len, /*aligned*/FALSE);
   ASN1T_CMAircraftMessage msgData;
   ASN1C_CMAircraftMessage cmAircraftMessage (cmDecodeBuffer, msgData);

   cmDecodeBuffer.SetTrace (trace);  // enable bin trace of decode

   stat = cmAircraftMessage.Decode ();

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      cmDecodeBuffer.BinDump ("cmAircraftMessage");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of CMAircraftMessage was successful\n");
         cmAircraftMessage.Print ("pdu");
      }
   }
   else {
       printf ("decode of CMAircraftMessage failed\n");
       cmDecodeBuffer.PrintErrorInfo ();
   }

   return stat;
}

