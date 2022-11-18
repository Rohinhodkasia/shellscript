#include "Employee.h"
#include "rtxsrc/rtxDiag.h"
#include "rtxmlsrc/rtXmlCppMsgBuf.h"

#define MAXMSGLEN 1024

int main (int argc, char* argv[])
{
   ASN1T_PersonnelRecord employee;
   const char*  filename = "message.xml";
   OSBOOL       trace = TRUE, verbose = FALSE;
   int          i, len, stat;
   OSOCTET      msgbuf[MAXMSGLEN];
   const OSOCTET* msgptr;
   const char*  ofilename = "message.dat";

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

   // Create ASN.1 message objects
   OSXMLDecodeBuffer decodeBuffer (filename);
   decodeBuffer.setDiag (verbose);
   ASN1C_PersonnelRecord employeeCDec (decodeBuffer, employee);

   stat = employeeCDec.Decode ();

   if (0 == stat) {
      if (trace) employeeCDec.Print ("employee");

      ASN1BEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
      encodeBuffer.setDiag (verbose);
      ASN1C_PersonnelRecord employeeCEnc (encodeBuffer, employee);

      // Encode

      if ((len = employeeCEnc.Encode ()) >= 0) {
         if (trace) {
            printf ("Encoding to DER was successful\n");
            printf ("Hex dump of encoded record:\n");
            encodeBuffer.hexDump (len);
            printf ("Binary dump:\n");
            encodeBuffer.binDump ();
         }
         msgptr = encodeBuffer.getMsgPtr ();
      }
      else {
         printf ("Encoding failed\n");
         encodeBuffer.printErrorInfo ();
         return len;
      }
     
      // Write the encoded message out to the output file 

      int ret = rtxFileWriteBinary (ofilename, msgptr, len);
      if (ret < 0) {
         printf ("Write to file %s failed\n", ofilename);
         return ret;
      }
   }
   else {
      decodeBuffer.printErrorInfo ();
   }

   return (stat);

}
