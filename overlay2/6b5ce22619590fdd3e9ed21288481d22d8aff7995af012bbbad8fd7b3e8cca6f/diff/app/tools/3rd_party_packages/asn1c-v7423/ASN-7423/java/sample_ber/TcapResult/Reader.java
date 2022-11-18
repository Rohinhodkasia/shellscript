package sample_ber.TcapResult;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import sample_ber.AIN.*;
import sample_ber.TCAP.*;

public class Reader {
   public static void main (String args[]) {
       String filename = new String ("message.dat");
       boolean trace = true;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
                Diag.instance().setEnabled (true);
            else if (args[i].equals ("-i")) 
                filename = new String (args[++i]);
            else if (args[i].equals ("-notrace")) trace = false;
            else {
                System.out.println ("usage: Reader [ -v ] [ -o <filename>");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -i <filename>  " +
                                    "read encoded msg from <filename>");
                System.out.println ("   -notrace  do not display trace info");
                return;
            }
         }
      }

      try {
          // Create an input file stream object

          FileInputStream in = new FileInputStream (filename);

          // Create a decode buffer object

          Asn1BerDecodeBuffer decodeBuffer = new Asn1BerDecodeBuffer (in);

          // Read and decode the TCAP header

          MessageType messageType = new MessageType ();
          messageType.decode (decodeBuffer);
          if (trace) {
              System.out.println ("Decode MessageType was successful");
              messageType.print (System.out, "messageType", 0);
              System.out.println ("");
          }

          // Decode the result

          Undirectional undirectional = 
              (Undirectional) messageType.getElement();

          ReturnResult resultPDU = (ReturnResult) 
              undirectional.components.elements[0].getElement();

          Asn1BerDecodeBuffer decodeBuffer2 = 
              new Asn1BerDecodeBuffer (resultPDU.result.parameter.value);

          CallInfoFromResource_RESULT result = 
              new CallInfoFromResource_RESULT ();

          result.decode (decodeBuffer2);
          if (trace) {
              System.out.println 
                  ("Decode CallInfoFromResource_RESULT was successful");
              result.print (System.out, "result", 0);
          }
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }
}
