package sample_per.VBrackets;

import com.objsys.asn1j.runtime.*;

public class Reader {

   public static void main (String args[])
   {
      String filename = new String ("message.dat");
      boolean aligned = true;
      boolean trace = true;
      // Process command line arguments
      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v"))
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-i")) 
               filename = new String (args[++i]);
            else if (args[i].equals ("-a")) 
               aligned = true;
            else if (args[i].equals ("-u")) 
               aligned = false;
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println("usage: Reader [ -a | -u ] " +
                                    "[ -v ] [ -i <filename>");
               System.out.println("   -a  PER aligned encoding (default)");
               System.out.println("   -u  PER unaligned encoding");
               System.out.println("   -v  verbose mode: print trace info");
               System.out.println("   -i <filename>  " +
                                   "read encoded msg from <filename>");
               System.out.println("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }

      try {
         // Diag.setTraceLevel(1);

         // Create an input file stream object
         java.io.FileInputStream ins = new java.io.FileInputStream (filename);

         // Create a decode buffer object
         Asn1PerDecodeBuffer decodeBuffer = 
            new Asn1PerDecodeBuffer (ins, aligned);

         // Enable bit field tracing
         if (trace) {
            decodeBuffer.getTraceHandler().enable();
         }

         // Read and decode the message
         TestSequence value = new TestSequence ();
         value.decode (decodeBuffer);
         if (trace) {
            System.out.println("Decode was successful");
            value.print (System.out, "value", 0);
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();
         System.exit(-1);
      }
   }
}
