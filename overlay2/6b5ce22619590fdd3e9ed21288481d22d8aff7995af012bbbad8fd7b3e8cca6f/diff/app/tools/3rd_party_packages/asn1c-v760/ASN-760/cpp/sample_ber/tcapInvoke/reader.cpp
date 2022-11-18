/* Test driver to read and decode an encoded ASN.1 message */

#include <stdio.h>
#include <stdlib.h>
#include "AIN-Operation.h"
#include "TCAPMessages.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int		i, stat;
   const char*  filename = "message.dat";
   OSBOOL       verbose = FALSE, trace = TRUE;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Read input file into a memory buffer */

   ASN1T_MessageType msgData;
   ASN1BERDecodeBuffer decodeBuffer;
   decodeBuffer.setDiag (verbose);
   ASN1C_MessageType messageType (decodeBuffer, msgData);

   decodeBuffer.readBinaryFile (filename);

   if (decodeBuffer.getStatus() != 0) {
      printf ("Error opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo ();
      return -1;
   }

   if (trace) decodeBuffer.binDump();

   /* Decode TCAP header */

   stat = messageType.Decode ();

   if (stat == 0) {
      if (trace) {
         printf ("\nDecode of MessageType was successful\n");
         messageType.Print ("MessageType");
      }
   }
   else {
      printf ("\nDecode of MessageType failed\n");
      decodeBuffer.printErrorInfo ();
      return -1;
   }

   /* Decode parameters */

   ASN1BERDecodeBuffer decodeBuffer2;
   decodeBuffer2.setDiag (verbose);

   ASN1T_CallInfoFromResource_ARGUMENT msgData2;
   ASN1C_CallInfoFromResource_ARGUMENT argument (decodeBuffer2, msgData2);

   ASN1CSeqOfList componentList 
      (decodeBuffer, msgData.u.undirectional->components);

   ASN1CSeqOfListIterator* iter = componentList.iterator ();

   while (iter->hasNext ()) {
      ASN1T_Component* pComponent = (ASN1T_Component*) iter->next();

      ASN1T_Invoke* pInvoke = pComponent->u.invoke;

      decodeBuffer2.setBuffer (pInvoke->parameter.data, 
                               pInvoke->parameter.numocts);

      stat = argument.Decode ();

      if (stat == 0) {
         if (trace) {
            printf ("\nDecode of CallInfoFromResource_ARGUMENT "
                    "was successful\n");
            argument.Print ("argument");
         }
      }
      else {
         printf ("\nDecode of CallInfoFromResource_ARGUMENT failed\n");
         decodeBuffer2.printErrorInfo ();
         return -1;
      }
   }

   return 0;
}
