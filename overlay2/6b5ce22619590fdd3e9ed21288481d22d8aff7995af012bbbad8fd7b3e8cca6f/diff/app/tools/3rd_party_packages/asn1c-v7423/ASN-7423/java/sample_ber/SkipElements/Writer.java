import com.objsys.asn1j.runtime.*;
import java.util.*;
import full.SkipElements.*;

public class Writer {

   /* PDU: SkipElements.PDU */
   public static void main(String args[]) {

      String filename = new String ("message.dat");
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
      
      // Create a message buffer object
      Asn1BerEncodeBuffer encodeBuffer =
         new Asn1BerEncodeBuffer ();
      try {
         PDU pDU;
         pDU = new PDU();
         pDU.firstName = new Asn1UTF8String("Thomas");
         pDU.lastName = new Asn1UTF8String("Trustworthy");
         pDU.details = new Details();
         pDU.details.birthYear = new Asn1Integer(2130);
         pDU.details.numChildren = new Asn1Integer(5);
         pDU.details.favoriteColor = new Asn1UTF8String("Khaki Rose");

         pDU.encode (encodeBuffer);
         if (trace) {
            System.out.println("Encoding was successful");
            System.out.println("Hex dump of encoded record:");
            encodeBuffer.hexDump ();
            System.out.println("Binary dump:");
            encodeBuffer.binDump ();
            // Write the encoded record to a file
            encodeBuffer.write (new java.io.FileOutputStream (filename));
         }
      }
      catch (Exception e) {
         System.out.println(e.getMessage());
         e.printStackTrace();
         System.exit(1);
      }
   }
}
