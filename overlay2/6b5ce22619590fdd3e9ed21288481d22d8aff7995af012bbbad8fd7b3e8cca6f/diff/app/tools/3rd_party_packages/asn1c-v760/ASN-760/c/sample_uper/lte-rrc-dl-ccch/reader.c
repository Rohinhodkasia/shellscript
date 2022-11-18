#include "EUTRA-RRC-Definitions.h"
#include "rtxsrc/rtxPrintStream.h"

int main (int argc, char** argv)
{
   DL_CCCH_Message data;
   OSCTXT      ctxt;
   OSOCTET*    pMsgBuf;
   OSBOOL      trace = TRUE, verbose = FALSE;
   const char* filename = "message.dat";
   int         i, stat;
   OSSIZE      len;

   OSRTStrBuf strBufDescr;
   char strbuf[10240];

   /* Process command line arguments */
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   /* Initialize context structure */
   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Read input file into a memory buffer */
   if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   pu_setBuffer (&ctxt, pMsgBuf, len, /*aligned*/FALSE);
   pu_setTrace (&ctxt, trace);

   asn1Init_DL_CCCH_Message (&data);

   /* Call compiler generated decode function */
   stat = asn1PD_DL_CCCH_Message (&ctxt, &data);
   if (stat != 0) {
      printf ("decode of data failed\n");
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return -1;
   }

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "data");
      printf ("\n");

      /* Set up print-to-stream callback to write to character string buffer */
      strBufDescr.strbuf = strbuf;
      strBufDescr.bufsize = sizeof(strbuf);
      strBufDescr.endx = 0;

      rtxSetPrintStream 
         (&ctxt, &rtxPrintStreamToStringCB, (void*)&strBufDescr);

      asn1PrtToStrm_DL_CCCH_Message (&ctxt, "Data", &data);

      /* Print contents of string buffer to stdout */
      printf ("%s\n", strbuf);
   }

   rtFreeContext (&ctxt);

   return 0;
}
