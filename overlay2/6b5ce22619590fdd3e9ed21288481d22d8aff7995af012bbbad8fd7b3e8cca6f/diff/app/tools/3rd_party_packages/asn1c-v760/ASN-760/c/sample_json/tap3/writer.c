/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.0A, Date: 22-Jun-2006.
 */
#include "TAP-0311.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxsrc/rtxStreamFile.h"

#include <stdio.h>
#include <stdlib.h>

static void setDateTime (DateTimeLong* pDateTime, 
                         const char* localTimeStamp, 
                         const char* utcTimeOffset)
{
   pDateTime->m.localTimeStampPresent = 1;
   pDateTime->m.utcTimeOffsetPresent = 1;
   pDateTime->localTimeStamp = localTimeStamp;
   pDateTime->utcTimeOffset = utcTimeOffset;
}

int main (int argc, char** argv)
{
   DataInterChange msgData;
   Notification notification;
   OSCTXT       ctxt;
   OSBOOL       trace = TRUE, verbose = FALSE;
   const char*  filename = "message.json";
   int          i, stat;

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context */

   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   stat = rtxStreamFileCreateWriter (&ctxt, filename);

   if (stat != 0) {
      printf ("Unable to open file %s for writing.\n", filename);
      rtFreeContext (&ctxt);
      return stat;
   }

   /* Populate structure of generated type */

   memset (&msgData, 0, sizeof(msgData));
   memset (&notification, 0, sizeof(notification));

   notification.m.senderPresent = 1;
   notification.m.recipientPresent = 1;
   notification.m.fileSequenceNumberPresent = 1;
   notification.m.fileCreationTimeStampPresent = 1;
   notification.m.fileAvailableTimeStampPresent = 1;
   notification.m.transferCutOffTimeStampPresent = 1;
   notification.m.specificationVersionNumberPresent = 1;
   notification.m.releaseVersionNumberPresent = 1;
   notification.m.operatorSpecInformationPresent = 1;

   notification.sender = "ABC42300";
   notification.recipient = "XYZ77701";
   notification.fileSequenceNumber = "0077223";

   setDateTime (&notification.fileCreationTimeStamp, 
                "032200153000", "0400");

   setDateTime (&notification.fileAvailableTimeStamp, 
                "041500222500", "0400");

   setDateTime (&notification.transferCutOffTimeStamp, 
                "060100000000", "0400");

   notification.specificationVersionNumber = 10;
   notification.releaseVersionNumber = 9;

   notification.m.operatorSpecInformationPresent = 1;

   rtxDListAppend 
      (&ctxt, &notification.operatorSpecInformation, 
       "OperatorSpecInformation");

   msgData.t = T_DataInterChange_notification;
   msgData.u.notification = &notification;

   /* Encode */

   stat = asn1JsonEnc_DataInterChange (&ctxt, &msgData);

   if (stat == 0) {
      if (trace) {
         printf ("Message Encoded successfully.\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return (stat);
   }

   /* Write the encoded message out to the output file */

   rtFreeContext (&ctxt);

   return 0;
}