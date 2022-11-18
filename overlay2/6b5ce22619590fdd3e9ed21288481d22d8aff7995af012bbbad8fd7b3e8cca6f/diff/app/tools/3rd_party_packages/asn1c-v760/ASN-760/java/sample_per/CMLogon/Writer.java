package sample_per.CMLogon;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Writer {
   public static void main (String args[]) {
      String filename = new String ("message.dat");
      boolean aligned = true, trace = true;

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
            else if (args[i].equals ("-notrace")) trace = false;
            else {
               System.out.println ("usage: Writer [ -a | -u ] [ -v ] " +
                                   "[ -o <filename>");
               System.out.println ("   -a  PER aligned encoding (default)");
               System.out.println ("   -u  PER unaligned encoding");
               System.out.println ("   -v  verbose mode: print trace info");
               System.out.println ("   -o <filename>  " +
                                   "write encoded msg to <filename>");
               System.out.println ("   -notrace  do not display trace info");
               return;
            }
         }
      }

      try {
         // Populate CMLogonRequest structure

         CMLogonRequest cmLogonRequest = new CMLogonRequest ();

         cmLogonRequest.aircraftFlightIdentification = 
            new AircraftFlightIdentification ("UA901");

         cmLogonRequest.cMLongTSAP = new LongTsap 
            (new Asn1OctetString ("AB901"), 
             new ShortTsap (null, new Asn1OctetString ("4440900901")));

         cmLogonRequest.facilityDesignation = 
            new FacilityDesignation ("KIADIZDS");

         // Plug structure into CMAircraftMessage variable

         CMAircraftMessage cmAircraftMessage = new CMAircraftMessage ();
         cmAircraftMessage.set_cmLogonRequest (cmLogonRequest);

         // Create a message buffer object 

         Asn1PerEncodeBuffer cmEncodeBuffer = 
            new Asn1PerEncodeBuffer (aligned);

         // Enable bit field tracing

         if (trace) {
            cmEncodeBuffer.getTraceHandler().enable();
         }

         // Encode

         if (trace) {
            System.out.println ("Encoding CM message..");
            System.out.println ("");
         }

         cmAircraftMessage.encode (cmEncodeBuffer);

         if (trace) {
            System.out.println ("CM Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            cmEncodeBuffer.hexDump ();
            System.out.println ("Binary dump:");
            cmEncodeBuffer.binDump ("cmAircraftMessage");
         }

         // Populate AARQ PDU structure

         int[] applCtxtNameOID   = { 1, 3, 27, 3, 1 };
         int[] callingAPTitleOID = { 1, 3, 27, 1, 500, 0 };

         AARQ_apdu aarq = new AARQ_apdu ();

         aarq.application_context_name = 
            new Application_context_name (applCtxtNameOID);

         aarq.calling_AP_title = new AP_title ();
         aarq.calling_AP_title.set_ap_title_form2
            (new AP_title_form2 (callingAPTitleOID));

         aarq.calling_AE_qualifier = new AE_qualifier ();
         aarq.calling_AE_qualifier.set_ae_qualifier_form2 
            (new AE_qualifier_form2 (1));

         // Populate external type with info in the encoded request and plug 
         // into the structure..

         Asn1BitString externalData = new Asn1BitString ();
         externalData.numbits = cmEncodeBuffer.getMsgBitCnt ();
         externalData.value = cmEncodeBuffer.getBuffer ();

         aarq.user_information = new Association_information (1);
         Asn1External_encoding ee = new Asn1External_encoding ();
         ee.set_arbitrary (externalData);
         aarq.user_information.elements[0] = 
            new Asn1External (null, null, null, ee);

         // Populate the ACSE structure and encode

         ACSE_apdu acse = new ACSE_apdu ();
         acse.set_aarq (aarq);

         if (trace) {
            System.out.println ("");
            System.out.println ("Encoding ACSE AARQ APDU..");
            System.out.println ("");
         }

         Asn1PerEncodeBuffer acseEncodeBuffer = 
            new Asn1PerEncodeBuffer (aligned);

         if (trace) {
            acseEncodeBuffer.getTraceHandler().enable();
         }

         acse.encode (acseEncodeBuffer);

         if (trace) {
            System.out.println ("ACSE Encoding was successful");
            System.out.println ("Hex dump of encoded record:");
            acseEncodeBuffer.hexDump ();
            System.out.println ("Binary dump:");
            acseEncodeBuffer.binDump ("acse");
         }

         // Write the encoded record to a file

         acseEncodeBuffer.write (new FileOutputStream (filename));

         // Generate a dump file for comparisons

         String fileSuffix = (aligned) ? "a" : "u";
         acseEncodeBuffer.hexDump 
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
