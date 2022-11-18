package sample_der.PKCS_1;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.util.*;

public class Writer {

   public static void main(String args[]) {

      String filename = new String ("message.dat");
      boolean trace = true;
      
      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v"))
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o"))
               filename = new String (args[++i]);
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println("usage: Writer [-v] [-o <filename>]");
               System.out.println("   -v  verbose mode: print trace info");
               System.out.println("   -o <filename>  " +
                                          "write encoded msg to <filename>");
               System.out.println("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }
      
      // Create a message buffer object
      Asn1DerEncodeBuffer encodeBuffer = new Asn1DerEncodeBuffer ();

      try {
         DigestInfo digestInfo;
         digestInfo = new DigestInfo();

         digestInfo.digestAlgorithm = new DigestAlgorithm();
         digestInfo.digestAlgorithm.algorithm = new Asn1ObjectIdentifier(
               new int[] { 2, 16, 840, 1, 101, 3, 4, 2, 1 } );

         byte[] octData = {
            (byte)0x00, (byte)0x11, (byte)0x22, (byte)0x33, 
            (byte)0x44, (byte)0x55, (byte)0x66, (byte)0x77, 
            (byte)0x88, (byte)0x99, (byte)0xaa, (byte)0xbb, 
            (byte)0xcc, (byte)0xdd, (byte)0xee, (byte)0xff, 
            (byte)0x00, (byte)0x11, (byte)0x22, (byte)0x33, 
            (byte)0x44, (byte)0x55, (byte)0x66, (byte)0x77, 
            (byte)0x88, (byte)0x99, (byte)0xaa, (byte)0xbb, 
            (byte)0xcc, (byte)0xdd, (byte)0xee, (byte)0xff
         };
         digestInfo.digest = new Asn1OctetString(octData);

         // Encode
         digestInfo.encode (encodeBuffer);

         if (trace) {
            System.out.println("Encoding was successful");
            System.out.println("Hex dump of encoded record:");
            encodeBuffer.hexDump ();
            System.out.println("Binary dump:");
            encodeBuffer.binDump ();
            // Write the encoded record to a file
            encodeBuffer.write (new FileOutputStream (filename));
         }
      }
      catch (Exception e) {
         System.out.println(e.getMessage());
         e.printStackTrace();
         System.exit(1);
      }
   }
}
