#include "Employee.h"

#define MAXMSGLEN 1024

int main (int argc, char* argv[])
{
   ASN1T_PersonnelRecord employee;
   const char*  filename = "message.xml";
   OSBOOL       trace = TRUE, verbose = FALSE;
   int          i, len, stat;
   OSOCTET	msgbuf[MAXMSGLEN];
   const OSOCTET* msgptr;
   FILE*        fp;
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

   OSXMLDecodeBuffer decodeBuffer (filename);
   decodeBuffer.setDiag (verbose);

   // Create ASN.1 message objects
   ASN1C_PersonnelRecord employeeC (decodeBuffer, employee);

   stat = employeeC.Decode ();

   if (0 != stat) {
      decodeBuffer.printErrorInfo ();
      return stat;
   }
   else {
      if (trace) employeeC.Print ("employee");
      ASN1BEREncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
      ASN1C_PersonnelRecord employeeC (encodeBuffer, employee);

      // Encode

      if ((len = employeeC.Encode ()) >= 0) {
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

      if (fp = fopen (ofilename, "wb")) {
         fwrite (msgptr, 1, len, fp);
         fclose (fp);
      }
      else {
         printf ("Error opening %s for write access\n", filename);
         return -1;
      }
   }

   return (stat);

}
