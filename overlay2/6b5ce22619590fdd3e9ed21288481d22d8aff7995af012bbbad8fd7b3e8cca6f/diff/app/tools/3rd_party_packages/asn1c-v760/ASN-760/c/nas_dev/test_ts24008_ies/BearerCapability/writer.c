#include "TS24008IES.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxCharStr.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxDiagBitTrace.h"
#include "rtxsrc/rtxError.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxPrint.h"

#define MAXMSGLEN 300

int main (int argc, char** argv)
{
   TS24008IE_BearerCapability* pvalue;

   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   const char*  filename = "message.dat";
   OSSIZE       len;
   int		i, ret;
   OSBOOL       verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else {
            printf ("usage: writer [-v]\n");
            printf ("   -v  verbose mode: print trace info\n");
            return 0;
         }
      }
   }

   /* Initialize context structure */

   ret = rtInitContext (&ctxt);
   if (0 != ret) {
      printf ("rtInitContext failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Populate data structure */

   pvalue = rtxMemAllocType (&ctxt, TS24008IE_BearerCapability);
   asn1Init_TS24008IE_BearerCapability (pvalue);

   pvalue->octet3.radioChannelRequirement = 2;
   pvalue->octet3.nonstandardCoding = 1;
   pvalue->octet3.packetXferMode = 0;
   pvalue->octet3.infoXferCap = TS24008IE_InfoXferCap_fax;

   pvalue->m.octet3aPresent = 1;
   pvalue->octet3a.coding = 0;
   pvalue->octet3a.ctm = 0;
   pvalue->octet3a.speechVersion = 5;

   pvalue->octet3b.n = 2;
   pvalue->octet3b.elem = rtxMemAllocArray(&ctxt, 2, TS24008IE_BearerCapOctet3b);
   pvalue->octet3b.elem[0].coding = FALSE;
   pvalue->octet3b.elem[0].spare = 0;
   pvalue->octet3b.elem[0].speechVersion = 2;
   pvalue->octet3b.elem[1].coding = TRUE;
   pvalue->octet3b.elem[1].spare = 0;
   pvalue->octet3b.elem[1].speechVersion = 3;

   pvalue->m.octet4Present = 1;
   pvalue->octet4.compression = 0;
   pvalue->octet4.structure = 1;
   pvalue->octet4.fullDuplexMode = 0;
   pvalue->octet4.configuration = 0;
   pvalue->octet4.nirr = 1;
   pvalue->octet4.establishment = 0;

   pvalue->m.octet5Present = 1;
   pvalue->m.octet5aPresent = 1;
   pvalue->m.octet5bPresent = 1;
   pvalue->octet5.accessIdentity = 2;
   pvalue->octet5.rateAdaption = 0;
   pvalue->octet5.signallingAccessProtocol = 0;
   pvalue->octet5a.otherITC = 0;
   pvalue->octet5a.otherRateAdaption = 0;
   pvalue->octet5b.rateAdaptionHeader = 0;
   pvalue->octet5b.multipleFrameEstablishment = 0;
   pvalue->octet5b.protocolSensitiveMode = 0;
   pvalue->octet5b.fullProtocolNegotiation = 1;
   pvalue->octet5b.assignorOnly = 1;
   pvalue->octet5b.uiNegotiation = 1;

   pvalue->m.octet6Present = 1;
   pvalue->m.octet6aPresent = 1;
   pvalue->m.octet6bPresent = 1;
   pvalue->m.octet6cPresent = 1;
   pvalue->m.octet6dPresent = 1;
   pvalue->m.octet6ePresent = 1;
   pvalue->m.octet6fPresent = 1;
   pvalue->m.octet6gPresent = 1;
   pvalue->octet6.layer1Identity = 2;
   pvalue->octet6.userInfoLayer1Protocol = 3;
   pvalue->octet6.asynchronous = 0;
   pvalue->octet6a.twoStopBits = 1;
   pvalue->octet6a.negotiation = 1;
   pvalue->octet6a.data8bits = 1;
   pvalue->octet6a.userRate = 11;
   pvalue->octet6b.intermediateRate = 0;
   pvalue->octet6b.nicOnTX = 0;
   pvalue->octet6b.nicOnRX = 0;
   pvalue->octet6b.parity = 4;
   pvalue->octet6c.connectionElement = 2;
   pvalue->octet6c.modemType = 26;
   pvalue->octet6d.otherModemType = 2;
   pvalue->octet6d.fixedNetworkUserRate = 4;
   pvalue->octet6e.acceptableChannelCodings = 11;
   pvalue->octet6e.maximumNumberOfTrafficChannels = 4;
   pvalue->octet6f.uimi = 2;
   pvalue->octet6f.wantedAirInterfaceUserRate = 14;
   pvalue->octet6g.acceptableChannelCodingsExtended = 4;
   pvalue->octet6g.asymmetryIndication = 2;
   pvalue->octet6g.spare = 0;

   pvalue->m.octet7Present = 1;
   pvalue->octet7.layer2Identity = 1;
   pvalue->octet7.userInformationLayer2Protocol = 22;

   /* Enable bit tracing */

   if (verbose) {
      rtxDiagCtxtBitFieldListInit (&ctxt);
   }

   /* Encode data */

   rtxCtxtSetBufPtr (&ctxt, msgbuf, sizeof(msgbuf));

   ret = NASEnc_TS24008IE_BearerCapability (&ctxt, pvalue);
   if (0 != ret) {
      printf ("encode BearerCapability failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   msgptr = rtxCtxtGetMsgPtr (&ctxt);
   len = rtxCtxtGetMsgLen (&ctxt);

   if (verbose) {
      printf ("Encoding was successful\n");
      printf ("Hex dump of encoded record:\n");
      rtxHexDump (msgptr, len);
      printf ("\n");
      printf ("Bit fields:\n");
      rtxDiagBitTracePrint (ctxt.pBitFldList, "");
      printf ("\n");
   }

   /* Write encoded message to output file */

   ret = rtxFileWriteBinary (filename, msgptr, len);
   if (0 != ret) {
      printf ("rtxFileWriteBinary failed; status = %d\n", ret);
      rtxErrPrint (&ctxt);
      return ret;
   }

   rtxFreeContext (&ctxt);

   return 0;
}
