/* This is an implementation of a simple print handler.  It outputs 
   the fields of an encoded PER message to stdout in a structured output 
   format..
*/
#include <stdlib.h>
#include "printHandler.h"
#include "rtsrc/rtPrint.h"

static int gs_IndentSpaces;

void initializePrintHandler
(Asn1NamedCEventHandler *printHandler, const char* varname)
{
   printHandler->startElement = &printStartElement;
   printHandler->endElement = &printEndElement;
   printHandler->boolValue = &printBoolValue;
   printHandler->intValue = &printIntValue;
   printHandler->uIntValue = &printuIntValue ;
   printHandler->bitStrValue = &printBitStrValue;
   printHandler->octStrValue = &printOctStrValue;
   printHandler->charStrValue = &printCharStrValue;
   printHandler->charStrValue16Bit = &printCharStr16BitValue ;
   printHandler->charStrValue32Bit = &printCharStr32BitValue;
   printHandler->nullValue = &printNullValue;
   printHandler->oidValue = &printOidValue;
   printHandler->realValue = &printRealValue;
   printHandler->enumValue = &printEnumValue;
   printHandler->openTypeValue = &printOpenTypeValue;
   printf ("%s = {\n", varname);
   gs_IndentSpaces += 3;
}

void finishPrint()
{
   printf ("}\n");
   gs_IndentSpaces -= 3;
   if (gs_IndentSpaces != 0) {
      printf ("ERROR: unbalanced structure\n");
   }
}

void indent ()
{
   int i=0;
   for (i = 0; i < gs_IndentSpaces; i++) printf (" ");
}

void printStartElement (const char* name, OSSIZE index)
{

   indent ();
   printf (name);
   if (index != OSNULLINDEX) printf ("[" OSSIZEFMT "]", index);
   printf (" = {\n");
   gs_IndentSpaces += 3;
}

void printEndElement (const char* name, OSSIZE index)
{
   gs_IndentSpaces -= 3;
   indent ();
   printf ("}\n");
}

void printBoolValue (OSBOOL value)
{
   const char* s = value ? "TRUE" : "FALSE";
   indent ();
   printf ("%s\n", s);
}

void printIntValue (OSINT32 value)
{
   indent ();
   printf ("%d\n", value);
}

void printuIntValue (OSUINT32 value)
{
   indent ();
   printf ("%u\n", value);
}

void printOctStrValue (OSSIZE numocts, const OSOCTET* data)
{
   OSSIZE i;
   indent ();
   printf ("0x");
   for (i = 0; i < numocts; i++) {
      printf ("%02x", data[i]);
   }
   printf ("\n");
}

void printBitStrValue (OSSIZE numbits, const OSOCTET* data)
{
   printOctStrValue ((numbits+7)/8, data);
}

void printCharStrValue (const char* value)
{
   indent ();
   printf ("\"%s\"\n", value);
}

void printCharStr16BitValue (OSSIZE nchars, OSUNICHAR* data)
{
   OSSIZE ui;
   indent ();

   for (ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("?");
   }

   printf ("\n");
}

void printCharStr32BitValue (OSSIZE nchars, OS32BITCHAR* data)
{
   OSSIZE ui;
   indent ();

   for (ui = 0; ui < nchars; ui++) {
      if (data[ui] >= 32 && data[ui] <= 127)
         printf ("%c", (char)data[ui]);
      else
         printf ("\\%d", data[ui]);
   }

   printf ("\n");
}

void printNullValue (void)
{
   indent ();
   printf ("NULL\n");
}

void printOidValue (OSUINT32 numSubIds, OSUINT32* pSubIds)
{
   OSUINT32 ui;
   ASN1OBJID oid;
   oid.numids = numSubIds;

   for ( ui = 0; ui < numSubIds; ui++)
      oid.subid[ui] = pSubIds[ui];

   indent ();
   rtPrintOIDValue (&oid);
}

void printRealValue (double value)
{
   indent ();
   printf ("%f\n", value);
}

void printEnumValue (OSUINT32 value, const OSUTF8CHAR* text)
{
   indent ();
   printf ("%s(%u)\n", text, value);
}

void printOpenTypeValue (OSSIZE numocts, const OSOCTET* data)
{
   indent ();
   printf ("< encoded data >\n");
}
