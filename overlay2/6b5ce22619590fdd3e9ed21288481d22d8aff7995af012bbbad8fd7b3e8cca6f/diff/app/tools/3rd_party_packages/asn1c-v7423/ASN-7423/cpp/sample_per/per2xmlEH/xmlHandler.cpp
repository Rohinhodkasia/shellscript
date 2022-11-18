// This is an implementation of an event handler class.  This class 
// outputs the fields of an ASN.1 encoded message to stdout in XML 
// format..

#include "xmlHandler.h"
#include "rtsrc/rtconv.h"
#include "rtsrc/rtPrint.h"

XMLHandler::XMLHandler (const char* varName) : 
   mVarName(varName), mIndentSpaces(0)
{
   printf ("<%s>", mVarName);
   mState = Init;
}

XMLHandler::~XMLHandler ()
{
   if (mState == End) {
      mIndentSpaces -= 3;
      indent ();
      printf ("</%s>\n", mVarName);
   }
   else
      printf ("\n");

   if (mIndentSpaces != 0) {
      printf ("ERROR: unbalanced structure\n");
   }
}

void XMLHandler::indent ()
{
   for (int i = 0; i < mIndentSpaces; i++) printf (" ");
}

void XMLHandler::startElement (const char* name, OSSIZE index)
{
   if (mState == Init || mState == Start) {
      printf ("\n");
      mIndentSpaces += 3;
   }
   indent ();
   printf ("<%s>", name);
   mState = Start;
}

void XMLHandler::endElement (const char* name, OSSIZE index)
{
   if (mState == End) {
      mIndentSpaces -= 3;
      indent ();
   }
   printf ("</%s>\n", name);
   mState = End;
}

void XMLHandler::boolValue (OSBOOL value)
{
   const char* s = value ? "true" : "false";
   printf (s);
   mState = Data;
}

void XMLHandler::intValue (OSINT32 value)
{
   printf ("%d", value);
   mState = Data;
}

void XMLHandler::uIntValue (OSUINT32 value)
{
   printf ("%u", value);
   mState = Data;
}

void XMLHandler::bitStrValue (OSSIZE numbits, const OSOCTET* data)
{
   char* s = new char [numbits + 8];
   printf ("%s", rtBitStrToString (numbits, data, s, numbits+8));
   delete [] s;
   mState = Data;
}

void XMLHandler::octStrValue (OSSIZE numocts, const OSOCTET* data)
{
   OSSIZE bufsiz = (numocts * 2) + 8;
   char* s = new char [bufsiz];
   printf ("%s", rtOctStrToString (numocts, data, s, bufsiz));
   delete [] s;
   mState = Data;
}

void XMLHandler::charStrValue (const char* value)
{
   printf ("\"%s\"", value);
   mState = Data;
}

void XMLHandler::charStrValue (OSSIZE nchars, const OSUTF8CHAR* data)
{
   for (OSUINT32 ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("?");
   }
   mState = Data;
}

void XMLHandler::charStrValue (OSSIZE nchars, OSUNICHAR* data)
{
   for (OSUINT32 ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("?");
   }
   mState = Data;
}

void XMLHandler::charStrValue (OSSIZE nchars, OS32BITCHAR* data)
{
   for (OSUINT32 ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("\\%d", data[ui]);
   }
   mState = Data;
}

void XMLHandler::nullValue ()
{
   printf ("= NULL");
   mState = Data;
}

void XMLHandler::oidValue (OSUINT32 numSubIds, OSUINT32* pSubIds)
{
   ASN1OBJID oid;
   oid.numids = numSubIds;

   for (OSUINT32 ui = 0; ui < numSubIds; ui++)
      oid.subid[ui] = pSubIds[ui];

   indent ();
   rtPrintOIDValue (&oid);
   mState = Data;
}

void XMLHandler::realValue (double value)
{
   printf ("%f", value);
   mState = Data;
}

void XMLHandler::enumValue (OSUINT32 value, const OSUTF8CHAR* text)
{
   printf ("%u", value);
   mState = Data;
}

void XMLHandler::openTypeValue (OSSIZE numocts, const OSOCTET* data)
{
   printf ("* encoded data *");
   mState = Data;
}
