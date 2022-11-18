package sample_per.RealDec;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.dat");
      boolean aligned = true, trace = true;
      String nr3a = new String("8991"),
             nr3b = new String("-8991.17"),
             nr3c = new String("8991,17e-02");

      // Process command line arguments

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
               System.out.println ("usage: Writer [ -a | -u ] [ -v ] " +
                                   "[ -o <filename>");
               System.out.println ("   -a  PER aligned encoding (default)");
               System.out.println ("   -u  PER unaligned encoding");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                   "write encoded msg to <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }

      // Create a data object and populate it with the data to be encoded

      PersonnelRecord personnelRecord = new PersonnelRecord ();

      // Create a message buffer object 

      Asn1PerEncodeBuffer encodeBuffer = new Asn1PerEncodeBuffer (aligned);

      // Enable bit field tracing

      if (trace) {
         encodeBuffer.getTraceHandler().enable();
      }

      // Encode

      try {
          Asn1BitString bits = new Asn1BitString ("'101'B");
          encodeBuffer.getTraceHandler().addElemName ("bits", -1);
          bits.encode (encodeBuffer);
          encodeBuffer.getTraceHandler().removeLastElemName ();

          byte b = 3;
          encodeBuffer.encodeLength (nr3a.length() + 1);
          encodeBuffer.copy (b);
          encodeBuffer.encodeBits (nr3a.getBytes(), 0, nr3a.length() * 8);

          encodeBuffer.encodeLength (nr3b.length() + 1);
          encodeBuffer.copy (b);
          encodeBuffer.encodeBits (nr3b.getBytes(), 0, nr3b.length() * 8);

          encodeBuffer.encodeLength (nr3c.length() + 1);
          encodeBuffer.copy (b);
          encodeBuffer.encodeBits (nr3c.getBytes(), 0, nr3c.length() * 8);

          if (trace) {
              System.out.println ("Encoding was successful");
              System.out.println ("Hex dump of encoded record:");
              encodeBuffer.hexDump ();
              System.out.println ("Binary dump:");
              encodeBuffer.binDump ("personnelRecord");
          }

          // Write the encoded record to a file

          encodeBuffer.write (new FileOutputStream (filename));

          // Generate a dump file for comparisons

          String fileSuffix = (aligned) ? "a" : "u";
          encodeBuffer.hexDump 
              (new PrintStream (new FileOutputStream 
                 ("message_" + fileSuffix + ".dmp")));
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }
}
