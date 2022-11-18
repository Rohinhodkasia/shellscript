package sample_xml.InfoObject;

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

      // Encode a format type

      Asn1Boolean b = new Asn1Boolean (true);
      Asn1XmlEncodeBuffer encodeBuffer = new Asn1XmlEncodeBuffer ();
      try {
         encodeBuffer.setIndent (0);
         b.encode (encodeBuffer, null, null);

         if (trace) {
            System.out.println ("Encoding of FormatType was successful");
            encodeBuffer.write (System.out);
            System.out.println ("");
         }
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }

      // Create a data object and populate it with the data to be encoded

      BIOMETRIC_IDENTIFIER bioID = new BIOMETRIC_IDENTIFIER();
      bioID.set_id (new Asn1RelativeOID (_TestValues.id_ibia_SecuGen));

      Format format = new Format (bioID, new Asn1XerOpenType(encodeBuffer));

      // Encode final message

      encodeBuffer.reset ();
      encodeBuffer.setIndent (3);
      try {
         format.encode (encodeBuffer);

         if (trace) {
            System.out.println ("Encoding of format was successful");
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
