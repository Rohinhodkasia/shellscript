..\..\..\bin\asn1c realTest.asn -ber -java -print -pkgpfx sample_ber
call ..\..\setenv.bat
javac *.java
java sample_ber.Real.Writer > writer.log
java sample_ber.Real.Reader > reader.log
