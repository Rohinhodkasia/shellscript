// Custom error handler class.  This is derived from the Asn1ErrorHandler 
// base class.  The only requirement is that the error pure virtual method 
// be implemented..

#ifndef _MYERRORHANDLER_H_
#define _MYERRORHANDLER_H_

#include "asn1CppEvtHndlr.h"

class MyErrorHandler : public Asn1ErrorHandler {
 protected:
   OSBOOL mbTrace;

 public:
   MyErrorHandler() : mbTrace(FALSE) {}

   // The error handler callback method.  This is the method that the user 
   // must override to provide customized error handling..

   virtual int error (OSCTXT* pCtxt, ASN1CCB* pCCB, int stat);

   // Set trace output on or off
   inline void setTrace (OSBOOL value) { mbTrace = value; }
} ;

#endif
