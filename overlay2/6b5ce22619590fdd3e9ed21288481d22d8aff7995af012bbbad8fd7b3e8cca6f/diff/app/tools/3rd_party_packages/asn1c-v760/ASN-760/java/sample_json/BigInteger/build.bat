..\..\..\bin\asn1c bigInt.asn -config bigInt.cfg -json -java -print -pkgname sample_json.BigInteger -config bigInt.cfg
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%
javac *.java
java sample_json.BigInteger.Writer > writer.log
java sample_json.BigInteger.Reader > reader.log
