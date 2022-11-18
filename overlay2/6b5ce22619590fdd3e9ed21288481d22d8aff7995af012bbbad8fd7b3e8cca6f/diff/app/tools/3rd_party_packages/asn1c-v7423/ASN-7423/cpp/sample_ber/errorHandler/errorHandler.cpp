// Custom error handler implementation

#include "errorHandler.h"
#include "asn1ber.h"

int MyErrorHandler::error (OSCTXT* pCtxt, ASN1CCB* pCCB, int stat)
{
   // This handler is set up to look explicitly for RTERR_NOTINSET 
   // errors because we know the SET might contain some bogus elements..

   if (stat == RTERR_NOTINSET) {

      // Print information on the error that was encountered

      if (mbTrace) {
         printf ("decode error detected:\n");
         rtxErrPrint (pCtxt);
         printf ("\n");
      }

      // Skip element

      xd_NextElement (pCtxt);

      // Return an OK status to indicate parsing can continue

      return 0;
   }

   else return stat;  // pass existing status back out

}

