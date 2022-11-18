#include "Employee.h"
#include "rtxsrc/rtxStreamFile.h"
#include "rtxsrc/rtxMemLeakCheck.h"

#define MAXMSGLEN 10240

int main (int argc, char* argv[])
{
   PersonnelRecord employee;
   const char*  filename = "message.xml";
   OSCTXT       ctxt;
   OSBOOL       trace = TRUE, verbose = FALSE;
   int          i, len, stat;
   const char*  ofilename = "message.dat";

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-i")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else if (!strcmp (argv[i], "-o")) ofilename = argv[++i];
         else {
            printf ("usage: reader [ -v ] [ -i <filename> ] [ -notrace ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -i <filename>  read XML doc from <filename>\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init context structure */

   stat = rtXmlInitContext (&ctxt);
   if (0 != stat) {
      printf ("context initialization failed\n");
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Open file input stream */

   stat = rtxStreamFileOpen (&ctxt, filename, OSRTSTRMF_INPUT);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return -1;
   }

   /* Call compiler generated decode function */

   stat = XmlDec_PersonnelRecord_PDU (&ctxt, &employee);
   if (stat != 0) {
      printf ("decode of employee record failed\n");
      rtxErrPrint (&ctxt);
      rtxStreamClose (&ctxt);
      return -1;
   }
   if (trace) {
      asn1Print_PersonnelRecord ("PersonnelRecord", &employee);
   }
   rtxStreamClose (&ctxt);

   /* Encode BER message from decoded XML message */

   if (stat == 0) {
      OSCTXT    berctxt;
      OSOCTET   msgbuf[MAXMSGLEN];
      OSOCTET*  msgptr;
      FILE*     fp;

      stat = rtInitContext (&berctxt);
      if (0 != stat) {
         printf ("context initialization failed\n");
         rtxErrPrint (&ctxt);
         return stat;
      }
      rtxSetDiag (&berctxt, verbose);

      /* Encode */

      xe_setp (&berctxt, msgbuf, sizeof(msgbuf));

      if ((len = asn1E_PersonnelRecord (&berctxt, &employee, ASN1EXPL)) > 0)
      {
         printf ("BER Encode of PersonnelRecord was successful\n");
         msgptr = xe_getp (&berctxt);

         if (trace) {
            if (XU_DUMP (msgptr) != 0) 
               printf ("dump of ASN.1 message failed.");
         }
      }
      else {
         rtxErrPrint (&berctxt);
         return len;
      }
     
      // Write the encoded message out to the output file 

      if (fp = fopen (ofilename, "wb")) {
         fwrite (msgptr, 1, len, fp);
         fclose (fp);
      }
      else {
         printf ("Error opening %s for write access\n", filename);
         return -1;
      }
      rtFreeContext (&berctxt);
   }

   rtFreeContext (&ctxt);
   return (stat);

}
