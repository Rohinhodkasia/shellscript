// This is an implementation of an event handler class.  This class 
// outputs the fields of an ASN.1 encoded message to stdout in XML 
// format..

#ifndef _XMLHANDLER_H_
#define _XMLHANDLER_H_

#include "rtsrc/asn1CppEvtHndlr64.h"

class XMLHandler : public Asn1NamedEventHandler64 {
 protected:
   const char* mVarName;
   int mIndentSpaces;
   enum State { Init, Start, Data, End } mState;

 public:
   XMLHandler (const char* varName);
   ~XMLHandler ();
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
