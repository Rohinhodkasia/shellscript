package sample_ber.TcapInvoke;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import sample_ber.AIN.*;
import sample_ber.TCAP.*;

public class Writer {
   public static void main (String args[]) {
       String filename = new String ("message.dat");
       boolean trace = true;

       // Process command line arguments

       if (args.length > 0) {
           for (int i = 0; i < args.length; i++) {
               if (args[i].equals ("-v")) 
                   Diag.instance().setEnabled (true);
               else if (args[i].equals ("-o")) 
                   filename = new String (args[++i]);
               else if (args[i].equals ("-notrace")) trace = false;
               else {
                   System.out.println ("usage: Writer [ -v ] [ -o <filename>");
                   System.out.println ("   -v  verbose mode: print trace info");
                   System.out.println ("   -o <filename>  " +
                                       "write encoded msg to <filename>");
                   System.out.println ("   -notrace  do not display trace info");
                   return;
               }
           }
       }

       // Create a data object and populate it with the data to be encoded

       CallInfoFromResource_ARGUMENT param = 
           new CallInfoFromResource_ARGUMENT();

       // IPReturnBlock

       byte[] ipData = new byte [120];
       for (int i = 0; i < 120; i++) {
           ipData[i] = (byte) i;
       }
       param.iPReturnBlock = new IPReturnBlock (ipData);

       // Amp1

       byte[] amp1Data = new byte [6];
       for (int i = 0; i < 6; i++) {
           amp1Data[i] = (byte) i;
       }
       param.amp1 = new Amp1 (amp1Data);

       // Amp2

       try {
           param.amp2 = new Amp2 ();
           param.amp2.ampAINNodeID = new AmpAINNodeID ();
           param.amp2.ampAINNodeID.set_spcID (new SpcID("'123'"));
           param.amp2.ampCLogSeqNo = new AmpCLogSeqNo (12345);
           param.amp2.ampCLogRepInd = AmpCLogRepInd.requestReport();
           param.amp2.ampCallProgInd = 
            AmpCallProgInd.callProgressVoiceAnnouncements();
           param.amp2.ampTestReqInd = new AmpTestReqInd (111);
           param.amp2.ampCLogName = new AmpCLogName ("'TestUser'");
       }
       catch (Asn1ValueParseException e) {
           System.out.println (e.getMessage());
           e.printStackTrace();           
           return;
       }

       // Encode argument

      Asn1BerEncodeBuffer encodeBuffer = new Asn1BerEncodeBuffer();

      try {
          param.encode (encodeBuffer, true);

          if (trace) {
              System.out.println ("Encoding was successful");
              System.out.println ("Hex dump of encoded record:");
              encodeBuffer.hexDump ();
              System.out.println ("Binary dump:");
              encodeBuffer.binDump ();
              System.out.println ("---");
          }
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          return;
      }

      // Create a TCAP Invoke PDU object to wrap the encoded argument. 
      // Note the optimization with the open type.  By constructing the 
      // object using only the length, a copy of the already-encoded 
      // message component is avoided..

      Asn1OpenType openType = new Asn1OpenType (encodeBuffer.getMsgLength());

      Invoke invoke = new Invoke ();
      invoke.invokeID = new InvokeIdType (1);
      invoke.operationCode = 
          new Asn1Integer (_AIN_OperationValues.callInfoFromResource);
      invoke.parameter = openType;

      Undirectional undirectional = new Undirectional ();
      undirectional.components = new ComponentPortion (1);
      undirectional.components.elements[0] = new Component ();
      undirectional.components.elements[0].set_invoke (invoke);

      MessageType messageType = new MessageType ();
      messageType.set_undirectional (undirectional);

      // Encode TCAP header

      try {
         messageType.encode (encodeBuffer, true);

         if (trace) {
            System.out.println ("Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            encodeBuffer.hexDump ();
            System.out.println ("Binary dump:");
            encodeBuffer.binDump ();
         }

         // Write the encoded record to a file

         encodeBuffer.write (new FileOutputStream (filename));

         // Generate a dump file for comparisons

         encodeBuffer.hexDump 
            (new PrintStream (new FileOutputStream ("message.dmp")));
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();           
         return;
      }
   }
}


