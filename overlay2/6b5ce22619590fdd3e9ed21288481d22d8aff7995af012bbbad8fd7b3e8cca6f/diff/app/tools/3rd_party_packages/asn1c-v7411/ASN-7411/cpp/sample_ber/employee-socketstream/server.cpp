// This test driver program reads an encoded record from a file 
// and decodes it and displays the results..

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtbersrc/ASN1BERDecodeStream.h"
#include "rtxsrc/OSRTSocketInputStream.h"
#include "rtxsrc/rtxMemLeakCheck.h"

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   ASN1TAG	tag;
   int		i, len;
   const char*  filename = "message.dat";
   OSBOOL       trace = TRUE, verbose = FALSE;
   int		port = 9000, destPort;
   char         ipAddressStr[100];
   OSIPADDR     destIP;

   // Process command line arguments

   strcpy (ipAddressStr, "127.0.0.1");
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-l")) {
            char* portStr;
            portStr = strchr (argv[++i], ':');
            if (portStr != 0) {
               *portStr = 0;
               strcpy (ipAddressStr, argv[i]);
               portStr++;
               port = atoi (portStr);
            }
            else
               strcpy (ipAddressStr, argv[i]);
         }
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: reader [ -v ] [ -l <ip-address:port> ]\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -l <ip-address:port>  bind local <ip-address:port>.\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   OSRTSocket listenSocket;

   if (listenSocket.bind (ipAddressStr, port) != 0) {
      printf ("listenSocket.bind failed, status %d\n", 
         listenSocket.getStatus ());
      return -1;
   }

   if (listenSocket.listen (1) != 0) {
      printf ("listenSocket.listen failed, status %d\n", 
         listenSocket.getStatus ());
      return -1;
   }

   if (trace) printf ("Wait for connection...\n");
   
   OSRTSocket* socket = listenSocket.accept (&destIP, &destPort);
   if (listenSocket.getStatus () != 0) {
      printf ("listenSocket.accept failed, status %d\n", 
         listenSocket.getStatus ());
      return -1;
   }

   if (trace) {
      char addr[100];

      printf ("Connection is established with %s:%d\n", 
         OSRTSocket::addrToString (destIP, addr, sizeof (addr)), destPort);
   }

   // Decode 

   OSRTSocketInputStream sockstrm (*socket);

   ASN1BERDecodeStream in (sockstrm);
   if (in.getStatus () != 0) {
      in.printErrorInfo ();
      return -1;
   }

   for (;;) {
      if (in.peekTagAndLen (tag, len) != 0) {
         printf ("peekTagAndLen failed\n");
         in.printErrorInfo ();
         return -1;
      }

      printf ("tag = %d, length = %d\n", tag, len);

      // If EOC, exit loop
      if (0 == tag && 0 == len) break;

      // Verify record is a personnel record

      if (tag == TV_PersonnelRecord) {

         // Decode
      
         ASN1T_PersonnelRecord msgData;
         ASN1C_PersonnelRecord employee (msgData);

         in >> employee;
         if (in.getStatus () != 0) {
            printf ("decode of PersonnelRecord failed\n");
            in.printErrorInfo ();
            return -1;
         }

         if (trace) {
            printf ("Decode of PersonnelRecord was successful\n");
            printf ("Decoded record:\n");
            employee.Print("Employee");
         }
      }
      else {
         printf ("unexpected tag %hx received\n", tag);
         return -1;
      }
   }

   socket->close (); 
   delete socket;
   return 0;
}
