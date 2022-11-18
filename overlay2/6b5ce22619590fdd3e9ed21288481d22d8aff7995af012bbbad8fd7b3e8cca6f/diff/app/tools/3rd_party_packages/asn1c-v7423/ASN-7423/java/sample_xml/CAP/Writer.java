/**
 * This is an implementation of the Common Alerting Protocol (CAP), 
 * an OASIS standard. 
 */
package sample_xml.CAP;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.util.*;

public class Writer {

   public static void main(String args[]) {

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
               System.exit(1);
            }
         }
      }
      
      // Create a message buffer object
      Asn1XmlEncodeBuffer encodeBuffer = new Asn1XmlEncodeBuffer();
      try {
         Alert alert;
         alert = new Alert();
         alert.identifier = new Asn1UTF8String ("43b080713727");
         alert.sender = new Asn1UTF8String ("hsas@dhs.gov");
         alert.sent = new XSD_DateTime ("2003-04-02T14:39:01-05:00");
         alert.status = Alert_status.actual();
         alert.msgType = Alert_msgType.alert();
         alert.scope = Alert_scope.public_();

         alert.info_list = new Alert_info [1];
         alert.info_list[0] = new Alert_info();
         alert.info_list[0].category_list = new Alert_info_category [1];
         alert.info_list[0].category_list[0] = Alert_info_category.security();

         alert.info_list[0].event = new Asn1UTF8String 
            ("Homeland Security Advisory System Update");

         alert.info_list[0].urgency = Alert_info_urgency.immediate();

         alert.info_list[0].severity = Alert_info_severity.severe();

         alert.info_list[0].certainty = Alert_info_certainty.likely();

         alert.info_list[0].senderName = new Asn1UTF8String
            ("U.S. Government, Department of Homeland Security");

         alert.info_list[0].headline = new Asn1UTF8String 
            ("Homeland Security Sets Code ORANGE");

         alert.info_list[0].description = new Asn1UTF8String
            ("The Department of Homeland Security has elevated the Homeland Security Advisory System threat level to ORANGE / High in response to intelligence which may indicate a heightened threat of terrorism.");

         alert.info_list[0].instruction = new Asn1UTF8String
            (" A High Condition is declared when there is a high risk of terrorist attacks. In addition to the Protective Measures taken in the previous Threat Conditions, Federal departments and agencies should consider agency specific Protective Measures in accordance with their existing plans.");

         alert.info_list[0].web = new Asn1UTF8String
            ("http://www.dhs.gov/dhspublic/display?theme=29");

         alert.info_list[0].parameter_list = new Asn1UTF8String [1];

         alert.info_list[0].parameter_list[0] = 
            new Asn1UTF8String ("HSAS=ORANGE");

         alert.info_list[0].resource_list = new Alert_info_resource [1];

         alert.info_list[0].resource_list[0] = 
            new Alert_info_resource();

         alert.info_list[0].resource_list[0].resourceDesc = 
            new Asn1UTF8String ("Image file (GIF)");

         alert.info_list[0].resource_list[0].uri = 
            new Asn1UTF8String  
            ("http://www.dhs.gov/dhspublic/getAdvisoryImage");

         alert.info_list[0].area_list = new Alert_info_area[1];

         alert.info_list[0].
            area_list[0] = new Alert_info_area();

         alert.info_list[0].
            area_list[0].areaDesc = new Asn1UTF8String
            ("U.S. nationwide and interests worldwide");

         alert.encode (encodeBuffer);
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
