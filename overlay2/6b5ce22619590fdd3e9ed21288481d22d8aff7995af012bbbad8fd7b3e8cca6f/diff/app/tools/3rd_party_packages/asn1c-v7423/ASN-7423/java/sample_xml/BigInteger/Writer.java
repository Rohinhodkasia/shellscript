package sample_xml.BigInteger;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.xml");
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
               System.out.println 
                  ("usage: Writer [-v] [-o <filename>] [-notrace]");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                   "write encoded msg to <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }

      // Create a data object and populate it with the data to be encoded

      Dss_Parms dssParms = new Dss_Parms 
          (new Asn1BigInteger ("112233445566778899aabbccddeeff", 16),
           new Asn1BigInteger ("-1234567890123456789012345678901234567890"), 
           new Asn1BigInteger ("1234567890123456789012345678901234567890"));

      if (trace) {
          System.out.println ("dssParms.p = " + dssParms.p);
          System.out.println ("dssParms.q = " + dssParms.q);
          System.out.println ("dssParms.g = " + dssParms.g + "\n");
      }

      // Create a message buffer object and encode the record

      try {
         Asn1XmlEncodeBuffer encodeBuffer = new Asn1XmlEncodeBuffer ();
   
         dssParms.encode (encodeBuffer);

         if (trace) {
            System.out.println ("Encoding was successful");
            encodeBuffer.write (System.out);
         }

         // Write the encoded record to a file

         encodeBuffer.write (new FileOutputStream (filename));
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }
}
