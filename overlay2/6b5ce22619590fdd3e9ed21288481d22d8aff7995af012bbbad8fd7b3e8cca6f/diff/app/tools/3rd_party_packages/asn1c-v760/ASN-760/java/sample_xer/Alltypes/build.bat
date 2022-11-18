..\..\..\bin\asn1c test.asn -xer -xmlpull -java -print -pkgname sample_xer.Alltypes
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.Alltypes.Writer > writer.log
java sample_xer.Alltypes.Reader > reader.log
