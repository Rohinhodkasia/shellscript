..\..\..\bin\asn1c bigInt.asn -config bigInt.cfg -xer -xmlpull -java -print -pkgname sample_xer.BigInteger -config bigInt.cfg
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.BigInteger.Writer > writer.log
java sample_xer.BigInteger.Reader > reader.log
