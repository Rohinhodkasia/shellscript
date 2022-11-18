package sample_der.PKCS15TokenInfo;

import com.objsys.asn1j.runtime.*;
import java.io.*;

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

      _SeqOfAlgorithmInfo algoInfo = new _SeqOfAlgorithmInfo (4);

      int[] algOID0 = { 1, 3, 14, 3, 2, 26 } ;
      byte[] encodedNULL = { 5, 0 };
      algoInfo.elements[0] = new AlgorithmInfo ();
      algoInfo.elements[0].reference = new Reference (1);
      algoInfo.elements[0].algorithm = new Asn1Integer (1); 
      algoInfo.elements[0].parameters = new Asn1OpenType(encodedNULL);
      algoInfo.elements[0].supportedOperations = new Operations ();
      algoInfo.elements[0].supportedOperations.set (Operations.hash, true);
      algoInfo.elements[0].algId = new Asn1ObjectIdentifier (algOID0);

      int[] algOID1 = { 1, 3, 36, 3, 4, 3, 2, 1 } ;
      algoInfo.elements[1] = new AlgorithmInfo ();
      algoInfo.elements[1].reference = new Reference (2);
      algoInfo.elements[1].algorithm = new Asn1Integer (2); 
      algoInfo.elements[1].parameters = new Asn1OpenType(encodedNULL);
      algoInfo.elements[1].supportedOperations = new Operations ();
      algoInfo.elements[1].supportedOperations.set 
          (Operations.compute_signature, true);
      algoInfo.elements[1].algId = new Asn1ObjectIdentifier (algOID1);

      int[] algOID2 = { 1, 0, 0 } ;
      algoInfo.elements[2] = new AlgorithmInfo ();
      algoInfo.elements[2].reference = new Reference (3);
      algoInfo.elements[2].algorithm = new Asn1Integer (3); 
      algoInfo.elements[2].parameters = new Asn1OpenType (encodedNULL);
      algoInfo.elements[2].supportedOperations = new Operations ();
      algoInfo.elements[2].supportedOperations.set 
          (Operations.compute_checksum, true);
      algoInfo.elements[2].supportedOperations.set 
          (Operations.verify_checksum, true);
      algoInfo.elements[2].algId = new Asn1ObjectIdentifier (algOID2);

      int[] algOID3 = { 1, 2, 840, 113549, 3, 7 } ;
      byte[] params3 = { 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 };
      algoInfo.elements[3] = new AlgorithmInfo ();
      algoInfo.elements[3].reference = new Reference (4);
      algoInfo.elements[3].algorithm = new Asn1Integer (4); 
      algoInfo.elements[3].parameters = new Asn1OpenType (params3);
      algoInfo.elements[3].supportedOperations = new Operations ();
      algoInfo.elements[3].supportedOperations.set 
          (Operations.encipher, true);
      algoInfo.elements[3].supportedOperations.set 
          (Operations.decipher, true);
      algoInfo.elements[3].algId = new Asn1ObjectIdentifier (algOID3);

      // TokenInfo

      TokenInfo tokenInfo = new TokenInfo ();
      tokenInfo.version = new TokenInfo_version (TokenInfo_version.v1);
      try {
          tokenInfo.serialNumber = 
              new Asn1OctetString ("'159752222515401240'H");
      }
      catch (Asn1ValueParseException vpe) {
          System.out.println ("unable to parse serial number value");
          return;
      }
      tokenInfo.manufacturerID = new Label ("XY, Inc.");
      tokenInfo.label = new Label ("Digital signature card");
      tokenInfo.tokenflags = new TokenFlags ();
      tokenInfo.tokenflags.set (TokenFlags.prnGeneration, true);
      tokenInfo.seInfo = new _SeqOfSecurityEnvironmentInfo (1);
      int[] oid = { 1, 0, 0 };
      tokenInfo.seInfo.elements[0] = new SecurityEnvironmentInfo (1, oid);
      tokenInfo.supportedAlgorithms = algoInfo;
      tokenInfo.issuerId = new Label ("wxy");
      tokenInfo.holderId = new Label ("vwx");

      // Create a message buffer object and encode the record

      Asn1DerEncodeBuffer encodeBuffer = new Asn1DerEncodeBuffer();

      try {
          tokenInfo.encode (encodeBuffer, true);

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


