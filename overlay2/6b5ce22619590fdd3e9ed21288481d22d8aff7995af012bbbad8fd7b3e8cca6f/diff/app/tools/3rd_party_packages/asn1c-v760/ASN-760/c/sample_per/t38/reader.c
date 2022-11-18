// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "T38.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   IFPPacket    primaryPacket, secondaryPacket;
   UDPTLPacket  udptlPacket;

   OSCTXT       c1, c2, c3;
   OSOCTET	msgbuf[200];
   const OSOCTET *msgptr;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int          i, stat;
   OSSIZE       len;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader -a | -u [ -v ] [ -i <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
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

   /* Create a new context structure */

   if (rtInitContext (&c1) != 0) {
      rtxErrPrint (&c2);
      return -1;
   }
   rtxSetDiag (&c1, verbose);
   pu_setBuffer (&c1, msgbuf, len, aligned);
   pu_setTrace (&c1, trace);

   /* First, decode the UDPTLPacket structure */

   stat = asn1PD_UDPTLPacket (&c1, &udptlPacket);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&c1, "udptlPacket");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of UDPTLPacket was successful:\n");
         asn1Print_UDPTLPacket ("udptlPacket", &udptlPacket);
      }
   }
   else {
      printf ("decode of UDPTLPacket failed\n");
      rtxErrPrint (&c1);
      return -1;
   }

   /* Decode primary IFPPacket */

   msgptr = udptlPacket.primary_ifp_packet.data;
   len = udptlPacket.primary_ifp_packet.numocts;

   if (rtInitSubContext (&c2, &c1) != 0) {
      rtxErrPrint (&c2);
      return -1;
   }
   rtxSetDiag (&c2, verbose);
   pu_setBuffer (&c2, msgbuf, len, aligned);
   pu_setTrace (&c2, trace);

   stat = asn1PD_IFPPacket (&c2, &primaryPacket);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&c2, "primaryPacket");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of IFPPacket was successful:\n");
         asn1Print_IFPPacket ("primaryPacket", &primaryPacket);
      }
   }
   else {
      printf ("decode of IFPPacket failed\n");
      rtxErrPrint (&c2);
      return -1;
   }

   rtFreeContext (&c2);

   /* Decode secondary IFP packets */

   if (udptlPacket.error_recovery.t == 
       T_UDPTLPacket_error_recovery_secondary_ifp_packets)
   {
      ASN1OpenType* pOpenType;
      OSRTDListNode* pNode = 
         udptlPacket.error_recovery.u.secondary_ifp_packets->head;
      i = 0;

      while (0 != pNode) {
         if (rtInitSubContext (&c3, &c1) != 0) {
            rtxErrPrint (&c3);
            return -1;
         }
         rtxSetDiag (&c3, verbose);
         pOpenType = (ASN1OpenType*) pNode->data;
         pu_setBuffer (&c3, (OSOCTET*)pOpenType->data, 
                       pOpenType->numocts, aligned);
         pu_setTrace (&c3, trace);

         stat = asn1PD_IFPPacket (&c3, &secondaryPacket);

         if (trace) {
            printf ("Dump of decoded bit fields for secondary packet %d:\n", 
                    ++i);
            pu_bindump (&c3, "secondaryPacket");
            printf ("\n");
         }

         if (stat == 0) {
            if (trace) {
               printf ("decode of IFPPacket was successful:\n");
               asn1Print_IFPPacket ("secondaryPacket", &secondaryPacket);
            }
         }
         else {
            printf ("decode of IFPPacket failed\n");
            rtxErrPrint (&c3);
            return -1;
         }

         rtFreeContext (&c3);
         pNode = pNode->next;
      }
   }
   else {
      printf ("ERROR: Unexpected error recovery choice option = %d\n", 
              udptlPacket.error_recovery.t);
      return -1;
   }

   rtFreeContext (&c1);
   return 0;
}

