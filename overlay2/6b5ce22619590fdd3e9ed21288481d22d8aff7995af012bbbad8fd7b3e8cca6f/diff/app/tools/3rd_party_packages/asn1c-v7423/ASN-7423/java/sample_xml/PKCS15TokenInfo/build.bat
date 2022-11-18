..\..\..\bin\asn1c PKCS15TokenInfo.asn -xml -xmlpull -java -print -pkgname sample_xml.PKCS15TokenInfo
..\..\..\bin\asn1c PKCS15TokenInfo.asn -xsd
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xml.PKCS15TokenInfo.Writer > writer.log
java sample_xml.PKCS15TokenInfo.Reader > reader.log
