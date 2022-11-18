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
      printf ("%s = {\n", mVarName);
   }
   mIndentSpaces += 3;
}

PrintHandler::~PrintHandler ()
{
   if (mbTrace) {
      printf ("}\n");
   }
   mIndentSpaces -= 3;
   if (mIndentSpaces != 0) {
      printf ("ERROR: unbalanced structure\n");
   }
}

void PrintHandler::indent ()
{
   for (int i = 0; i < mIndentSpaces; i++) printf (" ");
}

void PrintHandler::startElement (const char* name, int index)
{
   if (mbTrace) {
      indent ();
      printf (name);
      if (index >= 0) printf ("[%d]", index);
      printf (" = {\n");
   }
   mIndentSpaces += 3;
}

void PrintHandler::endElement (const char* name, int index)
{
   mIndentSpaces -= 3;
   if (mbTrace) {
      indent ();
      printf ("}\n");
   }
}

void PrintHandler::boolValue (OSBOOL value)
{
   if (mbTrace) {
      const char* s = value ? "TRUE" : "FALSE";
      indent ();
      printf ("%s\n", s);
   }
}

void PrintHandler::intValue (OSINT32 value)
{
   if (mbTrace) {
      indent ();
      printf ("%d\n", value);
   }
}

void PrintHandler::uIntValue (OSUINT32 value)
{
   if (mbTrace) {
      indent ();
      printf ("%u\n", value);
   }
}

void PrintHandler::int64Value (OSINT64 value)
{
   if (mbTrace) {
      indent ();
      printf (OSINT64FMT"\n", value);
   }
}

void PrintHandler::uInt64Value (OSUINT64 value)
{
   if (mbTrace) {
      indent ();
      printf (OSUINT64FMT"\n", value);
   }
}

void PrintHandler::bitStrValue (OSUINT32 numbits, const OSOCTET* data)
{
   if (mbTrace) {
      char* s = new char [numbits + 8];
      indent ();
      printf ("%s\n", rtBitStrToString (numbits, data, s, numbits+8));
      delete [] s;
   }
}

void PrintHandler::octStrValue (OSUINT32 numocts, const OSOCTET* data)
{
   if (mbTrace) {
      int bufsiz = (numocts * 2) + 8;
      char* s = new char [bufsiz];
      indent ();
      printf ("%s\n", rtOctStrToString (numocts, data, s, bufsiz));
      delete [] s;
   }
}

void PrintHandler::charStrValue (const char* value)
{
   if (mbTrace) {
      indent ();
      printf ("\"%s\"\n", value);
   }
}

void PrintHandler::charStrValue (OSUINT32 nchars, OSUNICHAR* data)
{
   if (mbTrace) {
      indent ();

      for (OSUINT32 ui = 0; ui < nchars; ui++) {
         if (data[ui] >= 32 && data[ui] <= 127)
            printf ("%c", (char)data[ui]);
         else
            printf ("?");
      }

      printf ("\n");
   }
}

void PrintHandler::charStrValue (OSUINT32 nchars, const OSUTF8CHAR* data)
{
   if (mbTrace) {
      indent ();

      for (OSUINT32 ui = 0; ui < nchars; ui++) {
         if (data[ui] >= 32 && data[ui] <= 127)
            printf ("%c", (char)data[ui]);
         else
            printf ("?");
      }

      printf ("\n");
   }
}

void PrintHandler::charStrValue (OSUINT32 nchars, OS32BITCHAR* data)
{
   if (mbTrace) {
      indent ();

      for (OSUINT32 ui = 0; ui < nchars; ui++) {
         if (data[ui] >= 32 && data[ui] <= 127)
            printf ("%c", (char)data[ui]);
         else
            printf ("\\%d", data[ui]);
      }

      printf ("\n");
   }
}

void PrintHandler::nullValue ()
{
   if (mbTrace) {
      indent ();
      printf ("NULL\n");
   }
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
}

void PrintHandler::realValue (double value)
{
   if (mbTrace) {
      indent ();
      printf ("%f\n", value);
   }
}

void PrintHandler::enumValue (OSUINT32 value, const OSUTF8CHAR* text)
{
   if (mbTrace) {
      indent ();
      printf ("%s(%u)\n", text, value);
   }
}

void PrintHandler::openTypeValue (OSUINT32 numocts, const OSOCTET* data)
{
   if (mbTrace) {
      indent ();
      printf ("< encoded data >\n");
   }
}
