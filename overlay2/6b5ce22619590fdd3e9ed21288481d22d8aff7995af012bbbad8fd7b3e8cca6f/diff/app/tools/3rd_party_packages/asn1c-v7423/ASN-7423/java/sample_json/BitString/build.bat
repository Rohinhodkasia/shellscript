..\..\..\bin\asn1c test.asn -json -java -print -pkgpfx sample_json -trace
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%
javac *.java
java sample_json.BitString.Writer > writer.log
java sample_json.BitString.Reader > reader.log
