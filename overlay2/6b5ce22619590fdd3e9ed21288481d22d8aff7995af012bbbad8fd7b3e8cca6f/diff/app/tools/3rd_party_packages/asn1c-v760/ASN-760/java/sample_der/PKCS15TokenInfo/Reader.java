package sample_der.PKCS15TokenInfo;

import com.objsys.asn1j.runtime.*;
import java.io.*;

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

          Asn1DerDecodeBuffer decodeBuffer = new Asn1DerDecodeBuffer (in);

          // Read and decode the message

          TokenInfo tokenInfo = new TokenInfo ();
          tokenInfo.decode (decodeBuffer);
          if (trace) {
              System.out.println ("Decode was successful");
              tokenInfo.print (System.out, "tokenInfo", 0);
          }
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }
}
