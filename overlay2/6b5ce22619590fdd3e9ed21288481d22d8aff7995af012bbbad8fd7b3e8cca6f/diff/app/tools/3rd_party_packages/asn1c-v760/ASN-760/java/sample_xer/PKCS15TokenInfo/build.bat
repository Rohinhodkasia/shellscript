..\..\..\bin\asn1c PKCS15TokenInfo.asn -xer -xmlpull -java -print -pkgname sample_xer.PKCS15TokenInfo
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.PKCS15TokenInfo.Writer > writer.log
java sample_xer.PKCS15TokenInfo.Reader > reader.log
java sample_xer.PKCS15TokenInfo.Writer -cxer > writer_cxer.log
java sample_xer.PKCS15TokenInfo.Reader > reader_cxer.log
