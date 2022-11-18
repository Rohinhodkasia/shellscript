/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.6.A, Date: 22-Oct-2012.
 */
package sample_json.Biometrics;

import com.objsys.asn1j.runtime.*;
import java.util.*;
import sample_json.Biometrics.SignatureAlgorithmIdentifier;
import sample_json.Biometrics.MACAlgorithmIdentifier;
import sample_json.Biometrics.SignedData;
import sample_json.Biometrics.AuthenticatedData;
import sample_json.Biometrics.EncryptedData;
import sample_json.Biometrics.EnvelopedData;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.XMLReaderFactory;

public class Reader {

   public static void main (String args[])
   {
      String filename = new String ("message.json");
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
               System.out.println("usage: Reader [ -v ] [ -i <filename>");
               System.out.println("   -v  verbose mode: print trace info");
               System.out.println("   -i <filename>  " +
                                   "read encoded msg from <filename>");
               System.out.println("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }

      try {
         // Create an input file stream object
         java.io.FileInputStream ins = new java.io.FileInputStream (filename);

         Asn1JsonDecodeBuffer decodeBuffer = new Asn1JsonDecodeBuffer(ins);
         // Read and decode the message
         BiometricSyntax value = new BiometricSyntax ();
         value.decode (decodeBuffer);
         if (trace) {
            System.out.println("Decode was successful");
            value.print (System.out, "value", 0);
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();
         System.exit(1);
      }
   }
}
