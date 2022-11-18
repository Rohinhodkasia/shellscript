package sample_ber.SnmpV1;

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
      // Set up to retrieve sysDescr object..

      SimpleSyntax simpleSyntax = new SimpleSyntax ();
      simpleSyntax.set_empty ();

      ObjectSyntax objectSyntax = new ObjectSyntax ();
      objectSyntax.set_simple (simpleSyntax);

      int[] sysDescrIdx = { 0 };
      ObjectName sysDescr = new ObjectName (_RFC1213_MIBValues.sysDescr);
      sysDescr.append (sysDescrIdx);

      VarBindList varBindList = new VarBindList (1);
      varBindList.elements[0] = new VarBind (sysDescr, objectSyntax);

      // Populate get_request PDU structure

      PDUs pdus = new PDUs ();
      pdus.set_get_request (new GetRequest_PDU (1, 0, 0, varBindList));

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
              System.out.println ("---");
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
