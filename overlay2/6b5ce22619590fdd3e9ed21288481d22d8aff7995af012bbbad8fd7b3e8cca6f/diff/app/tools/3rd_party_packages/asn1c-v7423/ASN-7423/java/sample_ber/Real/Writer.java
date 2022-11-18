package sample_ber.Real;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
       String filename = new String ("message.dat");
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
                System.out.println ("usage: Writer [ -v ] [ -o <filename>");
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

      try {
          personnelRecord.bits = new Asn1BitString ("'11010010111001'B");
          personnelRecord.name = new Asn1VisibleString ("Director");
          personnelRecord.fp = new FloatingPoint(-0.7654321E+139);
          //personnelRecord.fp = new FloatingPoint(Double.POSITIVE_INFINITY);
          //personnelRecord.fp = new FloatingPoint (Double.NEGATIVE_INFINITY);

          System.out.println ("Encoding real is: " + personnelRecord.fp);

          // Create a message buffer object and encode the record

          Asn1BerEncodeBuffer encodeBuffer = new Asn1BerEncodeBuffer();

          personnelRecord.encode (encodeBuffer, true);

          if (trace) {
              System.out.println ("Encoding was successful");
              System.out.println ("Hex dump of encoded record:");
              encodeBuffer.hexDump ();
              System.out.println ("Binary dump:");
              encodeBuffer.binDump ();
          }

          // Write the encoded record to a file

          encodeBuffer.write (new FileOutputStream (filename));

          // Generate a dump file for comparisons

          encodeBuffer.hexDump
              (new PrintStream (new FileOutputStream ("message.dmp")));
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();
          System.exit(-1);
      }
   }
}
