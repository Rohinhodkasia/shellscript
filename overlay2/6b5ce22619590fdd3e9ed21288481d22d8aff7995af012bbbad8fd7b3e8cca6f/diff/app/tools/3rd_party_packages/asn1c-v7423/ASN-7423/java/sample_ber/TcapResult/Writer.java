package sample_ber.TcapResult;

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

       CallInfoFromResource_RESULT result = 
           new CallInfoFromResource_RESULT ();

       // Resource type

       result.resourceType = new ResourceType (123);

       // StrParameterBlock

       byte[] flexData = new byte [120];
       for (int i = 0; i < 120; i++) {
           flexData[i] = (byte) i;
       }
       FlexParameterBlock flexParamBlock = 
           new FlexParameterBlock (flexData);

       result.strParameterBlock = new StrParameterBlock ();
       result.strParameterBlock.set_flexParameterBlock (flexParamBlock);

       // Amp1

       byte[] amp1Data = new byte [6];
       for (int i = 0; i < 6; i++) {
           amp1Data[i] = (byte) i;
       }
       result.amp1 = new Amp1 (amp1Data);

       // Amp2

       try {
           result.amp2 = new Amp2 ();
           result.amp2.ampAINNodeID = new AmpAINNodeID ();
           result.amp2.ampAINNodeID.set_spcID (new SpcID ("'123'"));
           result.amp2.ampCLogSeqNo = new AmpCLogSeqNo (12345);
           result.amp2.ampCLogRepInd = AmpCLogRepInd.requestReport();
           result.amp2.ampCallProgInd =
               AmpCallProgInd.callProgressVoiceAnnouncements();
           result.amp2.ampTestReqInd = new AmpTestReqInd (111);
           result.amp2.ampCLogName = new AmpCLogName ("'TestUser'");
       }
       catch (Asn1ValueParseException e) {
           System.out.println (e.getMessage());
           e.printStackTrace();           
           System.exit(-1);
       }

       // ServiceProviderID

       result.serviceProviderID = new ServiceProviderID ();
       result.serviceProviderID.set_ocn (new Ocn ("TestOCN"));

       // Service context

       result.serviceContext = new ServiceContext (4321);

       // Encode result

      Asn1BerEncodeBuffer encodeBuffer = new Asn1BerEncodeBuffer();

      try {
          result.encode (encodeBuffer, true);

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
          System.exit(-1);
      }

      // Create a TCAP Result PDU object to wrap the encoded argument. 
      // Note the optimization with the open type.  By constructing the 
      // object using only the length, a copy of the already-encoded 
      // message component is avoided..

      Asn1OpenType openType = new Asn1OpenType (encodeBuffer.getMsgLength());

      ReturnResult_result resultBody = new ReturnResult_result 
          (_AIN_OperationValues.callInfoFromResource, openType);

      ReturnResult resultPDU = new ReturnResult (1, resultBody);
      Undirectional undirectional = new Undirectional ();
      undirectional.components = new ComponentPortion (1);
      undirectional.components.elements[0] = new Component ();
      undirectional.components.elements[0].set_returnResultLast (resultPDU);

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
          System.exit(-1);
      }
   }
}
