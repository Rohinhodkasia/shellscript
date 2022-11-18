..\..\..\bin\asn1c *.asn -ber -java -print -asnstd x208 -pkgname sample_ber.SnmpV2 -config snmpV2.cfg -noencode -nodecode 
call ..\..\setenv.bat
javac *.java
java sample_ber.SnmpV2.Writer > writer.log
java sample_ber.SnmpV2.Reader > reader.log
