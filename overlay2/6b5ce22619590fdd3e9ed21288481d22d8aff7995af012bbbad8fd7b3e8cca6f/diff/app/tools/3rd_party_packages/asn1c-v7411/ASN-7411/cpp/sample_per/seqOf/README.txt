This sample program demonstrates the use of the -dynamic flag.  This 
example shows a SEQUENCE OF construct with a size constraint.  Normally 
the compiler would generate a static array for the elements.  
However, since -dynamic is specified on the command line, a pointer 
variable is generated for the elements.

