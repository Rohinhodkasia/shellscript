// This sample decodes a file with TS 32.297 headers and CDRs.

package sample_ber.TS32297;

import com.objsys.asn1j.runtime.*;
import java.util.*;
import sample_ber.TS32297.IPBinaryAddress;
import sample_ber.TS32297.IPTextRepresentedAddress;
import sample_ber.TS32297.TimeStamp;
import sample_ber.TS32297._SeqOfSDP_Media_Component;
import sample_ber.TS32297.Media_Components_List_Centrex_sDP_Session_Description;
import sample_ber.TS32297.SDP_Type;
import sample_ber.TS32297.Media_Components_List_sDP_Session_Description;
import sample_ber.TS32297.InvolvedParty;

public class Reader {

   public static void main (String args[])
   {
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
               System.out.println("usage: Reader [ -v ] [ -i <filename>");
               System.out.println("   -v  verbose mode: print trace info");
               System.out.println("   -i <filename>  " +
                                   "read encoded msg from <filename>");
               System.out.println("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }

      java.lang.Exception exception = null;
      IMSRecord value = new IMSRecord();
      TS32297FileHeader fileHeader = new TS32297FileHeader();
      TS32297CDRHeader cdrHeader = new TS32297CDRHeader();
      try {
         // Create an input file stream object
         java.io.FileInputStream ins = new java.io.FileInputStream (filename);

         // Create a decode buffer object
         Asn1BerDecodeBuffer decodeBuffer = 
            new Asn1BerDecodeBuffer (ins);
         
         // Decode TS 32.297 file header
         fileHeader.decode(decodeBuffer);
         if (trace) fileHeader.print();
         
         for (int i = 1; i <= fileHeader.mCDRCount; i++) {
            // Decode TS 32.297 record header
            cdrHeader.decode(decodeBuffer);
            if (trace) cdrHeader.print();
            
            // Read and decode the CDR.
            value.decode (decodeBuffer);
            value.print(System.out, "IMSRecord", 0);
            
            cdrHeader = new TS32297CDRHeader();
            value = new IMSRecord();
         }
      }
      catch (java.lang.Exception e) {
         exception = e;
      }
      Asn1Util.closeRuntime();

      if ( exception != null ) {
         System.out.println (exception.getMessage());
         exception.printStackTrace();
         System.exit(1);
      }
   }
}
