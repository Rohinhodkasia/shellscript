#include "PKCS-1.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
   const OSOCTET digest[] = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
   };
   DigestInfo   digestInfo;
   OSCTXT       ctxt;
   OSOCTET*     msgptr;
   OSBOOL       trace = TRUE, verbose = FALSE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int          i, len, stat;

   /* Process Command line arguments */
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

   /* Populate digest info */
   asn1Init_DigestInfo (&digestInfo);
   rtSetOID (&digestInfo.digestAlgorithm.algorithm, &id_sha256);
   digestInfo.digestAlgorithm.m.parametersPresent = TRUE;
   digestInfo.digestAlgorithm.parameters.t = 
      T_PKCS_1_PKCS1_v1_5DigestAlgorithms_id_sha256;
   digestInfo.digest.numocts = sizeof(digest);
   digestInfo.digest.data = (OSOCTET*) digest;

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_DigestInfo ("digestInfo", &digestInfo);
      printf ("\n");
   }

   /* Encode - uses dynamic encode buffer*/
   xe_setp (&ctxt, 0, 0);

   if ((len = asn1E_DigestInfo (&ctxt, &digestInfo, ASN1EXPL)) > 0)
   {
      msgptr = xe_getp (&ctxt);
      if (trace) {
         if (XU_DUMP (msgptr) != 0) 
            printf ("dump of ASN.1 message failed.");
      }
   }
   else {
      rtxErrPrint (&ctxt);
      rtFreeContext (&ctxt);
      return (-1);
   }

   /* Write the encoded message out to the output file */

   if ((fp = fopen (filename, "wb"))) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      rtFreeContext (&ctxt);
      return -1;
   }
   rtFreeContext (&ctxt);

   return 0;
}
