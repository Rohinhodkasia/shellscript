package sample_per.ParamType;

import com.objsys.asn1j.runtime.*;
import java.io.*;

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

      int[] algorithmOIDValue = { 0, 0, 8, 2250, 0, 1 };

      byte[] signatureValue = {
         (byte)0xaa, (byte)0xbb, (byte)0xcc, (byte)0xdd, 
         (byte)0xee, (byte)0xff
      };

      byte[] iv8Value = new byte [8];
      for (int i = 0; i < 8; i++) {
         iv8Value[i] = (byte)(i + 0x7d);
      }

      SignedName signedName = new SignedName ();
      signedName.toBeSigned = new Name ("John", "P", "Smith");
      signedName.algorithmOID = new Asn1ObjectIdentifier (algorithmOIDValue);
      signedName.paramS = new Params (222, iv8Value);
      signedName.signature = new Asn1BitString 
         (signatureValue.length * 8, signatureValue);

      // Create a message buffer object 

      Asn1PerEncodeBuffer encodeBuffer = new Asn1PerEncodeBuffer (aligned);

      // Enable bit field tracing

      if (trace) {
         encodeBuffer.getTraceHandler().enable();
      }

      // Encode

      try {
          signedName.encode (encodeBuffer);

          if (trace) {
              System.out.println ("Encoding was successful");
              System.out.println ("Hex dump of encoded record:");
              encodeBuffer.hexDump ();
              System.out.println ("Binary dump:");
              encodeBuffer.binDump ("signedName");
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
