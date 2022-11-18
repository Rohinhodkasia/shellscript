package sample_xer.BitString;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.util.BitSet;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.xml");
      boolean cxer = false, trace = true;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o")) 
               filename = new String (args[++i]);
            else if (args[i].equals ("-cxer")) 
               cxer = true;
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println ("usage: Writer [ -cxer ] [ -v ] " +
                                   "[ -o <filename>");
               System.out.println ("   -cxer  Use Canonical XER");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                   "write encoded msg to <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }

      try {
         // Create a data object and populate it with the data to be encoded

         BS3 bs3 = new BS3();
         bs3.set (BS3.a);
         bs3.clear (BS3.b);
         bs3.set (BS3.c);

         BS2 bs2 = new BS2 ("'0000000001'B");

         BitSet jbs = new BitSet();

         /*// in JDK 1.4 you may use this portion of code 
         jbs.set (2, 612);
         jbs.clear (611);
         jbs.flip (2, 611);
         jbs.flip (68);
         */

         for (int i = 2; i < 612; i++)
            jbs.set (i);
         jbs.clear (610);

         BS1 bs1 = new BS1 (jbs);

         BSSeq bsseq = new BSSeq (bs1, bs2, bs3);

         // Create a message buffer object and encode the record

         Asn1XerEncodeBuffer encodeBuffer = 
            new Asn1XerEncodeBuffer (cxer, 0);

         encodeBuffer.encodeStartDocument ();

         bsseq.encode (encodeBuffer, null);

         encodeBuffer.encodeEndDocument ();

         if (trace) {
            System.out.println ("Encoding was successful");
            encodeBuffer.write (System.out);
         }

         // Write the encoded record to a file

         encodeBuffer.write (new FileOutputStream (filename));
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();           
         System.exit(-1);
      }
   }
}
