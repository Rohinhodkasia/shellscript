package sample_per.CMLogon;

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

      try {
         // Create an input file stream object

         FileInputStream in = new FileInputStream (filename);

          // Create an ACSE decode buffer object

         Asn1PerDecodeBuffer acseDecodeBuffer = 
            new Asn1PerDecodeBuffer (in, aligned);

          // Enable bit field tracing

         if (trace) {
            acseDecodeBuffer.getTraceHandler().enable();
         }

         // Decode the ACSE header

         ACSE_apdu acse = new ACSE_apdu ();

         acse.decode (acseDecodeBuffer);

         if (trace) {
            System.out.println ("ACSE decode was successful");
            acse.print (System.out, "acse", 0);
            System.out.println ("");
            System.out.println ("Binary trace:");
            acseDecodeBuffer.binDump ("acse");
         }

         // Decode CM Aircraft Message 

         AARQ_apdu aarq = (AARQ_apdu) acse.getElement();
         Asn1External ext = aarq.user_information.elements[0];
         Asn1BitString externalData = 
            (Asn1BitString) ext.encoding.getElement();

         Asn1PerDecodeBuffer cmDecodeBuffer = 
            new Asn1PerDecodeBuffer (externalData.value, aligned);

         CMAircraftMessage cmAircraftMessage = new CMAircraftMessage ();

         if (trace) {
            cmDecodeBuffer.getTraceHandler().enable();
         }

         cmAircraftMessage.decode (cmDecodeBuffer);

         if (trace) {
            System.out.println ("CMAircraftMessage decode was successful");
            cmAircraftMessage.print (System.out, "cmAircraftMessage", 0);
            System.out.println ("");
            System.out.println ("Binary trace:");
            cmDecodeBuffer.binDump ("cmAircraftMessage");
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();           
         System.exit(-1);
      }
   }
}
