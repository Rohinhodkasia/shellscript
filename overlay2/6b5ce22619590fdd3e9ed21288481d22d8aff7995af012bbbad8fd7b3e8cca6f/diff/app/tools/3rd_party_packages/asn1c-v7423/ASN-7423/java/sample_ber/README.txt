JAVA SAMPLE PROGRAMS

These programs are of two general types:

1) Specifications only that are used as class libraries for other sample 
programs (for example, the AIN and SimpleROSE programs generate a set of 
class files for other example programs like TcapInvoke).

2) Sample programs that contain a reader and writer program for executing 
an encode and decode operation.

Each sample program contains a makefile for building it using the GNU make 
utility.  In addition, the sample contains a "build.bat" file for building 
on Windows systems that don't have a make utility program installed.

After compilation, a writer program can be run using the following command 
line: 

   java -classpath "../../asn1rt.jar;../.." <subdir1>.<subdir2>.Writer

In this specification, <subdir1> would be replaced with the first level 
subdirectory (sample_ber or sample_der) and subdir2 would be replaced with 
the actual sample subdirectory.  For example, to run the CSTA writer program 
in the sample_ber subdirectory, the following command line would be used:

   java -classpath "../../asn1rt.jar;../.." sample_ber.CSTA.Writer

This program will generate a message.dat and message.dmp file containing an 
encoded message.

The corresponding reader program can then be executed to read and decode the 
message.  The command line to execute the reader is as follows:

   java -classpath "../../asn1rt.jar;../.." <subdir1>.<subdir2>.Writer

Once again, <subdir1> would be replaced with the first level subdirectory 
(sample_ber or sample_der) and subdir2 would be replaced with 
the actual sample subdirectory.

The makefile will automatically run the Writer and Reader programs after they 
are built and redirect the output to writer.log and reader.log respectively.

