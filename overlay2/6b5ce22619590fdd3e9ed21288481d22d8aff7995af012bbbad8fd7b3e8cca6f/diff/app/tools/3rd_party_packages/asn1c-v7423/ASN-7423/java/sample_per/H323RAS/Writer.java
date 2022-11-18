package sample_per.H323RAS;

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

      int[] protocolID = { 0, 0, 8, 2250, 0, 2 } ;
      byte[] ip = { (byte)0xc0, (byte)0xa8, (byte)0x00, (byte)0x01 } ;

      RegistrationConfirm registrationConfirm = 
         new RegistrationConfirm ();

      registrationConfirm.requestSeqNum = new RequestSeqNum (1);
      registrationConfirm.protocolIdentifier = 
         new ProtocolIdentifier (protocolID);

      registrationConfirm.callSignalAddress = new _SeqOfTransportAddress (1);
      registrationConfirm.callSignalAddress.elements[0] = 
         new TransportAddress ();
      registrationConfirm.callSignalAddress.elements[0].set_ipAddress
         (new TransportAddress_ipAddress (ip, 1720));

      registrationConfirm.terminalAlias = new _SeqOfAliasAddress (1);
      registrationConfirm.terminalAlias.elements[0] = new AliasAddress ();
      registrationConfirm.terminalAlias.elements[0].set_h323_ID 
         (new Asn1BMPString ("anH323ID"));

      registrationConfirm.gatekeeperIdentifier = 
         new GatekeeperIdentifier ("aGatekeeperID");

      registrationConfirm.endpointIdentifier =
         new EndpointIdentifier ("anEndpointID");

      RasMessage rasMessage = new RasMessage ();
      rasMessage.set_registrationConfirm (registrationConfirm);

      // Create a message buffer object 

      Asn1PerEncodeBuffer encodeBuffer = new Asn1PerEncodeBuffer (aligned);

      // Enable bit field tracing

      if (trace) {
         encodeBuffer.getTraceHandler().enable();
      }

      // Encode

      try {
         rasMessage.encode (encodeBuffer);

         if (trace) {
            System.out.println ("Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            encodeBuffer.hexDump ();
            System.out.println ("Binary dump:");
            encodeBuffer.binDump ("rasMessage");
         }

         // Write the encoded record to a file

         encodeBuffer.write (new FileOutputStream (filename));

         // Generate a dump file for comparisons

         String fileSuffix = (aligned) ? "a" : "u";
         encodeBuffer.hexDump 
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
