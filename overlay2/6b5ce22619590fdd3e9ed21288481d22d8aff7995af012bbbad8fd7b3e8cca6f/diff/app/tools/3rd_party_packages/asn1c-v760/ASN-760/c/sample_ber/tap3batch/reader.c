/* This reader program reads a TAP3 large batch file in stages.  It     */
/* demonstrates the use of ASN1C for reading and processing large       */
/* files.                                                               */
/*                                                                      */
/* The structure of this file is expected to be that of a TAP3          */
/* TransferBatch file.  It is expected that this file will have         */
/* small, fixed length components for each of the single records and    */
/* have a large number of CallEventDetail records.  Each                */
/* CallEventDetail record will be sequentially read and processed from  */
/* the file.                                                            */

#include <stdio.h>
#include <stdlib.h>
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxDiag.h"
#include "TAP-0311.h"

static int decodeCallEventDetailList (OSCTXT* pctxt, int len);

static int decodeMessageComponent (OSCTXT* pctxt, ASN1TAG tag, int len);

static OSBOOL gTrace = TRUE;

int main (int argc, char** argv)
{
   OSCTXT	ctxt;   
   ASN1TAG	tag;
   int		i, len, stat;
   const char*  filename = "message.dat";
   ASN1CCB      ccb;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) rtxSetGlobalDiag (1);
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) { gTrace = FALSE; }
         else {
            printf ("usage: reader [ -v ] [ -i <filename> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context for stream first */

   if ((stat = berStrmInitContext (&ctxt)) != 0) {
      printf ("Initialization failed, status %d\n", stat);
      return -1;
   }

   /* Open the input stream to read data */

   stat = rtxStreamFileCreateReader (&ctxt, filename);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   /*
   // It is possible to decode whole message by one call to 
   // asn1BSD_DataInterChange (see below).

   stat = asn1BSD_DataInterChange (&ctxt, &dataInterChange, ASN1EXPL, 0);
   if (stat == 0) {
      if (gTrace) {
         asn1Print_DataInterChange ("DataInterChange", 
                                     &dataInterChange);
      }
   }
   else {
      printf ("Decode of message failed\n");
      rtxErrPrint (&ctxt.errInfo); 
   }
   */

   /* Read first tag/length pair and verify tag is TransferBatch tag */

   stat = berDecStrmTagAndLen (&ctxt, &tag, &len);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   if (tag != (TM_APPL|TM_CONS|1)) {
      printf ("Unexpected tag %x encountered (expecting APPL 1)\n", tag);
      return -1;
   }

   /* Loop to read and process each record in the batch file */

   ccb.len = len;
   ccb.bytes = OSRTSTREAM_BYTEINDEX (&ctxt);

   while (0 == stat && !BS_CHKEND (&ctxt, &ccb)) {
      stat = berDecStrmTagAndLen (&ctxt, &tag, &len);
      if (stat != 0) {
         rtxErrPrint (&ctxt);
         break;
      }

      switch (tag) {
      case (TM_APPL|TM_CONS|3):
         stat = decodeCallEventDetailList (&ctxt, len);
         break;

      case (TM_APPL|TM_CONS|4):
      case (TM_APPL|TM_CONS|5):
      case (TM_APPL|TM_CONS|6):
      case (TM_APPL|TM_CONS|7):
      case (TM_APPL|TM_CONS|8):
      case (TM_APPL|TM_CONS|15):
         stat = decodeMessageComponent (&ctxt, tag, len);
         break;
      }
   }

   berStrmFreeContext (&ctxt);
   return stat;
}


/* Decode call event detail list */
static int decodeCallEventDetailList (OSCTXT* pctxt, int length)
{
   int stat = 0;
   CallEventDetail callEventDetail;
   ASN1CCB ccb;

   ccb.len = length;
   ccb.bytes = OSRTSTREAM_BYTEINDEX (pctxt);

   while (!BS_CHKEND (pctxt, &ccb))
   {
      stat = asn1BSD_CallEventDetail (pctxt, 
         &callEventDetail, ASN1EXPL, length);

      if (stat == 0) {
         if (gTrace) {
            printf ("CallEventDetail record:\n");
            asn1Print_CallEventDetail ("CallEventDetail", &callEventDetail);
            printf ("\n");
            printf ("******************************************************\n");
            printf ("\n");
         }
      }
      else {
         printf ("Decode of CallEventDetail failed\n");
         printf ("stat = %d\n", stat);
         rtxErrPrint (pctxt); 
         break;
      }

      rtxMemReset (pctxt);
   }

   if (ccb.len == ASN_K_INDEFLEN) {
      if (berDecStrmMatchEOC (pctxt) != 0)
         return LOG_RTERR (pctxt, ASN_E_INVLEN);
   }
   return (stat);
}

/* Decode single message component record */

static int decodeMessageComponent (OSCTXT* pctxt, ASN1TAG tag, int len)
{
   BatchControlInfo     batchControlInfo;
   AccountingInfo       accountingInfo;
   NetworkInfo          networkInfo;
   MessageDescriptionInfoList messageDescriptionInfo;
   AuditControlInfo     auditControlInfo;
   int                  stat;

   switch (tag) {
   case (TM_APPL|TM_CONS|4):
      stat = asn1BSD_BatchControlInfo (pctxt, &batchControlInfo, ASN1IMPL, len);
      if (stat == 0) {
         if (gTrace) {
            printf ("BatchControlInfo record:\n");
            asn1Print_BatchControlInfo ("BatchControlInfo", 
                                        &batchControlInfo);
         }
      }
      break;

   case (TM_APPL|TM_CONS|5):
      stat = asn1BSD_AccountingInfo (pctxt, &accountingInfo, ASN1IMPL, len);
      if (stat == 0) {
         if (gTrace) {
            printf ("AccountingInfo record:\n");
            asn1Print_AccountingInfo ("AccountingInfo", &accountingInfo);
         }
      }
      break;

   case (TM_APPL|TM_CONS|6):
      stat = asn1BSD_NetworkInfo (pctxt, &networkInfo, ASN1IMPL, len);
      if (stat == 0) {
         if (gTrace) {
            printf ("NetworkInfo record:\n");
            asn1Print_NetworkInfo ("NetworkInfo", &networkInfo);
         }
      }
      break;

   case (TM_APPL|TM_CONS|8):
      stat = asn1BSD_MessageDescriptionInfoList 
         (pctxt, &messageDescriptionInfo, ASN1IMPL, len);
      if (stat == 0) {
         if (gTrace) {
            printf ("MessageDescriptionInfoList record:\n");
            asn1Print_MessageDescriptionInfoList 
               ("MessageDescriptionInfoList", &messageDescriptionInfo);
         }
      }
      break;

   case (TM_APPL|TM_CONS|15):
      stat = asn1BSD_AuditControlInfo (pctxt, &auditControlInfo, ASN1IMPL, len);
      if (stat == 0) {
         if (gTrace) {
            printf ("AuditControlInfo record:\n");
            asn1Print_AuditControlInfo ("AuditControlInfo", 
                                        &auditControlInfo);
         }
      }
      break;

   default:
      printf ("invalid option\n");
   }

   if (stat == 0) {
      if (gTrace) {
         printf ("\n");
         printf ("******************************************************\n");
         printf ("\n");
      }
   }
   else {
      printf ("Decode of message component failed\n");
      rtxErrPrint (pctxt); 
   }

   if (len == ASN_K_INDEFLEN) {
      if (berDecStrmMatchEOC (pctxt) != 0)
         return LOG_RTERR (pctxt, ASN_E_INVLEN);
   }

   return stat;
}
