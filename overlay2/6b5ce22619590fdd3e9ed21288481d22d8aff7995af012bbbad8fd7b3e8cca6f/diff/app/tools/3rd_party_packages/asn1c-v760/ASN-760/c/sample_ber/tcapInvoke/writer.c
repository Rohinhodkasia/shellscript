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

static int encodeOperationParameter (OSCTXT* pctxt);
static int encodeTCAPInvokeHeader (OSCTXT* pctxt, int msglen);

int main (int argc, char** argv)
{
   /* Run-time support variables */

   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   int		i, len;
   FILE*        fp;
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

   /* Initialize the encoding context */
   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   xe_setp (&ctxt, msgbuf, sizeof(msgbuf));

   /* Encode operation parameter */

   if ((len = encodeOperationParameter (&ctxt)) < 0) return len;

   /* Encode TCAP header on top of encoded parameter */

   if ((len = encodeTCAPInvokeHeader (&ctxt, len)) < 0) return len;

   msgptr = xe_getp (&ctxt);

   if (trace) {
      if (XU_DUMP (msgptr) != 0) 
         printf ("dump of ASN.1 message failed.");
   }

   /* Write the encoded message out to the output file */

   if (0 != (fp = fopen (filename, "wb"))) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   rtFreeContext (&ctxt);
   return 0;

}

/* Encode operation parameter */

static int encodeOperationParameter (OSCTXT* pctxt)
{
   CallInfoFromResource_ARGUMENT param;
   SpcID spcID;
   size_t i;
   int len;

   asn1Init_CallInfoFromResource_ARGUMENT (&param);

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
   param.amp2.ampCLogRepInd = requestReport;
   param.amp2.m.ampCallProgIndPresent = 1;
   param.amp2.ampCallProgInd = callProgressVoiceAnnouncements;
   param.amp2.m.ampTestReqIndPresent = 1;
   param.amp2.ampTestReqInd = 111;
   param.amp2.m.ampCLogNamePresent = 1;
   param.amp2.ampCLogName.numocts = strlen (CLOGNAME);
   strncpy ((char*)param.amp2.ampCLogName.data, CLOGNAME, 
            sizeof(param.amp2.ampCLogName.data));

   /* Extension parameters not present */

   /* Encode operation argument */

   len = asn1E_CallInfoFromResource_ARGUMENT (pctxt, &param, ASN1EXPL);

   if (len < 0) {
      printf ("Encode of callInfoFromResource_ARGUMENT failed.\n");
      rtxErrPrint (pctxt);
   }

   return len;
}

/* Encode TCAP header */

static int encodeTCAPInvokeHeader (OSCTXT* pctxt, int msglen)
{
   MessageType   messageType;
   Undirectional undirectional;
   Component*    pComponent;
   Invoke        invoke;
   int           len;

   /* Populate header structure */

   asn1Init_Invoke (&invoke);
   invoke.m.parameterPresent = 1;
   invoke.invokeID = 1;
   invoke.operationCode = ASN1V_callInfoFromResource;
   invoke.parameter.numocts = msglen;
   invoke.parameter.data = xe_getp (pctxt);

   pComponent = rtxMemAllocType (pctxt, Component);
   pComponent->t = T_Component_invoke;
   pComponent->u.invoke = &invoke;

   asn1Init_Undirectional (&undirectional);
   rtxDListAppend (pctxt, &undirectional.components, pComponent);

   messageType.t = T_MessageType_undirectional;
   messageType.u.undirectional = &undirectional;

   /* Encode */

   len = asn1E_MessageType (pctxt, &messageType, ASN1EXPL);

   if (len < 0) {
      printf ("Encode of MessageType failed.\n");
      rtxErrPrint (pctxt);
   }

   return len;
}
