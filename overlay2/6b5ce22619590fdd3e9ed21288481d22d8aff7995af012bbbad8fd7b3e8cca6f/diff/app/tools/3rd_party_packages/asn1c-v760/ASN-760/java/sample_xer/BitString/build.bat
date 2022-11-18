..\..\..\bin\asn1c test.asn -xer -xmlpull -java -print -pkgname sample_xer.BitString -trace
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.BitString.Writer > writer.log
java sample_xer.BitString.Reader > reader.log
java sample_xer.BitString.Writer -cxer > writer_cxer.log
java sample_xer.BitString.Reader > reader_cxer.log
