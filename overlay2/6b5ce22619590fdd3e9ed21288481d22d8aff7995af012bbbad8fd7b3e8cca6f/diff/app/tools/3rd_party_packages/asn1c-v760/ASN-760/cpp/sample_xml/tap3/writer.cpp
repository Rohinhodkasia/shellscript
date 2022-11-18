// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "TAP-0310.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

#define MAXMSGLEN 10240

static void setDateTime (ASN1T_DateTimeLong* pDateTime, 
                         const char* localTimeStamp, 
                         const char* utcTimeOffset)
{
   pDateTime->m.localTimeStampPresent = 1;
   pDateTime->m.utcTimeOffsetPresent = 1;
   pDateTime->localTimeStamp = localTimeStamp;
   pDateTime->utcTimeOffset = utcTimeOffset;
}

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSOCTET      msgbuf[MAXMSGLEN];
   int          i, stat;
   const char*  filename = "message.xml";
   OSBOOL       verbose = FALSE, trace = TRUE;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] [ -cxer ]\n");
            printf ("   -v             verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace       do not display trace info\n");
            return 0;
         }
      }
   }

   // Create an instance of the compiler generated class.  This
   // example uses a static message buffer..

   OSXMLEncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   encodeBuffer.setDiag (verbose);
   ASN1T_DataInterChange msgData;
   ASN1C_DataInterChange dataInterChange (encodeBuffer, msgData);

   // Populate structure of generated type

   ASN1T_Notification notification;
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

   ASN1C_OperatorSpecInfoList opSpecInfoListCtrl 
      (dataInterChange, notification.operatorSpecInformation);

   opSpecInfoListCtrl.Append ("OperatorSpecInformation");

   msgData.t = T_DataInterChange_notification;
   msgData.u.notification = &notification;

   // Encode 

   if ((stat = dataInterChange.Encode ()) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((const char*)msgbuf);
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return stat;
   }
  
   // Write encoded message to output file

   if (encodeBuffer.write (filename) < 0) {
      printf ("write message to output file '%s' failed.\n", filename);
      return -1;
   }

   return 0;

}
