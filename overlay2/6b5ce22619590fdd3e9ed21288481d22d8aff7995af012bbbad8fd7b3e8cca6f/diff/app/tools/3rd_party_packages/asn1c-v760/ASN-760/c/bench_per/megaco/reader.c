/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "MEDIA-GATEWAY-CONTROL.h"
#include "rtbench.h"

#include "rtclk.h"

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
  char *encoded;
} encoded_value;

encoded_value *encoded_list[MAX_FILES];

main (int argc, char** argv)
{
   MegacoMessage  msgdata;
   OSCTXT     ctxt, ctxt2;
   int          i, j, itercnt = ITERCNT, stat;
   OSBOOL       trace = FALSE, aligned = TRUE, verbose = FALSE;
   int          encoded_value_counter = 0, quantity_of_messages = 0;
   encoded_value *enc;

   DECLARE_RTCLK
   
   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) trace = verbose = TRUE;
         else if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-trace")) trace = TRUE;
         else if (!strcmp (argv[i], "-iter")) itercnt = atoi (argv[++i]);
         else {
            printf ("usage: reader [ options ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -trace         display trace info\n");
            printf ("   -iter <count>  set iteration count\n");
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
         fprintf(stderr, "Failed to allocate %u byte(s) of memory\n",
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
      enc->length = st.st_size;
      fread(enc->encoded, enc->length, 1, fd);

      fclose(fd);

      if (!aligned) {
         OSOCTET msgbuf[MAXMSGLEN], *msgptr;
         int len;
         
         /* Decode as aligned and then encode back as unaligned */

         pu_setBuffer (&ctxt2, enc->encoded, enc->length, TRUE);
         if ((stat = asn1PD_MegacoMessage (&ctxt2, &msgdata)) < 0) {
            printf ("pre-decode of MegacoMessage failed (%i)\n", quantity_of_messages);
            rtxErrPrint (&ctxt2);
            return -1;
         }

         pu_setBuffer (&ctxt2, msgbuf, sizeof (msgbuf), FALSE);
         if ((stat = asn1PE_MegacoMessage (&ctxt2, &msgdata)) < 0) {
            printf ("pre-encode of MegacoMessage failed (%i)\n", quantity_of_messages);
            rtxErrPrint (&ctxt2);
            return -1;
         }
      
         msgptr = pe_GetMsgPtr (&ctxt2, &len);
         free (enc->encoded);

         enc->encoded = malloc (len);
         enc->length = len;
         memcpy (enc->encoded, msgptr, len);
      }
      encoded_value_counter++;
      quantity_of_messages++;
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
   rtSetFastCopy (&ctxt, TRUE);

   /* Benchmark test loop */

   BEGIN_LOOP
      for (j = 0; j < quantity_of_messages;j++) {
         enc = encoded_list[j];

         pu_setBuffer (&ctxt, enc->encoded, enc->length, aligned);

         stat = asn1PD_MegacoMessage (&ctxt, &msgdata);

         if (stat != 0) {
            printf ("decode of MegacoMessage failed\n");
            rtxErrPrint (&ctxt);
            return -1;
         }
         rtxMemReset (&ctxt);
      }
   END_LOOP

   PRINT_READER

   /* Output is tab-delimited. It is expected that control Perl script  */
   /* has output header information and that writer was called before   */
   /* calling this program..                                            */

   if (trace) {
      printf ("Decode of MegacoMessage was successful\n");

      for (j = 0; j < quantity_of_messages;j++) {
         enc = encoded_list[j];
         pu_setBuffer (&ctxt, enc->encoded, enc->length, aligned);

         asn1PD_MegacoMessage (&ctxt, &msgdata);
         
         printf ("Hex dump of encoded record #%i:\n", j);
         pu_hexdump (&ctxt);

         printf ("Record:\n");
         asn1Print_MegacoMessage ("msgdata", &msgdata);
         printf ("\n\n");
         rtxMemReset (&ctxt);
      }
   }

   return 0;
}
