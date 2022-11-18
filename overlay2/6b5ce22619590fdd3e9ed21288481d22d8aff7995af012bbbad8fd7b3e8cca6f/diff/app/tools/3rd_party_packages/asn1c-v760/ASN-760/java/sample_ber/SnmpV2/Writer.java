package sample_ber.SnmpV2;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
       String filename = new String ("message.dat");
       boolean trace = true;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
                Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o")) 
                filename = new String (args[++i]);
            else if (args[i].equals ("-notrace")) trace = false;
            else {
                System.out.println ("usage: Writer [ -v ] [ -o <filename>");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -o <filename>  " +
                                    "write encoded msg to <filename>");
                System.out.println ("   -notrace  do not display trace info");
                return;
            }
         }
      }

      // Populate variable bindings structure:
      // This is a GetResponse for the UDB MIB returning the 
      // the udpLocalAddress field 

      int[] udpLocalAddressIdx = { 192, 180, 140, 202, 520 };
      ObjectName udpLocalAddressName = 
          new ObjectName (_UDP_MIBValues.udpLocalAddress);
      udpLocalAddressName.append (udpLocalAddressIdx);

      byte[] ipAddress = { (byte)135, (byte)180, (byte)140, (byte)202 };

      ApplicationSyntax applicationSyntax = new ApplicationSyntax ();
      applicationSyntax.set_ipAddress_value (new IpAddress (ipAddress));

      ObjectSyntax objectSyntax = new ObjectSyntax ();
      objectSyntax.set_application_wide (applicationSyntax);

      VarBind_aChoice udpLocalAddressValue = new VarBind_aChoice ();
      udpLocalAddressValue.set_value (objectSyntax);

      VarBindList varBindList  = new VarBindList (1);
      varBindList.elements[0] = 
          new VarBind (udpLocalAddressName, udpLocalAddressValue);

      // Populate get_response PDU structure

      PDUs pdus = new PDUs ();
      pdus.set_response (new Response_PDU (1827802204, 0, 0, varBindList));

      // Populate main message structure

      Asn1OctetString community = null;
      try {
          community = new Asn1OctetString ("public");
      }
      catch (Asn1ValueParseException e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }

      Message snmpMessage = new Message 
         (new Message_version (Message_version.version_1), community, pdus);

      // Encode 

      Asn1BerEncodeBuffer encodeBuffer = new Asn1BerEncodeBuffer();

      try {
          snmpMessage.encode (encodeBuffer, true);

          if (trace) {
              System.out.println ("Encoding was successful");
              System.out.println ("Hex dump of encoded record:");
              encodeBuffer.hexDump ();
              System.out.println ("Binary dump:");
              encodeBuffer.binDump ();
          }

          // Write the encoded record to a file

          encodeBuffer.write (new FileOutputStream (filename));

          // Generate a dump file for comparisons

          encodeBuffer.hexDump 
              (new PrintStream (new FileOutputStream ("message.dmp")));
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }
}
