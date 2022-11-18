package sample_ber.ToXML;

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

      PersonnelRecord personnelRecord = new PersonnelRecord ();
      personnelRecord.name = new Name ("John", "P", "Smith");
      personnelRecord.title = new Asn1IA5String ("Director");
      personnelRecord.number = new EmployeeNumber (51);
      personnelRecord.dateOfHire = new Date ("19710917");
      personnelRecord.nameOfSpouse = new Name ("Mary", "T", "Smith");
      personnelRecord.children = new _SeqOfChildInformation (2);
      personnelRecord.children.elements[0] =
          new ChildInformation (new Name ("Ralph", "T", "Smith"), "19571111");
      personnelRecord.children.elements[1] =
          new ChildInformation (new Name ("Susan", "B", "Jones"), "19590717");

      // Create a message buffer object and encode the record

      Asn1BerEncodeBuffer encodeBuffer = new Asn1BerEncodeBuffer();

      try {
          personnelRecord.encode (encodeBuffer, true);

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
