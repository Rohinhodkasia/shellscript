/* This test driver program reads an encoded record from a file         */
/* and decodes it and displays the results..                            */

#include <stdio.h>
#include <stdlib.h>
#include "H323-MESSAGES.h"
#include "rtxsrc/rtxPrintStream.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxFile.h"
#include "rtxsrc/rtxDiag.h"

int main (int argc, char** argv)
{
   H225H323_UserInformation userInfo;

   OSCTXT	ctxt;
   OSOCTET*     pMsgBuf;
   OSBOOL       aligned = TRUE, trace = TRUE, verbose = FALSE;
   const char*  filename = "message.dat";
   int		i, stat;
   OSSIZE       len;
   FILE*        fpLog; /* Pointer to Log file */

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader -a | -u [ -v ] [ -i <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
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

   /* Read input file */
   if (0 != rtxFileReadBinary (&ctxt, filename, &pMsgBuf, &len)) {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   pu_setBuffer (&ctxt, pMsgBuf, len, aligned);
   pu_setTrace (&ctxt, trace);

   /* Set up logging */
   if (0 == rtxFileOpen (&fpLog, "reader.log", "w")) {
      /* Here the callback function is registered as a global
         print handler. This means all print/debug streams
         will be passed to this handler.
      */
      rtxSetGlobalPrintStream (&rtxPrintStreamToFileCB, (void *) fpLog);
   }
   else {
      printf ("Open file reader.log for write access failed\n");
      return -1;
   }
   /* Call compiler generated decode function */

   stat = asn1PD_H225H323_UserInformation (&ctxt, &userInfo);

   if (trace) {
      pu_hexdump (&ctxt);
      pu_bindump (&ctxt, "userInfo");
   }

   if (stat == 0) {
      if (trace) {
         printf ("Decoding was successful. See reader.log for details.\n");
         asn1PrtToStrm_H225H323_UserInformation (NULL, "userInfo", &userInfo);
      }
   }
   else {
       rtxErrPrint (&ctxt);
       return -1;
   }

   fclose (fpLog);
   rtFreeContext (&ctxt);

   return 0;
}
