package sample_oer.Employee;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Reader {
   public static void main (String args[]) {
      String filename = new String ("message.dat");
      boolean trace = true;
      int itercnt = 1;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
                Diag.instance().setEnabled (true);
            else if (args[i].equals ("-i")) 
                filename = new String (args[++i]);
            else if (args[i].equals ("-iter")) 
                itercnt = Integer.parseInt (args[++i]);
            else if (args[i].equals ("-trace")) trace = true;
            else {
                System.out.println ("usage: Reader [ -v ] [ -o <filename>");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -i <filename>  " +
                                    "read encoded msg from <filename>");
                System.out.println ("   -iter <count>  set iteration count\n");
                System.out.println ("   -trace  display trace info");
                return;
            }
         }
      }

      PersonnelRecord msgdata = null;

      try {
         Asn1OerDecodeBuffer decodeBuffer = null;

         File file;
         FileInputStream in;

         file = new File (filename);
         decodeBuffer = new Asn1OerDecodeBuffer (new FileInputStream (file));

         // Read and decode the message
         msgdata = new PersonnelRecord ();
         msgdata.decode (decodeBuffer);

         if (trace) {
            System.out.println (
               "Decode of non-canonical message was successful");
            msgdata.print (System.out, "non-canonical-msgdata", 0);
         }

         //Now do the same for the canonical message
         file = new File (filename + ".canonical");
         decodeBuffer = new Asn1OerDecodeBuffer (new FileInputStream (file));
         decodeBuffer.setCanonicalMode(true);

         msgdata = new PersonnelRecord();
         msgdata.decode (decodeBuffer);

         if (trace) {
            System.out.println (
               "\n\nDecode of canonical message was successful");
            msgdata.print (System.out, "canonical-msgdata", 0);
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();    
         if ( msgdata != null ) {
            msgdata.print (System.out, "partly decoded msgdata", 0);
         }
         System.exit(-1);
      }
   }
}
