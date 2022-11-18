..\..\..\bin\asn1c employee.asn -ber -java -print -events -pkgname sample_ber.EventHandler 
call ..\..\setenv.bat
javac *.java
java sample_ber.EventHandler.Writer > writer.log
java sample_ber.EventHandler.Reader > reader.log
