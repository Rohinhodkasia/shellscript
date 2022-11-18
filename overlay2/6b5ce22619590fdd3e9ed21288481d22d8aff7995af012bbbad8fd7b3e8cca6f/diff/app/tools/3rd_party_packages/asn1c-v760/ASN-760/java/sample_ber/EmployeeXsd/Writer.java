package sample_ber.EmployeeXsd;

import com.objsys.asn1j.runtime.*;
import java.io.*;
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
               System.out.println ("usage: Writer [ -v ] [ -o <filename> ]");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                          "write encoded msg to <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }
      
      // Create a message buffer object
      Asn1BerEncodeBuffer encodeBuffer = new Asn1BerEncodeBuffer ();
      try {
         PersonnelRecord personnelRecord;
         personnelRecord = new PersonnelRecord();

         personnelRecord.name = new Name();

         personnelRecord.name.givenName = new Asn1UTF8String("John");
         personnelRecord.name.initial = new Asn1UTF8String("P");
         personnelRecord.name.familyName = new Asn1UTF8String("Smith");
         personnelRecord.number = new EmployeeNumber(51);
         personnelRecord.title = new Asn1UTF8String("Director");
         personnelRecord.dateOfHire = new Date("19710917");

         personnelRecord.nameOfSpouse = new Name();
         personnelRecord.nameOfSpouse.givenName = new Asn1UTF8String("Mary");
         personnelRecord.nameOfSpouse.initial = new Asn1UTF8String("T");
         personnelRecord.nameOfSpouse.familyName = new Asn1UTF8String("Smith");

         personnelRecord.children= new ChildInformation[2];

         personnelRecord.children[0] = new ChildInformation();
         personnelRecord.children[0].name = new Name();
         personnelRecord.children[0].name.givenName =
            new Asn1UTF8String("Ralph");
         personnelRecord.children[0].name.initial =
            new Asn1UTF8String("T");
         personnelRecord.children[0].name.familyName =
            new Asn1UTF8String("Smith");
         personnelRecord.children[0].dateOfBirth =
            new Date("19571111");

         personnelRecord.children[1] = new ChildInformation();
         personnelRecord.children[1].name = new Name();
         personnelRecord.children[1].name.givenName = 
            new Asn1UTF8String("Susan");
         personnelRecord.children[1].name.initial = 
            new Asn1UTF8String("B");
         personnelRecord.children[1].name.familyName = 
            new Asn1UTF8String("Jones");
         personnelRecord.children[1].dateOfBirth = 
            new Date("19590717");

         personnelRecord.encode (encodeBuffer);
         if (trace) {
            System.out.println ("Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            encodeBuffer.hexDump ();
            System.out.println ("Binary dump:");
            encodeBuffer.binDump ();
         }
         // Write the encoded record to a file
         encodeBuffer.write (new FileOutputStream (filename));
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();
         System.exit(-1);
      }
   }
}
