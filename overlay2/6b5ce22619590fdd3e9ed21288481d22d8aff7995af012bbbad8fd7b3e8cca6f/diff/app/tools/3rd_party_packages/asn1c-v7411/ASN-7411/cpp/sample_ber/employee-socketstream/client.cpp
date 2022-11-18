// This test driver program encodes a data record and writes the encoded 
// result to an output stream.

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#include "rtbersrc/ASN1BEREncodeStream.h"
#include "rtxsrc/OSRTSocketOutputStream.h"
#include "rtxsrc/rtxMemLeakCheck.h"
#ifndef WIN32
#include <unistd.h> /* for sleep() */
#endif

#define MAX_ATTEMPTS 10

static void fill_jSmith (ASN1C_PersonnelRecord& ccobj, 
                         ASN1T_PersonnelRecord* pPR);

static void fill_fJones (ASN1C_PersonnelRecord& ccobj, 
                         ASN1T_PersonnelRecord* pPR);

DECLARE_MEMLEAK_DETECTOR;

int main (int argc, char** argv)
{
   int     i;
   OSBOOL  trace = TRUE, verbose = FALSE;
   int     port = 9000;
   char    ipAddress[100];

   // Process command line arguments 

   strcpy (ipAddress, "127.0.0.1");
   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) {
            char* portStr;
            portStr = strchr (argv[++i], ':');
            if (portStr != 0) {
               *portStr = 0;
               strcpy (ipAddress, argv[i]);
               portStr++;
               port = atoi (portStr);
            }
            else
               strcpy (ipAddress, argv[i]);
         }
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: writer [ -v ] [ -o <ip-address:port>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <ip-address:port>  send encoded msg to <ip-address:port>.\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   OSRTSocket socket;

   /* Connect to the destination point */

   if (trace) printf ("Connecting to %s:%i...", ipAddress, port);
   for (i = 0; i < MAX_ATTEMPTS; i++) {
      if (socket.connect (ipAddress, port) == 0) {
         break;
      }
      else {
         if (i + 1 == MAX_ATTEMPTS) {
            printf ("\nConnection is failed, error code is %i\n", 
               socket.getStatus ());
            return socket.getStatus ();
         }
         else if (trace) {
            printf (".");
            fflush (stdout);
         }
      }
   }
   if (trace) printf ("\nConnection is established.\n");

   OSRTSocketOutputStream sockstrm (socket);

   ASN1BEREncodeStream out (sockstrm);
   if (out.getStatus () != 0) {
      out.printErrorInfo ();
      return -1;
   }

   // Create an instance of the compiler generated class.

   ASN1T_PersonnelRecord msgData;
   ASN1C_PersonnelRecord employee (msgData);
   employee.setDiag (verbose);

   // Populate structure of generated type

   fill_jSmith (employee, &msgData);

   // Encode

   out << employee;
   if (out.getStatus () != 0) {
      printf ("Encoding failed. Status = %i\n", out.getStatus());
      out.printErrorInfo ();
      return -1;
   }

   if (trace) {
      printf ("Encoding record 1 was successful\n");
   }

   // Create and send a 2nd instance

   fill_fJones (employee, &msgData);

   out << employee;
   if (out.getStatus () != 0) {
      printf ("Encoding failed. Status = %i\n", out.getStatus());
      out.printErrorInfo ();
      return -1;
   }

   if (trace) {
      printf ("Encoding record 2 was successful\n");
   }

   // Send an EOC to indicate end-of-data

   out.encodeEoc();
   if (out.getStatus () != 0) {
      printf ("Encode EOC failed. Status = %i\n", out.getStatus());
      out.printErrorInfo ();
      return -1;
   }

#ifndef WIN32
   /* We need to add the delay to avoid a bug in some Unix systems when
    * the socket is closed quickly before connection is actually accepted.
    * In this case 'accept()' returns the error and errno == ECONNABORTED. 
    * Client (writer) program does not receive any errors from sockets in 
    * this case. */
   sleep (2);
#endif

   if (trace) printf ("\nConnection is closed.\n");
   return 0;
}


// Routine to fill the employee record with test data 

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln);

static void fill_jSmith (ASN1C_PersonnelRecord& ccobj, 
                         ASN1T_PersonnelRecord* pPR)
{
   ASN1T_ChildInformation* pChildInfo;
   ASN1C__SeqOfChildInformation seqOfChildInfo (ccobj, pPR->children);

   fill_Name (&pPR->name, "John", "P", "Smith");

   pPR->title  = "Director";
   pPR->number = 51;
   pPR->dateOfHire = "19710917";

   fill_Name (&pPR->nameOfSpouse, "Mary", "T", "Smith");

   pPR->m.childrenPresent = TRUE;

   // fill first child record

   pChildInfo = seqOfChildInfo.NewElement();
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = "19571111";
   seqOfChildInfo.Append (pChildInfo);

   // fill second child record

   pChildInfo = seqOfChildInfo.NewElement();
   fill_Name (&pChildInfo->name, "Susan", "B", "Jones");
   pChildInfo->dateOfBirth = "19590717";
   seqOfChildInfo.Append (pChildInfo);

}

static void fill_fJones (ASN1C_PersonnelRecord& ccobj, 
                         ASN1T_PersonnelRecord* pPR)
{
   fill_Name (&pPR->name, "Fred", 0, "Jones");

   pPR->title  = "Programmer";
   pPR->number = 52;
   pPR->dateOfHire = "19720927";

   fill_Name (&pPR->nameOfSpouse, "Joan", "J", "Jones");

   pPR->m.childrenPresent = FALSE;
}

// Routine to fill a name structure

static void fill_Name (ASN1T_Name* pName, 
                       const char* fn, const char* mi, const char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->m.initialPresent = (mi != 0) ? 1 : 0;
   pName->familyName = ln;
}

