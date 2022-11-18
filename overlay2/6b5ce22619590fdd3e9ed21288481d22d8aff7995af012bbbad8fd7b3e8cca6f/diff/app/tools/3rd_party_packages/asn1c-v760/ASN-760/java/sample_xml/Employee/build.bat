..\..\..\bin\asn1c employee.asn -xml -xmlpull -java -print -pkgpfx sample_xml
..\..\..\bin\asn1c employee.asn -xsd
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xml.Employee.Writer > writer.log
java sample_xml.Employee.Reader > reader.log
