package sample_per.H323UI;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Reader {
   public static void main (String args[]) {
      String filename = new String ("message.dat");
      boolean aligned = true, trace = true;

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
               System.out.println ("usage: Reader [ -a | -u ] " +
                                   "[ -v ] [ -i <filename>");
               System.out.println ("   -a  PER aligned encoding (default)");
               System.out.println ("   -u  PER unaligned encoding");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -i <filename>  " +
                                   "read encoded msg from <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }

      // Create an input file stream object

      FileInputStream in = null;
      try {
         in = new FileInputStream (filename);
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();           
         System.exit(-1);
      }

      // Create a decode buffer object

      Asn1PerDecodeBuffer decodeBuffer = 
         new Asn1PerDecodeBuffer (in, aligned);

      H323_UserInformation userInfo = new H323_UserInformation ();

      try {
          // Enable bit field tracing

         if (trace) {
            decodeBuffer.getTraceHandler().enable();
         }

         // Read and decode the message

         userInfo.decode (decodeBuffer);
         if (trace) {
            System.out.println ("Decode was successful");
            userInfo.print (System.out, "userInfo", 0);
            System.out.println ("");
            System.out.println ("Binary trace:");
            decodeBuffer.binDump ("userInfo");
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();           
         System.out.println ("");
         System.out.println ("Decode failed.");
         userInfo.print (System.out, "userInfo", 0);
         System.out.println ("");
         System.out.println ("Binary trace:");
         decodeBuffer.binDump ("userInfo");
         System.exit(-1);
      }
   }
}
