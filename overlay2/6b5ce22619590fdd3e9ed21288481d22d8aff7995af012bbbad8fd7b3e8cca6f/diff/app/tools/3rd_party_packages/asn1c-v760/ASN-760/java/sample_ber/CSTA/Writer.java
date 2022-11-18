package sample_ber.CSTA;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import sample_ber.SimpleROSE.*;

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

      // Create a data object and populate it with the data to be encoded

      MakeCallArgument makeCallArgument = new MakeCallArgument ();

      makeCallArgument.callingDevice = new DeviceID ();
      makeCallArgument.callingDevice.
         set_dialingNumber (new NumberDigits("555-1212"));

      makeCallArgument.calledDirectoryNumber = new CalledDeviceID ();
      makeCallArgument.calledDirectoryNumber.set_notRequired ();

      // Create a message buffer object and encode the record

      Asn1BerEncodeBuffer encodeBuffer = new Asn1BerEncodeBuffer();

      try {
          makeCallArgument.encode (encodeBuffer, true);

          if (trace) {
              System.out.println ("Encoding was successful");
              System.out.println ("Hex dump of encoded record:");
              encodeBuffer.hexDump ();
              System.out.println ("Binary dump:");
              encodeBuffer.binDump ();
          }
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }

      // Create a ROSE Invoke PDU object to wrap the encoded call argument. 
      // Note the optimization with the open type.  By constructing the 
      // object using only the length, a copy of the already-encoded 
      // message component is avoided..

      Asn1OpenType openType = new Asn1OpenType (encodeBuffer.getMsgLength());

      RosePDU rosePDU = new RosePDU ();
      rosePDU.set_invokePDU
          (new InvokePDU (new InvokeIDType(1),   // invoke ID
                          null,                  // linked ID 
                          new Asn1Integer(10),   // operation code
                          openType));            // encoded argument

      // Encode the final message

      try {
          rosePDU.encode (encodeBuffer, true);

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

