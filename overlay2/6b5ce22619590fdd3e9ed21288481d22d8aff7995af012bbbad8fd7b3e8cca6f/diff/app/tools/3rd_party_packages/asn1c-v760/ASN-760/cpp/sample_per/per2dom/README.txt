This sample program shows how to convert a PER-encoded binary 
message into a structure that is similar to an XML Document Object Model 
(DOM) tree.  In this case, event handlers are used to do the translation.  
The event handlers receive all of the meta and encoded data from the 
message and use it to build the DOM-like tree structure.

This also demonstrates the use of a pure-parser.  The -notypes 
option is used to not generate any type definitions for the 
productions in the employee.asn file.  Instead, only parsing 
functions are generated.  When invoked, these functions will 
parse the incoming data and fire the event handler callbacks. 
The data is not decoded and saved in a structured type variable.

The implementation also contains a method (DOMTree::getValue) that 
shows how to query the structure for a given element value.

This sample contains the following files: 

employee.asn   - ASN.1 source file containing PersonnelRecord PDU definition
message.bin    - Binary file contain a PER-encoded employee record.
reader.cpp     - Application program for reading and parsing message.bin.
domHandler.cpp - Implementation of an event handler to build the DOM.
domHandler.h   - Event handler class definitions.
makefile       - Portable makefile to build the sample program.

To build the sample program, the portable makefile can be used. On Windows, 
the VisualStudio 'nmake' utility program can be used.  On UNIX/Linux the 
makefile can be execute with the 'make' utility.  Once built, the resulting 
reader.exe program can be executed from the command line to do the 
conversion.

