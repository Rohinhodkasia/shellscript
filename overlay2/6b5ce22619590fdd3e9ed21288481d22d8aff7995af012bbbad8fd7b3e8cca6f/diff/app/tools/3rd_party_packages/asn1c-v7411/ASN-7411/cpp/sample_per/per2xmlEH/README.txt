This sample program shows how to convert a PER-encoded binary 
message into XML format.  In this case, event handlers are used 
to do the translation.  The event handlers receive all of the 
meta and encoded data from the message and format it into XML as 
the PER message is parsed.

This also demonstrates the use of a pure-parser.  The -notypes 
option is used to not generate any type definitions for the 
productions in the employee.asn file.  Instead, only parsing 
functions are generated.  When invoked, these function will 
parse the incoming data and fire the event handler callbacks. 
The data is not decoded and saved in a structured type variable.

This sample contains the following files: 

employee.asn   - ASN.1 source file containing PersonnelRecord PDU definition
message.bin    - Binary file contain a PER-encoded employee record.
reader.cpp     - Application program for reading and parsing message.bin.
xmlHandler.cpp - Implementation of an event handler to format the message 
                 data into XML.
xmlHandler.h   - Event handler class definition.
makefile       - Portable makefile to build the sample program.

To build the sample program, the portable makefile can be used. On Windows, 
the VisualStudio 'nmake' utility program can be used.  On UNIX/Linux the 
makefile can be execute with the 'make' utility.  Once built, the resulting 
reader.exe program can be executed from the command line to do the 
conversion.

