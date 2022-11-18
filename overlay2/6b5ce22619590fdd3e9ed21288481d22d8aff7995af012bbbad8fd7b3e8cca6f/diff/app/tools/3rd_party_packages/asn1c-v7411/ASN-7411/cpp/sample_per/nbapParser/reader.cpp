// This test driver program reads an encoded record from a file
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "NBAP-PDU-Descriptions.h"
#include "printHandler.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   OSBOOL       verbose = FALSE, trace = TRUE;
   const char*  filename = "message.bin";
   int          i, stat;

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-a")) ; /* just skip */
         else if (!strcmp (argv[i], "-u")) ; /* just skip */
         else {
            printf ("usage: reader [ -v ] [ -i <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Read input file into a memory buffer 

   ASN1PERDecodeBuffer decodeBuffer (FALSE);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus() != 0) {
      printf("Error opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   ASN1C_NBAP_PDU pdu (decodeBuffer);

   // Create and register an event handler object

   Asn1NamedEventHandler* pHandler;
   if (trace)
      pHandler = new PrintHandler ("NBAP_PDU");
   else
      pHandler = new Asn1NullEventHandler64();

   decodeBuffer.addEventHandler (pHandler);

   // Call compiler generated parse function

   decodeBuffer.SetTrace (trace);

   stat = pdu.Parse ();

   delete pHandler;

   if (stat == 0) {
      if (trace) {
         printf ("parse was successful\n");
      }
   }
   else {
       printf ("parse failed\n");
       decodeBuffer.PrintErrorInfo ();
       return -1;
   }

   return 0;
}
