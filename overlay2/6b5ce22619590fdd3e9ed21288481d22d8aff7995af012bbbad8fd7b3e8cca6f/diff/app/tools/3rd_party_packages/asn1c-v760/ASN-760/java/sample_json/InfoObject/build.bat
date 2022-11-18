..\..\..\bin\asn1c test.asn -json -java -print -pkgname sample_json.InfoObject -trace
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%
javac *.java
java sample_json.InfoObject.Writer > writer.log
java sample_json.InfoObject.Reader > reader.log
