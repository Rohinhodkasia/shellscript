// This is an implementation of a simple print handler class.  It outputs 
// the fields of an encoded PER message to stdout in a structured output 
// format..

#include "printHandler.h"
#include "rtsrc/rtconv.h"
#include "rtsrc/rtPrint.h"

PrintHandler::PrintHandler (const char* varName) : 
   mVarName(varName), mIndentSpaces(0)
{
   printf ("%s = {\n", mVarName);
   mIndentSpaces += 3;
}

PrintHandler::~PrintHandler ()
{
   printf ("}\n");
   mIndentSpaces -= 3;
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
   indent ();
   printf ("%s", name);
   if (index != OSNULLINDEX) printf ("[%ld]", index);
   printf (" = {\n");
   mIndentSpaces += 3;
}

void PrintHandler::endElement (const char* name, OSSIZE index)
{
   mIndentSpaces -= 3;
   indent ();
   printf ("}\n");
}

void PrintHandler::boolValue (OSBOOL value)
{
   const char* s = value ? "TRUE" : "FALSE";
   indent ();
   printf ("%s\n", s);
}

void PrintHandler::intValue (OSINT32 value)
{
   indent ();
   printf ("%d\n", value);
}

void PrintHandler::uIntValue (OSUINT32 value)
{
   indent ();
   printf ("%u\n", value);
}

void PrintHandler::bitStrValue (OSSIZE numbits, const OSOCTET* data)
{
   char* s = new char [numbits + 8];
   indent ();
   printf ("%s\n", rtBitStrToString (numbits, data, s, numbits+8));
   delete [] s;
}

void PrintHandler::octStrValue (OSSIZE numocts, const OSOCTET* data)
{
   OSSIZE bufsiz = (numocts * 2) + 8;
   char* s = new char [bufsiz];
   indent ();
   printf ("%s\n", rtOctStrToString (numocts, data, s, bufsiz));
   delete [] s;
}

void PrintHandler::charStrValue (const char* value)
{
   indent ();
   printf ("\"%s\"\n", value);
}

void PrintHandler::charStrValue (OSSIZE nchars, OSUNICHAR* data)
{
   indent ();

   for (OSUINT32 ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("?");
   }

   printf ("\n");
}

void PrintHandler::charStrValue (OSSIZE nchars, const OSUTF8CHAR* data)
{
   indent ();

   for (OSUINT32 ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("?");
   }

   printf ("\n");
}

void PrintHandler::charStrValue (OSSIZE nchars, OS32BITCHAR* data)
{
   indent ();

   for (OSUINT32 ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("\\%d", data[ui]);
   }

   printf ("\n");
}

void PrintHandler::nullValue ()
{
   indent ();
   printf ("NULL\n");
}

void PrintHandler::oidValue (OSUINT32 numSubIds, OSUINT32* pSubIds)
{
   ASN1OBJID oid;
   oid.numids = numSubIds;

   for (OSUINT32 ui = 0; ui < numSubIds; ui++)
      oid.subid[ui] = pSubIds[ui];

   indent ();
   rtPrintOIDValue (&oid);
}

void PrintHandler::realValue (double value)
{
   indent ();
   printf ("%f\n", value);
}

void PrintHandler::enumValue (OSUINT32 value, const OSUTF8CHAR* text)
{
   indent ();
   printf ("%s(%u)\n", text, value);
}

void PrintHandler::openTypeValue (OSSIZE numocts, const OSOCTET* data)
{
   indent ();
   printf ("< encoded data >\n");
}
