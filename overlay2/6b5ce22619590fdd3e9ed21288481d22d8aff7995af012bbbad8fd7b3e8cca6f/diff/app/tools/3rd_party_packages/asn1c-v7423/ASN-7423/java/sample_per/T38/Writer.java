package sample_per.T38;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.dat");
      boolean aligned = true, trace = true;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o")) 
               filename = new String (args[++i]);
            else if (args[i].equals ("-a")) 
               aligned = true;
            else if (args[i].equals ("-u")) 
               aligned = false;
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println ("usage: Writer [ -a | -u ] [ -v ] " +
                                   "[ -o <filename>");
               System.out.println ("   -a  PER aligned encoding (default)");
               System.out.println ("   -u  PER unaligned encoding");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                   "write encoded msg to <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }

      // Create a data object and populate it with the data to be encoded

      byte[] testData1 = { (byte)0x01, (byte)0x02, (byte)0x03, (byte)0x04, 
                           (byte)0x05 };
      byte[] testData2 = { (byte)0x11, (byte)0x22, (byte)0x33 };
      byte[] testData3 = { (byte)0xaa, (byte)0xbb, (byte)0xcc, (byte)0xdd };
      byte[] testData4 = { (byte)0xee, (byte)0xff };

      try {
         IFPPacket ifpPacket = new IFPPacket ();

         ifpPacket.type_of_msg = new Type_of_msg ();
         ifpPacket.type_of_msg.set_data (Type_of_msg_data.v29_9600());

         ifpPacket.data_field = new Data_Field (4);

         ifpPacket.data_field.elements[0] = new Data_Field_element
            (Data_Field_element_field_type.hdlc_sig_end(), testData1);

         ifpPacket.data_field.elements[1] = new Data_Field_element
            (Data_Field_element_field_type.hdlc_fcs_OK(), testData2);

         ifpPacket.data_field.elements[2] = new Data_Field_element
            (Data_Field_element_field_type.t4_non_ecm_data(), testData3);

         ifpPacket.data_field.elements[3] = new Data_Field_element
            (Data_Field_element_field_type.t4_non_ecm_sig_end(), testData4);

         // Create a message buffer object 

         Asn1PerEncodeBuffer encodeBuffer1 = new Asn1PerEncodeBuffer (aligned);

         // Enable bit field tracing

         if (trace) {
            encodeBuffer1.getTraceHandler().enable();
         }

         // Encode

         ifpPacket.encode (encodeBuffer1);

         if (trace) {
            System.out.println ("Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            encodeBuffer1.hexDump ();
            System.out.println ("Binary dump:");
            encodeBuffer1.binDump ("ifpPacket");
         }

         // Populate and encode some secondary packet structures

         IFPPacket secPacket1 = new IFPPacket ();

         secPacket1.type_of_msg = new Type_of_msg ();
         secPacket1.type_of_msg.set_data
            (Type_of_msg_data.v27_2400());

         secPacket1.data_field = new Data_Field (1);

         secPacket1.data_field.elements[0] = new Data_Field_element
            (Data_Field_element_field_type.hdlc_sig_end(), testData4);

         // Encode

         Asn1PerEncodeBuffer encodeBuffer2 = new Asn1PerEncodeBuffer (aligned);
         if (trace) {
            encodeBuffer2.getTraceHandler().enable();
         }

         secPacket1.encode (encodeBuffer2);

         if (trace) {
            System.out.println ("Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            encodeBuffer2.hexDump ();
            System.out.println ("Binary dump:");
            encodeBuffer2.binDump ("secPacket1");
         }

         // Populate a 2nd secondary packet structure

         IFPPacket secPacket2 = new IFPPacket ();

         secPacket2.type_of_msg = new Type_of_msg ();
         secPacket2.type_of_msg.set_data
            (Type_of_msg_data.v17_14400());

         secPacket2.data_field = new Data_Field (1);

         secPacket2.data_field.elements[0] = new Data_Field_element
            (Data_Field_element_field_type.hdlc_sig_end());

         // Encode

         Asn1PerEncodeBuffer encodeBuffer3 = new Asn1PerEncodeBuffer (aligned);
         if (trace) {
            encodeBuffer3.getTraceHandler().enable();
         }

         secPacket2.encode (encodeBuffer3);

         if (trace) {
            System.out.println ("Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            encodeBuffer3.hexDump ();
            System.out.println ("Binary dump:");
            encodeBuffer3.binDump ("secPacket2");
         }

         // Populate UDPTL packet structure

         UDPTLPacket udptlPacket = new UDPTLPacket ();

         udptlPacket.seq_number = new Asn1Integer (1);

         udptlPacket.primary_ifp_packet = new Asn1OpenType 
            (encodeBuffer1.getBuffer(), 0, encodeBuffer1.getMsgByteCnt());

         UDPTLPacket_error_recovery_secondary_ifp_packets secIFPPkts =
            new UDPTLPacket_error_recovery_secondary_ifp_packets (2);

         secIFPPkts.elements[0] =
            new Asn1OpenType (encodeBuffer2.getBuffer(), 0, 
                              encodeBuffer2.getMsgByteCnt());

         secIFPPkts.elements[1] =
            new Asn1OpenType (encodeBuffer3.getBuffer(), 0, 
                              encodeBuffer3.getMsgByteCnt());

         udptlPacket.error_recovery = new UDPTLPacket_error_recovery ();
         udptlPacket.error_recovery.set_secondary_ifp_packets (secIFPPkts);

         // Encode

         Asn1PerEncodeBuffer encodeBuffer4 = new Asn1PerEncodeBuffer (aligned);
         if (trace) {
            encodeBuffer4.getTraceHandler().enable();
            System.out.println ("");
            System.out.println ("Encoding UDPTLPacket..");
            System.out.println ("");
         }

         udptlPacket.encode (encodeBuffer4);

         if (trace) {
            System.out.println ("Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            encodeBuffer4.hexDump ();
            System.out.println ("Binary dump:");
            encodeBuffer4.binDump ("udptlPacket");
         }

         // Write the encoded record to a file

         encodeBuffer4.write (new FileOutputStream (filename));

         // Generate a dump file for comparisons

         String fileSuffix = (aligned) ? "a" : "u";
         encodeBuffer4.hexDump 
            (new PrintStream (new FileOutputStream 
               ("message_" + fileSuffix + ".dmp")));
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }
}
