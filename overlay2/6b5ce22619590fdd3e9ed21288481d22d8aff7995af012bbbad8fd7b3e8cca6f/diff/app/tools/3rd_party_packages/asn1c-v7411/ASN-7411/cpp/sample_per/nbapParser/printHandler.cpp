// This is an implementation of a simple print handler class.  It outputs 
// the fields of an encoded PER message to stdout in a structured output 
// format..

#include "printHandler.h"
#include "rtsrc/rtconv.h"
#include "rtsrc/rtPrint.h"

PrintHandler::PrintHandler (const char* varName) : 
   mVarName(varName), mIndentSpaces(0)
{
   printf ("%s ", mVarName);
   mState = Init;
}

PrintHandler::~PrintHandler ()
{
   if (mState == End) {
      mIndentSpaces -= 3;
      indent ();
      printf ("}\n");
   }
   else
      printf ("\n");

   if (mIndentSpaces != 0) {
      printf ("ERROR: unbalanced structure\n");
   }
}

void PrintHandler::indent ()
{
   for (int i = 0; i < mIndentSpaces; i++) printf (" ");
}

void PrintHandler::startElement (const char* name, OSSIZE index)
{
   if (mState == Init || mState == Start) {
      printf ("{\n");
      mIndentSpaces += 3;
   }
   indent ();
   printf (name);
   if (index != OSNULLINDEX) printf ("[%d]", index);
   printf (" ");
   mState = Start;
}

void PrintHandler::endElement (const char* name, OSSIZE index)
{
   if (mState == End) {
      mIndentSpaces -= 3;
      indent ();
      printf ("}\n");
   }
   else
      printf ("\n");

   mState = End;
}

void PrintHandler::boolValue (OSBOOL value)
{
   const char* s = value ? "TRUE" : "FALSE";
   printf ("= %s", s);
   mState = Data;
}

void PrintHandler::intValue (OSINT32 value)
{
   printf ("= %d", value);
   mState = Data;
}

void PrintHandler::uIntValue (OSUINT32 value)
{
   printf ("= %u", value);
   mState = Data;
}

void PrintHandler::bitStrValue (OSSIZE numbits, const OSOCTET* data)
{
   char* s = new char [numbits + 8];
   printf ("= %s", rtBitStrToString (numbits, data, s, numbits+8));
   delete [] s;
   mState = Data;
}

void PrintHandler::octStrValue (OSSIZE numocts, const OSOCTET* data)
{
   OSSIZE bufsiz = (numocts * 2) + 8;
   char* s = new char [bufsiz];
   printf ("= %s", rtOctStrToString (numocts, data, s, bufsiz));
   delete [] s;
   mState = Data;
}

void PrintHandler::charStrValue (const char* value)
{
   printf ("= \"%s\"", value);
   mState = Data;
}

void PrintHandler::charStrValue (OSSIZE nchars, const OSUTF8CHAR* data)
{
   for (OSSIZE ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("?");
   }
   mState = Data;
}

void PrintHandler::charStrValue (OSSIZE nchars, OSUNICHAR* data)
{
   for (OSSIZE ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("?");
   }
   mState = Data;
}

void PrintHandler::charStrValue (OSSIZE nchars, OS32BITCHAR* data)
{
   for (OSSIZE ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("\\%d", data[ui]);
   }
   mState = Data;
}

void PrintHandler::nullValue ()
{
   printf ("= NULL");
   mState = Data;
}

void PrintHandler::oidValue (OSUINT32 numSubIds, OSUINT32* pSubIds)
{
   OSUINT32 ui;
   printf ("= { ");
   for (ui = 0; ui < numSubIds; ui++) {
      printf ("%d ", pSubIds[ui]);
   }
   printf ("}");
   mState = Data;
}

void PrintHandler::realValue (double value)
{
   printf ("= %f", value);
   mState = Data;
}

void PrintHandler::enumValue (OSUINT32 value, const OSUTF8CHAR* text)
{
   printf ("= %s(%u)", text, value);
   mState = Data;
}

void PrintHandler::openTypeValue (OSSIZE numocts, const OSOCTET* data)
{
   printf ("= < encoded data >");
   mState = Data;
}
