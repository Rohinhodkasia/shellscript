..\..\..\bin\asn1c bigInt.asn -config bigInt.cfg -xml -xmlpull -java -print -pkgname sample_xml.BigInteger
..\..\..\bin\asn1c bigInt.asn -config bigInt.cfg -xsd
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xml.BigInteger.Writer > writer.log
java sample_xml.BigInteger.Reader > reader.log
