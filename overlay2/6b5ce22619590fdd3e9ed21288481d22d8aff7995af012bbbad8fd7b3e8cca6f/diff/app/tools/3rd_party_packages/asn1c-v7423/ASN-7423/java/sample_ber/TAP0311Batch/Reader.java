package sample_ber.TAP0311Batch;

import com.objsys.asn1j.runtime.*;
import java.io.*;

public class Reader {
   public static void main (String args[]) {
       String filename = new String ("message.dat");
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
                System.out.println ("usage: Reader [ -v ] [ -o <filename>");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -i <filename>  " +
                                    "read encoded msg from <filename>");
                System.out.println ("   -notrace  do not display trace info");
                return;
            }
         }
      }

      try {
         // Create an input file stream object

         FileInputStream in = new FileInputStream (filename);

         // Create a decode buffer object

         Asn1BerDecodeBuffer buffer = new Asn1BerDecodeBuffer (in);

         /* Loop to read and process each record in the batch file */

         Asn1Tag tag = new Asn1Tag ();
         buffer.mark (8);
         int len = buffer.decodeTagAndLength (tag);

         if (tag.equals (Asn1Tag.APPL, Asn1Tag.CONS, 1))
         {
            buffer.reset();
            decodeTransferBatch(buffer, true, len, trace);
         }
         else if (tag.equals (Asn1Tag.APPL, Asn1Tag.CONS, 2))
         {
            buffer.reset();
            Notification notification = new Notification();
            notification.decode (buffer, true, len);
            if(trace) {
               notification.print (System.out, "notification", 0);
            }
         }
         else {
            throw new Asn1InvalidChoiceOptionException (buffer, tag);
         }

         System.out.println ("Decode was successful");
      }
      catch (Exception e) {
          System.out.println (e.getMessage());
          e.printStackTrace();           
          System.exit(-1);
      }
   }

   public static void decodeTransferBatch
      (Asn1BerDecodeBuffer buffer, boolean explicit, 
       int implicitLength, boolean trace)
      throws Asn1Exception, java.io.IOException
   {
      BatchControlInfo batchControlInfo;  // optional
      AccountingInfo accountingInfo;  // optional
      NetworkInfo networkInfo;  // optional
      MessageDescriptionInfoList messageDescriptionInfo;  // optional
      AuditControlInfo auditControlInfo;  // optional

      int llen = (explicit) ?
         matchTag (buffer, TransferBatch.TAG) : implicitLength;

      // decode SEQUENCE

      Asn1BerDecodeContext context =
         new Asn1BerDecodeContext (buffer, llen);

      IntHolder elemLen = new IntHolder();

      // decode batchControlInfo

      if (context.matchElemTag (Asn1Tag.APPL, Asn1Tag.CONS, 4, elemLen, false)) {
         batchControlInfo = new BatchControlInfo();
         batchControlInfo.decode (buffer, true, elemLen.value);
         if(trace) {
            batchControlInfo.print (System.out, "batchControlInfo", 0);
         }
      }

      // decode accountingInfo

      if (context.matchElemTag (Asn1Tag.APPL, Asn1Tag.CONS, 5, elemLen, false)) {
         accountingInfo = new AccountingInfo();
         accountingInfo.decode (buffer, true, elemLen.value);
         if(trace) {
            accountingInfo.print (System.out, "accountingInfo", 0);
         }
      }

      // decode networkInfo

      if (context.matchElemTag (Asn1Tag.APPL, Asn1Tag.CONS, 6, elemLen, false)) {
         networkInfo = new NetworkInfo();
         networkInfo.decode (buffer, true, elemLen.value);
         if(trace) {
            networkInfo.print (System.out, "networkInfo", 0);
         }
      }

      // decode messageDescriptionInfo

      if (context.matchElemTag (Asn1Tag.APPL, Asn1Tag.CONS, 8, elemLen, false)) {
         messageDescriptionInfo = new MessageDescriptionInfoList();
         messageDescriptionInfo.decode (buffer, true, elemLen.value);
         if(trace) {
            messageDescriptionInfo.print (System.out, "messageDescriptionInfo", 0);
         }
      }

      // decode callEventDetails

      if (context.matchElemTag (Asn1Tag.APPL, Asn1Tag.CONS, 3, elemLen, false)) {
         decodeCallEventDetailList (buffer, true, elemLen.value, trace);
      }

      // decode auditControlInfo

      if (context.matchElemTag (Asn1Tag.APPL, Asn1Tag.CONS, 15, elemLen, false)) {
         auditControlInfo = new AuditControlInfo();
         auditControlInfo.decode (buffer, true, elemLen.value);
         if(trace) {
            auditControlInfo.print (System.out, "auditControlInfo", 0);
         }
      }

      if (explicit && llen == Asn1Status.INDEFLEN) {
         matchTag (buffer, Asn1Tag.EOC);
      }
   }

   public static void decodeCallEventDetailList
      (Asn1BerDecodeBuffer buffer, boolean explicit, int implicitLength, boolean trace)
      throws Asn1Exception, java.io.IOException
   {
      int llen = (explicit) ?
         matchTag (buffer, CallEventDetailList.TAG) : implicitLength;

      // decode SEQUENCE OF or SET OF
      //LinkedList llist = new LinkedList ();
      Asn1BerDecodeContext context =
          new Asn1BerDecodeContext (buffer, llen);
      CallEventDetail element;
      int elemLen = 0;

      while (!context.expired()) {
         element = new CallEventDetail();
         element.decode (buffer, true, elemLen);
         if(trace) {
            element.print (System.out, "callEventDetail", 0);
         }
         //llist.add (element);
      }

      //CallEventDetail[] elements = new CallEventDetail [llist.size()];
      //llist.toArray (elements);

      if (explicit && llen == Asn1Status.INDEFLEN) {
         matchTag (buffer, Asn1Tag.EOC);
      }
   }

   public static int matchTag (Asn1BerDecodeBuffer buffer, Asn1Tag tag)
      throws Asn1Exception, java.io.IOException
   {
      Asn1Tag   parsedTag = new Asn1Tag ();
      IntHolder parsedLen = new IntHolder ();
      if (buffer.matchTag (tag.mClass, tag.mForm, tag.mIDCode, 
                           parsedTag, parsedLen)) {
         return parsedLen.value;
      }
      else
         throw new Asn1TagMatchFailedException 
            (buffer, new Asn1Tag(tag.mClass, tag.mForm, tag.mIDCode), parsedTag);
   }

   static {
      Asn1Type._setKey (_TAP_0311Rtkey._rtkey);
   }
}
