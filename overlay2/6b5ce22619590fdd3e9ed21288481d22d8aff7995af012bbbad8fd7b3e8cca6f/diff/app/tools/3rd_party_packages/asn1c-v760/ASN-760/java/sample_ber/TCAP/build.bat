..\..\..\bin\asn1c90 tcap.asn -ber -java -print -pkgname sample_ber.TCAP
call ..\..\setenv.bat
javac *.java
