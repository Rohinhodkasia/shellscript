/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtsrc/asn1CEvtHndlr.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

static int errorHandler (OSCTXT *pctxt, ASN1CCB *pCCB, int stat) 
{
   /* This handler is set up to look explicitly for RTERR_NOTINSET 
      errors because we know the SET might contain some bogus elements. */

   if (stat == RTERR_NOTINSET || stat == RTERR_INVOPT) {
      /* Let's report the tag value of the offending element and then
       * skip past it. */

      /* The tag value. */
      ASN1TAG tag;

      /* A buffer to hold the textual value of the tag. */
      char buf[128]; 

      /* Buffers to hold some compact error text. */
      char cerr1[1750], cerr2[1750];

      /* The error info */
      OSRTErrInfo *pErrInfo = 0;

      /* The locally-generated status. */
      int lstat; 

      /* The current byte index.  We'll use this to restore our position in
       * the buffer. */
      size_t curIndex = pctxt->buffer.byteIndex;

      /* Decode the tag. */
      xd_tag (pctxt, &tag);

      /* Reset buffer location to allow us to skip past the next element. */
      pctxt->buffer.byteIndex = curIndex;

      /* Get a nice textual representation of the tag. */
      xu_fmt_tag2 (&tag, buf);
      printf ("Invalid tag found: %s at index %u.\n", buf, curIndex);
      printf ("Skipping next element.\n");

      /* rtxErrPrint (pctxt); */

      /* The compact error information. */
      pErrInfo = OSRT_GET_FIRST_ERROR_INFO(pctxt);
      os_snprintf (cerr1, sizeof(cerr1), "ERROR: Status %d -- ", pErrInfo->status);
      rtxErrFmtMsg (pErrInfo, cerr2, sizeof(cerr2));
      strncat (cerr1, cerr2, 1750);

      printf ("%s\n\n", cerr1);

      /* Reset the error status; n.b., this will clear out the entire error 
       * stack, and previous errors will be erased. */
      rtxErrReset (pctxt);
      
      /* Skip element */

      lstat = xd_NextElement (pctxt);

      if (lstat != 0) {
         return LOG_RTERR (pctxt, lstat);
      }

      /* Return an OK status to indicate parsing can continue */

      return 0;
   }

   else return stat;  /* pass existing status back out */
}

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT       ctxt;
   OSOCTET*     msgbuf;
   ASN1TAG      tag;
   size_t       len;
   int          i, stat;
   const char*  filename = "message.dat";
   OSBOOL       trace = TRUE, verbose = FALSE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -i <filename>\n");
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

   /* Add error handler. */
   rtSetErrorHandler (&ctxt, &errorHandler);

   /* Read input file into a memory buffer */

   stat = rtxFileReadBinary (&ctxt, filename, &msgbuf, &len);
   if (0 != stat) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   stat = xd_setp64 (&ctxt, msgbuf, len, &tag, 0, 0);
   if (0 != stat) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   asn1Init_PersonnelRecord (&employee);

   /* Decode */

   if (tag == TV_PersonnelRecord) {

      /* Call compiler generated decode function */

      stat = asn1D_PersonnelRecord (&ctxt, &employee, ASN1EXPL, 0);
      if (stat == 0) {
         if (trace) {
            printf ("Decode of PersonnelRecord was successful\n");
            printf ("Decoded record:\n");
            asn1Print_PersonnelRecord ("Employee", &employee);
         }
      }
      else {
         printf ("decode of PersonnelRecord failed\n");
         rtxErrPrint (&ctxt);
         return -1;
      }
   }
   else {
      printf ("unexpected tag %hx received\n", tag);
   }

   rtFreeContext (&ctxt);

   return 0;
}
