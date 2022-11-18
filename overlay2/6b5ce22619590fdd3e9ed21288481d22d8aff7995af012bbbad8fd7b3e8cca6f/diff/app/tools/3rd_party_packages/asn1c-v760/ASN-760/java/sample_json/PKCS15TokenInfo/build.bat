..\..\..\bin\asn1c PKCS15TokenInfo.asn -json -java -print -pkgpfx sample_json
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%
javac *.java
java sample_json.PKCS15TokenInfo.Writer > writer.log
java sample_json.PKCS15TokenInfo.Reader > reader.log
