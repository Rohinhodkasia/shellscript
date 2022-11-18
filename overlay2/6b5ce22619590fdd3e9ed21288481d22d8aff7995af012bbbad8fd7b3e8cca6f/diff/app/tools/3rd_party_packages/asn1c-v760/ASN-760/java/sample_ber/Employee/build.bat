..\..\..\bin\asn1c employee.asn -ber -java -print -pkgpfx sample_ber
call ..\..\setenv.bat
javac *.java
java sample_ber.Employee.Writer > writer.log
java sample_ber.Employee.Reader > reader.log
