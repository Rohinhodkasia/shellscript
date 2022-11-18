// This is an implementation of a simple print handler class.  It outputs 
// the fields of an encoded PER message to stdout in a structured output 
// format..

#include "printHandler.h"
#include "rtsrc/rtconv.h"
#include "rtsrc/rtPrint.h"

PrintHandler::PrintHandler (const char* varName) : 
   mVarName(varName), mIndentSpaces(0), mbTrace(FALSE)
{
   if (mbTrace) {
      printf ("%s ", mVarName);
   }
   mState = Init;
}

PrintHandler::~PrintHandler ()
{
   if (mbTrace) {
      if (mState == End) {
         mIndentSpaces -= 3;
         indent ();
         printf ("}\n");
      }
      else {
         printf ("\n");
      }

      if (mIndentSpaces != 0) {
         printf ("ERROR: unbalanced structure\n");
      }
   }
}

void PrintHandler::indent ()
{
   for (int i = 0; i < mIndentSpaces; i++) printf (" ");
}

void PrintHandler::startElement (const char* name, OSSIZE index)
{
   if (mbTrace) {
      if (mState == Init || mState == Start) {
         printf ("{\n");
         mIndentSpaces += 3;
      }
      indent ();
      printf (name);
      if (index != OSNULLINDEX) printf ("[%d]", index);
      printf (" ");
   }
   mState = Start;
}

void PrintHandler::endElement (const char* name, OSSIZE index)
{
   if (mbTrace) {
      if (mState == End) {
         mIndentSpaces -= 3;
         indent ();
         printf ("}\n");
      }
      else
         printf ("\n");
   }
   mState = End;
}

void PrintHandler::boolValue (OSBOOL value)
{
   if (mbTrace) {
      const char* s = value ? "TRUE" : "FALSE";
      printf ("= %s", s);
   }
   mState = Data;
}

void PrintHandler::intValue (OSINT32 value)
{
   if (mbTrace) {
      printf ("= %d", value);
   }
   mState = Data;
}

void PrintHandler::uIntValue (OSUINT32 value)
{
   if (mbTrace) {
      printf ("= %u", value);
   }
   mState = Data;
}

void PrintHandler::bitStrValue (OSSIZE numbits, const OSOCTET* data)
{
   if (mbTrace) {
      char* s = new char [numbits + 8];
      printf ("= %s", rtBitStrToString (numbits, data, s, numbits+8));
      delete [] s;
   }
   mState = Data;
}

void PrintHandler::octStrValue (OSSIZE numocts, const OSOCTET* data)
{
   if (mbTrace) {
      OSSIZE bufsiz = (numocts * 2) + 8;
      char* s = new char [bufsiz];
      printf ("= %s", rtOctStrToString (numocts, data, s, bufsiz));
      delete [] s;
   }
   mState = Data;
}

void PrintHandler::charStrValue (const char* value)
{
   if (mbTrace) {
      printf ("= \"%s\"", value);
   }
   mState = Data;
}

void PrintHandler::charStrValue (OSSIZE nchars, OSUNICHAR* data)
{
   if (mbTrace) {
      for (OSUINT32 ui = 0; ui < nchars; ui++) {
         if (data[ui] >= 32 && data[ui] <= 127)
            printf ("%c", (char)data[ui]);
         else
            printf ("?");
      }
   }
   mState = Data;
}

void PrintHandler::charStrValue (OSSIZE nchars, OS32BITCHAR* data)
{
   if (mbTrace) {
      for (OSUINT32 ui = 0; ui < nchars; ui++) {
         if (data[ui] >= 32 && data[ui] <= 127)
            printf ("%c", (char)data[ui]);
         else
            printf ("\\%d", data[ui]);
      }
   }
   mState = Data;
}

void PrintHandler::nullValue ()
{
   if (mbTrace) {
      printf ("= NULL");
   }
   mState = Data;
}

void PrintHandler::oidValue (OSUINT32 numSubIds, OSUINT32* pSubIds)
{
   if (mbTrace) {
      ASN1OBJID oid;
      oid.numids = numSubIds;

      for (OSUINT32 ui = 0; ui < numSubIds; ui++)
         oid.subid[ui] = pSubIds[ui];

      indent ();
      rtPrintOIDValue (&oid);
   }
   mState = Data;
}

void PrintHandler::realValue (double value)
{
   if (mbTrace) {
      printf ("= %f", value);
   }
   mState = Data;
}

void PrintHandler::enumValue (OSUINT32 value, const OSUTF8CHAR* text)
{
   if (mbTrace) {
      printf ("= %s(%u)", text, value);
   }
   mState = Data;
}

void PrintHandler::openTypeValue (OSSIZE numocts, const OSOCTET* data)
{
   if (mbTrace) {
      printf ("= < encoded data >");
   }
   mState = Data;
}
