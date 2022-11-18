..\..\..\bin\asn1c myHTTP.asn -ber -java -print -pkgpfx sample_ber
call ..\..\setenv.bat
javac *.java
java sample_ber.MyHTTP.Writer > writer.log
java sample_ber.MyHTTP.Reader > reader.log
