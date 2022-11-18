/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "H323-MESSAGES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

#define MAXMSGLEN 1024

static ASN1OBJID gProtocolID = {
   6, { 0, 0, 8, 2250, 0, 2 }
} ;

extern "C"
void writeToFile(void* pPrntStrmInfo, const char* fmtspec, 
                 va_list arglist);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET      msgbuf[MAXMSGLEN]; 
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   const char*  filename = "message.dat";
   int          i, stat;
   OSSIZE       len;
   FILE*        fpLog;
   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [ -v ] [ -o <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Populate structure */

   ASN1T_H225Setup_UUIE setup;
   memset (&setup, 0, sizeof(setup));
   setup.protocolIdentifier = gProtocolID;
   for (i = 0; i < 16; i++)
      setup.conferenceID.data[i] = i + 1;
   setup.conferenceGoal.t = T_H225Setup_UUIE_conferenceGoal_create;
   setup.callType.t = T_H225CallType_pointToPoint;

   /* extension fields */
   setup.m.callIdentifierPresent = TRUE;
   setup.m.mediaWaitForConnectPresent = TRUE;
   setup.m.canOverlapSendPresent = TRUE;
   for (i = 0; i < 16; i++)
       setup.callIdentifier.guid.data[i] = i + 1;
   setup.mediaWaitForConnect = FALSE;
   setup.canOverlapSend = FALSE;

   ASN1T_H225H323_UserInformation userInfo;
   memset (&userInfo, 0, sizeof(userInfo));
   userInfo.h323_uu_pdu.h323_message_body.t = 
      T_H225H323_UU_PDU_h323_message_body_setup;
   userInfo.h323_uu_pdu.h323_message_body.u.setup = &setup;

   /* Encode */

   ASN1PEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf), aligned);
   ASN1C_H225H323_UserInformation userInfoC (encodeBuffer, userInfo);
 
   /* Set up logging */
   if(fpLog = fopen("writer.log", "w"))
   {
      /* Here the callback function is registered for a
         particular context. This means all print/debug 
         streams associated with this context will be
         passed to this handler.
      */
      userInfoC.setPrintStream(&writeToFile, (void *) fpLog);
   }
   else
   {
      printf("Failed to setup logging\n");
      return -1;
   }

   encodeBuffer.setTrace (trace);

   if ((stat = userInfoC.Encode ()) == 0) {
      if (trace) {
         printf ("Encoding was successful. See writer.log for details.\n");
         encodeBuffer.hexDump ();
         encodeBuffer.binDump ("userInfo");
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.getMsgLen ();
   }
   else {
      encodeBuffer.printErrorInfo ();
      return -1;
   }
  
   /* Write the encoded message out to the output file */

   stat = rtxFileWriteBinary (filename, msgptr, len);
   if (stat < 0) {
      printf ("Error writing to file %s, status = %d\n", filename, stat);
   }

   fclose (fpLog);

   return 0;

}

/*
   This is a callback function, which is called for handling all
   the run time logging/printing. The callback function can be 
   registered at the context level, which means it is used for
   logging/printing debug messages related to a particular context.
   It can also be registered at a global level, which applies
   to all contexts.
*/
void writeToFile(void* pPrntStrmInfo, const char* fmtspec, 
                 va_list arglist)
{
   FILE * fp = (FILE*) pPrntStrmInfo;
   vfprintf(fp, fmtspec, arglist);
   return;
}

