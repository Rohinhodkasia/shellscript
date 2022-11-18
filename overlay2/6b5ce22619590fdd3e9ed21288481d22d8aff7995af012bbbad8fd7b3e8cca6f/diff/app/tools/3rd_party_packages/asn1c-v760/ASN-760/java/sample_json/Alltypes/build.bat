..\..\..\bin\asn1c test.asn -json -java -print -pkgname sample_json.Alltypes
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%
javac *.java
java sample_json.Alltypes.Writer > writer.log
java sample_json.Alltypes.Reader > reader.log
