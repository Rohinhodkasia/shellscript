..\..\..\bin\asn1c biometrics.asn -xer -xmlpull -java -print -pkgname sample_xer.Biometrics -config xcbf.cfg
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%;../../xmlpull/kxml2-2.3.0.tiny.jar
javac *.java
java sample_xer.Biometrics.Writer > writer.log
java sample_xer.Biometrics.Reader > reader.log
