/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "TAP-0311.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxMemLeakCheck.h"

static void setTimeStamp (const char* localTimeStamp, 
                          const char* utcOffset, 
                          DateTimeLong* pTimeStamp);

int main (int argc, char** argv)
{
   /* Compiler generated TAP3 structures */

   DataInterChange dataInterChange;
   Notification notification;
   
   /* Run-time support variables */

   OSCTXT	ctxt;
   int		i, stat;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
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

   if ((stat = berStrmInitContext (&ctxt)) != 0) {
      printf ("Initialization failed, status %d\n", stat);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   stat = rtxStreamFileCreateWriter (&ctxt, filename);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Populate structure of generated type */

   asn1Init_Notification (&notification);

   notification.m.senderPresent = 1;
   notification.sender = "ABC42300";

   notification.m.recipientPresent = 1;
   notification.recipient = "XYZ77701";

   notification.m.fileSequenceNumberPresent = 1;
   notification.fileSequenceNumber = "0077223";

   notification.m.fileCreationTimeStampPresent = 1;
   setTimeStamp ("032200153000", "0400", 
                 &notification.fileCreationTimeStamp);

   notification.m.fileAvailableTimeStampPresent = 1;
   setTimeStamp ("041500222500", "0400", 
                 &notification.fileAvailableTimeStamp);

   notification.m.transferCutOffTimeStampPresent = 1;
   setTimeStamp ("060100000000", "0400", 
                 &notification.transferCutOffTimeStamp);

   notification.m.specificationVersionNumberPresent = 1;
   notification.specificationVersionNumber = 3;

   notification.m.releaseVersionNumberPresent = 1;
   notification.releaseVersionNumber = 11;

   notification.m.operatorSpecInformationPresent = 1;

   rtxDListAppend 
      (&ctxt, &notification.operatorSpecInformation, 
       "OperatorSpecInformation");

   dataInterChange.t = T_DataInterChange_notification;
   dataInterChange.u.notification = &notification;

   /* Encode */

   stat = asn1BSE_DataInterChange (&ctxt, &dataInterChange, ASN1EXPL);

   rtxStreamClose (&ctxt);

   if (stat != 0) {
      rtxErrPrint (&ctxt);
      berStrmFreeContext (&ctxt);
      return stat;
   }

   /* dump the data */
   if (trace) {
      OSOCTET* msgptr;
      size_t flen;

      stat = rtxFileReadBinary (&ctxt, filename, &msgptr, &flen);

      if (stat == 0) {
         if (XU_DUMP (msgptr) != 0) 
            printf ("dump of ASN.1 message failed.");
      }
      else {
         printf ("read encoded TAP3 batch file failed.\n");
         rtxErrPrint (&ctxt);
      }
   }

   berStrmFreeContext (&ctxt);

   return stat;
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
