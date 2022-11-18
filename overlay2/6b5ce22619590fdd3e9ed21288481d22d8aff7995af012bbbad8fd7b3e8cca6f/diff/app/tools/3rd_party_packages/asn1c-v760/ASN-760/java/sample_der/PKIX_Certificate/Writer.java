package sample_der.PKIX_Certificate;

import com.objsys.asn1j.runtime.*;

public class Writer {

   private static RDNSequence set_test_authority() {
      RDNSequence obj1 = new RDNSequence(3);
      RelativeDistinguishedName rdn1 = new RelativeDistinguishedName(1);
      rdn1.elements[0] = new RelativeDistinguishedName_element();
      RelativeDistinguishedName rdn2 = new RelativeDistinguishedName(1);
      rdn2.elements[0] = new RelativeDistinguishedName_element();
      RelativeDistinguishedName rdn3 = new RelativeDistinguishedName(1);
      rdn3.elements[0] = new RelativeDistinguishedName_element();

      rdn1.elements[0].setUsing_at_x520countryName
         (new _at_x520countryName_Type("CA"));

      _at_x520OrganizationName_Type orgName =
         new _at_x520OrganizationName_Type();
      orgName.set_printableString
         (new Asn1PrintableString("Bovine Ballistics, Inc"));
      rdn2.elements[0].setUsing_at_x520OrganizationName(orgName);
            
      X520CommonName commonName = new X520CommonName();
      commonName.set_printableString
         (new Asn1PrintableString("Test Security Authority"));
      rdn3.elements[0].setUsing_at_x520CommonName(commonName);
            
      obj1.elements[0] = rdn1;
      obj1.elements[1] = rdn2;
      obj1.elements[2] = rdn3;

      return obj1;
   }

   /* PDU: PKIX1Explicit-2009.Certificate */
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
         Certificate certificate = new Certificate();

         certificate.toBeSigned = new TBSCertificate();

         certificate.toBeSigned.version = new Version(2);

         certificate.toBeSigned.serialNumber =
            new CertificateSerialNumber
            ("160118841221132149945952828414366461591");

         certificate.toBeSigned.signature = new TBSCertificate_signature();
         certificate.toBeSigned.signature.algorithm =
            new Asn1ObjectIdentifier(_PKIXAlgs_2009Values.rsaEncryption);

         /* Populate open type with encoded string of type NULL */
         {
            byte[] openData = { (byte)0x05, (byte)0x00 };
            certificate.toBeSigned.signature.parameters =
               new Asn1OpenType(openData);
         }

         certificate.toBeSigned.issuer = new Name();
         certificate.toBeSigned.issuer.setElement
            (Name._RDNSEQUENCE, set_test_authority());

         certificate.toBeSigned.validity = new Validity();

         certificate.toBeSigned.validity.notBefore = new Time();
         certificate.toBeSigned.validity.notBefore.setElement
            (Time._UTCTIME, new Asn1UTCTime("970123050000Z"));

         certificate.toBeSigned.validity.notAfter = new Time();
         certificate.toBeSigned.validity.notAfter.setElement
            (Time._UTCTIME, new Asn1UTCTime("010123045959Z"));

         certificate.toBeSigned.subject = new Name();
         certificate.toBeSigned.subject.setElement
            (Name._RDNSEQUENCE, set_test_authority());

         certificate.toBeSigned.subjectPublicKeyInfo =
            new SubjectPublicKeyInfo();

         certificate.toBeSigned.subjectPublicKeyInfo.algorithm =
            new SubjectPublicKeyInfo_algorithm();

         certificate.toBeSigned.subjectPublicKeyInfo.algorithm.algorithm =
            new Asn1ObjectIdentifier(_PKIXAlgs_2009Values.rsaEncryption);

         /* Populate open type with encoded string of type NULL */
         {
            byte[] openData = { (byte)0x05, (byte)0x00 };
            certificate.toBeSigned.subjectPublicKeyInfo.algorithm.parameters =
               new Asn1OpenType(openData);
         }

         certificate.toBeSigned.subjectPublicKeyInfo.subjectPublicKey = new Asn1BitString
            ("'0011000010000001110010010000001010000001110000010000000011110010" +
             "1001001100110101011000101001111001011011010111110101001111001011" +
             "1100111100100111011011010110101000110000110110011001101111100111" +
             "1001001011010100011011101011001101010010001000000001101000100101" +
             "0101000011111011010011110110000110010010001010111010011110011110" +
             "1001110001100111110100101110110100011111010101001000100011000110" +
             "1100001010101110100000100111011011110001101111110100010011100001" +
             "0000011011100000101100101010110010010011001010000001000111011111" +
             "1111001111000010101100100110010100111010101101100111011110011110" +
             "0000011000001100010100001100100000011010001111100011001110100001" +
             "0011011101110011011100101010111001001000110010010100010100110110" +
             "1010011011110000110001110010111110110011111001100011001011000110" +
             "1110101111110111100011100010111101010110100100010011100000001101" +
             "0100110011001101000100000011000111111101110000111111100010000110" +
             "0011111010111101100000110010001010101101010010100110111001000100" +
             "0101100110101001100011000111010000100001011000110111011010110011" +
             "0000011100010001001110111001110000110000100000111111000001101000" +
             "0110000101111110100010111010001111111100000110110101111101011001" +
             "0110111000111000111010100110101101101010110110110111101111000100" +
             "0111011010111010010101011110001111011001110101010111101110101000" +
             "0000011011001011001000111100101000001111110101101000000111111010" +
             "1111000010110101011100001101011000000110101100110010111000100000" +
             "1011100011000000110010101010010110011001000010001110000011000110" +
             "0001101011011011010011011001010110111011100011010110000110010111" +
             "1110010000111111010101101110101010000011111011100111010100000010" +
             "00000011000000010000000000000001'B");

         certificate.toBeSigned.mV2ExtPresent = true;
         certificate.toBeSigned.issuerUniqueID = new UniqueIdentifier
            ("'0111100001110101110001000110000101110101010100010001000111010000" +
             "1001001001000011000010000000000000001001011110100010111010010111'B");

         certificate.toBeSigned.subjectUniqueID = new UniqueIdentifier
            ("'0111100001110101110001000110000101110101010100010001000111010000" +
             "1001001001000011000010000000000000001001011110100010111010010111'B");

         certificate.toBeSigned.mV3ExtPresent = true;
         certificate.toBeSigned.extensions = new TBSCertificate_extensions(1);

         certificate.toBeSigned.extensions.elements[0] =
            new TBSCertificate_extensions_element();

         certificate.toBeSigned.extensions.elements[0].
            setUsing_ext_BasicConstraints(new BasicConstraints(true, 255));

         certificate.toBeSigned.extensions.elements[0].critical =
            new Asn1Boolean(true);

         certificate.toBeSigned.extElem1= null;

         certificate.algorithm = new Certificate_algorithm();
         certificate.algorithm.algorithm = 
            new Asn1ObjectIdentifier(_PKIXAlgs_2009Values.rsaEncryption);

         /* Populate open type with encoded string of type NULL */
         {
            byte[] openData = { (byte)0x05, (byte)0x00 };
            certificate.algorithm.parameters =
               new Asn1OpenType(openData);
         }


         certificate.signature = new Asn1BitString
            ("'0011000010000001101101101011110101101100110010001111100111110110" +
             "1101100000110111101110111101010110011011100101001010001110100101" +
             "1100111101110100110010011010000111111110010011011001000010100000" +
             "1011010001101111010011100100001010101100000111011000010001101101" +
             "1110100110000111111110010101011000001000110110000101111011001011" +
             "1111000001110001101001111100100101010111001100101000101000110001" +
             "1000011011110101001101001010010111010010011010101100010010100000" +
             "1000000010001011110011101111001101111111100111001001011010110001" +
             "0011010001100110110001010100000100000011110110000110101101110110" +
             "1011100100110011010000010001011101101111101011100011111110111000" +
             "0100101010000011110010000001011011100101110011001001101001001011" +
             "0010101001010110100001101101100110010101110001101111001000111101" +
             "1110001010001111011001001000110011110001110111100110000101111111" +
             "1101111011001011100101010101000010000000110000110100101100001110" +
             "1111100001111111000111100100010111000110111111100100111100010110" +
             "1001100000100101001001000101100110011101100110101100110110110110" +
             "1110000011111101111111101001101100110111000001001011010001111011" +
             "0101100000111101010000011001010010011011000110111000100101100001" +
             "0001100001001011001111000111010111110000000101100100101111000110" +
             "1110000101000110110000100011101001110101110111100000100100001100" +
             "0011001010010010011001100111100110010000010011110001000111010111" +
             "1111101110111000101110110111110001000011110001011010100011001000" +
             "1011110111010111010000100101100101011010010101001100000010100010" +
             "1010100100111001101100101011010110011101011000110110010111011000'B");
         certificate.encode (encodeBuffer);
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
      catch (Exception e) {
         System.out.println(e.getMessage());
         e.printStackTrace();
         System.exit(1);
      }
   }
}
