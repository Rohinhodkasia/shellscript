..\..\..\bin\asn1c ainop.asn -asnstd x208 -ber -java -print -pkgname sample_ber.AIN -genjsources
call ..\..\setenv.bat
javac *.java
