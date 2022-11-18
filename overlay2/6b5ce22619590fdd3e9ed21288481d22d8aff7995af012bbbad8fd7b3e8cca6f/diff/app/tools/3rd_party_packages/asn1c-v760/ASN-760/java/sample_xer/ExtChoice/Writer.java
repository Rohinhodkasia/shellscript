package sample_xer.ExtChoice;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.xml");
      int tvalue = 2;
      boolean cxer = false, trace = true;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o")) 
               filename = new String (args[++i]);
            else if (args[i].equals ("-cxer")) 
               cxer = true;
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println ("usage: Writer [ -cxer ] [ -v ] " +
                                   "[ -o <filename>");
               System.out.println ("   -cxer  Use Canonical XER");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                   "write encoded msg to <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }

      // Create a data object and populate it with the data to be encoded
      AliasAddressList aliasAddressList = new AliasAddressList (10);

      for (tvalue = 1; tvalue <= aliasAddressList.elements.length; tvalue ++) {
         AliasAddress aliasAddress = new AliasAddress ();

         switch (tvalue) {
         case 1:
            aliasAddress.set_e164 (new Asn1IA5String ("#111,222"));
            break;
         case 2:
            aliasAddress.set_h323_ID (new Asn1BMPString ("TESTSTRING"));
            break;
         case 3:
            aliasAddress.set_aNull ();
            break;
         case 4:
            aliasAddress.set_url_ID 
               (new Asn1IA5String ("http://www.obj-sys.com"));
            break;
         case 5:
            aliasAddress.set_transportID 
               (new AliasAddress_transportID ("Truck", 111));
            break;
         case 6:
            aliasAddress.set_email_ID 
               (new Asn1IA5String ("objective@obj-sys.com"));
            break;
         case 7:
            aliasAddress.set_partyNumber (new PartyNumber (555));
            break;
         case 8:
            aliasAddress.set_boolVal (new Asn1Boolean (true));
            break;
         case 9:
            aliasAddress.set_enumVal (EnumVal.two());
            break;
         case 10:
            aliasAddress.setElement (AliasAddress._EXTELEM1, 
               new Asn1XerOpenType (new String ("<extension>This is an extension element.</extension>").getBytes ()));
            break;
         default:
            System.out.println ("invalid element number " + tvalue);
            return;
         }
         aliasAddressList.elements[tvalue - 1] = aliasAddress;
      }
      if (trace) {
         System.out.println ("The following record will be encoded:");
         aliasAddressList.print (System.out, "aliasAddressList", 0);
         System.out.println ("");
      }

      // Create a message buffer object 
      try {
         Asn1XerEncodeBuffer encodeBuffer = new Asn1XerEncodeBuffer (cxer, 0);
   
         encodeBuffer.encodeStartDocument ();

         aliasAddressList.encode (encodeBuffer, null);

         encodeBuffer.encodeEndDocument ();

         if (trace) {
            System.out.println ("Encoding was successful");
            encodeBuffer.write (System.out);
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
