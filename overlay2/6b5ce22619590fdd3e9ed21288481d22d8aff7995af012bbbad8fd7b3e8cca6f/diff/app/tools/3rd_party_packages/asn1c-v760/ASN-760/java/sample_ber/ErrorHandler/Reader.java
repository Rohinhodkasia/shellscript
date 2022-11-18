package sample_ber.ErrorHandler;

import com.objsys.asn1j.runtime.*;
import java.util.*;

public class Reader {

   public static class Handler implements Asn1BerExceptionHandler
   {
   	public RuntimeException handleException(Asn1Exception e, 
                                       Asn1BerDecodeBuffer buffer)
      {
         try {
            if (e instanceof Asn1MissingRequiredException ||
               e instanceof Asn1InvalidEnumException) 
            {
               //ignore exception; no recovery action required
               System.out.println("IGNORED: " + e.getMessage());
               return null;
            }
            else if (e instanceof Asn1SeqOrderException ||
                     e instanceof Asn1UnexpectedElementException ||
                     e instanceof Asn1SetDuplicateException ||
                     e instanceof Asn1NotInSetException ||
                     e instanceof Asn1InvalidChoiceOptionException) 
            {
               //skip the offending element
               buffer.skipTLV();
               System.out.println("IGNORED: " + e.getMessage());
               return null;
            }
         }
         catch (java.io.IOException ignored) {
            //ignore: recovery failed
         }
         
         return e;
      }                                    
   }
   
   
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
      sample_ber.ErrorHandler.READ.PDU value = null;
      try {
         // Create an input file stream object
         java.io.FileInputStream ins = new java.io.FileInputStream (filename);

         // Create a decode buffer object
         Asn1BerDecodeBuffer decodeBuffer = 
            new Asn1BerDecodeBuffer (ins);
            
         decodeBuffer.setExceptionHandler(new Handler());
         
         // Read and decode the message
         value = new sample_ber.ErrorHandler.READ.PDU ();
         value.decode (decodeBuffer);
      }
      catch (java.lang.Exception e) {
         exception = e;
      }
      if (trace) {
         if ( exception == null ) System.out.println("Decode was successful");
         else System.out.println("Decode failed");
         if ( value != null )  {
            value.print (System.out, exception == null ? "value" : "partial value", 0);
         }
      }

      Asn1Util.closeRuntime();

      if ( exception != null ) {
         System.out.println (exception.getMessage());
         exception.printStackTrace();
         System.exit(1);
      }
   }
}
