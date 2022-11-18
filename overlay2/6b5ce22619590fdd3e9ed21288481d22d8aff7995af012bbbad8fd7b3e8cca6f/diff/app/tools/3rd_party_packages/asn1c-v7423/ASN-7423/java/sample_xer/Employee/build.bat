..\..\..\bin\asn1c employee.asn -xer -xmlpull -java -print -pkgname sample_xer.Employee
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.Employee.Writer > writer.log
java sample_xer.Employee.Reader > reader.log
java sample_xer.Employee.Writer -cxer > writer_cxer.log
java sample_xer.Employee.Reader > reader_cxer.log
