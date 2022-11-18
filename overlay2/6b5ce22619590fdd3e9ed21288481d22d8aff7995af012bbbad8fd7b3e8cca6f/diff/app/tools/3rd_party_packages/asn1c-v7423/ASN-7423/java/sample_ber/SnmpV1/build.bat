..\..\..\bin\asn1c *.asn -ber -java -print -asnstd x208 -pkgname sample_ber.SnmpV1 
call ..\..\setenv.bat
javac *.java
java sample_ber.SnmpV1.Writer > writer.log
java sample_ber.SnmpV1.Reader > reader.log
