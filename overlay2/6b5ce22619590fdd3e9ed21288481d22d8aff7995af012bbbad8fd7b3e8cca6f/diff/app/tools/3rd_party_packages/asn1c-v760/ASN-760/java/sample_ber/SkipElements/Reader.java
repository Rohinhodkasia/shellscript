import com.objsys.asn1j.runtime.*;
import java.util.*;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.XMLReaderFactory;

public class Reader {

   public static void main (String args[])
   {
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
               System.out.println("usage: Reader [ -v ] [ -i <filename>");
               System.out.println("   -v  verbose mode: print trace info");
               System.out.println("   -i <filename>  " +
                                   "read encoded msg from <filename>");
               System.out.println("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }

      //First, read using normal reader
      try {
         // Create an input file stream object
         java.io.FileInputStream ins = new java.io.FileInputStream (filename);

         // Create a decode buffer object
         Asn1BerDecodeBuffer decodeBuffer = 
            new Asn1BerDecodeBuffer (ins);
         // Read and decode the message
         full.SkipElements.PDU value = new full.SkipElements.PDU ();
         value.decode (decodeBuffer);
         if (trace) {
            System.out.println("Decode was successful");
            value.print (System.out, "value", 0);
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();
      }

      //Next, read using partial reader
      try {
         // Create an input file stream object
         java.io.FileInputStream ins = new java.io.FileInputStream (filename);

         // Create a decode buffer object
         Asn1BerDecodeBuffer decodeBuffer = 
            new Asn1BerDecodeBuffer (ins);
         // Read and decode the message
         partial.SkipElements.PDU value = new partial.SkipElements.PDU ();
         value.decode (decodeBuffer);
         if (trace) {
            System.out.println("Decode was successful");
            value.print (System.out, "value", 0);
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();
      }
   }
}
