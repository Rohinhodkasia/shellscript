// writer.cpp : This sample program will construct and write a TAP3
// batch file out in stages so that the entire batch does not need to 
// be encoded in memory.

#include <stdio.h>
#include <stdlib.h>
#include "TAP-0311.h"
#include "rtbersrc/ASN1BEREncodeStream.h"
#include "rtxsrc/OSRTFileOutputStream.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxPrint.h"

#include "rtsrc/rtBCD.h"

#define MAXMSGLEN 1024

static int encode_BatchControlInfo (ASN1BEREncodeStream& fos);
static int encode_AccountingInfo (ASN1BEREncodeStream& fos);
static int encode_NetworkInfo (ASN1BEREncodeStream& fos);
static int encode_MessageDescriptionInfo (ASN1BEREncodeStream& fos);
static int encode_CallDetailList (ASN1BEREncodeStream& fos);

static int encode_MobileOriginatedCall (FILE *infp, ASN1BEREncodeStream& fos);

static int load_ChargeDetail 
(OSCTXT* pctxt, ASN1T_ChargeDetail *pChargeDetail, const char* chargeType,
 ASN1T_Charge charge, ASN1T_ChargeableUnits chargeableUnits, 
 ASN1T_ChargedUnits chargedUnits, const char* dayCategory, 
 const char* timeBand);

static int encode_AuditControlInfo (ASN1BEREncodeStream& fos);

static void setTimeStamp (const char* localTimeStamp, 
                          const char* utcOffset, 
                          ASN1T_DateTimeLong* pTimeStamp)
{
   pTimeStamp->m.localTimeStampPresent = 1;
   pTimeStamp->m.utcTimeOffsetPresent = 1;
   pTimeStamp->localTimeStamp = localTimeStamp;
   pTimeStamp->utcTimeOffset = utcOffset;
}

static void setDateTime (const char* localTimeStamp, 
                         int utcOffset, ASN1T_DateTime* pTimeStamp)
{
   pTimeStamp->m.localTimeStampPresent = 1;
   pTimeStamp->m.utcTimeOffsetCodePresent = 1;
   pTimeStamp->localTimeStamp = localTimeStamp;
   pTimeStamp->utcTimeOffsetCode = utcOffset;
}

static OSBOOL gTrace = TRUE;

DECLARE_MEMLEAK_DETECTOR;

int main(int argc, char** argv)
{
   /* Run-time support variables */

   int		i;
   const char	*filename = "message.dat";

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) rtxSetGlobalDiag (1);
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) gTrace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   ASN1BEREncodeStream fos (new OSRTFileOutputStream (filename));

   if (fos.getStatus () != 0) { fos.printErrorInfo (); return -1; }

   /* Encode an initial indefinite length marker with the outer level   */
   /* tag ([APPLICATION 1]) for the TransferBatch structure.  Then      */
   /* write this tag and length to the output file.                     */

   if (fos.encodeTagAndIndefLen (TM_APPL|TM_CONS|1) != 0) {
      fos.printErrorInfo (); return -1;
   }

   /* Now sequentially encode and write each of the message components  */
   /* in the SEQUENCE to the output file until the 'callEventDetails'   */
   /* element is encountered.  In this sample each of the message       */
   /* component records is hard-coded..                                 */

   if (encode_BatchControlInfo (fos) != 0) { 
      fos.printErrorInfo (); return -1; 
   }
   if (encode_AccountingInfo (fos) != 0) { 
      fos.printErrorInfo (); return -1; 
   }
   if (encode_NetworkInfo (fos) != 0) { 
      fos.printErrorInfo (); return -1; 
   }
   if (encode_MessageDescriptionInfo (fos) != 0) { 
      fos.printErrorInfo (); return -1; 
   }

   /* The call detail list is handled differently.  It is possible to   */
   /* have a very large number of these records which would make        */
   /* encoding the whole list in memory difficult.  The solution is to  */
   /* drop another indefinite tag/length into the file and then encode  */
   /* and write each call detail record.  See this routine for further  */
   /* details..                                                         */

   if (encode_CallDetailList (fos) != 0) { 
      fos.printErrorInfo (); return -1; 
   }

   if (encode_AuditControlInfo (fos) != 0) { 
      fos.printErrorInfo (); return -1; 
   }
	
   /* This is where the final EOC marker is written to the file */

   if (fos.encodeEoc () != 0) { 
      fos.printErrorInfo (); return -1; 
   }

   fos.close ();

   /* dump the data */
   if (gTrace) {
      FILE* fp;
      size_t flen;
      OSCTXT ctxt;

      rtInitContext (&ctxt);
      /* Open the input file in read binary mode */

      if ((fp = fopen (filename, "rb")) == 0) {
         printf ("Error opening %s for read access\n", filename);
         return -1;
      }
      fseek (fp, 0, SEEK_END);
      flen = (size_t) ftell (fp);
      fseek (fp, 0, SEEK_SET);

      if (flen > 0) {
         OSOCTET* msgptr =  (OSOCTET*)rtxMemAlloc (&ctxt, flen);
         if (fread (msgptr, 1, flen, fp) != flen) {
            printf ("Error reading %s\n", filename);
            return -1;
         }

         if (XU_DUMP (msgptr) != 0) 
            printf ("dump of ASN.1 message failed.");
      }

      fclose (fp);
      rtFreeContext (&ctxt);
   }

   return 0;
}

static int encode_BatchControlInfo (ASN1BEREncodeStream& fos)
{	
   ASN1T_BatchControlInfo bci;

   bci.m.senderPresent = 1;
   bci.m.recipientPresent = 1;
   bci.m.fileSequenceNumberPresent = 1;
   bci.m.fileCreationTimeStampPresent = 1;
   bci.m.transferCutOffTimeStampPresent = 1;
   bci.m.fileAvailableTimeStampPresent = 1;
   bci.m.specificationVersionNumberPresent = 1;
   bci.m.releaseVersionNumberPresent = 1;
   bci.m.fileTypeIndicatorPresent = 0;
   bci.m.rapFileSequenceNumberPresent = 0;
   bci.m.operatorSpecInformationPresent = 0;

   bci.sender             = "USA27";
   bci.recipient          = "DEUD2";
   bci.fileSequenceNumber = "00272";

   setTimeStamp ("20000307080756", "-0500", &bci.fileCreationTimeStamp);
   setTimeStamp ("20000307080751", "-0500", &bci.transferCutOffTimeStamp);
   setTimeStamp ("20000307080756", "-0500", &bci.fileAvailableTimeStamp);

   bci.specificationVersionNumber = 3;
   bci.releaseVersionNumber = 11;

   ASN1C_BatchControlInfo bciC (bci);
   fos << bciC;

   return fos.getStatus ();
}

static int encode_AccountingInfo (ASN1BEREncodeStream& fos)
{
   ASN1T_AccountingInfo accountingInfo;

   accountingInfo.m.taxationPresent = 1;
   accountingInfo.m.discountingPresent = 0;
   accountingInfo.m.localCurrencyPresent = 1;
   accountingInfo.m.tapCurrencyPresent = 1;
   accountingInfo.m.currencyConversionInfoPresent = 1;
   accountingInfo.m.tapDecimalPlacesPresent = 1;

   ASN1CSeqOfList taxationList (fos, accountingInfo.taxation);

   ASN1T_Taxation* pTaxation = 
      rtxMemAllocType (fos.getCtxtPtr(), ASN1T_Taxation);
   asn1Init_Taxation (pTaxation);

   pTaxation->m.taxCodePresent = 1;
   pTaxation->m.taxTypePresent = 1;
   pTaxation->m.taxRatePresent = 1;
   pTaxation->taxCode = 0;

   pTaxation->taxType = "03";
   pTaxation->taxRate = "0225343";
   taxationList.append (pTaxation);

   pTaxation = 
      rtxMemAllocType (fos.getCtxtPtr(), ASN1T_Taxation);
   asn1Init_Taxation (pTaxation);
   pTaxation->m.taxCodePresent = 1;
   pTaxation->m.taxTypePresent = 1;
   pTaxation->m.taxRatePresent = 1;
   pTaxation->taxCode = 1;
   pTaxation->taxType = "02";
   pTaxation->taxRate = "0600343";
   taxationList.append (pTaxation);

   accountingInfo.localCurrency = "USD";
   accountingInfo.tapCurrency = "USD";
	
   ASN1CSeqOfList excRateList (fos, accountingInfo.currencyConversionInfo);
   ASN1T_CurrencyConversion* pCurrConv;
   
   pCurrConv = rtxMemAllocType (fos.getCtxtPtr(), ASN1T_CurrencyConversion);
   asn1Init_CurrencyConversion (pCurrConv);
   pCurrConv->m.exchangeRateCodePresent = 1;
   pCurrConv->m.numberOfDecimalPlacesPresent = 1;
   pCurrConv->m.exchangeRatePresent = 1;
   pCurrConv->exchangeRateCode = 0;
   pCurrConv->numberOfDecimalPlaces = 6;
   pCurrConv->exchangeRate = 1000000;

   excRateList.append (pCurrConv);

   accountingInfo.tapDecimalPlaces = 2;

   ASN1C_AccountingInfo accountingInfoC (accountingInfo);
   fos << accountingInfoC;

   return fos.getStatus ();
}

static int encode_NetworkInfo (ASN1BEREncodeStream& fos)
{
   ASN1T_NetworkInfo networkInfo;

   /* OSOCTET bdata[50]; */

   networkInfo.m.utcTimeOffsetInfoPresent = 1;
   networkInfo.m.recEntityInfoPresent = 1;

   ASN1CSeqOfList utcList (fos, networkInfo.utcTimeOffsetInfo);
   ASN1T_UtcTimeOffsetInfo* pUtcTimeOffset;

   pUtcTimeOffset = rtxMemAllocType (fos.getCtxtPtr(), 
      ASN1T_UtcTimeOffsetInfo);
   asn1Init_UtcTimeOffsetInfo (pUtcTimeOffset);
   pUtcTimeOffset->m.utcTimeOffsetCodePresent = 1;
   pUtcTimeOffset->m.utcTimeOffsetPresent = 1;
   pUtcTimeOffset->utcTimeOffsetCode = 0;
   pUtcTimeOffset->utcTimeOffset = "-0500";
 
   utcList.append (pUtcTimeOffset);

   ASN1CSeqOfList recList (fos, networkInfo.recEntityInfo);
   ASN1T_RecEntityInformation* pRecEntity;

   pRecEntity = rtxMemAllocType (fos.getCtxtPtr(), ASN1T_RecEntityInformation);
   asn1Init_RecEntityInformation (pRecEntity);
   pRecEntity->m.recEntityCodePresent = 1;
   pRecEntity->m.recEntityTypePresent = 1;
   pRecEntity->m.recEntityIdPresent = 1;
   pRecEntity->recEntityCode = 0;
   pRecEntity->recEntityType = 1;

   recList.append (pRecEntity);

   pRecEntity = rtxMemAllocType (fos.getCtxtPtr(), ASN1T_RecEntityInformation);
   asn1Init_RecEntityInformation (pRecEntity);
   pRecEntity->m.recEntityCodePresent = 1;
   pRecEntity->m.recEntityTypePresent = 1;
   pRecEntity->m.recEntityIdPresent = 1;
   pRecEntity->recEntityCode = 1;
   pRecEntity->recEntityType = 1;

   recList.append (pRecEntity);

   pRecEntity = rtxMemAllocType (fos.getCtxtPtr(), ASN1T_RecEntityInformation);
   asn1Init_RecEntityInformation (pRecEntity);
   pRecEntity->m.recEntityCodePresent = 1;
   pRecEntity->m.recEntityTypePresent = 1;
   pRecEntity->m.recEntityIdPresent = 1;
   pRecEntity->recEntityCode = 2;
   pRecEntity->recEntityType = 1;

   recList.append (pRecEntity);

   /* ASN1CSeqOfList calledNumList (fos, networkInfo.calledNumAnalysis);
   ASN1T_CalledNumAnalysis* pCalledNum;

   pCalledNum = rtxMemAllocType (fos.getCtxtPtr(), ASN1T_CalledNumAnalysis);
   asn1Init_CalledNumAnalysis (pCalledNum);
   pCalledNum->m.calledNumAnalysisCodePresent = 0;
   pCalledNum->m.countryCodeTablePresent = 1;
   pCalledNum->m.iacTablePresent = 1;

   ASN1C_CountryCodeList cclist (fos, pCalledNum->countryCodeTable);
   ASN1T_CountryCode* pcc = cclist.NewElement();
   pcc = "1";
   cclist.Append (pcc);

   ASN1C_IacList iacList (fos, pCalledNum->iacTable);
   ASN1T_Iac* piac = iacList.NewElement();
   piac = "011";
   iacList.Append (piac);

   calledNumList.append (pCalledNum); */

   ASN1C_NetworkInfo networkInfoC (networkInfo);
   fos << networkInfoC;

   return fos.getStatus ();
}

/* static int encode_VasInfo (ASN1BEREncodeStream& fos)
{	
   ASN1T_VasInfoList vasInfo;

   ASN1CSeqOfList vasInfoList (fos, vasInfo);
   ASN1T_VasInformation* pVasInfo;

   pVasInfo = rtxMemAllocType (fos.getCtxtPtr(), ASN1T_VasInformation);
   asn1Init_VasInformation (pVasInfo);
   pVasInfo->m.vasCodePresent = 1;
   pVasInfo->m.vasShortDescPresent = 1;
   pVasInfo->m.vasDescPresent = 1; 

   pVasInfo->vasCode = 1;
   
   setAsciiString ("Short", &pVasInfo->vasShortDesc);
   setAsciiString ("Description", &pVasInfo->vasDesc);

   vasInfoList.append (pVasInfo);

   ASN1C_VasInfoList vasInfoC (vasInfo);
   fos << vasInfoC;

   return fos.getStatus ();
} */


static int encode_MessageDescriptionInfo (ASN1BEREncodeStream& fos)
{
   ASN1T_MessageDescriptionInformation* pMsgDescr;
   ASN1T_MessageDescriptionInfoList messageDescriptionInfo;

   ASN1CSeqOfList msgDescrList (fos, messageDescriptionInfo);

   pMsgDescr = rtxMemAllocType (fos.getCtxtPtr(), 
      ASN1T_MessageDescriptionInformation);
   asn1Init_MessageDescriptionInformation (pMsgDescr);
   pMsgDescr->m.messageDescriptionCodePresent = 1;
   pMsgDescr->m.messageDescriptionPresent = 1;
   pMsgDescr->messageDescriptionCode = 1;
   pMsgDescr->messageDescription = "Description";

   msgDescrList.append (pMsgDescr);

   ASN1C_MessageDescriptionInfoList messageDescriptionInfoC (messageDescriptionInfo);
   fos << messageDescriptionInfoC;

   return fos.getStatus ();
}

/* Encode call detail list.  This part of the sample gets its data from */
/* a data input file.  This could just as easily be a database or other */
/* storage device containing large numbers of call detail records.      */
/* The records are sequentially read and encoded and written to the     */
/* output file.                                                         */

static int encode_CallDetailList (ASN1BEREncodeStream& fos)
{
   const char* infilename = "input.dat";
   FILE* inFile = fopen (infilename, "rb");
   if (0 == inFile) {
      printf ("Error opening %s for read access\n", infilename);
      return -1;
   }

   char buffer[100] = {0};

   /* First, encode and write and indefinite tag/length pair for the    */
   /* 'CallEventDetailList' production ([APPLICATION 3]).  The          */
   /* generated structure for this production will not be used.         */
   /* Instead, each of the CallEventDetail records will be individually */
   /* encoded and then written to the output file followed by an EOC    */
   /* marker to terminate the list.                                     */

   fos.encodeTagAndIndefLen (TM_APPL|TM_CONS|3);

   /* This is the loop to read and encode call detail records */

   while (!feof(inFile)) {
      fgets (buffer, sizeof(buffer), inFile);

      if (strncmp (buffer, "CALL DATA", 9) == 0) {
         encode_MobileOriginatedCall (inFile, fos);
      }

      memset (buffer, 0, sizeof(buffer));
   }

   /* This is where the EOC marker that terminates the list is written */

   fos.encodeEoc ();

   fclose (inFile);
	
   return fos.getStatus ();
}

static int encode_MobileOriginatedCall (FILE *infp, ASN1BEREncodeStream& fos)
{	
   ASN1T_MobileOriginatedCall mOC;
   ASN1T_MobileOriginatedCall* pMOC = &mOC;
   ASN1T_CallEventDetail cED;
   OSCTXT* pctxt = fos.getCtxtPtr();

   char buffer[100] = {0};
   char *pbuffer = NULL;
   int  count = 0;
   int  args = 0;
   char calledNumber[20];
   char calledPlace[20];
   char localTimeStamp[20];
   int  timeOffset = 0;
   int  totalCall = 0;
   int  recEntityCode = 0, locationArea = 0, cellId = 0;
   char servingBid[20];
   char locationDescription[40];
   char teleServiceCode[3];
   int  radioChannelRequested = 0, radioChannelUsed = 0, exchangeRateCode = 0;
   char chargedItem[2];
   char callType[2];
   int  numChargeDetail=0;
   char chargeType[3];
   int  charge;
   int  chargeableUnits;
   int  chargedUnits;
   char dayCategory[2];
   char timeBand[2];
   OSOCTET imsiData[50], imeiData[50], msisdnData[50];

   /* This procedure expects the call data to be laid out in three     */
   /* lines like the input file provided.  It is not set up to handle   */
   /* any format and is not truely dynamic in nature                    */

   pMOC->m.basicCallInformationPresent = 1;
   pMOC->m.locationInformationPresent = 1;
   pMOC->m.equipmentIdentifierPresent = 1;
   pMOC->m.basicServiceUsedListPresent = 1;
   pMOC->m.camelServiceUsedPresent = 0;
   pMOC->m.operatorSpecInformationPresent = 0;

   pMOC->basicCallInformation.m.chargeableSubscriberPresent = 1;
   pMOC->basicCallInformation.m.rapFileSequenceNumberPresent = 0;
   pMOC->basicCallInformation.m.destinationPresent = 1;
   pMOC->basicCallInformation.m.destinationNetworkPresent = 0;
   pMOC->basicCallInformation.m.callEventStartTimeStampPresent = 1;
   pMOC->basicCallInformation.m.totalCallEventDurationPresent = 1;
   pMOC->basicCallInformation.m.simToolkitIndicatorPresent = 0;
   pMOC->basicCallInformation.m.causeForTermPresent = 0;

   /* chargeable subscriber */
   pMOC->basicCallInformation.chargeableSubscriber.t = 
      T_ChargeableSubscriber_simChargeableSubscriber;

   pMOC->basicCallInformation.chargeableSubscriber.u.simChargeableSubscriber = 
      (ASN1T_SimChargeableSubscriber*) 
      rtxMemAlloc (pctxt, sizeof(ASN1T_SimChargeableSubscriber));

   asn1Init_SimChargeableSubscriber (pMOC->basicCallInformation.
         chargeableSubscriber.u.simChargeableSubscriber);

   pMOC->basicCallInformation.chargeableSubscriber.
      u.simChargeableSubscriber -> m.imsiPresent = 1;
   pMOC->basicCallInformation.chargeableSubscriber.
      u.simChargeableSubscriber -> m.msisdnPresent = 1;

   pMOC->basicCallInformation.chargeableSubscriber.
      u.simChargeableSubscriber->imsi.numocts = 
      rtStringToBCD ("250123000113003", imsiData, sizeof (imsiData), TRUE);
   pMOC->basicCallInformation.chargeableSubscriber.
      u.simChargeableSubscriber->imsi.data = imsiData;

   pMOC->basicCallInformation.chargeableSubscriber.
      u.simChargeableSubscriber->msisdn.numocts = 
      rtStringToBCD ("79024113000", msisdnData, sizeof (msisdnData), TRUE);
   pMOC->basicCallInformation.chargeableSubscriber.
      u.simChargeableSubscriber->msisdn.data = msisdnData;

   /* destination */
   pMOC->basicCallInformation.destination.m.calledNumberPresent = 1;
   pMOC->basicCallInformation.destination.m.dialledDigitsPresent = 1;
   pMOC->basicCallInformation.destination.m.calledPlacePresent = 1;
   pMOC->basicCallInformation.destination.m.calledRegionPresent = 0;

   args = fscanf (infp, "%s %s %s %d %d", 
                  calledNumber, calledPlace, localTimeStamp, 
                  &timeOffset, &totalCall);
	
   pMOC->basicCallInformation.destination.dialledDigits = "1100254876";
   pMOC->basicCallInformation.destination.calledNumber  = calledNumber;
   pMOC->basicCallInformation.destination.calledPlace   = calledPlace;

   /* Call event start time stamp */
   setDateTime (localTimeStamp, timeOffset, 
                &pMOC->basicCallInformation.callEventStartTimeStamp);

   /* Event Duration */
   pMOC->basicCallInformation.totalCallEventDuration = totalCall;

   /* location information */
   pMOC->locationInformation.m.networkLocationPresent = 1;
   pMOC->locationInformation.m.homeLocationInformationPresent = 0;
   pMOC->locationInformation.m.geographicalLocationPresent = 1;

   pMOC->locationInformation.networkLocation.m.recEntityCodePresent = 1;
   pMOC->locationInformation.networkLocation.m.callReferencePresent = 0;
   pMOC->locationInformation.networkLocation.m.locationAreaPresent = 1;
   pMOC->locationInformation.networkLocation.m.cellIdPresent = 1;

   args = fscanf (infp, "%d %d %d %s %s", 
                  &recEntityCode, &locationArea, &cellId, servingBid, 
                  locationDescription);

   pMOC->locationInformation.networkLocation.recEntityCode = recEntityCode;
   pMOC->locationInformation.networkLocation.locationArea = locationArea;
   pMOC->locationInformation.networkLocation.cellId = cellId;

   pMOC->locationInformation.geographicalLocation.m.servingNetworkPresent = 0;
   pMOC->locationInformation.geographicalLocation.m.servingBidPresent = 1;
   pMOC->locationInformation.geographicalLocation.m.
      servingLocationDescriptionPresent = 1;
   pMOC->locationInformation.geographicalLocation.servingBid = servingBid;
   pMOC->locationInformation.geographicalLocation.servingLocationDescription =
      locationDescription;

   /* equipment information */
   pMOC->equipmentIdentifier.u.imei = 
      (ASN1T_Imei*) rtxMemAlloc (pctxt, sizeof(ASN1T_Imei));

   pMOC->equipmentIdentifier.u.imei -> numocts = 
      rtStringToBCD ("49013810114356", imeiData, sizeof (imeiData), TRUE);
   pMOC->equipmentIdentifier.u.imei -> data = imeiData;

   pMOC->equipmentIdentifier.t = 2;

   /* basic service used list */

   ASN1CSeqOfList bsuList (fos, pMOC->basicServiceUsedList);
   ASN1T_BasicServiceUsed* pBSU;

   pBSU = rtxMemAllocType (pctxt, ASN1T_BasicServiceUsed);
   asn1Init_BasicServiceUsed (pBSU);
   pBSU->m.basicServicePresent = 1;
   pBSU->m.chargingTimeStampPresent = 0;
   pBSU->m.chargeInformationListPresent = 1;

   pBSU->basicService.m.serviceCodePresent = 1;
   pBSU->basicService.m.transparencyIndicatorPresent = 0;
   pBSU->basicService.m.fnurPresent = 0;
   pBSU->basicService.m.userProtocolIndicatorPresent = 0;
   pBSU->basicService.serviceCode.t = 
      T_BasicServiceCode_teleServiceCode;

   args = fscanf (infp, "%s %d %d %1s %d %1s",
                  teleServiceCode, &radioChannelRequested, &radioChannelUsed, 
                  chargedItem, &exchangeRateCode, callType);

   pBSU->basicService.serviceCode.u.teleServiceCode = teleServiceCode;

   /* build charge information list */

   ASN1CSeqOfList chargeInfoList (fos, pBSU->chargeInformationList);
   ASN1T_ChargeInformation* pChargeInfo;

   pChargeInfo = rtxMemAllocType (pctxt, ASN1T_ChargeInformation);
   asn1Init_ChargeInformation (pChargeInfo);
   pChargeInfo->m.chargedItemPresent = 1;
   pChargeInfo->m.exchangeRateCodePresent = 1;
   pChargeInfo->m.callTypeGroupPresent = 1;
   pChargeInfo->m.chargeDetailListPresent = 1;
   pChargeInfo->m.taxInformationPresent = 0;
   pChargeInfo->m.discountInformationPresent = 0;
   pChargeInfo->chargedItem = chargedItem;
   pChargeInfo->exchangeRateCode = exchangeRateCode;

   pChargeInfo->callTypeGroup.m.callTypeLevel1Present = 0;
   pChargeInfo->callTypeGroup.m.callTypeLevel2Present = 0;
   pChargeInfo->callTypeGroup.m.callTypeLevel3Present = 0;


   /* build charge detail list */
   ASN1CSeqOfList chargeDetailList (fos, pChargeInfo->chargeDetailList);
   ASN1T_ChargeDetail* pChargeDetail;

   while (args == 6) {
      /* when you get to the next call this call will read the       */
      /* first two characters of the next call line.  This will be   */
      /* the number before CALL DATA.  Again another short cut.      */

      args = fscanf (infp, "%2s %d %d %d %1s %1s\n", 
                     chargeType, &charge, &chargeableUnits, 
                     &chargedUnits, dayCategory, timeBand);

      if (args == 6) {
         pChargeDetail = rtxMemAllocType (pctxt, ASN1T_ChargeDetail);
         asn1Init_ChargeDetail (pChargeDetail);

         load_ChargeDetail (pctxt, pChargeDetail, chargeType, charge, 
                            chargeableUnits, chargedUnits, dayCategory, 
                            timeBand);

         chargeDetailList.append (pChargeDetail);
      }
   }

   chargeInfoList.append (pChargeInfo);
   bsuList.append (pBSU);

   cED.t = T_CallEventDetail_mobileOriginatedCall;
   cED.u.mobileOriginatedCall = pMOC;

   ASN1C_CallEventDetail cEDC (cED);
   fos << cEDC;

   return fos.getStatus ();
}

int load_ChargeDetail (OSCTXT* pctxt,
                       ASN1T_ChargeDetail *pChargeDetail, 
                       const char* chargeType,
                       ASN1T_Charge charge, 
                       ASN1T_ChargeableUnits chargeableUnits, 
                       ASN1T_ChargedUnits  chargedUnits,
                       const char* dayCategory, 
                       const char* timeBand)
{
   char* _chargeType;

   pChargeDetail->m.chargeTypePresent = 1;
   pChargeDetail->m.chargePresent = 1;
   pChargeDetail->m.chargeableUnitsPresent = 1;
   pChargeDetail->m.chargedUnitsPresent = 1;
   pChargeDetail->m.chargeDetailTimeStampPresent = 0;

   _chargeType = (char*)rtxMemAlloc (pctxt, strlen (chargeType) + 1);
   strcpy (_chargeType, chargeType);
   pChargeDetail->chargeType = _chargeType;
   pChargeDetail->charge = charge;
   pChargeDetail->chargeableUnits = chargeableUnits;
   pChargeDetail->chargedUnits = chargedUnits;

   return 0;
}

static int encode_AuditControlInfo (ASN1BEREncodeStream& fos)
{
   ASN1T_AuditControlInfo auditControlInfo;
   OSCTXT* pctxt = fos.getCtxtPtr();

   auditControlInfo.m.earliestCallTimeStampPresent = 1;
   auditControlInfo.m.latestCallTimeStampPresent = 1;
   auditControlInfo.m.totalTaxRefundPresent = 0;
   auditControlInfo.m.totalTaxValuePresent = 1;
   auditControlInfo.m.totalDiscountValuePresent = 1;
   auditControlInfo.m.totalDiscountRefundPresent = 0;
   auditControlInfo.m.totalAdvisedChargeValueListPresent = 0;
   auditControlInfo.m.callEventDetailsCountPresent = 1;
   auditControlInfo.m.operatorSpecInformationPresent = 0;

   setTimeStamp ("20000305203647", "-0500", 
                 &auditControlInfo.earliestCallTimeStamp);

   setTimeStamp ("20000305222654", "-0500", 
                 &auditControlInfo.latestCallTimeStamp);

   auditControlInfo.totalTaxValue = 63;
   auditControlInfo.totalDiscountValue = 0;
   auditControlInfo.callEventDetailsCount = 7;

   ASN1C_AuditControlInfo auditControlInfoC (auditControlInfo);
   fos << auditControlInfoC;

   return fos.getStatus ();
}
