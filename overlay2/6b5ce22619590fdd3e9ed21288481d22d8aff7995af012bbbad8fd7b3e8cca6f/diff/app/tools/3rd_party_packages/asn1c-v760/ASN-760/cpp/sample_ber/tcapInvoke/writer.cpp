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

static int encodeOperationParameter (ASN1BEREncodeBuffer& encodeBuffer);
static int encodeTCAPInvokeHeader (ASN1BEREncodeBuffer& encodeBuffer, int msglen);

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

   // Encode operation parameter

   if ((len = encodeOperationParameter (encodeBuffer)) < 0) return len;

   // Encode TCAP header on top of encoded parameter

   if ((len = encodeTCAPInvokeHeader (encodeBuffer, len)) < 0) return len;

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

// Encode operation parameter

static int encodeOperationParameter (ASN1BEREncodeBuffer& encodeBuffer)
{
   ASN1T_CallInfoFromResource_ARGUMENT param;
   ASN1C_CallInfoFromResource_ARGUMENT argument (encodeBuffer, param);
   ASN1T_SpcID spcID;
   int i, len;

   /* IPReturnBlock */

   param.m.iPReturnBlockPresent = 1;
   for (i = 0; i < sizeof(param.iPReturnBlock.data); i++) {
      param.iPReturnBlock.data[i] = (OSOCTET) i;
   }
   param.iPReturnBlock.numocts = i;

   /* Amp1 */

   param.m.amp1Present = 1;
   for (i = 0; i < sizeof(param.amp1.data); i++) {
      param.amp1.data[i] = (OSOCTET) i;
   }
   param.amp1.numocts = i;

   /* Amp2 */

   param.m.amp2Present = 1;
   spcID.numocts = 3;
   strncpy ((char*)spcID.data, "123", 3);
   param.amp2.ampAINNodeID.t = T_AmpAINNodeID_spcID;
   param.amp2.ampAINNodeID.u.spcID = &spcID;
   param.amp2.m.ampCLogSeqNoPresent = 1;
   param.amp2.ampCLogSeqNo = 12345;
   param.amp2.m.ampCLogRepIndPresent = 1;
   param.amp2.ampCLogRepInd = AmpCLogRepInd::requestReport;
   param.amp2.m.ampCallProgIndPresent = 1;
   param.amp2.ampCallProgInd = AmpCallProgInd::callProgressVoiceAnnouncements;
   param.amp2.m.ampTestReqIndPresent = 1;
   param.amp2.ampTestReqInd = 111;
   param.amp2.m.ampCLogNamePresent = 1;
   param.amp2.ampCLogName.numocts = strlen (CLOGNAME);
   strncpy ((char*)param.amp2.ampCLogName.data, CLOGNAME, 
            sizeof(param.amp2.ampCLogName.data));

   /* Extension parameters not present */

   /* Encode operation argument */

   if ((len = argument.Encode()) < 0) {
      printf ("Encode of CallInfoFromResource_ARGUMENT failed.\n");
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   return len;
}

/* Encode TCAP header */

static int encodeTCAPInvokeHeader (ASN1BEREncodeBuffer& encodeBuffer, 
                                   int msglen)
{
   ASN1T_MessageType   messageType;
   ASN1C_MessageType   messageContainer (encodeBuffer, messageType);
   ASN1T_Undirectional undirectional;
   ASN1T_Component     components[1];
   ASN1T_Invoke        invoke;
   int                 len;

   /* Populate header structure */

   memset (&invoke, 0, sizeof(invoke));
   invoke.m.parameterPresent = 1;
   invoke.invokeID = 1;
   invoke.operationCode = ASN1V_callInfoFromResource;
   invoke.parameter.numocts = msglen;
   invoke.parameter.data = (OSOCTET*)encodeBuffer.getMsgPtr();

   components[0].t = T_Component_invoke;
   components[0].u.invoke = &invoke;

   ASN1CSeqOfList componentList (encodeBuffer, undirectional.components);
   componentList.append (&components[0]);

   messageType.t = T_MessageType_undirectional;
   messageType.u.undirectional = &undirectional;

   /* Encode */

   len = messageContainer.Encode ();

   if (len < 0) {
      printf ("Encode of MessageType failed.\n");
      encodeBuffer.printErrorInfo();
      exit(-1);
   }

   return len;
}
