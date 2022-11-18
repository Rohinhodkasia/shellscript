..\..\..\bin\asn1c employee.asn -oer -java -print -pkgpfx sample_oer
call ..\..\setenv.bat
javac *.java
java sample_oer.Employee.Writer > writer.log
java sample_oer.Employee.Reader > reader.log
