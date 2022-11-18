/* This test driver program encodes a data record and writes the        */
/* encoded result to an output stream.                                  */

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"
#ifndef WIN32
#include <unistd.h> /* for sleep() */
#endif
#include "rtxsrc/rtxMemLeakCheck.h"
#include "rtxsrc/rtxStreamSocket.h"
#include "rtxsrc/rtxDiag.h"

#define MAX_ATTEMPTS 10

static void fill_jSmith (OSCTXT* pctxt, PersonnelRecord* pPR);

int main (int argc, char** argv)
{
   PersonnelRecord employee;
   OSCTXT	ctxt;
   int		i, stat, port = 9000;
   const char* ipAddress = "127.0.0.1";
   OSBOOL       verbose = FALSE, trace = TRUE;

   DECLARE_MEMLEAK_DETECTOR;

   /* Process command line arguments */

   if (argc > 1) {
      for (i = 1; i < argc; i++) {
         if (!strcmp (argv[i], "-v")) verbose = TRUE;
         else if (!strcmp (argv[i], "-o")) {
            char* portStr;
            ipAddress = argv[++i];
            portStr = strchr (ipAddress, ':');
            if (portStr != 0) {
               *portStr = 0;
               portStr++;
               port = atoi (portStr);
            }
         }
         else if (!strcmp (argv[i], "-notrace")) trace = FALSE;
         else {
            printf ("usage: client [ -v ] [ -o <ip-address:port>\n");
            printf ("   -v  verbose mode: print trace info\n");
            printf ("   -o <ip-address:port>  send encoded msg to <ip-address:port>.\n");
            printf ("   -notrace  do not display trace info\n");
            return 0;
         }
      }
   }

   /* Init socket library */

   rtxSocketsInit ();

   /* Init context */

   if ((stat = rtInitContext (&ctxt)) != 0) {
      printf ("Initialization failed, status %d\n", stat);
      return -1;
   }

   rtxSetDiag (&ctxt, verbose);

   stat = rtxStreamSocketCreateWriter (&ctxt, ipAddress, port);
   if (stat != 0) {
      rtxErrPrint (&ctxt);
      return stat;
   }

   /* Populate structure of generated type */

   fill_jSmith (&ctxt, &employee);

   /* Encode */

   if (asn1BSE_PersonnelRecord (&ctxt, &employee, ASN1EXPL) != 0) 
   {
      rtxErrPrint (&ctxt);
      berStrmFreeContext (&ctxt);
      return (-1);
   }

#ifndef WIN32
   /* We need to add the delay to avoid a bug in some Unix systems when
    * the socket is closed quickly before connection is actually accepted.
    * In this case 'accept()' returns the error and errno == ECONNABORTED. 
    * Client (writer) program does not receive any errors from sockets in 
    * this case. */
   sleep (2);
#endif

   //rtxStreamSocketClose will flush, so this isn't strictly necessary
   //in this case; we'd want it if we were going to keep the stream open.
   rtxStreamFlush(&ctxt);
   
   rtxStreamSocketClose (&ctxt);

   if (trace) printf ("\nConnection is closed.\n");

   berStrmFreeContext (&ctxt);
   return 0;
}


/* Routine to fill the employee record with test data */

static void fill_Name (Name* pName, char* fn, char* mi, char* ln);

static void fill_jSmith (OSCTXT* pctxt, PersonnelRecord* pPR)
{
   ChildInformation* pChildInfo;

   fill_Name (&pPR->name, "John", "P", "Smith");

   pPR->title  = "Director";
   pPR->number = 51;
   pPR->dateOfHire = "19710917";

   fill_Name (&pPR->nameOfSpouse, "Mary", "T", "Smith");
   pPR->m.nameOfSpousePresent = 1;
   pPR->m.childrenPresent = 1;
   pPR->m.dateOfFirePresent = 0;

   rtxDListInit (&pPR->children);

   /* fill first child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);
   fill_Name (&pChildInfo->name, "Ralph", "T", "Smith");
   pChildInfo->dateOfBirth = "19571111";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);

   /* fill second child record */

   pChildInfo = rtxMemAllocType (pctxt, ChildInformation);
   fill_Name (&pChildInfo->name, "Susan", 0, "Jones");
   pChildInfo->dateOfBirth = "19590717";
   rtxDListAppend (pctxt, &pPR->children, pChildInfo);
}

/* Routine to fill a name structure */

static void fill_Name (Name* pName, char* fn, char* mi, char* ln)
{
   pName->givenName = fn;
   pName->initial = mi;
   pName->m.initialPresent = (mi != 0) ? 1 : 0;
   pName->familyName = ln;
}

