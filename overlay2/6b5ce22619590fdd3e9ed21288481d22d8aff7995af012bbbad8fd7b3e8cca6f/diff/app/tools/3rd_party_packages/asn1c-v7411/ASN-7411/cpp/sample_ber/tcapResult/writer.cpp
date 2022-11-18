/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "TCAPMessages.h"
#include "AIN-Operation.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024
#define CLOGNAME  "TestUser"

static int encodeOperationResult (ASN1BEREncodeBuffer& encodeBuffer);
static int encodeTCAPResultHeader (ASN1BEREncodeBuffer& encodeBuffer, int msglen);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   /* Run-time support variables */

   OSOCTET	msgbuf[MAXMSGLEN];
   int		i, len;
   FILE*        fp;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;
   const OSOCTET* msgptr;

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

   // Initialize encode buffer object.  This example uses a static 
   // message buffer..

   ASN1BEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   encodeBuffer.setDiag (verbose);

   // Encode operation result

   if ((len = encodeOperationResult (encodeBuffer)) < 0) return len;

   // Encode TCAP header on top of encoded result body

   if ((len = encodeTCAPResultHeader (encodeBuffer, len)) < 0) return len;

   msgptr = encodeBuffer.getMsgPtr ();

   if (trace) {
      printf ("Encoding was successful\n");
      printf ("Hex dump of encoded record:\n");
      encodeBuffer.hexDump (len);
      printf ("Binary dump:\n");
      encodeBuffer.binDump ();
   }

   // Write the encoded message out to the output file

   if (fp = fopen (filename, "wb")) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   return 0;

}


// Encode operation result

static int encodeOperationResult (ASN1BEREncodeBuffer& encodeBuffer)
{
   ASN1T_CallInfoFromResource_RESULT result;
   ASN1C_CallInfoFromResource_RESULT resultC (encodeBuffer, result);
   ASN1T_FlexParameterBlock flexParameterBlock;
   ASN1T_SpcID spcID;
   int i, len;

   memset (&result, 0, sizeof(result));

   /* ResourceType */

   result.m.resourceTypePresent = 1;
   result.resourceType = 123;

   /* StrParameterBlock */

   for (i = 0; i < sizeof(flexParameterBlock.data); i++) {
      flexParameterBlock.data[i] = (OSOCTET) i;
   }
   flexParameterBlock.numocts = i;
   result.m.strParameterBlockPresent = 1;
   result.strParameterBlock.t = T_StrParameterBlock_flexParameterBlock;
   result.strParameterBlock.u.flexParameterBlock = &flexParameterBlock;

   /* Amp1 */

   result.m.amp1Present = 1;
   for (i = 0; i < sizeof(result.amp1.data); i++) {
      result.amp1.data[i] = (OSOCTET) i;
   }
   result.amp1.numocts = i;

   /* Amp2 */

   result.m.amp2Present = 1;
   spcID.numocts = 3;
   strncpy ((char*)spcID.data, "123", 3);
   result.amp2.ampAINNodeID.t = T_AmpAINNodeID_spcID;
   result.amp2.ampAINNodeID.u.spcID = &spcID;
   result.amp2.m.ampCLogSeqNoPresent = 1;
   result.amp2.ampCLogSeqNo = 12345;
   result.amp2.m.ampCLogRepIndPresent = 1;
   result.amp2.ampCLogRepInd = AmpCLogRepInd::requestReport;
   result.amp2.m.ampCallProgIndPresent = 1;
   result.amp2.ampCallProgInd = AmpCallProgInd::callProgressVoiceAnnouncements;
   result.amp2.m.ampTestReqIndPresent = 1;
   result.amp2.ampTestReqInd = 111;
   result.amp2.m.ampCLogNamePresent = 1;
   result.amp2.ampCLogName.numocts = strlen (CLOGNAME);
   strncpy ((char*)result.amp2.ampCLogName.data, CLOGNAME, 
            sizeof(result.amp2.ampCLogName.data));

   /* ServiceProviderID */

   result.m.serviceProviderIDPresent = 1;
   result.serviceProviderID.t = T_ServiceProviderID_ocn;
   result.serviceProviderID.u.ocn = "TestOCN";

   /* ServiceContext */

   result.m.serviceContextPresent = 1;
   result.serviceContext = 4321;

   /* Extension parameters not present */

   /* Encode operation result */

   if ((len = resultC.Encode()) < 0) {
      printf ("Encode of callInfoFromResource_RESULT failed.\n");
      encodeBuffer.printErrorInfo ();
      exit (-1);
   }

   return len;
}

/* Encode TCAP header */

static int encodeTCAPResultHeader (ASN1BEREncodeBuffer& encodeBuffer, 
                                   int msglen)
{
   ASN1T_MessageType   messageType;
   ASN1C_MessageType   messageContainer (encodeBuffer, messageType);
   ASN1T_Undirectional undirectional;
   ASN1T_Component     components[1];
   ASN1T_ReturnResult  result;
   int                 len;

   /* Populate header structure */

   memset (&result, 0, sizeof(result));
   result.m.resultPresent = 1;
   result.invokeID = 1;
   result.result.operationCode = ASN1V_callInfoFromResource;
   result.result.parameter.numocts = msglen;
   result.result.parameter.data = (OSOCTET*)encodeBuffer.getMsgPtr();

   components[0].t = T_Component_returnResultLast;
   components[0].u.returnResultLast = &result;

   ASN1CSeqOfList componentList (encodeBuffer, undirectional.components);
   componentList.append (&components[0]);

   messageType.t = T_MessageType_undirectional;
   messageType.u.undirectional = &undirectional;

   /* Encode */

   if ((len = messageContainer.Encode()) < 0) {
      printf ("Encode of MessageType failed.\n");
      encodeBuffer.printErrorInfo();
      exit (-1);
   }

   return len;
}
