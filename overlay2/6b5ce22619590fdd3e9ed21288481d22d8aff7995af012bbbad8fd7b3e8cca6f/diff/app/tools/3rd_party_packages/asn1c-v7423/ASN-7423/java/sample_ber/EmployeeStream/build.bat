..\..\..\bin\asn1c employee.asn -ber -java -print -pkgpfx sample_ber -stream
call ..\..\setenv.bat
javac *.java
java sample_ber.EmployeeStream.Writer > writer.log
java sample_ber.EmployeeStream.Reader > reader.log
