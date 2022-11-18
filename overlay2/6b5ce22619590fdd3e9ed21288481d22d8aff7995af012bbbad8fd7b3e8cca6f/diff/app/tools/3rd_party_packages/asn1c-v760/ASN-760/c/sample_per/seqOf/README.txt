This sample program demonstrates the use of the <storage> configuration
setting.  This example shows a SEQUENCE OF construct with a size 
constraint.  Normally the compiler would generate a static array for 
the elements.  However, since <storage>dynamic</storage> is specified 
on the command line, a pointer variable is generated for the elements.

