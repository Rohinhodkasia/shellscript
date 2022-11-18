package sample_xml.PurchaseOrder;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.util.*;
import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;

public class Writer {

   public static void main (String args[]) {

      String filename = new String ("message.xml");
      boolean trace = true;
      
      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v"))
               Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o"))
               filename = new String (args[++i]);
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println 
                  ("usage: Writer [-v] [-o <filename>] [-notrace]");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                          "write encoded msg to <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }
      
      // Create a message buffer object
      Asn1XmlEncodeBuffer encodeBuffer = new Asn1XmlEncodeBuffer();

      try {
         // Populate purchase order object

         PurchaseOrder purchaseOrder = new PurchaseOrder ();
         purchaseOrder.orderDate = new XSD_Date ("2003-04-01");

         purchaseOrder.shipTo = new USAddress();
         purchaseOrder.shipTo.name = new Asn1UTF8String ("Joe Smith");
         purchaseOrder.shipTo.street = 
            new Asn1UTF8String ("1 Morning Light Rd");
         purchaseOrder.shipTo.city = new Asn1UTF8String ("Glenmoore");
         purchaseOrder.shipTo.state = new Asn1UTF8String ("PA");
         purchaseOrder.shipTo.zip = new Asn1Integer(19343);

         purchaseOrder.billTo = new USAddress();
         purchaseOrder.billTo.name = new Asn1UTF8String ("Bill Jones");
         purchaseOrder.billTo.street = 
            new Asn1UTF8String ("102 Pickering Way, Suite 506");
         purchaseOrder.billTo.city = new Asn1UTF8String ("Exton");
         purchaseOrder.billTo.state = new Asn1UTF8String ("PA");
         purchaseOrder.billTo.zip = new Asn1Integer(19341);

         purchaseOrder.comment = new Comment ("Need this ASAP!");

         purchaseOrder.items= new Items(2);
         purchaseOrder.items.elements[0] = new Items_item();
         purchaseOrder.items.elements[0].partNum = new SKU ("111-AA");
         purchaseOrder.items.elements[0].productName = 
            new Asn1UTF8String ("Acme Widget");
         purchaseOrder.items.elements[0].quantity = new Asn1Integer (50);
         purchaseOrder.items.elements[0].uSPrice = new Asn1Integer (200);

         purchaseOrder.items.elements[1] = new Items_item();
         purchaseOrder.items.elements[1].partNum = new SKU ("222-BB");
         purchaseOrder.items.elements[1].productName = 
            new Asn1UTF8String ("Wizbang Gadget");
         purchaseOrder.items.elements[1].quantity = new Asn1Integer (99);
         purchaseOrder.items.elements[1].uSPrice = new Asn1Integer (777);
         purchaseOrder.items.elements[1].comment = 
            new Comment ("I would like these in the color red");
         purchaseOrder.items.elements[1].shipDate = 
            new XSD_Date ("2003-03-26");

         // Encode

         purchaseOrder.encode (encodeBuffer);

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
