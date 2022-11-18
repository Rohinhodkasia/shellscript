/**
 * This file was generated by the Objective Systems ASN1C Compiler
 * (http://www.obj-sys.com).  Version: 6.0A, Date: 24-Jul-2006.
 */
#include "Cap.h"
#include "rtxsrc/rtxCommon.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

int main (int argc, char** argv)
{
   const char* filename = "message.xml";
   int         stat, i;
   OSBOOL      trace = TRUE, verbose = FALSE;

   // Process command line arguments
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <filename>] \n");
            printf ("   -v  verbose mode: print debug info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Create an instance of the compiler generated class.
   // This example uses a dynamic message buffer..
   OSXMLEncodeBuffer encodeBuffer (0, 0);
   encodeBuffer.setDiag (verbose);
   ASN1T_Alert msgData;
   ASN1C_Alert AlertPDU (encodeBuffer, msgData);

   msgData.identifier = (const OSUTF8CHAR*) "43b080713727";

   msgData.sender = (const OSUTF8CHAR*) "hsas@dhs.gov";

   msgData.sent = "2003-04-02T14:39:01-05:00";

   msgData.status = Alert_status::actual;

   msgData.msgType = Alert_msgType::alert;

   msgData.m.scopePresent = 1;
   msgData.scope = Alert_scope::public_;

   { ASN1T_Alert_info* pdata1;
   ASN1CSeqOfList listHelper (AlertPDU, msgData.info_list);

   pdata1 = (ASN1T_Alert_info*) AlertPDU.memAlloc (sizeof(ASN1T_Alert_info));
   memset (pdata1, 0, sizeof(ASN1T_Alert_info));

   { static ASN1T_Alert_info_category category_array[] = 
      { Alert_info_category::security };
   pdata1->category_list.n = 1;
   pdata1->category_list.elem = category_array;
   }

   pdata1->event
       = (const OSUTF8CHAR*) "Homeland Security Advisory System Update";

   pdata1->urgency = Alert_info_urgency::immediate;

   pdata1->severity = Alert_info_severity::severe;

   pdata1->certainty = Alert_info_certainty::likely;

   pdata1->m.senderNamePresent = 1;
   pdata1->senderName
       = (const OSUTF8CHAR*) "U.S. Government, Department of Homeland Security";

   pdata1->m.headlinePresent = 1;
   pdata1->headline
       = (const OSUTF8CHAR*) "Homeland Security Sets Code ORANGE";

   pdata1->m.descriptionPresent = 1;
   pdata1->description
       = (const OSUTF8CHAR*) "The Department of Homeland Security has elevated the Homeland Security Advisory System threat level to ORANGE / High in response to intelligence which may indicate a heightened threat of terrorism.";

   pdata1->m.instructionPresent = 1;
   pdata1->instruction
       = (const OSUTF8CHAR*) " A High Condition is declared when there is a high risk of terrorist attacks. In addition to the Protective Measures taken in the previous Threat Conditions, Federal departments and agencies should consider agency specific Protective Measures in accordance with their existing plans.";

   pdata1->m.webPresent = 1;
   pdata1->web
       = (const OSUTF8CHAR*) "http://www.dhs.gov/dhspublic/display?theme=29";

   { ASN1CSeqOfList listHelper (AlertPDU, pdata1->parameter_list);
   listHelper.append ((void*)"HSAS=ORANGE");
   }

   { ASN1T_Alert_info_resource* pdata3;
   ASN1CSeqOfList listHelper (AlertPDU, pdata1->resource_list);
   pdata3 = (ASN1T_Alert_info_resource*) 
      AlertPDU.memAlloc (sizeof(ASN1T_Alert_info_resource));
   memset (pdata3, 0, sizeof(ASN1T_Alert_info_resource));

   pdata3->resourceDesc = (const OSUTF8CHAR*) "Image file (GIF)";

   pdata3->m.uriPresent = 1;
   pdata3->uri
       = (const OSUTF8CHAR*) "http://www.dhs.gov/dhspublic/getAdvisoryImage";

   listHelper.append ((void*)pdata3);
   }

   { ASN1T_Alert_info_area* pdata3;
   ASN1CSeqOfList listHelper (AlertPDU, pdata1->area_list);

   pdata3 = (ASN1T_Alert_info_area*) 
      AlertPDU.memAlloc (sizeof(ASN1T_Alert_info_area));

   memset (pdata3, 0, sizeof(ASN1T_Alert_info_area));

   pdata3->areaDesc
      = (const OSUTF8CHAR*) "U.S. nationwide and interests worldwide";

   listHelper.append ((void*)pdata3);
   }

   listHelper.append ((void*)pdata1);
   }

   // Encode
   if ((stat = AlertPDU.Encode()) == 0) {
      if (trace) {
         printf ("encoded XML message:\n");
         printf ((const char*)encodeBuffer.getMsgPtr());
         printf ("\n");
      }
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      return (-1);
   }

   // Write the encoded message out to the output file
   if (encodeBuffer.write (filename) < 0) {
      printf ("Error writing XML document to file '%s'\n", filename);
      return -1;
   }
   return 0;
}