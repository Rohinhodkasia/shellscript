package sample_per.TimeString;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.util.Calendar;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.dat");
      boolean aligned = true, trace = true;

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
      TimesSeq tmSeq = new TimesSeq();
      tmSeq.genTime = new GenTime("19991224085044");
      tmSeq.utcTime = new UtcTime("9912140850Z");

      // Create a message buffer object and encode the record
      Asn1PerEncodeBuffer encodeBuffer = new Asn1PerEncodeBuffer(aligned);

      if (trace) {
         encodeBuffer.getTraceHandler().enable();
      }
      try {
          Calendar current = Calendar.getInstance();
          tmSeq.genTime.setTime(current);
          tmSeq.genTime.setFraction("2");
          
          tmSeq.utcTime.setYear(1985);
          tmSeq.utcTime.setMonth(Asn1Time.February);
          tmSeq.utcTime.setDay(22);
          tmSeq.utcTime.setHour(5);
          tmSeq.utcTime.setMinute(35);
          tmSeq.utcTime.setUTC(true);

          tmSeq.encode (encodeBuffer);
          if (trace) {
              System.out.println ("Encoding was successful");
              System.out.println ("Hex dump of encoded record:");
              encodeBuffer.hexDump ();
              System.out.println ("Binary dump:");
              encodeBuffer.binDump ("tmSeq");
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
