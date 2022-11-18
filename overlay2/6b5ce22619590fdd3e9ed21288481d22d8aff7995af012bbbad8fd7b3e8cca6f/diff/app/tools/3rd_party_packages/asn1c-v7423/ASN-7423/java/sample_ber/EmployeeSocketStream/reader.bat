..\..\..\bin\asn1c employee.asn -ber -java -print -pkgpfx sample_ber -stream
call ..\..\setenv.bat
javac *.java
java sample_ber.EmployeeSocketStream.Reader
