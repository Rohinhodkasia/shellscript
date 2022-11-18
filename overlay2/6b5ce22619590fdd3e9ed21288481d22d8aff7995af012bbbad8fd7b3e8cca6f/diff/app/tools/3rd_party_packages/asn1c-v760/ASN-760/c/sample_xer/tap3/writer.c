/* This test driver program encodes a data record and writes the encoded 
   result to an output file. */

#include <stdio.h>
#include <stdlib.h>
#include "TAP-0311.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 10240

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
   OSOCTET    msgbuf[MAXMSGLEN];
   int          i, stat;
   const char* filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE, cxer = FALSE;
   OSCTXT     ctxt;
   FILE*        fp;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-cxer")) cxer = TRUE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -cxer          use canonical XER rules (CXER)\n");
            printf ("   -v             verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace       do not display trace info\n");
            return 0;
         }
      }
   }

   /* Create an instance of the compiler generated class.  This
      example uses a static message buffer. */

   if (rtXmlInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   rtXmlSetEncBufPtr(&ctxt, msgbuf, sizeof(msgbuf));
   if (cxer) rtxCtxtSetFlag(&ctxt, OSXMLC14N);

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

   stat = XmlEnc_DataInterChange_PDU (&ctxt, &msgData);

   if (stat == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((char*)msgbuf);
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      exit (-1);
   }
  
   /* Write the encoded message out to the output file */

   if (fp = fopen (filename, "w")) {
      fputs ((char*)msgbuf, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   rtFreeContext (&ctxt);
   return 0;
}
