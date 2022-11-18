/* writer.c : This sample program will construct and write a TAP3       */
/* batch file out in stages so that the entire batch does not need to   */
/* be encoded in memory..                                               */

#include <stdio.h>
#include <stdlib.h>
#include "TAP-0311.h"
#include "rtsrc/rtBCD.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxMemLeakCheck.h"

#define MAXMSGLEN 1024

static int encode_BatchControlInfo(OSCTXT* pctxt);
static int encode_AccountingInfo(OSCTXT* pctxt);
static int encode_NetworkInfo(OSCTXT* pctxt);
static int encode_MessageDescriptionInfo(OSCTXT* pctxt);
static int encode_CallDetailList(OSCTXT* pctxt);

static int load_MobileOriginatedCall
(OSCTXT* pctxt, MobileOriginatedCall *pMOC, FILE *infp);

static int load_ChargeDetail (OSCTXT* pctxt,
                       ChargeDetail *pChargeDetail, 
                       const char* chargeType,
                       Charge charge, 
                       ChargeableUnits chargeableUnits, 
                       ChargedUnits  chargedUnits,
                       const char* dayCategory, 
                       const char* timeBand);

static int encode_AuditControlInfo(OSCTXT* pctxt);

static int setBCDString 
(OSCTXT* pctxt, const char* str, OSDynOctStr64* poctstr)
{
   int len;
   OSOCTET* data;

   if (0 == poctstr) return RTERR_INVPARAM;
   poctstr->numocts = (strlen(str)/2) + 1;

   data = (OSOCTET*) rtxMemAlloc (pctxt, poctstr->numocts);
   if (0 == data) return RTERR_NOMEM;
   poctstr->data = data;

   len = rtStringToBCD (str, data, poctstr->numocts, TRUE);
   if (len > 0) poctstr->numocts = len;

   return len;
}

static void setTimeStamp (const char* localTimeStamp, 
                          const char* utcOffset, 
                          DateTimeLong* pTimeStamp)
{
   pTimeStamp->m.localTimeStampPresent = 1;
   pTimeStamp->m.utcTimeOffsetPresent = 1;
   pTimeStamp->localTimeStamp = localTimeStamp;
   pTimeStamp->utcTimeOffset = utcOffset;
}

static void setDateTime (const char* localTimeStamp, 
                         int utcOffset, DateTime* pTimeStamp)
{
   pTimeStamp->m.localTimeStampPresent = 1;
   pTimeStamp->m.utcTimeOffsetCodePresent = 1;
   pTimeStamp->localTimeStamp = localTimeStamp;
   pTimeStamp->utcTimeOffsetCode = utcOffset;
}

int main(int argc, char** argv)
{
   /* Run-time support variables */

   OSCTXT	ctxt;   
   int		i, stat;
   char		*filename = "message.dat";
   OSBOOL     trace = TRUE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) rtxSetGlobalDiag (1);
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Encode an initial indefinite length marker with the outer level   */
   /* tag ([APPLICATION 1]) for the TransferBatch structure.  Then      */
   /* write this tag and length to the output file.                     */

   /* Init context for stream first */

   if ((stat = berStrmInitContext (&ctxt)) != 0) {
      printf ("Initialization failed, status %d\n", stat);
      return -1;
   }

   stat = rtxStreamFileCreateWriter (&ctxt, filename);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   do {

      stat = berEncStrmTagAndIndefLen (&ctxt, TM_APPL|TM_CONS|1);
      if (stat != 0) break;

      /* Now sequentially encode and write each of the message components  */
      /* in the SEQUENCE to the output file until the 'callEventDetails'   */
      /* element is encountered.  In this sample each of the message       */
      /* component records is hard-coded..                                 */

      /* After each encode operation, free up everything as if you are     */
      /* starting over.  The data has already been written to the output   */
      /* file. The final output file will have all the call records        */
      /* encoded for the indefinite length message.                        */

      stat = encode_BatchControlInfo (&ctxt);
      if (stat != 0) break;

      stat = encode_AccountingInfo (&ctxt);
      if (stat != 0) break;

      stat = encode_NetworkInfo (&ctxt);
      if (stat != 0) break;

      stat = encode_MessageDescriptionInfo (&ctxt);
      if (stat != 0) break;

      /* The call detail list is handled differently.  It is possible to   */
      /* have a very large number of these records which would make        */
      /* encoding the whole list in memory difficult.  The solution is to  */
      /* drop another indefinite tag/length into the file and then encode  */
      /* and write each call detail record.  See this routine for further  */
      /* details..                                                         */

      stat = encode_CallDetailList (&ctxt);
      if (stat != 0) break;

      stat = encode_AuditControlInfo (&ctxt);
      if (stat != 0) break;

      stat = berEncStrmEOC (&ctxt);
      if (stat != 0) break;

   } while (0);
   
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* dump the data */
   if (trace) {
      FILE* fp;
      size_t flen;

      rtxStreamClose (&ctxt);
   
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
   }

   berStrmFreeContext (&ctxt);
   return stat;
}

static int encode_BatchControlInfo(OSCTXT* pctxt)
{	
   BatchControlInfo bci;

   asn1Init_BatchControlInfo (&bci);
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

   bci.sender = "USA27";
   bci.recipient = "DEUD2";
   bci.fileSequenceNumber = "00272";

   setTimeStamp ("20000307080756", "-0500", &bci.fileCreationTimeStamp);
   setTimeStamp ("20000307080751", "-0500", &bci.transferCutOffTimeStamp);
   setTimeStamp ("20000307080756", "-0500", &bci.fileAvailableTimeStamp);

   bci.specificationVersionNumber = 3;
   bci.releaseVersionNumber = 11;

   return asn1BSE_BatchControlInfo(pctxt, &bci, ASN1EXPL);
}

static int encode_AccountingInfo(OSCTXT* pctxt)
{
   Taxation* pTaxation;
   CurrencyConversion* pCurrConv;
   AccountingInfo accountingInfo;

   asn1Init_AccountingInfo (&accountingInfo);

   accountingInfo.m.taxationPresent = 1;
   accountingInfo.m.discountingPresent = 0;
   accountingInfo.m.localCurrencyPresent = 1;
   accountingInfo.m.tapCurrencyPresent = 1;
   accountingInfo.m.currencyConversionInfoPresent = 1;
   accountingInfo.m.tapDecimalPlacesPresent = 1;

   /* Populate tax rate list */

   rtxDListInit (&accountingInfo.taxation);

   pTaxation = rtxMemAllocType (pctxt, Taxation);
   asn1Init_Taxation (pTaxation);
   pTaxation->m.taxCodePresent = 1;
   pTaxation->m.taxTypePresent = 1;
   pTaxation->m.taxRatePresent = 1;
   pTaxation->taxCode = 0;
   pTaxation->taxType = "03";
   pTaxation->taxRate = "0225343";
   rtxDListAppend (pctxt, &accountingInfo.taxation, pTaxation);

   pTaxation = rtxMemAllocType (pctxt, Taxation);
   asn1Init_Taxation (pTaxation);
   pTaxation->m.taxCodePresent = 1;
   pTaxation->m.taxTypePresent = 1;
   pTaxation->m.taxRatePresent = 1;
   pTaxation->taxCode = 1;
   pTaxation->taxType = "02";
   pTaxation->taxRate = "0600343";
   rtxDListAppend (pctxt, &accountingInfo.taxation, pTaxation);
	
   /* Populate currency fields */

   accountingInfo.localCurrency = "USD";
   accountingInfo.tapCurrency = "USD";
	
   /* Populate currency conversion list */

   rtxDListInit (&accountingInfo.currencyConversionInfo);

   pCurrConv = rtxMemAllocType (pctxt, CurrencyConversion);
   asn1Init_CurrencyConversion (pCurrConv);
   pCurrConv->m.exchangeRateCodePresent = 1;
   pCurrConv->m.numberOfDecimalPlacesPresent = 1;
   pCurrConv->m.exchangeRatePresent = 1;
   pCurrConv->exchangeRateCode = 0;
   pCurrConv->numberOfDecimalPlaces = 6;
   pCurrConv->exchangeRate = 1000000;
   rtxDListAppend (pctxt, &accountingInfo.currencyConversionInfo, pCurrConv);

   accountingInfo.tapDecimalPlaces = 2;

   return asn1BSE_AccountingInfo(pctxt, &accountingInfo, ASN1EXPL);
}

static int encode_NetworkInfo (OSCTXT* pctxt)
{
   RecEntityInformation* pRecEntity;
   UtcTimeOffsetInfo* pUtcTimeOffset;
   NetworkInfo networkInfo;

   asn1Init_NetworkInfo (&networkInfo);
   networkInfo.m.utcTimeOffsetInfoPresent = 1;
   networkInfo.m.recEntityInfoPresent = 1;

   rtxDListInit (&networkInfo.utcTimeOffsetInfo);

   pUtcTimeOffset = rtxMemAllocType (pctxt, UtcTimeOffsetInfo);
   asn1Init_UtcTimeOffsetInfo (pUtcTimeOffset);
   pUtcTimeOffset->m.utcTimeOffsetCodePresent = 1;
   pUtcTimeOffset->m.utcTimeOffsetPresent = 1;
   pUtcTimeOffset->utcTimeOffsetCode = 0;
   pUtcTimeOffset->utcTimeOffset = "-0500";
   rtxDListAppend (pctxt, &networkInfo.utcTimeOffsetInfo, pUtcTimeOffset);

   rtxDListInit (&networkInfo.recEntityInfo);

   pRecEntity = rtxMemAllocType (pctxt, RecEntityInformation);
   asn1Init_RecEntityInformation (pRecEntity);
   pRecEntity->m.recEntityCodePresent = 1;
   pRecEntity->m.recEntityTypePresent = 1;
   pRecEntity->m.recEntityIdPresent = 1;
   pRecEntity->recEntityCode = 0;
   pRecEntity->recEntityType = 1;
   pRecEntity->recEntityId = "aRecEntityId";

   rtxDListAppend (pctxt, &networkInfo.recEntityInfo, pRecEntity);

   pRecEntity = rtxMemAllocType (pctxt, RecEntityInformation);
   asn1Init_RecEntityInformation (pRecEntity);
   pRecEntity->m.recEntityCodePresent = 1;
   pRecEntity->m.recEntityTypePresent = 1;
   pRecEntity->m.recEntityIdPresent = 1;
   pRecEntity->recEntityCode = 1;
   pRecEntity->recEntityType = 1;
   pRecEntity->recEntityId = "aRecEntityId";

   rtxDListAppend (pctxt, &networkInfo.recEntityInfo, pRecEntity);

   pRecEntity = rtxMemAllocType (pctxt, RecEntityInformation);
   asn1Init_RecEntityInformation (pRecEntity);
   pRecEntity->m.recEntityCodePresent = 1;
   pRecEntity->m.recEntityTypePresent = 1;
   pRecEntity->m.recEntityIdPresent = 1;
   pRecEntity->recEntityCode = 2;
   pRecEntity->recEntityType = 1;
   pRecEntity->recEntityId = "aRecEntityId";

   rtxDListAppend (pctxt, &networkInfo.recEntityInfo, pRecEntity);

   return asn1BSE_NetworkInfo (pctxt, &networkInfo, ASN1EXPL);
}

static int encode_MessageDescriptionInfo (OSCTXT* pctxt)
{
   MessageDescriptionInformation* pMsgDescr;
   MessageDescriptionInfoList messageDescriptionInfo;
	
   rtxDListInit (&messageDescriptionInfo);
   pMsgDescr = rtxMemAllocType (pctxt, MessageDescriptionInformation);
   asn1Init_MessageDescriptionInformation (pMsgDescr);
   pMsgDescr->m.messageDescriptionCodePresent = 1;
   pMsgDescr->m.messageDescriptionPresent = 1;

   pMsgDescr->messageDescriptionCode = 1;
   pMsgDescr->messageDescription = "Description";

   rtxDListAppend (pctxt, &messageDescriptionInfo, pMsgDescr);

   return asn1BSE_MessageDescriptionInfoList
      (pctxt, &messageDescriptionInfo, ASN1EXPL);
}

/* Encode call detail list.  This part of the sample gets its data from */
/* a data input file.  This could just as easily be a database or other */
/* storage device containing large numbers of call detail records.      */
/* The records are sequentially read and encoded and written to the     */
/* output file.                                                         */

static int encode_CallDetailList(OSCTXT* pctxt)
{
   const char* infilename = "input.dat";
   FILE*   inFile;
   CallEventDetail cED;
   MobileOriginatedCall mOC;
   int stat;
   char buffer[100] = {0};

   /* First, encode and write an indefinite tag/length pair for the     */
   /* 'CallEventDetailList' production ([APPLICATION 3]).  The          */
   /* generated structure for this production will not be used.         */
   /* Instead, each of the CallEventDetail records will be individually */
   /* encoded and then written to the output file followed by an EOC    */
   /* marker to terminate the list.                                     */

   stat = berEncStrmTagAndIndefLen (pctxt, TM_APPL|TM_CONS|3);
   if (stat != 0) return stat;
   
   cED.t = T_CallEventDetail_mobileOriginatedCall;
   cED.u.mobileOriginatedCall = &mOC;	

   /* open input file */
   if (!(inFile = fopen (infilename, "rb"))) {
      printf ("Error opening %s for read access\n", infilename);
      return -1;
   };

   /* This is the loop to read and encode call detail records */

   while (!feof(inFile)) {
      fgets (buffer, sizeof(buffer), inFile);

      if (strncmp (buffer, "CALL DATA", 9) == 0) {
         load_MobileOriginatedCall (pctxt, &mOC, inFile);

         stat = asn1BSE_CallEventDetail(pctxt, &cED, ASN1EXPL);

         if (stat != 0) {
            rtxErrPrint (pctxt); 
            exit (6);
         }
      }

      memset (buffer, 0, sizeof(buffer));
   }

   stat = berEncStrmEOC (pctxt);
   if (stat != 0) return stat;

   fclose (inFile);
	
   return 0;
}	

int load_MobileOriginatedCall (OSCTXT* pctxt, 
                               MobileOriginatedCall *pMOC, 
                               FILE *infp)
{	
   int args = 0;
   char *calledNumber = (char *) rtxMemAlloc( pctxt, 20 );
   char *calledPlace = (char *) rtxMemAlloc( pctxt, 20 );
   char *localTimeStamp = (char *) rtxMemAlloc( pctxt, 20 );
   int timeOffset;
   int totalCall = 0;
   int recEntityCode = 0, locationArea = 0, cellId = 0;
   char *servingBid = (char *) rtxMemAlloc( pctxt, 20 );
   char *locationDescription = (char *) rtxMemAlloc( pctxt, 40 );
   char *teleServiceCode = (char *) rtxMemAlloc( pctxt, 3 );
   int radioChannelRequested = 0, radioChannelUsed = 0, exchangeRateCode = 0;
   char *chargedItem = (char *) rtxMemAlloc( pctxt, 2);
   char *callType = (char *) rtxMemAlloc( pctxt, 2);
   char *chargeType = (char *) rtxMemAlloc( pctxt, 3 ); 
   int  charge;
   int  chargeableUnits;
   int  chargedUnits;
   char *dayCategory = (char *) rtxMemAlloc( pctxt, 2 );
   char *timeBand = (char *) rtxMemAlloc( pctxt, 2 );
   OSOCTET *imsiData = (OSOCTET *) rtxMemAlloc( pctxt, 50 ),
             *imeiData = (OSOCTET *) rtxMemAlloc( pctxt, 50 ), 
             *msisdnData = (OSOCTET *) rtxMemAlloc( pctxt, 50 );
   BasicServiceUsed* pBSU;
   ChargeInformation* pChargeInfo;
   ChargeDetail* pChargeDetail;

   memset (pMOC, 0, sizeof(MobileOriginatedCall));

   /* This procedure expects the call data to be layed out in three     */
   /* lines like the input file provided.  It is not set up to handle   */
   /* any format and is not truely dynamic in nature                    */

   pMOC->m.basicCallInformationPresent = 1;
   pMOC->m.locationInformationPresent = 1;
   pMOC->m.equipmentIdentifierPresent = 1;
   pMOC->m.basicServiceUsedListPresent = 1;
   pMOC->m.supplServiceCodePresent = 0;
   pMOC->m.thirdPartyInformationPresent = 0;
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
      rtxMemAllocType (pctxt, SimChargeableSubscriber);
   asn1Init_SimChargeableSubscriber (pMOC->basicCallInformation.chargeableSubscriber.u.simChargeableSubscriber);

   pMOC->basicCallInformation.chargeableSubscriber.u.
      simChargeableSubscriber->m.imsiPresent = 1;

   pMOC->basicCallInformation.chargeableSubscriber.u.
      simChargeableSubscriber->m.msisdnPresent = 1;

   pMOC->basicCallInformation.chargeableSubscriber.u.
      simChargeableSubscriber->imsi.numocts =
      rtStringToBCD ("250123000113003", imsiData, 50, TRUE); 

   pMOC->basicCallInformation.chargeableSubscriber.u.
      simChargeableSubscriber->imsi.data = imsiData;

   pMOC->basicCallInformation.chargeableSubscriber.u.
      simChargeableSubscriber->msisdn.numocts =
      rtStringToBCD ("79024113000", msisdnData, 50, TRUE); 

   pMOC->basicCallInformation.chargeableSubscriber.u.
      simChargeableSubscriber->msisdn.data = msisdnData;

   /* destination */
   pMOC->basicCallInformation.destination.m.calledNumberPresent = 1;
   pMOC->basicCallInformation.destination.m.dialledDigitsPresent = 1;
   pMOC->basicCallInformation.destination.m.calledPlacePresent = 1;
   pMOC->basicCallInformation.destination.m.calledRegionPresent = 0;

   args = fscanf (infp, "%s %s %s %d %d", 
                  calledNumber, calledPlace, localTimeStamp, 
                  &timeOffset, &totalCall);
	
   pMOC->basicCallInformation.destination.dialledDigits = "1100254876";

   setBCDString (pctxt, calledNumber, 
                 &pMOC->basicCallInformation.destination.calledNumber);

   pMOC->basicCallInformation.destination.calledPlace = calledPlace;

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

   pMOC->locationInformation.geographicalLocation.
      servingLocationDescription = locationDescription;

   /* equipment information */
   pMOC->equipmentIdentifier.t = T_ImeiOrEsn_imei;
   pMOC->equipmentIdentifier.u.imei = rtxMemAllocType (pctxt, Imei);

   pMOC->equipmentIdentifier.u.imei -> numocts =
      rtStringToBCD ("49013810114356", imeiData, 50, TRUE);

   pMOC->equipmentIdentifier.u.imei -> data = imeiData;

   /* basic service used list */

   rtxDListInit (&pMOC->basicServiceUsedList);
   pBSU = rtxMemAllocType (pctxt, BasicServiceUsed);
   asn1Init_BasicServiceUsed (pBSU);
   pBSU->m.basicServicePresent = 1;
   pBSU->m.chargingTimeStampPresent = 0;
   pBSU->m.chargeInformationListPresent = 1;

   pBSU->basicService.m.serviceCodePresent = 1;
   pBSU->basicService.m.transparencyIndicatorPresent = 0;
   pBSU->basicService.m.fnurPresent = 0;
   pBSU->basicService.m.userProtocolIndicatorPresent = 0;
   pBSU->basicService.m.guaranteedBitRatePresent = 0;
   pBSU->basicService.m.maximumBitRatePresent = 0;

   pBSU->basicService.serviceCode.t = 
      T_BasicServiceCode_teleServiceCode;

   args = fscanf (infp, "%s %d %d %1s %d %1s",
                  teleServiceCode, &radioChannelRequested, &radioChannelUsed, 
                  chargedItem, &exchangeRateCode, callType);

   pBSU->basicService.serviceCode.u.teleServiceCode = teleServiceCode;

   /* build charge information list */

   rtxDListInit (&pBSU->chargeInformationList);
   pChargeInfo = rtxMemAllocType (pctxt, ChargeInformation);
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
   rtxDListInit (&pChargeInfo->chargeDetailList);

   while (args == 6) {

      /* when you get to the next call this call will read the          */
      /* first two characters of the next call line.  This will be      */
      /* the number before CALL DATA.                                   */

      args = fscanf (infp, "%2s %d %d %d %1s %1s\n", 
                     chargeType, &charge, &chargeableUnits, 
                     &chargedUnits, dayCategory, timeBand);

      if (args == 6) {
         pChargeDetail = rtxMemAllocType (pctxt, ChargeDetail);
         asn1Init_ChargeDetail (pChargeDetail);

         load_ChargeDetail (pctxt, pChargeDetail, chargeType, charge, 
                            chargeableUnits, chargedUnits, dayCategory, 
                            timeBand);

         rtxDListAppend (pctxt, &pChargeInfo->chargeDetailList, pChargeDetail);
      };
   };

   rtxDListAppend (pctxt, &pBSU->chargeInformationList, pChargeInfo);
   rtxDListAppend (pctxt, &pMOC->basicServiceUsedList, pBSU);

   return 0;
}

int load_ChargeDetail (OSCTXT* pctxt,
                       ChargeDetail *pChargeDetail, 
                       const char* chargeType,
                       Charge charge, 
                       ChargeableUnits chargeableUnits, 
                       ChargedUnits  chargedUnits,
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

static int encode_AuditControlInfo (OSCTXT* pctxt)
{
   AuditControlInfo auditControlInfo;

   asn1Init_AuditControlInfo (&auditControlInfo);

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
	
   return asn1BSE_AuditControlInfo (pctxt, &auditControlInfo, ASN1EXPL);
}
