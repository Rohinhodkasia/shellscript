..\..\..\bin\asn1c canonical.asn -coer -java -print -pkgpfx sample_oer
call ..\..\setenv.bat
javac *.java
java sample_oer.Canonical.Writer > writer.log
java sample_oer.Canonical.Reader > reader.log
