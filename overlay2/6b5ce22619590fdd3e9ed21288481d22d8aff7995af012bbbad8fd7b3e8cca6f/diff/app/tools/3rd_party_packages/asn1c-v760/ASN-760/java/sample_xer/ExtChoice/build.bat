..\..\..\bin\asn1c extChoice.asn -xer -xmlpull -java -print -pkgname sample_xer.ExtChoice -trace
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.ExtChoice.Writer > writer.log
java sample_xer.ExtChoice.Reader > reader.log
java sample_xer.ExtChoice.Writer -cxer > writer_cxer.log
java sample_xer.ExtChoice.Reader > reader_cxer.log
