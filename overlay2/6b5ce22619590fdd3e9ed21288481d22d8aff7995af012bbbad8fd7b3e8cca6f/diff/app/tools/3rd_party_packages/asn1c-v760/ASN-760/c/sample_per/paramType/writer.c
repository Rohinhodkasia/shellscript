/* This test driver program encodes a data record and writes the        */
/* encoded result to an output file..                                   */

#include <stdio.h>
#include <stdlib.h>
#include "ParamType.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxsrc/rtxFile.h"

#define MAXMSGLEN 1024

static void fill_SignedName(SignedName* p);

int main (int argc, char** argv)
{
   SignedName   signedName;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN], *msgptr;
   OSBOOL       verbose = FALSE, trace = TRUE;
   const char*  filename = "message.dat";
   int		i, len, stat;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Create a new context structure */

   if (rtInitContext (&ctxt) != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }
   rtxSetDiag (&ctxt, verbose);
   pu_setBuffer (&ctxt, msgbuf, sizeof(msgbuf), TRUE);
   pu_setTrace (&ctxt, trace);

   /* Populate signedName structure (note: this is the structure that   */
   /* was generated by the compiler)..					*/

   fill_SignedName (&signedName);

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_SignedName ("signedName", &signedName);
      printf ("\n");
   }

   /* Encode */

   if ((stat = asn1PE_SignedName (&ctxt, &signedName)) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         pu_hexdump (&ctxt);
         printf ("Binary dump:\n");
         pu_bindump (&ctxt, "signedName");
      }
   }
   else {
      printf ("Encoding failed\n");
      rtxErrPrint (&ctxt);
      return -1;
   }
  
   msgptr = pe_GetMsgPtr (&ctxt, &len);

   /* Write the encoded message out to the output file */

   stat = rtxFileWriteBinary(filename, msgptr, (OSSIZE)len);
   if (0 != stat) {
      printf ("Error opening %s for write access\n", filename);
   }
   else if (trace) {
      printf ("Wrote %d bytes to file %s..\n", len, filename);
   }
   
   rtFreeContext (&ctxt);

   return 0;
}


/* Routine to fill record with test data */

static void fill_Name (Name* pName, char* fn, char* mi, char* ln);

static ASN1OBJID algorithmOIDValue = {
   6, { 0, 0, 8, 2250, 0, 1 }
} ;

static OSOCTET signatureValue[] = {
   0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
} ;

static void fill_SignedName (SignedName* p)
{
   int i;
   memset (p, 0, sizeof(SignedName));

   fill_Name (&p->toBeSigned, "John", "P", "Smith");

   rtSetOID (&p->algorithmOID, &algorithmOIDValue);

   p->paramS.m.ranIntPresent = 1;
   p->paramS.m.iv8Present = 1;
   p->paramS.ranInt = 222;
   p->paramS.iv8.numocts = 8;
   for (i = 0; i < 8; i++) {
      p->paramS.iv8.data[i] = i + 0x7d;
   }

   p->signature_.numbits = sizeof(signatureValue) * 8;
   p->signature_.data = signatureValue;
}

/* Routine to fill a name structure */

static void fill_Name (Name* pName, char* fn, char* mi, char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->familyName = ln;
}
