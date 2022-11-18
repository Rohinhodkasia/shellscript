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
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE;
   int          i, stat;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -i <filename> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // First, decode the UDPTLPacket structure

   OSXMLDecodeBuffer decodeBuffer1 (filename);
   ASN1T_UDPTLPacket udptlData;
   ASN1C_UDPTLPacket udptlPacket (decodeBuffer1, udptlData);

   stat = udptlPacket.Decode ();

   if (0 == stat) {
      if (trace) {
         printf ("decode of UDPTLPacket was successful:\n");
         udptlPacket.Print ("udptlPacket");
         printf ("\n");
         printf ("***\n");
      }
   }
   else {
      printf ("decode of UDPTLPacket failed\n");
      decodeBuffer1.printErrorInfo ();
      return (1);
   }

   // Decode primary IFPPacket

   const OSOCTET* msgptr = udptlData.primary_ifp_packet.data;
   OSSIZE len = udptlData.primary_ifp_packet.numocts;

   OSXMLDecodeBuffer decodeBuffer2 (msgptr, len);
   ASN1T_IFPPacket primaryData;
   ASN1C_IFPPacket primaryPacket (decodeBuffer2, primaryData);

   stat = primaryPacket.Decode ();

   if (stat == 0) {
      if (trace) {
         printf ("decode of IFPPacket was successful:\n");
         primaryPacket.Print ("primaryPacket");
         printf ("***\n");
      }
   }
   else {
      printf ("decode of IFPPacket failed\n");
      decodeBuffer2.printErrorInfo ();
      return (2);
   }

   if (udptlData.error_recovery.t == 
       T_UDPTLPacket_error_recovery_secondary_ifp_packets) 
   {
      // Decode secondary IFPPacket
      ASN1CSeqOfList list 
         (decodeBuffer2, *udptlData.error_recovery.u.secondary_ifp_packets, 
          FALSE);

      ASN1CSeqOfListIterator* iter = list.iterator ();
      int i = 0;
      while (iter->hasNext ()) {
         ASN1TOpenType* ot = (ASN1TOpenType*)iter->next ();

         const OSOCTET* msgptr = ot->data;
         OSSIZE len = ot->numocts;

         OSXMLDecodeBuffer decodeBuffer3 (msgptr, len);
         ASN1T_IFPPacket secondaryData;
         ASN1C_IFPPacket secondaryPacket (decodeBuffer3, secondaryData);

         stat = secondaryPacket.Decode ();

         if (stat == 0) {
            if (trace) {
               printf ("decode of secondary IFPPacket was successful:\n");
               char s[256];
               sprintf (s, "secondaryPacket[%i]", i++);
               secondaryPacket.Print (s);
               printf ("\n");
            }
         }
         else {
            printf ("decode of secondary IFPPacket failed\n");
            decodeBuffer2.printErrorInfo ();
            return (2);
         }
      }
   }

   return (stat);

}
