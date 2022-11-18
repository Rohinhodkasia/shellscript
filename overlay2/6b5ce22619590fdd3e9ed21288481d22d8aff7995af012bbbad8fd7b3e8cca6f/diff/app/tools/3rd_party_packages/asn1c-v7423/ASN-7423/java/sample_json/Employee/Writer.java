
package sample_json.Employee;

import com.objsys.asn1j.runtime.*;
import java.util.*;

public class Writer {

   /* PDU: Employee.PersonnelRecord */
   public static void main(String args[]) {

      String filename = new String ("message.json");
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
      
      // Create an encoding stream
      Asn1JsonOutputStream encodeStream = null;
      try {
         encodeStream = new Asn1JsonOutputStream (new java.io.OutputStreamWriter( new java.io.FileOutputStream(filename), "UTF-8") );

         // Create a data object and populate it with the data to be encoded

         PersonnelRecord personnelRecord = new PersonnelRecord ();
         personnelRecord.name = new Name ("John", "P", "Smith");
         personnelRecord.name.extElem1 = new Asn1OpenExt();
         personnelRecord.name.extElem1.setOpenType(
            new Asn1OpenType( "\"nickname\":\"Smithy\"", Asn1OpenType.JSON ), 0);
         personnelRecord.name.extElem1.setOpenType(
            new Asn1OpenType( "\"salutation\":\"Mr.\"", Asn1OpenType.JSON ), 1);
         personnelRecord.title = new Asn1IA5String ("Director");
         personnelRecord.number = new EmployeeNumber (51);
         personnelRecord.dateOfHire = new Date ("19710917");
         personnelRecord.nameOfSpouse = new Name ("Mary", "T", "Smith");
         personnelRecord.children = new _SeqOfChildInformation (2);
         personnelRecord.children.elements[0] =
             new ChildInformation (new Name ("Ralph", "T", "Smith"), "19571111");
         personnelRecord.children.elements[1] =
             new ChildInformation (new Name ("Susan", "B", "Jones"), "19590717");

         personnelRecord.encode (encodeStream);
         if (trace) {
            System.out.println("Encoding was successful");
         }
      }
      catch (Exception e) {
         System.out.println(e.getMessage());
         e.printStackTrace();
         System.exit(1);
      }
      finally {
         try {
            if (encodeStream != null) encodeStream.close ();
         }
         catch (Exception e) {
         }
      }
   }
}
