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
#include "MEDIA-GATEWAY-CONTROL.h"
#include "rtxsrc/rtxBench.h"

#define MAXMSGLEN 10240

#define MAXBUFFERSIZE 800

#define MAX_FILES 28

static const char* file_list[] = {
    "msg01.bin",
    "msg02.bin",
    "msg03.bin",
    "msg04.bin",
    "msg05.bin",
    "msg06.bin",
    "msg07.bin",
    "msg08.bin",
    "msg09.bin",
    "msg10.bin",
    "msg11.bin",
    "msg12.bin",
    "msg13.bin",
    "msg14.bin",
    "msg15.bin",
    "msg16.bin",
    "msg17.bin",
    "msg18.bin",
    "msg19.bin",
    "msg20.bin",
    "msg21.bin",
    "msg22.bin",
    "msg23.bin",
    "msg24.bin",
    "msg25.bin",
    "msg26.bin",
    "msg27.bin",
    "msg28.bin",
    NULL
};

typedef struct encoded_value_t {
  const char* description;
  int    pdunumber;
  int    length;
  double etime;
  double dtime;
  double ftime;
  OSOCTET *encoded;
  MegacoMessage msgdata;
} encoded_value;

encoded_value *encoded_list[MAX_FILES];

int main (int argc, char** argv)
{
   MegacoMessage  msgdata;
   OSCTXT     ctxt, ctxt2, ctxt3;
   OSOCTET    msgbuf[MAXMSGLEN];
   int        i, j, len = 0, stat;
   OSBOOL     trace = FALSE, aligned = TRUE, verbose = FALSE;
   int        encoded_value_counter = 0, quantity_of_messages = 0;
   encoded_value *enc;
   const char*  resultsFile = "bench.csv";
   clock_t	start, finish;
   OSRTBenchmarkData benchData;
   
   memset (&benchData, 0, sizeof(benchData));
   benchData.itercnt = ITERCNT;
   benchData.program = "megaco";
   benchData.encRules = "per";
      
   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) trace = verbose = TRUE;
         else if (!strcmp (argv[i], "-trace")) trace = TRUE;
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

   if ((stat = rtInitContext (&ctxt2)) != 0) {
      printf ("rtInitASN1Context failed\n");
      rtxErrPrint (&ctxt2);
      return -1;
   }
   rtxSetDiag (&ctxt2, verbose);

   /* Load all messages in memory */

   while (file_list[encoded_value_counter]) {
      FILE *fd;
      struct stat st;

      if (quantity_of_messages >= MAX_FILES) {
         fprintf(stderr, "Too many files specified\n");
         return 1;
      }
      
      if (!(fd = fopen(file_list[encoded_value_counter],"rb"))) {
         perror(file_list[encoded_value_counter]);
         encoded_value_counter++;
         continue;
      }
      if (!(enc = encoded_list[quantity_of_messages] = malloc(sizeof(encoded_value)))) {
         fprintf(stderr, "Failed to allocate %lu byte(s) of memory\n",
                 sizeof(encoded_value));
         return 1;
      }
      fstat(fileno(fd), &st);
      if (!(enc->encoded = malloc(st.st_size))) {
         fprintf(stderr, "Failed to allocate %lu byte(s) of memory\n",
                 st.st_size);
         return 1;
      }
      
      /* Fill in the structure */
      enc->description = file_list[quantity_of_messages];
      len+=enc->length = st.st_size;
      if (fread(enc->encoded, enc->length, 1, fd) != 1) {
         printf("read data file %s failed.\n",
                file_list[encoded_value_counter]);
         return -1;
      }
      fclose(fd);
      encoded_value_counter++;
      quantity_of_messages++;

      /* Decode message */

      pu_setBuffer (&ctxt2, enc->encoded, enc->length, TRUE);

      stat = asn1PD_MegacoMessage (&ctxt2, &enc->msgdata);

      if (stat != 0) {
         printf ("decode of MegacoMessage failed\n");
         rtxErrPrint (&ctxt2);
         return -1;
      }
   }

   if (!quantity_of_messages) {
      fprintf(stderr, "No valid messages found\n");
      return 1;
   }

   /* Init context structure */

   if ((stat = rtInitContext (&ctxt)) != 0) {
      printf ("rtInitContext failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);

   /* Encode benchmark test loop */

   benchData.msgSize = 0;
   start = clock();

   for (i = 0; i < (int)benchData.itercnt; i++) {
      for (j = 0; j < quantity_of_messages;j++) {
         pu_setBuffer (&ctxt, msgbuf, sizeof(msgbuf), aligned);
         if ((stat = asn1PE_MegacoMessage (&ctxt, &encoded_list[j]->msgdata)) < 0) {
            rtxErrPrint (&ctxt);
            return (-1);
         }
         if (0 == i) {
            pe_GetMsgPtr (&ctxt3, &len);

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

   if ((stat = rtInitContext (&ctxt3)) != 0) {
      printf ("rtInitASN1Context failed\n");
      rtxErrPrint (&ctxt3);
      return -1;
   }
   rtxSetDiag (&ctxt3, verbose);
   rtSetFastCopy (&ctxt3, TRUE);

   /* Decode benchmark test loop */

   for (i = 0; i < (int)benchData.itercnt; i++) {
      for (j = 0; j < quantity_of_messages;j++) {
         enc = encoded_list[j];

         pu_setBuffer (&ctxt3, enc->encoded, enc->length, aligned);

         stat = asn1PD_MegacoMessage (&ctxt3, &msgdata);

         if (stat != 0) {
            printf ("decode of MegacoMessage failed\n");
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

