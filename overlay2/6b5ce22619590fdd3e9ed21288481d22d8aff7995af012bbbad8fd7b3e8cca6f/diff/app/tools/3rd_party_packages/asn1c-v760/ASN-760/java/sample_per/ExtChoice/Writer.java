package sample_per.ExtChoice;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.dat");
      boolean aligned = true, trace = true;
      int tvalue = 2;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v")) 
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o")) 
               filename = new String (args[++i]);
            else if (args[i].equals ("-a")) 
               aligned = true;
            else if (args[i].equals ("-u")) 
               aligned = false;
            else if (args[i].equals ("-t")) 
               tvalue = Integer.parseInt (args[++i]);
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println ("usage: Writer [ -a | -u ] [ -v ] " +
                                   "[ -o <filename>");
               System.out.println ("   -a  PER aligned encoding (default)");
               System.out.println ("   -u  PER unaligned encoding");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                   "write encoded msg to <filename>");
               System.out.println ("   -t <option>  select option number");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }

      // Create a data object and populate it with the data to be encoded

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
      default:
         System.out.println ("invalid element number " + tvalue);
         return;
      }

      if (trace) {
         System.out.println ("The following record will be encoded:");
         aliasAddress.print (System.out, "aliasAddress", 0);
         System.out.println ("");
      }

      // Create a message buffer object 

      Asn1PerEncodeBuffer encodeBuffer = new Asn1PerEncodeBuffer (aligned);

      // Enable bit field tracing

      if (trace) {
         encodeBuffer.getTraceHandler().enable();
      }

      // Encode

      try {
          aliasAddress.encode (encodeBuffer);

          if (trace) {
              System.out.println ("Encoding was successful");
              System.out.println ("Hex dump of encoded record:");
              encodeBuffer.hexDump ();
              System.out.println ("Binary dump:");
              encodeBuffer.binDump ("aliasAddress");
          }

          // Write the encoded record to a file

          encodeBuffer.write (new FileOutputStream (filename));

          // Generate a dump file for comparisons

          String fileSuffix = (aligned) ? "a" : "u";
          encodeBuffer.hexDump 
              (new PrintStream (new FileOutputStream 
                 ("message_" + fileSuffix + ".dmp")));
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }
}
