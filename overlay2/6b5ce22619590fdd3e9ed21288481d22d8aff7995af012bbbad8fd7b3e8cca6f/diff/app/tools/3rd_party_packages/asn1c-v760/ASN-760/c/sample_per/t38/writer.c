// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "T38.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

OSOCTET testData1[] = { 0x00 };
OSOCTET testData2[] = { 0x11, 0x22, 0x33 };
OSOCTET testData3[] = { 0xaa, 0xbb, 0xcc, 0xdd };
OSOCTET testData4[] = { 0xee, 0xff };

int main (int argc, char** argv)
{
   ASN1OpenType secIfpPackets[2];
   Data_Field_element dataFieldSeq[10];
   IFPPacket    primaryPacket, secPacket1, secPacket2;
   UDPTLPacket  udptlPacket;
   UDPTLPacket_error_recovery_secondary_ifp_packets secIfpPacketSeq;

   OSCTXT       c1, c2, c3, c4;
   OSOCTET	buf1[100], buf2[100], buf3[100], buf4[200], *msgptr;
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int		i, len, stat;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

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

   /* Populate primary IFP packet structure */

   if (rtInitContext (&c1) != 0) {
      rtxErrPrint (&c1);
      return -1;
   }
   rtxSetDiag (&c1, verbose);
   primaryPacket.type_of_msg.t = T_Type_of_msg_data;
   primaryPacket.type_of_msg.u.data = v21;
   primaryPacket.m.data_fieldPresent = TRUE;
   rtxDListInit (&primaryPacket.data_field);

   dataFieldSeq[0].m.field_dataPresent = TRUE;
   dataFieldSeq[0].field_type = hdlc_data;
   dataFieldSeq[0].field_data.numocts = 1;
   dataFieldSeq[0].field_data.data = testData1;
   rtxDListAppend (&c1, &primaryPacket.data_field, &dataFieldSeq[0]);

   dataFieldSeq[1].m.field_dataPresent = FALSE;
   dataFieldSeq[1].field_type = hdlc_fcs_OK_sig_end;
   dataFieldSeq[1].field_data.numocts = 0;
   dataFieldSeq[1].field_data.data = 0;
   rtxDListAppend (&c1, &primaryPacket.data_field, &dataFieldSeq[1]);

   dataFieldSeq[2].m.field_dataPresent = TRUE;
   dataFieldSeq[2].field_type = t4_non_ecm_data;
   dataFieldSeq[2].field_data.numocts = 4;
   dataFieldSeq[2].field_data.data = testData3;

   dataFieldSeq[3].m.field_dataPresent = FALSE;
   dataFieldSeq[3].field_type = t4_non_ecm_sig_end;
   dataFieldSeq[3].field_data.numocts = 0;
   dataFieldSeq[3].field_data.data = 0;

   /* Encode */

   pu_setBuffer (&c1, buf1, sizeof(buf1), aligned);
   pu_setTrace (&c1, trace);

   stat = asn1PE_IFPPacket (&c1, &primaryPacket);

   if (stat == 0) {
      if (trace) {
         pu_hexdump (&c1);
         pu_bindump (&c1, "primaryPacket");
      }
   }
   else {
      rtxErrPrint (&c1);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&c1, &len);

   udptlPacket.primary_ifp_packet.numocts = len;
   udptlPacket.primary_ifp_packet.data = msgptr;

   /* Populate and encode some secondary packet structures */

   if (rtInitSubContext (&c2, &c1) != 0) {
      rtxErrPrint (&c2);
      return -1;
   }
   rtxSetDiag (&c2, verbose);
   secPacket1.type_of_msg.t = T_Type_of_msg_data;
   secPacket1.type_of_msg.u.data = v27_2400;
   secPacket1.m.data_fieldPresent = TRUE;
   rtxDListInit (&secPacket1.data_field);

   dataFieldSeq[0].m.field_dataPresent = TRUE;
   dataFieldSeq[0].field_type = hdlc_sig_end;
   dataFieldSeq[0].field_data.numocts = 2;
   dataFieldSeq[0].field_data.data = testData4;
   rtxDListAppend (&c2, &secPacket1.data_field, &dataFieldSeq[0]);

   pu_setBuffer (&c2, buf2, sizeof(buf2), aligned);
   pu_setTrace (&c2, trace);

   stat = asn1PE_IFPPacket (&c2, &secPacket1);

   if (stat == 0) {
      if (trace) {
         pu_hexdump (&c2);
         pu_bindump (&c2, "secPacket1");
      }
   }
   else {
      rtxErrPrint (&c2);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&c2, &len);

   if (rtInitSubContext (&c3, &c1) != 0) {
      rtxErrPrint (&c3);
      return -1;
   }
   rtxSetDiag (&c3, verbose);
   secIfpPackets[0].numocts = len;
   secIfpPackets[0].data = msgptr;

   secPacket2.type_of_msg.t = T_Type_of_msg_data;
   secPacket2.type_of_msg.u.data = v17_14400;
   secPacket2.m.data_fieldPresent = TRUE;
   rtxDListInit (&secPacket2.data_field);

   dataFieldSeq[0].m.field_dataPresent = FALSE;
   dataFieldSeq[0].field_type = hdlc_sig_end;
   dataFieldSeq[0].field_data.numocts = 0;
   dataFieldSeq[0].field_data.data = 0;
   rtxDListAppend (&c3, &secPacket2.data_field, &dataFieldSeq[0]);

   pu_setBuffer (&c3, buf3, sizeof(buf3), aligned);
   pu_setTrace (&c3, trace);

   stat = asn1PE_IFPPacket (&c3, &secPacket2);

   if (stat == 0) {
      if (trace) {
         pu_hexdump (&c3);
         pu_bindump (&c3, "secPacket2");
      }
   }
   else {
      rtxErrPrint (&c3);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&c3, &len);

   if (rtInitSubContext (&c4, &c1) != 0) {
      rtxErrPrint (&c4);
      return -1;
   }
   rtxSetDiag (&c4, verbose);
   secIfpPackets[1].numocts = len;
   secIfpPackets[1].data = msgptr;

   rtxDListInit (&secIfpPacketSeq);
   rtxDListAppend (&c4, &secIfpPacketSeq, &secIfpPackets[0]);
   rtxDListAppend (&c4, &secIfpPacketSeq, &secIfpPackets[1]);

   /* Populate UDPTLPacket structure */

   udptlPacket.seq_number = 1;

   /* note: primary packet field was populated earlier */

   udptlPacket.error_recovery.t = 
     T_UDPTLPacket_error_recovery_secondary_ifp_packets;

   udptlPacket.error_recovery.u.secondary_ifp_packets = &secIfpPacketSeq;

   /* Encode the UDPTLPacket structure */

   if (trace) {
      printf ("\n");
      printf ("Encoding UDPTLPacket..\n");
      printf ("\n");
   }

   pu_setBuffer (&c4, buf4, sizeof(buf4), aligned);
   pu_setTrace (&c4, trace);

   stat = asn1PE_UDPTLPacket (&c4, &udptlPacket);

   if (stat == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&c4);
         printf ("Binary dump:\n");
         pu_bindump (&c4, "udptlPacket");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&c4);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&c4, &len);

   /* Write the encoded message out to the output file */

   if (fp = fopen (filename, "wb")) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   rtFreeContext (&c4);
   rtFreeContext (&c3);
   rtFreeContext (&c2);
   rtFreeContext (&c1);
   return 0;

}
