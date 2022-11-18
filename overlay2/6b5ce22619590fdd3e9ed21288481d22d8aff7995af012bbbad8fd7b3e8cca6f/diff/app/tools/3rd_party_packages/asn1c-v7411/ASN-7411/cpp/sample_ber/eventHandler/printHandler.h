// This is an implementation of a simple print handler class.  It outputs 
// the fields of an encoded PER message to stdout in a structured output 
// format..

#ifndef _PRINTHANDLER_H_
#define _PRINTHANDLER_H_

#include "rtsrc/asn1CppEvtHndlr.h"

class PrintHandler : public Asn1NamedEventHandler {
 protected:
   const char* mVarName;
   int mIndentSpaces;
   OSBOOL mbTrace;

 public:
   PrintHandler (const char* varName);
   ~PrintHandler ();
   void indent ();
   virtual void startElement (const char* name, int index = -1);
   virtual void endElement (const char* name, int index = -1);
   virtual void boolValue (OSBOOL value);
   virtual void intValue (OSINT32 value);
   virtual void uIntValue (OSUINT32 value);
   virtual void int64Value (OSINT64 value);
   virtual void uInt64Value (OSUINT64 value);
   virtual void bitStrValue (OSUINT32 numbits, const OSOCTET* data);
   virtual void octStrValue (OSUINT32 numocts, const OSOCTET* data);
   virtual void charStrValue (const char* value);
   virtual void charStrValue (OSUINT32 nchars, OSUNICHAR* data);
   virtual void charStrValue (OSUINT32 nchars, OS32BITCHAR* data);
   virtual void charStrValue (OSUINT32 nchars, const OSUTF8CHAR *data);
   virtual void nullValue ();
   virtual void oidValue (OSUINT32 numSubIds, OSUINT32* pSubIds);
   virtual void realValue (double value);
   virtual void enumValue (OSUINT32 value, const OSUTF8CHAR* text);
   virtual void openTypeValue (OSUINT32 numocts, const OSOCTET* data);

   inline void setTrace (OSBOOL value) { mbTrace = value; }
};

#endif
