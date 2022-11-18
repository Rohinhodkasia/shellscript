..\..\..\bin\asn1c PKCS15TokenInfo.asn -der -java -print -pkgpfx sample_der
call ..\..\setenv.bat
javac *.java
java sample_der.PKCS15TokenInfo.Writer > writer.log
java sample_der.PKCS15TokenInfo.Reader > reader.log
