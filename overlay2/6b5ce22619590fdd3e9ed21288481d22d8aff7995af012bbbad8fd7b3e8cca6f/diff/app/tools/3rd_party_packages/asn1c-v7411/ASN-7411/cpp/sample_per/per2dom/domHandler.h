// This is an implementation of an event handler class.  This class 
// outputs the fields of an ASN.1 encoded message to a structure 
// similar to an XML Document Object Model (DOM) tree..

#ifndef _DOMHANDLER_H_
#define _DOMHANDLER_H_

#include "rtsrc/asn1CppEvtHndlr64.h"
#include "rtxsrc/rtxStack.h"

class DOMNode {
 protected:
   DOMNode* next;      // sibling node
   DOMNode* children;  // child nodes
   DOMNode () : next(0), children(0) {}

 public:
   friend class DOMTree;
   enum Type { Element, Text } ;
   virtual ~DOMNode() {}
   virtual const char* getName() const = 0;
   virtual const char* getValue() const = 0;
   virtual OSBOOL isA (Type type) const = 0;
   virtual void print () const = 0;
   void freeNodes ();
   void printNodes (int level);
} ;

class DOMElemNode : public DOMNode {
 protected:
   const char* mName;
 public:
   DOMElemNode (const char* name) : DOMNode(), mName(name) {}
   virtual const char* getName() const { return mName; }
   virtual const char* getValue() const { return 0; }
   virtual OSBOOL isA (Type type) const { return (type == Element); }
   virtual void print () const { printf ("element node : '%s'\n", mName); }
} ;

class DOMTextNode : public DOMNode {
 protected:
   char* mValue;
 public:
   DOMTextNode (const char* value);
   virtual ~DOMTextNode() { delete [] mValue; }
   virtual const char* getName() const { return "TEXT"; }
   virtual const char* getValue() const { return mValue; }
   virtual OSBOOL isA (Type type) const { return (type == Text); }
   virtual void print () const { printf ("text node : '%s'\n", mValue); }
} ;

class DOMTree {
 protected:
   DOMNode* mpRoot;
   DOMNode* mpCurrNode;
   OSRTStack mNodeStack;

 public:
   DOMTree (OSCTXT* pctxt);
   ~DOMTree ();
   void addChild (DOMNode* pNode);
   void addSibling (DOMNode* pNode);
   void moveUpOneLevel ();
   const char* getValue (const char* elemName);
   void print ();
} ;

class DOMHandler : public Asn1NamedEventHandler64 {
 protected:
   DOMTree mDOMTree;
   const char* mVarName;
   enum State { Init, Start, Data, End } mState;

 public:
   DOMHandler (OSCTXT* pctxt, const char* varName);
   ~DOMHandler ();
   DOMTree& getTree() { return mDOMTree; }
   virtual void startElement (const char* name, OSSIZE index = OSNULLINDEX);
   virtual void endElement (const char* name, OSSIZE index = OSNULLINDEX);
   virtual void boolValue (OSBOOL value);
   virtual void intValue (OSINT32 value);
   virtual void uIntValue (OSUINT32 value);
   virtual void bitStrValue (OSSIZE numbits, const OSOCTET* data);
   virtual void octStrValue (OSSIZE numocts, const OSOCTET* data);
   virtual void charStrValue (const char* value);
   virtual void charStrValue (OSSIZE nchars, OSUNICHAR* data);
   virtual void charStrValue (OSSIZE nchars, OS32BITCHAR* data);
   virtual void nullValue ();
   virtual void oidValue (OSUINT32 numSubIds, OSUINT32* pSubIds);
   virtual void realValue (double value);
   virtual void enumValue (OSUINT32 value, const OSUTF8CHAR* text=NULL);
   virtual void openTypeValue (OSSIZE numocts, const OSOCTET* data);

};

#endif
