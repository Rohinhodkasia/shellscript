..\..\..\bin\asn1c bigInt.asn -config bigInt.cfg -der -java -print -pkgname sample_der.BigInteger
call ..\..\setenv.bat
javac *.java
java sample_der.BigInteger.Writer > writer.log
java sample_der.BigInteger.Reader > reader.log
