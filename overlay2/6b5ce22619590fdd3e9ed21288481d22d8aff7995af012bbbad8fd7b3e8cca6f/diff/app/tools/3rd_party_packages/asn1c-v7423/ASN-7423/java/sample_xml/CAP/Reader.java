package sample_xml.CAP;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.util.*;
import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

public class Reader {

   public static void main (String args[]) {
      String filename = new String ("message.xml");
      String vendorParserClass =  "org.apache.xerces.parsers.SAXParser";
      boolean trace = true;
      // Process command line arguments
      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v"))
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-i")) 
               filename = new String (args[++i]);
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println ("usage: Reader [ -v ] [ -i <filename>");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -i <filename>  " +
                                   "read encoded msg from <filename>");
               System.out.println ("   -notrace  do not display trace info");
               System.exit(1);
            }
         }
      }

      java.io.InputStream inputFile = null;

      try {
         // Create an XML reader object
         inputFile = new java.io.BufferedInputStream(
                        new java.io.FileInputStream(filename) );

         org.xmlpull.v1.XmlPullParserFactory xmlInputFactory =
            org.xmlpull.v1.XmlPullParserFactory.newInstance();

         
         org.xmlpull.v1.XmlPullParser reader =
            xmlInputFactory.newPullParser();

         reader.setFeature(
            org.xmlpull.v1.XmlPullParser.FEATURE_PROCESS_NAMESPACES, true);

         reader.setInput(inputFile, null);         // Read and decode the message
         Alert value = new Alert ();
         value.decodeDocument (reader);
         if (trace) {
            System.out.println ("Decode was successful");
            value.print (System.out, "value", 0);
         }
      }
      catch (Exception e) {
         System.out.println (e.getMessage());
         e.printStackTrace();
         System.exit(-1);
      }
   }
}
