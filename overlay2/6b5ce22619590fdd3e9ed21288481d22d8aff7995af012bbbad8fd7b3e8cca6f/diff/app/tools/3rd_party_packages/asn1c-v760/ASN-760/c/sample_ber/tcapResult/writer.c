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

static int encodeOperationResult (OSCTXT* pctxt);
static int encodeTCAPResultHeader (OSCTXT* pctxt, int msglen);

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

   if ((len = encodeOperationResult (&ctxt)) < 0) return len;

   /* Encode TCAP header on top of encoded parameter */

   if ((len = encodeTCAPResultHeader (&ctxt, len)) < 0) return len;

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

static int encodeOperationResult (OSCTXT* pctxt)
{
   CallInfoFromResource_RESULT result;
   FlexParameterBlock flexParameterBlock;
   SpcID spcID;
   size_t i;
   int len;

   asn1Init_CallInfoFromResource_RESULT (&result);

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
   result.amp2.ampCLogRepInd = requestReport;
   result.amp2.m.ampCallProgIndPresent = 1;
   result.amp2.ampCallProgInd = callProgressVoiceAnnouncements;
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

   len = asn1E_CallInfoFromResource_RESULT (pctxt, &result, ASN1EXPL);

   if (len < 0) {
      printf ("Encode of CallInfoFromResource_RESULT failed.\n");
      rtxErrPrint (pctxt);
   }

   return len;
}

/* Encode TCAP header */

static int encodeTCAPResultHeader (OSCTXT* pctxt, int msglen)
{
   MessageType   messageType;
   Undirectional undirectional;
   Component     components[1];
   ReturnResult  result;
   int           len;

   /* Populate header structure */

   asn1Init_ReturnResult (&result);
   result.m.resultPresent = 1;
   result.invokeID = 1;
   result.result.operationCode = ASN1V_callInfoFromResource;
   result.result.parameter.numocts = msglen;
   result.result.parameter.data = xe_getp (pctxt);

   components[0].t = T_Component_returnResultLast;
   components[0].u.returnResultLast = &result;

   asn1Init_Undirectional (&undirectional);

   rtxDListAppendArray (pctxt, &undirectional.components, 
                       components, 1, sizeof(Component));

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
