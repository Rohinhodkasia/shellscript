package sample_ber.EmployeeSocketStream;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.net.*;
import java.lang.Thread;

public class Writer {
   public static void main (String args[]) {
       String ipAddress = "127.0.0.1";
       int port = 9000;
       boolean trace = true;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o")) {
               String param = new String (args[++i]);
               ipAddress = new String (param);
               int pi = ipAddress.indexOf (':');
               if (pi != -1)
                  ipAddress = ipAddress.substring (0, pi);
               String portStr = param.substring (pi + 1);
               try {
                  port = Integer.parseInt (portStr);
               }
               catch (Exception x) {
                  System.out.println ("Invalid port value");
                  return;
               }
            }
            else if (args[i].equals ("-notrace")) trace = false;
            else {
                System.out.println ("usage: Writer [ -v ] [ -o <ip-address:port> ]");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -o <ip-address:port>  send encoded " +
                   "msg to <ip-address:port>");
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
          new ChildInformation (new Name ("Susan", "Jones"), "19590717");

      Asn1BerOutputStream out = null;
      try {
         // wait a second to make sure that the server is up; this is a
         // concession to Ant's spawn property, which doesn't let us give
         // a wait timeout
         Thread.sleep(1000);

         Socket socket = new Socket (ipAddress, port, null, 0);
         
         // Create a message buffer object and encode the record

         out = new Asn1BerOutputStream (socket.getOutputStream ());

         personnelRecord.encode (out, true);

         if (trace) {
             System.out.println ("Encoding was successful");
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();           
         System.exit(-1);
      }
      finally {
         try {
            if (out != null) 
               out.close ();
          }
          catch (Exception e) {System.exit(-1);}
      }
   }
}
