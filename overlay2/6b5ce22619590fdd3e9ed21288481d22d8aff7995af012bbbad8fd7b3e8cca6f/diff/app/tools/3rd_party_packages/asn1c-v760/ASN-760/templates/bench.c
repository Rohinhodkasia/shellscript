/* 
This benchmark test driver program does the following:

1. Populates a test data record.
2. Executes a benchmark timing loop to encode the record a given number of 
   times and records the results.
3. Executes a benchmark timing loop to decode the record a given number of 
   times and records the results.
4. Prints the results to a CSV file.
*/
#include <stdio.h>
#include <stdlib.h>
<include-files>
#include "rtxsrc/rtxBench.h"
#include "rtxsrc/rtxCharStr.h"

 /* hex dump of encoded message 1 */
unsigned char encdata1[] = {
} ;

 /* hex dump of encoded message 1 */
unsigned char encdata2[] = {
} ;
/* add more as needed .. */

typedef struct {
   <PDU-Type> decoded;
   OSSIZE  enclen;
   OSOCTET* encoded;
} PDU_VALUE;

#define PDU_COUNT 2

static PDU_VALUE gs_msgdata[PDU_COUNT];

int main (int argc, char* argv[])
{
   <PDU-Type> msgdata;
   OSCTXT  ctxt, ctxt2, ctxt3;
   OSOCTET bindata[1024], *msgptr;
   /* 16K static memheap - adjust size as needed */
   OSOCTET staticMemHeap[16*1024];
   size_t  i, j;
   int     len, ret;
   OSBOOL  trace = FALSE, aligned = FALSE, verbose = FALSE;

   const char*  resultsFile = "bench.csv";
   clock_t	start, finish;
   OSRTBenchmarkData benchData;
   
   /* add encoded messages to message array */
   i = 0;
   gs_msgdata[i].enclen = sizeof(encdata1);
   gs_msgdata[i++].encoded = encdata1;

   gs_msgdata[i].enclen = sizeof(encdata2);
   gs_msgdata[i++].encoded = encdata2;

   memset (&benchData, 0, sizeof(benchData));
   benchData.itercnt = 100000;
   benchData.program = "dsrc";
   benchData.encRules = "uper";

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < (size_t)argc; i++) {
         if (!strcmp (argv[i], "-v")) trace = verbose = TRUE;
         else if (!strcmp (argv[i], "-trace")) trace = TRUE;
	 else if (!strcmp (argv[i], "-iter")) 
            benchData.itercnt = (size_t) atoi(argv[++i]);
	 else if (!strcmp (argv[i], "-resfile")) resultsFile = argv[++i];
         else {
            printf ("usage: writer [ options ]\n");
            printf ("   -v  verbose mode: print extended trace info\n");
            printf ("   -trace         display trace info\n");
	    printf ("   -iter <count>  set iteration count\n");
	    printf ("   -resfile <filename> set results filename\n");
            return 0;
         }
      }
   }

   /* Init context structure */

   if ((ret = rtInitContext (&ctxt2)) != 0) {
      printf ("rtInitASN1Context failed\n");
      rtxErrPrint (&ctxt2);
      return -1;
   }
   rtxSetDiag (&ctxt2, verbose);

   /* Convert each message to binary and decode */

   for (i = 0; i < PDU_COUNT; i++) {

      /* Decode message */

      pu_setBuffer (&ctxt2, gs_msgdata[i].encoded, 
                    gs_msgdata[i].enclen, aligned);

      asn1Init_<PDU-Type> (&gs_msgdata[i].decoded);

      ret = asn1PD_<PDU-Type> (&ctxt2, &gs_msgdata[i].decoded);

      if (ret != 0) {
         printf ("decode failed\n");
         rtxErrPrint (&ctxt2);
         return -1;
      }
   }

   /* Init context structure */

   if ((ret = rtInitContext (&ctxt)) != 0) {
      printf ("rtInitContext failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Encode benchmark test loop */

   benchData.msgSize = 0;
   start = clock();

   for (i = 0; i < benchData.itercnt; i++) {
      for (j = 0; j < PDU_COUNT; j++) {
         pu_setBuffer (&ctxt, bindata, sizeof(bindata), aligned);
         ret = asn1PE_<PDU-Type> (&ctxt, &gs_msgdata[j].decoded);
         if (ret < 0) {
            rtxErrPrint (&ctxt);
            return (-1);
         }
         if (0 == i) {
            msgptr = pe_GetMsgPtr (&ctxt, &len);

            benchData.msgSize += len;

            if (trace) {
               printf ("Encoding was successful\n");
               printf ("Hex dump of encoded record:\n");
               pu_hexdump (&ctxt);
            }
         }
         rtxMemReset (&ctxt);
      }
   }
   finish = clock();

   benchData.encodeMsecs = (unsigned long)
      ((finish - start) * 1000 / CLOCKS_PER_SEC);

   /* Init context structure */

   if ((ret = rtInitContext (&ctxt3)) != 0) {
      printf ("rtInitASN1Context failed\n");
      rtxErrPrint (&ctxt3);
      return -1;
   }
   rtxSetDiag (&ctxt3, verbose);
   rtSetFastCopy (&ctxt3, TRUE);

   /* Set static memory heap */

   rtxMemHeapRelease (&ctxt3.pMemHeap);
   rtxMemStaticHeapCreate 
      (&ctxt3.pMemHeap, staticMemHeap, sizeof(staticMemHeap));

   /* Decode benchmark test loop */

   start = clock();

   for (i = 0; i < benchData.itercnt; i++) {
      for (j = 0; j < PDU_COUNT; j++) {
         pu_setBuffer (&ctxt3, gs_msgdata[j].encoded, 
                       gs_msgdata[j].enclen, aligned);

         asn1Init_MessageFrame (&msgdata);

         ret = asn1PD_MessageFrame (&ctxt3, &msgdata);

         if (ret != 0) {
            printf ("decode failed\n");
            rtxErrPrint (&ctxt3);
            return -1;
         }
         rtxMemReset (&ctxt3);
      }
   }

   finish = clock();

   benchData.decodeMsecs = (unsigned long)
      ((finish - start) * 1000 / CLOCKS_PER_SEC);

   rtxBenchPrintResults (resultsFile, &benchData);

   return 0;
}
