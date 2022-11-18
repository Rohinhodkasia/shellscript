/* Test driver to read and decode an encoded ASN.1 message */

#include <stdio.h>
#include <stdlib.h>
#include "AIN-Operation.h"
#include "TCAPMessages.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

#define MAXMSGLEN 1024

int main (int argc, char** argv)
{
   MessageType  messageType;
   Invoke*      pInvoke;
   Component*   pComponent;
   CallInfoFromResource_ARGUMENT param;
   OSCTXT	ctxt;
   OSOCTET	msgbuf[MAXMSGLEN];
   int		i, stat;
   OSSIZE       len;
   FILE*        fp;
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

   /* Read input file into a memory buffer */

   if (0 != (fp = fopen (filename, "rb"))) {
      len = fread (msgbuf, 1, sizeof(msgbuf), fp);
   }
   else {
      printf ("Error opening %s for read access\n", filename);
      return -1;
   }

   /* Init context structure */

   stat = rtInitContext (&ctxt);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }
   rtxSetDiag (&ctxt, verbose);

   stat = xd_setp64 (&ctxt, msgbuf, len, 0, 0, 0);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   if (trace) XU_DUMP (msgbuf);

   /* Decode TCAP header */

   stat = asn1D_MessageType (&ctxt, &messageType, ASN1EXPL, 0);

   if (stat == 0) {
      if (trace) {
         printf ("Decode of MessageType was successful\n");
         asn1Print_MessageType ("MessageType", &messageType);
      }
   }
   else {
      rtxErrPrint (&ctxt); 
      printf ("Decode of MessageType failed\n");
      return -1;
   }

   /* Decode parameter */

   pComponent = (Component*) 
      messageType.u.undirectional->components.head->data;

   pInvoke = pComponent->u.invoke;

   stat = xd_setp64 (&ctxt, 
                     pInvoke->parameter.data, 
                     pInvoke->parameter.numocts,
                     0, 0, 0);

   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   stat = asn1D_CallInfoFromResource_ARGUMENT (&ctxt, &param, ASN1EXPL, 0);

   if (stat == 0) {
      if (trace) {
         printf ("Decode of CallInfoFromResource_ARGUMENT was successful\n");
         asn1Print_CallInfoFromResource_ARGUMENT ("param", &param);
      }
   }
   else {
      rtxErrPrint (&ctxt); 
      printf ("Decode of CallInfoFromResource_ARGUMENT failed\n");
      return -1;
   }

   rtFreeContext (&ctxt);

   return 0;
}
