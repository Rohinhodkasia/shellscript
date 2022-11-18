..\..\..\bin\asn1c employee.asn -xer -xmlpull -java -print -pkgname sample_xer.EmployeeEXER
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.EmployeeEXER.Writer > writer.log
java sample_xer.EmployeeEXER.Reader > reader.log
