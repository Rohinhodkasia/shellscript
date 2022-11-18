#include "rd.h"
#include "rtsrc/asn1CppRawEvtHndlr.h"
#include "rtxsrc/rtxCommon.h"

#include <stdio.h>
#include <stdlib.h>

#define MAXREADLEN 1024

class SampleHandler : public Asn1RawEventHandler
{
private:
   static void indent(OSSIZE cnt)
   {
      for(size_t i = 0; i < cnt; i++) {
         printf("   ");
      }
   }
   
public:
   OSSIZE mIndent;

   SampleHandler() : mIndent(0) {}
   
   ASN1RawEventResp component (OSCTXT* pctxt, OSSIZE componentID,
            OSBOOL nestedValues)
   {
      indent(mIndent);
      printf("Component " OSSIZEFMT "\n", componentID);
      
      if (componentID == RAWID_RAWEVENTS_PDU_RECORD) {
         /* Decode the Record ourselves, and print it.  Then tell the
            parser we've consumed it. */
         ASN1T_Record rec;
         asn1PD_Record(pctxt, &rec);
         printf("The Record is:\n");
         asn1Print_Record("record", &rec);
         
         return ASN1RER_CONSUMED;
      }
      else if (componentID == RAWID_RAWEVENTS_PDU_VALUES ||
               componentID == RAWID_RAWEVENTS__SEQOFVALUETABLE_ELEMENT ||
               componentID == RAWID_RAWEVENTS_VALUETABLE_DATA) {
         /* We want to get events for the above elements */
         mIndent++;
         return ASN1RER_PARSE;
      }
      else return ASN1RER_QUIET_PARSE;
   }

   void endComponent (OSCTXT* pctxt, OSSIZE componentID)
   {
      mIndent--;   
   }

   ASN1RawEventResp actualType (OSCTXT* pctxt, OSSIZE actualTypeID, OSSIZE len)
   {
      indent(mIndent);
      
      /* All branches here return ASN1RER_CONSUMED or ASN1RER_QUIET_PARSE, so
         we won't receive an end component event.  Decrement indent here.
      */
      mIndent--;
      
      if (actualTypeID == 0) {
         printf("Actual type event for unknown type"
            " having length of " OSSIZEFMT "\n", len);
         return ASN1RER_QUIET_PARSE;
      }
      else if (actualTypeID == RAWID_RAWEVENTS_VALUETABLE_DATA_T_ASN1T_RECORD)
      {
         /* Open type's actual type is Record.  Decode it ourselves, and print it.
            Then tell the parser we've consumed it. */
         ASN1T_Record rec;
         asn1PD_Record(pctxt, &rec);
         printf("Open type is Record:\n");
         asn1Print_Record("record", &rec);
         
         return ASN1RER_CONSUMED;
      }   
      else {
         printf("Actual type event for " OSSIZEFMT 
            " having length of " OSSIZEFMT "\n", actualTypeID, len);
         return ASN1RER_QUIET_PARSE;
      }
   }
   
};


int main (int argc, char** argv)
{
   OSBOOL      aligned = TRUE;
   const char* filename = "message.per";
   OSBOOL       trace = TRUE, verbose = FALSE;
   int          i, stat;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-a")) aligned = TRUE;
         else if (!strcmp (argv[i], "-u")) {
            aligned = FALSE;
            filename = "message.uper";
         }
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [-v] [-i <filename>] [-a|-u] [-notrace]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read encoded msg from <filename>\n");
            printf ("   -a  use PER aligned encoding\n");
            printf ("   -u  use PER unaligned encoding\n");
            printf ("   -notrace  do not display trace info\n");
            return 1;
         }
      }
   }

   ASN1PERDecodeBuffer decodeBuffer (aligned);
   decodeBuffer.readBinaryFile (filename);
   if (decodeBuffer.getStatus() != 0) {
      printf("Error opening %s for read access\n", filename);
      decodeBuffer.printErrorInfo();
      return -1;
   }
   decodeBuffer.SetTrace (trace);
   
   SampleHandler handler;
   handler.addEventHandler(decodeBuffer);
   
   stat = asn1PP_PDU(decodeBuffer.getCtxtPtr(), ASN1RER_PARSE);
   if (stat != 0) {
      printf ("decode failed\n");
      decodeBuffer.PrintErrorInfo ();
      return stat;
   }

   if (trace) {
      printf ("Decode of data was successful\n");
   }
   return 0;
}
