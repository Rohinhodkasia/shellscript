This sample program demonstrates the use of the -tables and -3gpp command 
line option to generate special code for table constraint processing.  The 
sample comes from the NBAP ASN.1 specification and shows a multi-layered 
message consisting of information objects used at five different levels.  

To encode this message, the developer declares and populates each of the 
message object message structures.  Unlike earlier versions, it is not 
necessary to populate open type fields.  Structures for all of the 
different types of fields that can make up the various parts of a 
message are built directly into the code in the form of union constructs. 
The fields in the union are derived from the information object set 
definitions within the specification. 

On the decode side, the reader has to simply make a call to the NBAP-PDU 
decode function to decode the entire multi-part message.  The generated 
print function is capable of printing all of the decoded open type data 
within the message.

