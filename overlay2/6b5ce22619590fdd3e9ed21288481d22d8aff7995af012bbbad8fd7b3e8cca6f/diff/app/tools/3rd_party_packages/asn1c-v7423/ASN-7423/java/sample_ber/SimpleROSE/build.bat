..\..\..\bin\asn1c simple-ROSE.asn -ber -java -print -pkgpfx sample_ber
call ..\..\setenv.bat
javac *.java
