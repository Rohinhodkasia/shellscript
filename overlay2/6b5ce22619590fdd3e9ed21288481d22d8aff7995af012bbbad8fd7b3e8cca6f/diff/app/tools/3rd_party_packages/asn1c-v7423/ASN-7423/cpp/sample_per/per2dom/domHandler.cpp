// This is an implementation of an event handler class.  This class 
// outputs the fields of an ASN.1 encoded message to a DOM-like tree 
// structure..

#include "domHandler.h"
#include "rtsrc/rtconv.h"
#include "rtsrc/rtPrint.h"
#include "rtxsrc/osMacros.h"

void DOMNode::freeNodes ()
{
   DOMNode* pNode = this, *pNextNode;
   while (0 != pNode) {
      if (0 != pNode->children) {
         pNode->children->freeNodes();
      }
      pNextNode = pNode->next;
      delete pNode;
      pNode = pNextNode;
   }
}

void DOMNode::printNodes (int level)
{
   DOMNode* pNode = this;
   while (0 != pNode) {
      printf ("%d : ", level);
      pNode->print ();
      if (0 != pNode->children) {
         pNode->children->printNodes (level+1);
      }
      pNode = pNode->next;
   }
}

DOMTextNode::DOMTextNode (const char* value) : DOMNode()
{
   if (0 != value) {
      mValue = new char [strlen(value)+1];
      strcpy (mValue, value);
   }
   else mValue = 0;
}

DOMTree::DOMTree (OSCTXT* pctxt) : mpRoot(0), mpCurrNode(0)
{
   rtxStackInit (pctxt, &mNodeStack);
}

DOMTree::~DOMTree ()
{
   if (0 != mpRoot) mpRoot->freeNodes();
}

void DOMTree::addChild (DOMNode* pNode)
{
   if (0 == mpCurrNode) {
      mpRoot = pNode;
   }
   else if (0 == mpCurrNode->children) {
      mpCurrNode->children = pNode;
   }
   else {
      DOMNode* pChildNode = mpCurrNode->children;
      while (0 != pChildNode->next) {
         pChildNode = pChildNode->next;
      }
      pChildNode->next = pNode;
   }

   if (pNode->isA (DOMNode::Element)) {
      if (0 != mpCurrNode) {
         rtxStackPush (&mNodeStack, (void*)mpCurrNode);
      }
      mpCurrNode = pNode;
   }
}

void DOMTree::addSibling (DOMNode* pNode)
{
   if (0 != mpCurrNode && 0 == mpCurrNode->next) {
      mpCurrNode->next = pNode;
      mpCurrNode = pNode;
   }
}

void DOMTree::moveUpOneLevel ()
{
   mpCurrNode = (DOMNode*) rtxStackPop (&mNodeStack);
}

const char* DOMTree::getValue (const char* elemName)
{
   char* workbuf = new char [strlen(elemName)+1];
   strcpy (workbuf, elemName);
   const char* tok = strtok (workbuf, ".");
   const char* nodeName;
   DOMNode* pnode = mpRoot;
   while (0 != tok) {
      while (0 != pnode) {
         nodeName = pnode->getName();
         if (0 != nodeName && !strcmp (tok, nodeName))
            break;
         else
            pnode = pnode->next;
      }
      if (0 != pnode) {
         tok = strtok (NULL, ".");
         if (0 != tok) pnode = pnode->children;
      }
   }
   delete [] workbuf;
   if (0 != pnode && 0 != pnode->children) {
      return pnode->children->getValue();
   }
   return 0;
}

void DOMTree::print ()
{
   if (0 != mpRoot) mpRoot->printNodes (1);
}

DOMHandler::DOMHandler (OSCTXT* pctxt, const char* varName) : 
   mVarName(varName), mDOMTree(pctxt)
{
   DOMNode* pDOMNode = new DOMElemNode (varName);
   mDOMTree.addChild (pDOMNode);
   mState = Init;
}

DOMHandler::~DOMHandler ()
{
}

void DOMHandler::startElement (const char* name, OSSIZE index)
{
   DOMNode* pDOMNode = new DOMElemNode (name);
   if (mState == Init || mState == Start) {
      mDOMTree.addChild (pDOMNode);
   }
   else {
      mDOMTree.addSibling (pDOMNode);
   }
   mState = Start;
}

void DOMHandler::endElement (const char* name, OSSIZE index)
{
   if (mState == End) {
      mDOMTree.moveUpOneLevel();
   }
   mState = End;
}

void DOMHandler::boolValue (OSBOOL value)
{
   const char* s = value ? "true" : "false";
   DOMNode* pDOMNode = new DOMTextNode (s);
   mDOMTree.addChild (pDOMNode);
   mState = Data;
}

void DOMHandler::intValue (OSINT32 value)
{
   char strbuf[32];
   os_snprintf (strbuf, sizeof(strbuf), "%d", value);
   DOMNode* pDOMNode = new DOMTextNode (strbuf);
   mDOMTree.addChild (pDOMNode);
   mState = Data;
}

void DOMHandler::uIntValue (OSUINT32 value)
{
   char strbuf[32];
   os_snprintf (strbuf, sizeof(strbuf), "%u", value);
   DOMNode* pDOMNode = new DOMTextNode (strbuf);
   mDOMTree.addChild (pDOMNode);
   mState = Data;
}

void DOMHandler::bitStrValue (OSSIZE numbits, const OSOCTET* data)
{
   char* s = new char [numbits + 8];
   rtBitStrToString (numbits, data, s, numbits+8);
   DOMNode* pDOMNode = new DOMTextNode (s);
   mDOMTree.addChild (pDOMNode);
   delete [] s; // DOMTextNode ctor will make copy
   mState = Data;
}

void DOMHandler::octStrValue (OSSIZE numocts, const OSOCTET* data)
{
   OSSIZE bufsiz = (numocts * 2) + 8;
   char* s = new char [bufsiz];
   rtOctStrToString (numocts, data, s, bufsiz);
   DOMNode* pDOMNode = new DOMTextNode (s);
   mDOMTree.addChild (pDOMNode);
   delete [] s; // DOMTextNode ctor will make copy
   mState = Data;
}

void DOMHandler::charStrValue (const char* value)
{
   DOMNode* pDOMNode = new DOMTextNode (value);
   mDOMTree.addChild (pDOMNode);
   mState = Data;
}

void DOMHandler::charStrValue (OSSIZE nchars, OSUNICHAR* data)
{
   /* TODO: implement */
   mState = Data;
}

void DOMHandler::charStrValue (OSSIZE nchars, OS32BITCHAR* data)
{
   /* TODO: implement */
   mState = Data;
}

void DOMHandler::nullValue ()
{
   DOMNode* pDOMNode = new DOMTextNode ("NULL");
   mDOMTree.addChild (pDOMNode);
   mState = Data;
}

void DOMHandler::oidValue (OSUINT32 numSubIds, OSUINT32* pSubIds)
{
   size_t bufsiz = numSubIds * 5; // 5 chars per subid should be enough
   char* s = new char [bufsiz]; 
   rtOIDToString (numSubIds, pSubIds, s, bufsiz);
   DOMNode* pDOMNode = new DOMTextNode (s);
   mDOMTree.addChild (pDOMNode);
   delete [] s; // DOMTextNode ctor will make copy
   mState = Data;
}

void DOMHandler::realValue (double value)
{
   char s[100];
   os_snprintf (s, 100, "%f", value);
   DOMNode* pDOMNode = new DOMTextNode (s);
   mDOMTree.addChild (pDOMNode);
   mState = Data;
}

void DOMHandler::enumValue (OSUINT32 value, const OSUTF8CHAR* text)
{
   char strbuf[32];
   os_snprintf (strbuf, 32, "%u", value);
   DOMNode* pDOMNode = new DOMTextNode (strbuf);
   mDOMTree.addChild (pDOMNode);
   mState = Data;
}

void DOMHandler::openTypeValue (OSSIZE numocts, const OSOCTET* data)
{
   DOMHandler::octStrValue (numocts, data);
}
