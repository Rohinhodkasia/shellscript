package sample_oer.Employee;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.dat");
      boolean trace = true;
      int itercnt = 1;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
                Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o")) 
                filename = new String (args[++i]);
            else if (args[i].equals ("-iter")) 
                itercnt = Integer.parseInt (args[++i]);
            else if (args[i].equals ("-trace")) trace = true;
            else {
                System.out.println ("usage: Writer [ -v ] [ -o <filename>");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -o <filename>  " +
                                    "write encoded msg to <filename>");
                System.out.println ("   -iter <count>  set iteration count\n");
                System.out.println ("   -trace  display trace info");
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

      try {
         personnelRecord.print(System.out, "personnelRecord", 0);
         System.out.println();

         Asn1OerEncodeBuffer encodeBuffer = new Asn1OerEncodeBuffer();

         personnelRecord.encode (encodeBuffer);
      
         if (trace) {
            System.out.println ("Encoding NON-CANONICAL was successful");
            System.out.println ("Hex dump of encoded NON-CANONICAL record:");
            encodeBuffer.hexDump ();
         }
  
         // Write the encoded record to a file
         encodeBuffer.write (new FileOutputStream (filename));

         //Now encode it in canonical mode
         encodeBuffer.reset();
         encodeBuffer.setCanonicalMode(true);
         personnelRecord.encode(encodeBuffer);         

         if (trace) {
             System.out.println ("Encoding CANONICAL was successful");
             System.out.println ("Hex dump of encoded CANONICAL record:");
             encodeBuffer.hexDump ();
         }

         // Write the encoded record to a file

         encodeBuffer.write (new FileOutputStream (filename + ".canonical"));
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();           
         System.exit(-1);
      }
   }
}
