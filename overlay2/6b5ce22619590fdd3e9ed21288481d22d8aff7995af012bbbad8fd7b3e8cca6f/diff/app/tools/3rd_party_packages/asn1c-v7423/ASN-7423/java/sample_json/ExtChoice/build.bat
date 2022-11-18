..\..\..\bin\asn1c extChoice.asn -json -java -print -pkgpfx sample_json -trace
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%
javac *.java
java sample_json.ExtChoice.Writer > writer.log
java sample_json.ExtChoice.Reader > reader.log
