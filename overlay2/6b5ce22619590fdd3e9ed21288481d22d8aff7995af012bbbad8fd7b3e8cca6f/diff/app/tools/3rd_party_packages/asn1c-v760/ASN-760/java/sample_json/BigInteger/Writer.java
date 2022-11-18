package sample_json.BigInteger;

import com.objsys.asn1j.runtime.*;
import java.util.*;

public class Writer {

   /* PDU: BigInt.BigIntType */
   public static void main(String args[]) {

      String filename = new String ("message.json");
      boolean trace = true;
      
      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v"))
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o"))
               filename = new String (args[++i]);
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println("usage: Writer [-v] [-o <filename>]");
               System.out.println("   -v  verbose mode: print trace info");
               System.out.println("   -o <filename>  " +
                                          "write encoded msg to <filename>");
               System.out.println("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }
      
      // Create an encoding stream
      Asn1JsonOutputStream encodeStream = null;
      try {
         encodeStream = new Asn1JsonOutputStream (new java.io.OutputStreamWriter( new java.io.FileOutputStream(filename), "UTF-8") );

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

         dssParms.encode (encodeStream);
         if (trace) {
            System.out.println("Encoding was successful");
         }
      }
      catch (Exception e) {
         System.out.println(e.getMessage());
         e.printStackTrace();
         System.exit(1);
      }
      finally {
         try {
            if (encodeStream != null) encodeStream.close ();
         }
         catch (Exception e) {
         }
      }
   }
}
