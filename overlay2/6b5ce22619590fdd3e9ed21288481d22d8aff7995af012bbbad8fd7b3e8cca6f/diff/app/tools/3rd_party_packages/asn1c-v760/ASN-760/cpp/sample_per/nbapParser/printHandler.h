// This is an implementation of a simple print handler class.  It outputs 
// the fields of an encoded PER message to stdout in a structured output 
// format..

#ifndef _PRINTHANDLER_H_
#define _PRINTHANDLER_H_

#include "rtsrc/asn1CppEvtHndlr64.h"

class PrintHandler : public Asn1NamedEventHandler64 {
 protected:
   const char* mVarName;
   int mIndentSpaces;
   enum State { Init, Start, Data, End } mState;

 public:
   PrintHandler (const char* varName);
   ~PrintHandler ();
   void indent ();
   virtual void startElement (const char* name, OSSIZE index = OSNULLINDEX);
   virtual void endElement (const char* name, OSSIZE index = OSNULLINDEX);
   virtual void boolValue (OSBOOL value);
   virtual void intValue (OSINT32 value);
   virtual void uIntValue (OSUINT32 value);
   virtual void bitStrValue (OSSIZE numbits, const OSOCTET* data);
   virtual void octStrValue (OSSIZE numocts, const OSOCTET* data);
   virtual void charStrValue (const char* value);
   virtual void charStrValue (OSSIZE nchars, const OSUTF8CHAR* data);
   virtual void charStrValue (OSSIZE nchars, OSUNICHAR* data);
   virtual void charStrValue (OSSIZE nchars, OS32BITCHAR* data);
   virtual void nullValue ();
   virtual void oidValue (OSUINT32 numSubIds, OSUINT32* pSubIds);
   virtual void realValue (double value);
   virtual void enumValue (OSUINT32 value, const OSUTF8CHAR* text=NULL);
   virtual void openTypeValue (OSSIZE numocts, const OSOCTET* data);

};

#endif
