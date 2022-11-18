..\..\..\bin\asn1c extChoice.asn -xml -xmlpull -java -print -pkgpfx sample_xml -trace
..\..\..\bin\asn1c extChoice.asn -xsd
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xml.ExtChoice.Writer > writer.log
java sample_xml.ExtChoice.Reader > reader.log
