This sample program demonstrates new C++ memory management features added in 
the ASN1C version 5.6 release.  In prior releases, it was always necessary to 
maintain either a message buffer object or control class object when working 
with data in a compiler generated data structure.  The new release makes this 
no longer necessary as long as the generated type is designated to be a PDU 
type. 

In the reader example program, the message component is decoded in a separate 
function.  The decoded component is then returned to the caller using the 
control class 'newCopy' method.  This creates a copy of the object that will 
persist after the control class and message buffer objects are deleted.  The 
returned object can be deleted using the standard C++ 'delete' operator when 
it is no longer needed.

