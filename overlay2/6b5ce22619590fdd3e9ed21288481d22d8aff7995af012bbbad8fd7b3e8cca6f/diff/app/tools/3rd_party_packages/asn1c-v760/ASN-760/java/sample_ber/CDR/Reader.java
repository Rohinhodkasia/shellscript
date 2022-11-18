/* This sample illustrate decoding BER-encoded IMSRecords from a 3GPP 32.297 CDR
   file.  Each record is encoded to a JSON file and printed to standard output.
*/

package sample_ber.CDR;

import com.objsys.asn1j.runtime.*;
import java.util.*;
import sample_ber.CDR.IMSRecord;

public class Reader {

   public static void main (String args[])
   {
      String filename = new String ("message.dat");
      String jsonFilename = new String ("message.json");
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
               System.out.println("usage: Reader [ -v ] [ -i <filename>");
               System.out.println("   -v  verbose mode: print trace info");
               System.out.println("   -i <filename>  " +
                                   "read encoded msg from <filename>");
               System.out.println("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }

      Asn1JsonOutputStream encodeStream = null;
      Exception exception = null;
      IMSRecord value = null;
      try {
         // Create an input file stream object
         java.io.FileInputStream ins = new java.io.FileInputStream (filename);

         // Create a decode buffer object
         Asn1BerDecodeBuffer decodeBuffer = 
            new Asn1BerDecodeBuffer (ins);
            
         // Create JSON outputstream to file
         encodeStream = new Asn1JsonOutputStream (
            new java.io.OutputStreamWriter( 
               new java.io.FileOutputStream(jsonFilename), "UTF-8") );            
            
         // Read CDR file header
         decodeBuffer.read4Bytes();   //file length
         int headerLen = decodeBuffer.read4Bytes();
         decodeBuffer.skip(10);  //identifiers & timestamps
         int numRecs = decodeBuffer.read4Bytes();
         
         // Skip ahead to first CDR; we already read 22 bytes above
         decodeBuffer.skip(headerLen - 22);
         
         for(int i = 0; i < numRecs; i++) {
         
            // Read CDR header
            decodeBuffer.skip(2);      //CDR header length
            int releaseAndVersion = decodeBuffer.readByte();
            
            if ( (releaseAndVersion & 0xE0) == 0x70 )
            {
               //CDR header is total of 5 octets
               decodeBuffer.skip(2);
            }
            else {
               //CDR header is total of 4 octets
               decodeBuffer.skip(1);
            }
                        
            // Read and decode the message
            value = new IMSRecord ();
            value.decode (decodeBuffer);
            
            value.encode(encodeStream);
            
            value.print (System.out, "CDR Record " + i, 0);
         }
            
      }
      catch (Exception e) {
         exception = e;
      }
      finally {
         if ( encodeStream != null ) 
            try { encodeStream.close(); } catch(Exception e) {}
      }

      Asn1Util.closeRuntime();

      if ( exception != null ) {
         System.out.println("Decode failed");
         System.out.println (exception.getMessage());
         exception.printStackTrace();
         System.exit(1);
      }
   }
}
