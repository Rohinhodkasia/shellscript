This program demonstrates the fault-tolerant capabilities that can be 
achieved by using an error handler.  The message.dat file contains a 
BER-encoded employee record with an error in it.  The error is a bogus 
element that was added to one of the constructed types.  The error 
handler will be triggered when the bogus element is encountered.  The 
action will be to output a warning messages and skip the element.  An 
ASN_OK status is returned to allow parsing to continue.

