/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.6.A, Date: 20-Sep-2012.
 */
package sample_json.ExtChoice;

import com.objsys.asn1j.runtime.*;
import java.util.*;

public class Writer {

   /* PDU: ExtChoice.AliasAddressList */
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
         AliasAddressList aliasAddressList = new AliasAddressList (10);

         for (int tvalue = 1; tvalue <= aliasAddressList.elements.length; tvalue ++) {
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
                  new Asn1OpenType ("\"extension\":\"This is an extension element.\"",
                     Asn1OpenType.JSON) );
               break;
            default:
               System.out.println ("invalid element number " + tvalue);
               return;
            }
            aliasAddressList.elements[tvalue - 1] = aliasAddress;
         }

         aliasAddressList.encode (encodeStream);
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
