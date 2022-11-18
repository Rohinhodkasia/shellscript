package sample_ber.ErrorHandler;

import com.objsys.asn1j.runtime.*;
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
      Asn1BerEncodeBuffer encodeBuffer =
         new Asn1BerEncodeBuffer ();
      try {
         sample_ber.ErrorHandler.WRITE.PDU pdu;
         pdu = new sample_ber.ErrorHandler.WRITE.PDU();

         pdu.a = new Asn1Integer(0);
         pdu.z = new Asn1Integer(99);
         pdu.b = new Asn1Integer(1);
         pdu.extras = new sample_ber.ErrorHandler.WRITE.Extras();
         pdu.extras.a = new Asn1Integer(0);
         pdu.extras.b = new Asn1Integer(1);
         pdu.extras.c = new Asn1Integer(2);
         pdu.extras.d = new Asn1Integer(3);
         pdu.extras.e = new Asn1Integer(4);
         pdu.allreq = new sample_ber.ErrorHandler.WRITE.AllReq();
         pdu.allreq.a = new Asn1Integer(0);
         pdu.allreq.b = new Asn1Integer(1);
         pdu.allreq.c = new Asn1Integer(2);
         pdu.allreq.d = new Asn1Integer(3);
         pdu.myset = new sample_ber.ErrorHandler.WRITE.MySet();
         pdu.myset.a = new Asn1Integer(0);
         pdu.myset.b = new Asn1Integer(1);
         pdu.myset.c = new Asn1Integer(2);
         pdu.color = sample_ber.ErrorHandler.WRITE.Color.black();
         pdu.mychoice = new sample_ber.ErrorHandler.WRITE.MyChoice();
         pdu.mychoice.set_c( new Asn1Integer(5) );
         pdu.z = new Asn1Integer(99);
         pdu.encode (encodeBuffer);
         if (trace) {
            System.out.println("Encoding was successful");
            System.out.println("Hex dump of encoded record:");
            encodeBuffer.hexDump ();
            System.out.println("Binary dump:");
            encodeBuffer.binDump ();
            // Write the encoded record to a file
            encodeBuffer.write (new java.io.FileOutputStream (filename));
         }
      }
      catch (java.lang.Exception e) {
         System.out.println(e.getMessage());
         e.printStackTrace();
         System.exit(1);
      }
      finally {
         Asn1Util.closeRuntime();
      }
   }
}
