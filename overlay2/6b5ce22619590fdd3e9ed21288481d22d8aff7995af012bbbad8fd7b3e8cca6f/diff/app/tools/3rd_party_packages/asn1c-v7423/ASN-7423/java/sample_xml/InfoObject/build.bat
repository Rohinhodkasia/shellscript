..\..\..\bin\asn1c test.asn -xml -xmlpull -java -print -pkgname sample_xml.InfoObjectXmlPull -trace
..\..\..\bin\asn1c test.asn -xsd
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xml.InfoObject.Writer > writer.log
java sample_xml.InfoObject.Reader > reader.log
