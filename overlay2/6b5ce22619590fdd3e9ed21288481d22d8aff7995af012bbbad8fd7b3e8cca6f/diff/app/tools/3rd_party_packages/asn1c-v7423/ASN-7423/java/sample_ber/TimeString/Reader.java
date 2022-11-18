package sample_ber.TimeString;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Reader {
   public static void main (String args[]) {
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
                System.out.println ("usage: Reader [ -v ] [ -o <filename>");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -i <filename>  " +
                                    "read encoded msg from <filename>");
                System.out.println ("   -notrace  do not display trace info");
                return;
            }
         }
      }

      try {
          // Create an input file stream object

          FileInputStream in = new FileInputStream (filename);

          // Create a decode buffer object

          Asn1BerDecodeBuffer decodeBuffer = new Asn1BerDecodeBuffer (in);

          // Read and decode the message
          TimesSeq tmSeq = new TimesSeq ();
          tmSeq.decode (decodeBuffer);
          if (trace) {
              System.out.println ("Decode was successful");
              tmSeq.print (System.out, "tmSeq", 0);
          }
          System.out.println("GenTime:");
          System.out.println("Year: " + tmSeq.genTime.getYear());
          System.out.println("Month: " + tmSeq.genTime.getMonth());
          System.out.println("Day: " + tmSeq.genTime.getDay());
          System.out.println("Hour: " + tmSeq.genTime.getHour());
          System.out.println("Minute: " + tmSeq.genTime.getMinute());
          System.out.println("Second: " + tmSeq.genTime.getSecond());
          System.out.println("Fraction: " + tmSeq.genTime.getFraction());
          System.out.println("DiffH: " + tmSeq.genTime.getDiffHour());
          System.out.println("DiffM: " + tmSeq.genTime.getDiffMinute());

          System.out.println("");
          System.out.println("UtcTime:");
          System.out.println("Year: " + tmSeq.utcTime.getYear());
          System.out.println("Month: " + tmSeq.utcTime.getMonth());
          System.out.println("Day: " + tmSeq.utcTime.getDay());
          System.out.println("Hour: " + tmSeq.utcTime.getHour());
          System.out.println("Minute: " + tmSeq.utcTime.getMinute());
          System.out.println("Second: " + tmSeq.utcTime.getSecond());
          System.out.println("DiffH: " + tmSeq.utcTime.getDiffHour());
          System.out.println("DiffM: " + tmSeq.utcTime.getDiffMinute());
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }
}
