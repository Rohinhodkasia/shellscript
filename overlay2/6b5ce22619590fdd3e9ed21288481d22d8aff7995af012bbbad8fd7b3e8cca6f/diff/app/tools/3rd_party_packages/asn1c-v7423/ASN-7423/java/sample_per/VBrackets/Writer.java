package sample_per.VBrackets;

import com.objsys.asn1j.runtime.*;
import java.util.*;

public class Writer {

   public static void main(String args[]) {

      String filename = new String ("message.dat");
      boolean aligned = true;
      boolean trace = true;
      
      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v"))
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o"))
               filename = new String (args[++i]);
            else if (args[i].equals ("-a"))
               aligned = true;
            else if (args[i].equals ("-u"))
               aligned = false;
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println("usage: Writer [-a|-u] [-v] [-o <filename>] [-notrace]");
               System.out.println("   -a  PER aligned encoding (default)");
               System.out.println("   -u  PER unaligned encoding");
               System.out.println("   -v  verbose mode: print trace info");
               System.out.println("   -o <filename>  " +
                                          "write encoded msg to <filename>");
               System.out.println("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }
      
      // Create a message buffer object
      Asn1PerEncodeBuffer encodeBuffer =
         new Asn1PerEncodeBuffer (aligned);
      try {
         if (trace) {
            encodeBuffer.getTraceHandler().enable();
         }
         TestSequence testSequence;
         testSequence = new TestSequence();
         testSequence.item_code = new Asn1Integer(29);
         testSequence.item_name = new Asn1IA5String("SHERRY");
         testSequence.urgency = TestSequence_urgency.high();
         testSequence.alternate_item_code = new Asn1Integer(45);
         testSequence.mV3ExtPresent = true;
         testSequence.alternate_item_name = new Asn1IA5String("PORT");
         testSequence.extElem1 = null;

         testSequence.encode (encodeBuffer);

         if (trace) {
            System.out.println("Encoding was successful");
            System.out.println("Hex dump of encoded record:");
            encodeBuffer.hexDump ();
            System.out.println("Binary dump:");
            encodeBuffer.binDump ("value");
            // Write the encoded record to a file
            encodeBuffer.write (new java.io.FileOutputStream (filename));
         }
      }
      catch (Exception e) {
         System.out.println(e.getMessage());
         e.printStackTrace();
         System.exit(-1);
      }
   }
}
