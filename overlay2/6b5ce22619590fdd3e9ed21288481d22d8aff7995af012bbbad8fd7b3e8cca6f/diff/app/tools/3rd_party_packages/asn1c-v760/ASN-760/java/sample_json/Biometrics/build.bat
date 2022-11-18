..\..\..\bin\asn1c biometrics.asn -json -java -print -pkgname sample_json.Biometrics -config xcbf.cfg
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%
javac *.java
java sample_json.Biometrics.Writer > writer.log
java sample_json.Biometrics.Reader > reader.log
