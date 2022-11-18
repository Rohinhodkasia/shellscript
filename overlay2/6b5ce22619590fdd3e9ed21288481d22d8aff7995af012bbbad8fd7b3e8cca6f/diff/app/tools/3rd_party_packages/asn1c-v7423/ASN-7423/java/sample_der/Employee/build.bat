..\..\..\bin\asn1c employee.asn -der -java -print -pkgpfx sample_der
call ..\..\setenv.bat
javac *.java
java sample_der.Employee.Writer > writer.log
java sample_der.Employee.Reader > reader.log
