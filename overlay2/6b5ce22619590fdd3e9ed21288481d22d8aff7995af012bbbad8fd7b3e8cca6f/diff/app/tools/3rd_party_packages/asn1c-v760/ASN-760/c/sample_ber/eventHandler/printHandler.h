/* This is an implementation of a simple print handler.  It outputs 
   the fields of an encoded PER message to stdout in a structured output 
   format..
*/

#ifndef _PRINTHANDLER_H_
#define _PRINTHANDLER_H_

#include "asn1CEvtHndlr.h"

Asn1NamedCEventHandler printHandler;

void initializePrintHandler
   (Asn1NamedCEventHandler *printHandler, const char* varname);
void finishPrint();
void indent ();
void printStartElement (const char* name, OSSIZE index );
void printEndElement (const char* name, OSSIZE index );
void printBoolValue (OSBOOL value);
void printIntValue (OSINT32 value);
void printuIntValue (OSUINT32 value);
void printBitStrValue (OSSIZE numbits, const OSOCTET* data);
void printOctStrValue (OSSIZE numocts, const OSOCTET* data);
void printCharStrValue (const char* value);
void printCharStr16BitValue (OSSIZE nchars, OSUNICHAR* data);
void printCharStr32BitValue (OSSIZE nchars, OS32BITCHAR* data);
void printNullValue (void);
void printOidValue (OSUINT32 numSubIds, OSUINT32* pSubIds);
void printRealValue (double value);
void printEnumValue (OSUINT32 value, const OSUTF8CHAR* text);
void printOpenTypeValue (OSSIZE numocts, const OSOCTET* data);

#endif
