..\..\..\bin\asn1c test.asn -xer -xmlpull -java -print -pkgname sample_xer.InfoObject -trace
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.InfoObject.Writer > writer.log
java sample_xer.InfoObject.Reader > reader.log
