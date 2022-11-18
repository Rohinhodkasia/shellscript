// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "T38.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.dat";
   int          i, stat;
   OSSIZE       len;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader -a | -u [ -v ] [ -i <filename> ] ");
            printf ("[ -notrace ]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // First, decode the UDPTLPacket structure

   ASN1PERDecodeBuffer decodeBuffer1 (aligned);
   ASN1T_UDPTLPacket udptlData;
   ASN1C_UDPTLPacket udptlPacket (decodeBuffer1, udptlData);

   decodeBuffer1.readBinaryFile (filename);
   if (decodeBuffer1.getStatus() != 0) {
      printf("Error opening %s for read access\n", filename);
      decodeBuffer1.printErrorInfo();
      return -1;
   }
   decodeBuffer1.setTrace (trace);

   stat = udptlPacket.Decode ();

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      decodeBuffer1.binDump ("udptlPacket");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of UDPTLPacket was successful:\n");
         udptlPacket.Print ("udptlPacket");
      }
   }
   else {
       printf ("decode of UDPTLPacket failed\n");
       decodeBuffer1.printErrorInfo ();
       exit (-1);
   }

   // Decode primary IFPPacket

   const OSOCTET* msgptr = udptlData.primary_ifp_packet.data;
   len = udptlData.primary_ifp_packet.numocts;

   ASN1PERDecodeBuffer decodeBuffer2 (msgptr, len, aligned);
   ASN1T_IFPPacket primaryData;
   ASN1C_IFPPacket primaryPacket (decodeBuffer2, primaryData);

   decodeBuffer2.setTrace (trace);

   stat = primaryPacket.Decode ();

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      decodeBuffer2.BinDump ("primaryPacket");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of IFPPacket was successful:\n");
         primaryPacket.Print ("primaryPacket");
      }
   }
   else {
       printf ("decode of IFPPacket failed\n");
       decodeBuffer2.printErrorInfo ();
       exit (-1);
   }

   return 0;
}

