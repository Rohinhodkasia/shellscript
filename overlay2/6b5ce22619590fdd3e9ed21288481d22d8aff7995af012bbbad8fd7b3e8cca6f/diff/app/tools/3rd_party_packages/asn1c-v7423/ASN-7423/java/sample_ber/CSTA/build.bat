cd ..\SimpleRose
call .\build.bat
cd ..\CSTA
..\..\..\bin\asn1c makeCallArgument.asn -ber -java -print -pkgname sample_ber.CSTA
call ..\..\setenv.bat
javac *.java
java sample_ber.CSTA.Writer > writer.log
java sample_ber.CSTA.Reader > reader.log
