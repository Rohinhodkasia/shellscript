// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "T38.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

OSOCTET testData1[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
OSOCTET testData2[] = { 0x11, 0x22, 0x33 };
OSOCTET testData3[] = { 0xaa, 0xbb, 0xcc, 0xdd };
OSOCTET testData4[] = { 0xee, 0xff };

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int          i, stat;
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-cxer")) cxer = TRUE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -cxer          use canonical XER rules (CXER)\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Populate primary IFP packet structure 

   OSOCTET buf1[1024];
   OSXMLEncodeBuffer encodeBuffer1 (buf1, sizeof(buf1));
   rtxCtxtSetFlag (encodeBuffer1.getCtxtPtr(), OSXMLC14N);
   rtxCtxtSetFlag (encodeBuffer1.getCtxtPtr(), OSXMLFRAG);

   ASN1T_IFPPacket primaryData;
   ASN1C_IFPPacket primaryPacket (encodeBuffer1, primaryData);

   primaryData.type_of_msg.t = T_Type_of_msg_data;
   primaryData.type_of_msg.u.data = Type_of_msg_data::v29_9600;

   primaryData.m.data_fieldPresent = TRUE;
   ASN1T_Data_Field_element* pDataFieldElem;
   ASN1CSeqOfList dataFieldList (encodeBuffer1, primaryData.data_field);

   pDataFieldElem = (ASN1T_Data_Field_element*)
      primaryPacket.memAlloc (sizeof(ASN1T_Data_Field_element));
   memset (pDataFieldElem, 0, sizeof(ASN1T_Data_Field_element));
   pDataFieldElem->m.field_dataPresent = TRUE;
   pDataFieldElem->field_type = Data_Field_element_field_type::hdlc_sig_end;
   pDataFieldElem->field_data.numocts = 5;
   pDataFieldElem->field_data.data = testData1;
   dataFieldList.append (pDataFieldElem);

   pDataFieldElem = (ASN1T_Data_Field_element*)
      primaryPacket.memAlloc (sizeof(ASN1T_Data_Field_element));
   memset (pDataFieldElem, 0, sizeof(ASN1T_Data_Field_element));
   pDataFieldElem->m.field_dataPresent = TRUE;
   pDataFieldElem->field_type = Data_Field_element_field_type::hdlc_fcs_OK;
   pDataFieldElem->field_data.numocts = 3;
   pDataFieldElem->field_data.data = testData2;
   dataFieldList.append (pDataFieldElem);

   pDataFieldElem = (ASN1T_Data_Field_element*)
      primaryPacket.memAlloc (sizeof(ASN1T_Data_Field_element));
   memset (pDataFieldElem, 0, sizeof(ASN1T_Data_Field_element));
   pDataFieldElem->m.field_dataPresent = TRUE;
   pDataFieldElem->field_type = Data_Field_element_field_type::t4_non_ecm_data;
   pDataFieldElem->field_data.numocts = 4;
   pDataFieldElem->field_data.data = testData3;
   dataFieldList.append (pDataFieldElem);

   pDataFieldElem = (ASN1T_Data_Field_element*)
      primaryPacket.memAlloc (sizeof(ASN1T_Data_Field_element));
   memset (pDataFieldElem, 0, sizeof(ASN1T_Data_Field_element));
   pDataFieldElem->m.field_dataPresent = TRUE;
   pDataFieldElem->field_type = 
      Data_Field_element_field_type::t4_non_ecm_sig_end;
   pDataFieldElem->field_data.numocts = 2;
   pDataFieldElem->field_data.data = testData4;
   dataFieldList.append (pDataFieldElem);

   // Encode

   stat = primaryPacket.Encode ();

   if (stat == 0) {
      if (trace) {
         printf ("primaryPacket encoded XML message:\n");
         buf1 [encodeBuffer1.getMsgLen ()] = 0;
         printf ((const char*)buf1);
         printf ("\n");
         printf ("***\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer1.printErrorInfo ();
      return -1;
   }
  
   // Populate fields in UDPTL packet structure for later use

   OSOCTET buf4[4096];
   OSXMLEncodeBuffer encodeBuffer4 (buf4, sizeof(buf4));
   if (cxer) rtxCtxtSetFlag (encodeBuffer4.getCtxtPtr(), OSXMLC14N);

   ASN1T_UDPTLPacket udptlData;
   ASN1C_UDPTLPacket udptlPacket (encodeBuffer4, udptlData);

   udptlData.primary_ifp_packet.data = 
     (OSOCTET*) encodeBuffer1.getMsgPtr ();

   udptlData.primary_ifp_packet.numocts = encodeBuffer1.getMsgLen ();

   // Populate and encode some secondary packet structures

   OSOCTET buf2[1024];
   OSXMLEncodeBuffer encodeBuffer2 (buf2, sizeof(buf2));
   rtxCtxtSetFlag (encodeBuffer2.getCtxtPtr(), OSXMLC14N);
   rtxCtxtSetFlag (encodeBuffer2.getCtxtPtr(), OSXMLFRAG);

   ASN1T_IFPPacket secData;
   ASN1C_IFPPacket secPacket1 (encodeBuffer2, secData);

   secData.type_of_msg.t = T_Type_of_msg_data;
   secData.type_of_msg.u.data = Type_of_msg_data::v27_2400;

   secData.m.data_fieldPresent = TRUE;
   ASN1CSeqOfList secDataFldLst (encodeBuffer2, secData.data_field);
   pDataFieldElem = (ASN1T_Data_Field_element*)
      secPacket1.memAlloc (sizeof(ASN1T_Data_Field_element));
   memset (pDataFieldElem, 0, sizeof(ASN1T_Data_Field_element));
   pDataFieldElem->m.field_dataPresent = TRUE;
   pDataFieldElem->field_type = Data_Field_element_field_type::hdlc_sig_end;
   pDataFieldElem->field_data.numocts = 2;
   pDataFieldElem->field_data.data = testData4;
   secDataFldLst.append (pDataFieldElem);

   stat = secPacket1.Encode ();

   if (stat == 0) {
      if (trace) {
         printf ("secPacket1 encoded XML message:\n");
         buf2 [encodeBuffer2.getMsgLen ()] = 0;
         printf ((const char*)buf2);
         printf ("\n");
         printf ("***\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer2.printErrorInfo ();
      return -1;
   }
  
   ASN1T_UDPTLPacket_error_recovery_secondary_ifp_packets secIfpPacketSeq;
   ASN1C_UDPTLPacket_error_recovery_secondary_ifp_packets secIfpPacketSeqC 
      (encodeBuffer2, secIfpPacketSeq);

   ASN1TOpenType *pSecIfpPacket;
   pSecIfpPacket = (ASN1TOpenType*)
      secIfpPacketSeqC.memAlloc (sizeof(ASN1TOpenType));
   pSecIfpPacket->numocts = encodeBuffer2.getMsgLen ();
   pSecIfpPacket->data = (OSOCTET*) encodeBuffer2.getMsgPtr ();
   secIfpPacketSeqC.append (pSecIfpPacket);

   OSOCTET buf3[1024];
   OSXMLEncodeBuffer encodeBuffer3 (buf3, sizeof(buf3));
   rtxCtxtSetFlag (encodeBuffer3.getCtxtPtr(), OSXMLC14N);
   rtxCtxtSetFlag (encodeBuffer3.getCtxtPtr(), OSXMLFRAG);

   ASN1T_IFPPacket secData2;
   ASN1C_IFPPacket secPacket2 (encodeBuffer3, secData2);

   secData2.type_of_msg.t = T_Type_of_msg_data;
   secData2.type_of_msg.u.data = Type_of_msg_data::v17_14400;

   secData2.m.data_fieldPresent = TRUE;
   ASN1CSeqOfList secData2FldLst (encodeBuffer3, secData2.data_field);
   pDataFieldElem = (ASN1T_Data_Field_element*)
      secPacket2.memAlloc (sizeof(ASN1T_Data_Field_element));
   memset (pDataFieldElem, 0, sizeof(ASN1T_Data_Field_element));
   pDataFieldElem->m.field_dataPresent = FALSE;
   pDataFieldElem->field_type = Data_Field_element_field_type::hdlc_sig_end;
   pDataFieldElem->field_data.numocts = 0;
   pDataFieldElem->field_data.data = 0;
   secData2FldLst.append (pDataFieldElem);

   stat = secPacket2.Encode ();

   if (stat == 0) {
      if (trace) {
         printf ("secPacket2 encoded XML message:\n");
         buf3 [encodeBuffer3.getMsgLen ()] = 0;
         printf ((const char*)buf3);
         printf ("\n");
         printf ("***\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer3.printErrorInfo ();
      return -1;
   }
  
   pSecIfpPacket = (ASN1TOpenType*)
      secIfpPacketSeqC.memAlloc (sizeof(ASN1TOpenType));
   pSecIfpPacket->numocts = encodeBuffer3.getMsgLen ();
   pSecIfpPacket->data = (OSOCTET*) encodeBuffer3.getMsgPtr ();
   secIfpPacketSeqC.append (pSecIfpPacket);

   // Populate UDPTLPacket structure

   udptlData.seq_number = 1;

   // note: primary packet field was populated earlier

   udptlData.error_recovery.t = 
     T_UDPTLPacket_error_recovery_secondary_ifp_packets;

   udptlData.error_recovery.u.secondary_ifp_packets = 
      &secIfpPacketSeq;

   // Encode the UDPTLPacket structure

   if (trace) {
      printf ("\n");
      printf ("Encoding UDPTLPacket..\n");
      printf ("\n");
   }

   stat = udptlPacket.Encode ();

   if (stat == 0) {
      if (trace) {
         printf ("udptlPacket encoded XML message:\n");
         printf ((const char*)buf4);
         printf ("\n");
         printf ("***\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer4.printErrorInfo ();
      return -1;
   }
  
   // Write encoded message to output file

   if (encodeBuffer4.write (filename) < 0) {
      printf ("write message to output file '%s' failed.\n", filename);
      return -1;
   }

   return 0;
}
