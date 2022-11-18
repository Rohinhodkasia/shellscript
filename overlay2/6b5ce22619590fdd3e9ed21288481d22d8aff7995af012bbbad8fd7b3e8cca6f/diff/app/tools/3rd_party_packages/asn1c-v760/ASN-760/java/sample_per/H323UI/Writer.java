package sample_per.H323UI;

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
      byte[] guid = new byte [16];
      for (int i = 0; i < guid.length; i++) {
         guid[i] = (byte) (i + 1);
      }

      Setup_UUIE setup = new Setup_UUIE ();
      setup.protocolIdentifier = new ProtocolIdentifier (protocolID);
      setup.sourceInfo = new EndpointType ();
      setup.sourceInfo.mc = Asn1Boolean.FALSE_VALUE;
      setup.sourceInfo.undefinedNode = Asn1Boolean.FALSE_VALUE;
      setup.activeMC = Asn1Boolean.FALSE_VALUE;
      setup.conferenceID = new ConferenceIdentifier (guid);
      setup.conferenceGoal = new Setup_UUIE_conferenceGoal ();
      setup.conferenceGoal.set_create ();
      setup.callType = new CallType ();
      setup.callType.set_pointToPoint ();
      setup.callIdentifier = new CallIdentifier (guid);
      setup.mediaWaitForConnect = Asn1Boolean.FALSE_VALUE;
      setup.canOverlapSend = Asn1Boolean.FALSE_VALUE;

      H323_UserInformation userInfo = new H323_UserInformation ();
      userInfo.h323_uu_pdu = new H323_UU_PDU ();
      userInfo.h323_uu_pdu.h323_message_body = 
         new H323_UU_PDU_h323_message_body ();
      userInfo.h323_uu_pdu.h323_message_body.set_setup (setup);

      // Create a message buffer object 

      Asn1PerEncodeBuffer encodeBuffer = new Asn1PerEncodeBuffer (aligned);

      // Enable bit field tracing

      if (trace) {
         encodeBuffer.getTraceHandler().enable();
      }

      // Encode

      try {
         userInfo.encode (encodeBuffer);

         if (trace) {
            System.out.println ("Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            encodeBuffer.hexDump ();
            System.out.println ("Binary dump:");
            encodeBuffer.binDump ("userInfo");
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
