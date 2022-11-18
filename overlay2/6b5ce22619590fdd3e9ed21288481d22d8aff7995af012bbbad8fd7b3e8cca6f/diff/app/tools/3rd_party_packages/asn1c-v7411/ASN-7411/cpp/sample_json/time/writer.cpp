// This test driver program encodes a data record and writes the        
// encoded result to an output file..                                   

#include <stdio.h>
#include <stdlib.h>
#include "TimeString.h"
#include "rtsrc/ASN1CTime.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxDiag.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int		i;
   const OSOCTET* msgptr;
   FILE*        fp;
   const char*  filename = "message.json";
   OSBOOL       verbose = FALSE; 
   OSOCTET msgbuf[1024];

   // Process command line arguments 

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) filename = argv[++i];
         else if (!strcmp (argv[i], "-notrace")) { }
         else {
            printf ("usage: writer [ -v ] [ -o <filename>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <filename>  write encoded msg to <filename>\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   // Populate structure of generated type 

   OSJSONEncodeBuffer encodeBuffer (msgbuf, sizeof(msgbuf));
   encodeBuffer.setDiag (verbose);
   ASN1T_TimesSeq msgData;
   ASN1C_TimesSeq tmSeq (encodeBuffer, msgData);

   msgData.genTime = 0;
   ASN1CGeneralizedTime gtt(encodeBuffer, msgData.genTime);
   time_t ltime;
   time(&ltime);
   int stat = 0;

   stat = gtt.setTime(ltime, TRUE);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }
   stat = gtt.setFraction(3);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   msgData.utcTime = 0;
   ASN1CUTCTime utt(encodeBuffer, msgData.utcTime);
   utt.clear();
   stat = utt.setYear(1985);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   stat = utt.setMonth(ASN1CTime::February);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   stat = utt.setDay(22);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   stat = utt.setHour(5);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   stat = utt.setMinute(35);
   if (stat != 0) {
      encodeBuffer.printErrorInfo ();
      exit(-1);
   }

   // Encode in a dynamic buffer 
   stat = tmSeq.Encode();

   if (stat == 0) {
         printf ("Encoding was successful\n");
         msgptr = encodeBuffer.getMsgPtr ();
   }
   else {
      printf ("Encoding failed\n");
      encodeBuffer.printErrorInfo ();
      exit (-1);
   }
  
   // Write the encoded message out to the output file 

   if (fp = fopen (filename, "wb")) {
      fwrite (msgptr, 1, strlen((const char *)msgptr), fp);
      fclose (fp);
   }
   else {
      printf ("Error opening %s for write access\n", filename);
      return -1;
   }

   return 0;

}
