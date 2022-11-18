package sample_ber.TAP0311Batch;

import com.objsys.asn1j.runtime.*;
import java.io.*;
import java.util.*;

public class Writer {
   public static void main (String args[]) {
       String filename = new String ("message.dat");
       boolean trace = true;

      // Process command line arguments

      if (args.length > 0) {
         for (int i = 0; i < args.length; i++) {
            if (args[i].equals ("-v"))
                Diag.instance().setEnabled (true);
            else if (args[i].equals ("-o"))
                filename = new String (args[++i]);
            else if (args[i].equals ("-notrace")) trace = false;
            else {
                System.out.println ("usage: Writer [ -v ] [ -o <filename>");
                System.out.println ("   -v  verbose mode: print trace info");
                System.out.println ("   -o <filename>  " +
                                    "write encoded msg to <filename>");
                System.out.println ("   -notrace  do not display trace info");
                return;
            }
         }
      }

      // Create a data object and populate it with the data to be encoded

      Asn1BerOutputStream out = null;

      try {
         out = new Asn1BerOutputStream (new FileOutputStream(filename));

         out.encodeTagAndIndefLen (TransferBatch.TAG);

         encode_BatchControlInfo (out);
         encode_AccountingInfo (out);
         encode_NetworkInfo (out);
         encode_MessageDescriptionInfoList (out);

         /* The call detail list is handled differently.  It is possible to   */
         /* have a very large number of these records which would make        */
         /* encoding the whole list in memory difficult.  The solution is to  */
         /* drop another indefinite tag/length into the file and then encode  */
         /* and write each call detail record.  See this routine for further  */
         /* details..                                                         */

         encode_CallDetailList (out);

         encode_AuditControlInfo (out);

         out.encodeEOC ();
         
         if (trace) {
            out.close ();
            out = null;

            Asn1BerDecodeBuffer decodeBuffer = 
                new Asn1BerDecodeBuffer (new FileInputStream (filename));

            try {
                decodeBuffer.parse (new Asn1BerMessageDumpHandler (System.out));
            }
            catch (Exception e) {
                System.out.println (e.getMessage());
                e.printStackTrace();           
            }
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

   static void encode_BatchControlInfo (Asn1BerOutputStream out)
      throws Asn1Exception, java.io.IOException
   {
      BatchControlInfo bci = new BatchControlInfo ();

      bci.sender             = new Asn1VisibleString ("USA27");
      bci.recipient          = new Asn1VisibleString ("DEUD2");
      bci.fileSequenceNumber = new Asn1NumericString ("00272");

      bci.fileCreationTimeStamp   = new DateTimeLong (
         new Asn1NumericString("20000307080756"),
         new Asn1VisibleString("-0500"));
      bci.transferCutOffTimeStamp = new DateTimeLong (
         new Asn1NumericString("20000307080751"),
         new Asn1VisibleString("-0500"));
      bci.fileAvailableTimeStamp  = new DateTimeLong (
         new Asn1NumericString("20000307080756"),
         new Asn1VisibleString("-0500"));

      bci.specificationVersionNumber = new Asn1Integer (3);
      bci.releaseVersionNumber = new Asn1Integer (11);

      bci.encode (out, true);
   }

   static void encode_AccountingInfo (Asn1BerOutputStream out)
      throws Asn1Exception, java.io.IOException
   {
      AccountingInfo accountingInfo = new AccountingInfo ();

      accountingInfo.taxation = new TaxationList (2);

      accountingInfo.taxation.elements [0] =
         new Taxation (
            new Asn1Integer(0), new Asn1VisibleString("03"), 
            new Asn1NumericString("0225343"), new Asn1NumericString("0"));
      accountingInfo.taxation.elements [1] =
         new Taxation (
            new Asn1Integer(1), new Asn1VisibleString("02"), 
            new Asn1NumericString("0600343"), new Asn1NumericString("0"));

      accountingInfo.localCurrency = new Asn1VisibleString ("USD");
      accountingInfo.tapCurrency = new Asn1VisibleString ("USD");

      accountingInfo.currencyConversionInfo = new CurrencyConversionList (1);
      accountingInfo.currencyConversionInfo.elements [0] =
         new CurrencyConversion (0L, 6L, 1000000L);

      accountingInfo.tapDecimalPlaces = new Asn1Integer (2);

      accountingInfo.encode (out, true);
   }

   static void encode_NetworkInfo (Asn1BerOutputStream out)
      throws Asn1Exception, java.io.IOException
   {
      NetworkInfo networkInfo = new NetworkInfo ();

      networkInfo.utcTimeOffsetInfo = new UtcTimeOffsetInfoList (1);
      networkInfo.utcTimeOffsetInfo.elements [0] =
         new UtcTimeOffsetInfo (
            new Asn1Integer (0), new Asn1VisibleString ("-0500"));

      networkInfo.recEntityInfo = new RecEntityInfoList (3);
      networkInfo.recEntityInfo.elements [0] =
         new RecEntityInformation (0L, 1L, "3");
      // networkInfo.recEntityInfo.elements [0].recEntityId.set_msisdn (
      //   new Asn1OctetString (Asn1Util.stringToBCD ("80952416046")));

      networkInfo.recEntityInfo.elements [1] =
         new RecEntityInformation (1L, 1L, "3");
      // networkInfo.recEntityInfo.elements [1].recEntityId.set_msisdn (
      //   new Asn1OctetString (Asn1Util.stringToBCD ("80952416046")));

      networkInfo.recEntityInfo.elements [2] =
         new RecEntityInformation (2L, 1L, "3");
      // networkInfo.recEntityInfo.elements [2].recEntityId.set_msisdn (
      //   new Asn1OctetString (Asn1Util.stringToBCD ("80952416046")));

      /* networkInfo.calledNumAnalysis = new CalledNumAnalysisList (1);
      networkInfo.calledNumAnalysis.elements [0] = new CalledNumAnalysis (
         null, new CountryCodeList (1), new IacList (1));
      networkInfo.calledNumAnalysis.elements [0].countryCodeTable.elements [0] =
         new Asn1OctetString ("1");
      networkInfo.calledNumAnalysis.elements [0].iacTable.elements [0] =
         new Asn1OctetString ("011"); */

      networkInfo.encode (out, true);
   }

   /* static void encode_VasInfoList (Asn1BerOutputStream out)
      throws Asn1Exception, java.io.IOException
   {
      VasInfoList vasInfo = new VasInfoList (1);

      vasInfo.elements [0] = new VasInformation (new Asn1Integer(1), 
         new Asn1OctetString("Short"), 
         new Asn1OctetString("Description"));

      vasInfo.encode (out, true);
   } */

   static void encode_MessageDescriptionInfoList (Asn1BerOutputStream out)
      throws Asn1Exception, java.io.IOException
   {
      MessageDescriptionInfoList messageDescriptionInfo = new MessageDescriptionInfoList (1);

      messageDescriptionInfo.elements [0] =
         new MessageDescriptionInformation (new Asn1Integer(1), 
            new Asn1VisibleString("Description"));

      messageDescriptionInfo.encode (out, true);
   }

   /* Encode call detail list.  This part of the sample gets its data from */
   /* a data input file.  This could just as easily be a database or other */
   /* storage device containing large numbers of call detail records.      */
   /* The records are sequentially read and encoded and written to the     */
   /* output file.                                                         */

   static void encode_CallDetailList (Asn1BerOutputStream out)
      throws Asn1Exception, java.io.IOException
   {
      BufferedReader reader = new BufferedReader (new FileReader ("input.dat"));

      out.encodeTagAndIndefLen (CallEventDetailList.TAG);

      try {
         String str;
         while ((str = reader.readLine ()) != null) {
            if (str.indexOf ("CALL DATA", 0) != -1) {
               encode_MobileOriginatedCall (reader, out);
            }
         }
      }
      catch (java.io.IOException ex) {
      }

      reader.close ();

      out.encodeEOC ();
   }

   static void encode_MobileOriginatedCall (BufferedReader reader, Asn1BerOutputStream out)
      throws Asn1Exception, java.io.IOException
   {
      MobileOriginatedCall mOC = new MobileOriginatedCall ();
      CallEventDetail cED = new CallEventDetail ();

      cED.set_mobileOriginatedCall (mOC);

      /* This procedure expects the call data to be layed out in three     */
      /* lines like the input file provided.  It is not set up to handle   */
      /* any format and is not truely dynamic in nature                    */

      mOC.basicCallInformation = new MoBasicCallInformation ();
      /* chargeable subscriber */
      mOC.basicCallInformation.chargeableSubscriber = new ChargeableSubscriber ();
      mOC.basicCallInformation.chargeableSubscriber.set_simChargeableSubscriber (
         new SimChargeableSubscriber (
            new Asn1BCDString ("250123000113003"),
            new Asn1BCDString ("79024113000")));


      /* destination */
      mOC.basicCallInformation.destination = new Destination ();
      String line = reader.readLine ();
      StringTokenizer toker = new StringTokenizer (line, " ");
      String calledNumber = toker.nextToken ();
      String calledPlace = toker.nextToken ();
      String localTimeStamp = toker.nextToken ();
      long timeOffset = Long.parseLong (toker.nextToken ());
      long totalCall = Long.parseLong (toker.nextToken ());

      mOC.basicCallInformation.destination.calledNumber = 
                        new Asn1BCDString (Asn1Value.parseString(calledNumber));
      mOC.basicCallInformation.destination.calledPlace = new Asn1VisibleString (calledPlace);

      /* Call event start time stamp */
      mOC.basicCallInformation.callEventStartTimeStamp = new DateTime (
         new Asn1NumericString (localTimeStamp), 
         new Asn1Integer(timeOffset));

      /* Event Duration */
      mOC.basicCallInformation.totalCallEventDuration = new Asn1Integer (totalCall);


      /* location information */
      mOC.locationInformation = new LocationInformation ();
      mOC.locationInformation.networkLocation = new NetworkLocation ();

      line = reader.readLine ();
      toker = new StringTokenizer (line, " ");
      long recEntityCode = Long.parseLong (toker.nextToken ());
      long locationArea = Long.parseLong (toker.nextToken ());
      long cellId = Long.parseLong (toker.nextToken ());
      String servingBid = toker.nextToken ();
      String locationDescription = toker.nextToken ();

      mOC.locationInformation.networkLocation.recEntityCode = new Asn1Integer (recEntityCode);
      mOC.locationInformation.networkLocation.locationArea = new Asn1Integer (locationArea);
      mOC.locationInformation.networkLocation.cellId = new Asn1Integer (cellId);

      mOC.locationInformation.geographicalLocation = new GeographicalLocation ();
      mOC.locationInformation.geographicalLocation.servingBid = 
         new Asn1VisibleString (servingBid);
      mOC.locationInformation.geographicalLocation.servingLocationDescription = 
         new Asn1VisibleString (locationDescription);

      /* equipment information */
      mOC.equipmentIdentifier = new ImeiOrEsn ();
      mOC.equipmentIdentifier.set_imei (
         new Asn1BCDString (Asn1Util.stringToBCD ("49013810114356")));

      /* basic service used list */

      mOC.basicServiceUsedList = new BasicServiceUsedList (1);
      BasicServiceUsed bsu = new BasicServiceUsed ();
      mOC.basicServiceUsedList.elements [0] = bsu;

      bsu.basicService = new BasicService ();
      bsu.basicService.serviceCode = new BasicServiceCode ();

      line = reader.readLine ();
      toker = new StringTokenizer (line, " ");
      String teleServiceCode = toker.nextToken ();
      long radioChannelRequested = Long.parseLong (toker.nextToken ());
      long radioChannelUsed = Long.parseLong (toker.nextToken ());
      String chargedItem = toker.nextToken ();
      long exchangeRateCode = Long.parseLong (toker.nextToken ());
      String callType = toker.nextToken ();

      bsu.basicService.serviceCode.set_teleServiceCode (new Asn1VisibleString (teleServiceCode));
      
      /* build charge information list */
      bsu.chargeInformationList = new ChargeInformationList (1);

      ChargeInformation chargeInfo = new ChargeInformation ();
      bsu.chargeInformationList.elements [0] = chargeInfo;
      chargeInfo.chargedItem = new Asn1VisibleString (chargedItem);
      chargeInfo.exchangeRateCode = new Asn1Integer (exchangeRateCode);
      chargeInfo.callTypeGroup = new CallTypeGroup (
         null, null, null);

      LinkedList chargeDetailList = new LinkedList ();

      do {
         /* when you get to the next call this call will read the       */
         /* first two characters of the next call line.  This will be   */
         /* the number before CALL DATA.  Again another short cut.      */

         line = reader.readLine ();
         if (line == null) break;

         toker = new StringTokenizer (line, " ");
         try {
            String chargeType = toker.nextToken ();
            long charge = Long.parseLong (toker.nextToken ());
            long chargeableUnits = Long.parseLong (toker.nextToken ());
            long chargedUnits = Long.parseLong (toker.nextToken ());
            String dayCategory = toker.nextToken ();
            String timeBand = toker.nextToken ();


            ChargeDetail chargeDetail = new ChargeDetail ();

            load_ChargeDetail (chargeDetail, chargeType, charge,
                               chargeableUnits, chargedUnits, dayCategory,
                               timeBand);

            chargeDetailList.add (chargeDetail);
         }
         catch (NoSuchElementException ex) {
            break;
         }
      } while (true);

      chargeInfo.chargeDetailList = new ChargeDetailList (chargeDetailList.size ());
      chargeDetailList.toArray (chargeInfo.chargeDetailList.elements);

      cED.encode (out, true);
   }

   static void load_ChargeDetail (ChargeDetail chargeDetail,
                                  String chargeType,
                                  long charge,
                                  long chargeableUnits,
                                  long  chargedUnits,
                                  String dayCategory,
                                  String timeBand)
      throws Asn1Exception, java.io.IOException
   {
      chargeDetail.chargeType = new Asn1NumericString (chargeType);
      chargeDetail.charge = new Asn1Integer (charge);
      chargeDetail.chargeableUnits = new Asn1Integer (chargeableUnits);
      chargeDetail.chargedUnits = new Asn1Integer (chargedUnits);
   }

   static void encode_AuditControlInfo (Asn1BerOutputStream out)
      throws Asn1Exception, java.io.IOException
   {
      AuditControlInfo auditControlInfo = new AuditControlInfo ();

      auditControlInfo.earliestCallTimeStamp = new DateTimeLong (
         new Asn1NumericString("20000305203647"), 
         new Asn1VisibleString("-0500"));
      auditControlInfo.latestCallTimeStamp = new DateTimeLong (
         new Asn1NumericString("20000305222654"),
         new Asn1VisibleString("-0500"));

      auditControlInfo.totalTaxValue = new Asn1Integer (63);
      auditControlInfo.totalDiscountValue = new Asn1Integer (0);
      auditControlInfo.callEventDetailsCount = new Asn1Integer (7);
   	
      auditControlInfo.encode (out, true);
   }
}
