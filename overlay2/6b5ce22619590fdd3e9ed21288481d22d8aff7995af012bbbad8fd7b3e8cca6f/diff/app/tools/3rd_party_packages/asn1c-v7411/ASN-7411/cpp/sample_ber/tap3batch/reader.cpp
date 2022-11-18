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
#include "TAP-0311.h"
#include "rtbersrc/ASN1BERDecodeStream.h"
#include "rtxsrc/OSRTFileInputStream.h"
#include "rtxsrc/rtxMemLeakCheck.h"

static void decodeCallEventDetailList (ASN1BERDecodeStream& fis, int len);

static void decodeMessageComponent 
(ASN1BERDecodeStream& fis, ASN1TAG tag, int len);

static OSBOOL gTrace = TRUE;

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   ASN1TAG	tag;
   int		i, len;
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

   ASN1BERDecodeStream fis (new OSRTFileInputStream (filename));
   if (fis.getStatus () != 0) { fis.printErrorInfo (); return -1; }

   /* Read first tag/length pair and verify tag is TransferBatch tag */

   if (fis.decodeTagAndLen (tag, len) != 0) {
      fis.printErrorInfo (); 
      return -1;
   }

   if (tag != (TM_APPL|TM_CONS|1)) {
      printf ("Unexpected tag %x encountered (expecting APPL 1)\n", tag);
      return -1;
   }

   /* Loop to read and process each record in the batch file */

   ccb.len = len;
   ccb.bytes = fis.byteIndex ();

   while (!fis.chkend (ccb)) {
      fis.mark (32);
      fis.decodeTagAndLen (tag, len);

      if (fis.getStatus () != 0) { fis.printErrorInfo (); return -1; }

      switch (tag) {
      case (TM_APPL|TM_CONS|3):
         decodeCallEventDetailList (fis, len);
         break;

      case (TM_APPL|TM_CONS|4):
      case (TM_APPL|TM_CONS|5):
      case (TM_APPL|TM_CONS|6):
      case (TM_APPL|TM_CONS|7):
      case (TM_APPL|TM_CONS|8):
      case (TM_APPL|TM_CONS|15):
         decodeMessageComponent (fis, tag, len);
         break;
      }
   }

   if(ccb.len == ASN_K_INDEFLEN) {/* check end of indefinite length */
      fis.decodeEoc ();
   }
   if (fis.getStatus () != 0) { fis.printErrorInfo (); return -1; }
   return 0;
}


/* Decode call event detail list */
static void decodeCallEventDetailList (ASN1BERDecodeStream& fis, int length)
{
   int stat = 0;
   ASN1CCB ccb;

   ccb.len = length;
   ccb.bytes = fis.byteIndex ();

   while (!fis.chkend (ccb)) {
      ASN1T_CallEventDetail callEventDetail;
      ASN1C_CallEventDetail cedC (callEventDetail);

      fis >> cedC;

      if (gTrace) {
         printf ("CallEventDetail record:\n");
         cedC.Print ("CallEventDetail");
         printf ("\n");
         printf ("******************************************************\n");
         printf ("\n");
      }
   }

   if(ccb.len == ASN_K_INDEFLEN) {/* check end of indefinite length */
      fis.decodeEoc ();
   }
}

/* Decode single message component record */

static void decodeMessageComponent (ASN1BERDecodeStream& fis, 
                                    ASN1TAG tag, int len)
{
   ASN1T_BatchControlInfo     batchControlInfo;
   ASN1T_AccountingInfo       accountingInfo;
   ASN1T_NetworkInfo          networkInfo;
   ASN1T_MessageDescriptionInfoList messageDescriptionInfo;
   ASN1T_AuditControlInfo     auditControlInfo;

   fis.reset ();
   switch (tag) {
   case (TM_APPL|TM_CONS|4): {
      ASN1C_BatchControlInfo batchControlInfoC (batchControlInfo);
      fis >> batchControlInfoC;
      if (gTrace) {
         printf ("BatchControlInfo record:\n");
         batchControlInfoC.Print ("BatchControlInfo");
      }
      break;
   }
   case (TM_APPL|TM_CONS|5): {
      ASN1C_AccountingInfo accountingInfoC (accountingInfo);
      fis >> accountingInfoC;
      if (gTrace) {
         printf ("AccountingInfo record:\n");
         accountingInfoC.Print ("AccountingInfo");
      }
      break;
   }
   case (TM_APPL|TM_CONS|6): {
      ASN1C_NetworkInfo networkInfoC (networkInfo);
      fis >> networkInfoC;
      if (gTrace) {
         printf ("NetworkInfo record:\n");
         networkInfoC.Print ("NetworkInfo");
      }
      break;
   }
/*   case (TM_APPL|TM_CONS|7): {
      ASN1C_VasInfoList vasInfoC (vasInfo);
      fis >> vasInfoC;
      if (gTrace) {
         printf ("VasInfoList record:\n");
         vasInfoC.Print ("VasInfoList");
      }
      break;
   } */
   case (TM_APPL|TM_CONS|8): {
      ASN1C_MessageDescriptionInfoList messageDescriptionInfoC (messageDescriptionInfo);
      fis >> messageDescriptionInfoC;
      if (gTrace) {
         printf ("MessageDescriptionInfoList record:\n");
         messageDescriptionInfoC.Print ("MessageDescriptionInfoList");
      }
      break;
   }
   case (TM_APPL|TM_CONS|15): {
      ASN1C_AuditControlInfo auditControlInfoC (auditControlInfo);
      fis >> auditControlInfoC;
      if (gTrace) {
         printf ("AuditControlInfo record:\n");
         auditControlInfoC.Print ("AuditControlInfo");
      }
      break;
   }
   default:
      printf ("invalid option\n");
   }

   if (gTrace) {
      printf ("\n");
      printf ("******************************************************\n");
      printf ("\n");
   }
}
