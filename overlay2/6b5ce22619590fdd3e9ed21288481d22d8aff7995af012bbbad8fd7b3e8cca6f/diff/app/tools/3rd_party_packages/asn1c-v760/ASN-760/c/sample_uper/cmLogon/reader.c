/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "ACSE-1.h"
#include "CMMessageSetVersion1.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

int main (int argc, char** argv)
{
   ACSE_apdu    acse;
   CMAircraftMessage cmAircraftMessage;
   External*    pExternal;
   OSCTXT	ctxt, ctxt2;
   OSOCTET*	msgbuf;
   const OSOCTET *msgptr;
   const char*  filename = "message.dat";
   int		i, stat;
   size_t       len;
   OSBOOL       trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v][-i <filename>][-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context structure */

   if (rtInitContext (&ctxt) != 0) {
      printf ("Error initializing context\n");
      return -1;
   }

   rtxSetDiag (&ctxt, verbose);

   stat = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
   if (0 != stat) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   /* Set message buffer and PER bit tracing */

   pu_setBuffer (&ctxt, msgbuf, len, /* aligned */ FALSE);
   pu_setTrace (&ctxt, trace);

   /* First, decode the ACSE header */

   stat = asn1PD_ACSE_apdu (&ctxt, &acse);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt, "acse");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of ACSE_apdu was successful\n");
         asn1Print_ACSE_apdu ("acse", &acse);
      }
   }
   else {
      printf ("decode of ACSE_apdu failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }

   /* Check fields for expected values */

   if (acse.t != T_ACSE_apdu_aarq) {
      printf ("ERROR: expecting T_ACSE_apdu_aarq, got %d\n", acse.t);
      return (-1);
   }

   if (!acse.u.aarq->m.user_informationPresent) {
      printf ("ERROR: encoded aircraft message is not present.\n");
      return (-1);
   }

   if (acse.u.aarq->user_information.count != 1) {
      printf ("ERROR: expecting only 1 external element, got " OSSIZEFMT "\n",
              acse.u.aarq->user_information.count);
      return (-1);
   }

   pExternal = (External*) rtxDListFindByIndex 
      (&acse.u.aarq->user_information, 0)->data;

   if (0 == pExternal) {
      printf ("ERROR: unable to retrieve list element 0\n");
      return (-1);
   }

   if (pExternal->encoding.t != T_External_encoding_arbitrary) {
      printf ("ERROR: expecting arbitray encoding, got %d\n",
              pExternal->encoding.t);
      return (-1);
   }

   /* Decode CM Aircraft Message */

   msgptr = pExternal->encoding.u.arbitrary->data;
   len = (pExternal->encoding.u.arbitrary->numbits + 7) / 8;

   rtInitContext (&ctxt2);
   pu_setBuffer (&ctxt2, (OSOCTET*)msgptr, len, /* aligned */FALSE);
   pu_setTrace (&ctxt2, trace);

   stat = asn1PD_CMAircraftMessage (&ctxt2, &cmAircraftMessage);

   if (trace) {
      printf ("Dump of decoded bit fields:\n");
      pu_bindump (&ctxt2, "cmAircraftMessage");
      printf ("\n");
   }

   if (stat == 0) {
      if (trace) {
         printf ("decode of CMAircraftMessage was successful\n");
         asn1Print_CMAircraftMessage ("cmAircraftMessage", &cmAircraftMessage);
      }
   }
   else {
      printf ("decode of CMAircraftMessage failed\n");
      rtxErrPrint (&ctxt2);
      return -1;
   }

   rtFreeContext (&ctxt);
   rtFreeContext (&ctxt2);

   return 0;
}

