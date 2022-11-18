..\..\..\bin\asn1c employee.asn -ber -java -print -events -pkgname sample_ber.ToXML
call ..\..\setenv.bat
javac *.java
java sample_ber.ToXML.Writer > writer.log
java sample_ber.ToXML.Reader > reader.log
