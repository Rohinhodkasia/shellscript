// This test driver program encodes a data record and writes the encoded 
// result to an output file..

#include <stdio.h>
#include <stdlib.h>
#include "ParamType.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

static void fill_SignedName  (ASN1T_SignedName* p);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   const OSOCTET* msgptr;
   OSOCTET	msgbuf[MAXMSGLEN];
   OSBOOL       verbose = FALSE, aligned = TRUE, trace = TRUE;
   FILE*        fp;
   const char*  filename = "message.dat";
   int		i, len, stat;

   // Process command line arguments

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) aligned = FALSE;
         else if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer -a | -u [ -v ] [ -o <filename> ] ");
            printf ("[ -notrace ]\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Create an instance of the compiler generated class.  This
   // example uses a static message buffer..

   ASN1PEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf), aligned);
   ASN1T_SignedName msgData;
   ASN1C_SignedName signedName (encodeBuffer, msgData);

   // Populate the msgData structure

   fill_SignedName (&msgData);

   if (trace) {
      printf ("The following record will be encoded:\n");
      asn1Print_SignedName ("signedName", &msgData);
      printf ("\n");
   }

   // Encode

   encodeBuffer.SetTrace (trace);

   if ((stat = signedName.Encode ()) == 0) {
      if (trace) {
         printf ("Encoding was successful\n");
         printf ("Hex dump of encoded record:\n");
         encodeBuffer.HexDump ();
         printf ("Binary dump:\n");
         encodeBuffer.BinDump ("signedName");
      }
      msgptr = encodeBuffer.getMsgPtr ();
      len = encodeBuffer.GetMsgLen ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.PrintErrorInfo ();
      return -1;
   }
  
   // Write the encoded message out to the output file

   if (fp = fopen (filename, "wb")) {
      fwrite (msgptr, 1, len, fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   return 0;

}


/* Routine to fill record with test data */

static ASN1OBJID algorithmOIDValue = {
   6, { 0, 0, 8, 2250, 0, 1 }
} ;

static OSOCTET signatureValue[] = {
   0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
} ;

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->familyName = ln;
}

static void fill_SignedName (ASN1T_SignedName* p)
{
   int i;

   fill_Name (&p->toBeSigned, "John", "P", "Smith");

   p->algorithmOID = algorithmOIDValue;

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
