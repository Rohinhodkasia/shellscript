This sample program shows how to convert a PER-encoded binary 
message into XML format.  In this case, the sample message is 
first decoded using a generated PER decoder and then re-encoded 
using a generated XER/XML encoder.

This sample contains the following files: 

employee.asn - ASN.1 source file containing PersonnelRecord PDU definition
message.bin  - Binary file contain a PER-encoded employee record.
reader.cpp   - Application program for reading and decoding message.bin 
               and then re-encoding and saving as message.xml.
makefile     - Portable makefile to build the sample program.

To build the sample program, the portable makefile can be used. On Windows, 
the VisualStudio 'nmake' utility program can be used.  On UNIX/Linux the 
makefile can be execute with the 'make' utility.  Once built, the resulting 
reader.exe program can be executed from the command line to do the 
conversion.

