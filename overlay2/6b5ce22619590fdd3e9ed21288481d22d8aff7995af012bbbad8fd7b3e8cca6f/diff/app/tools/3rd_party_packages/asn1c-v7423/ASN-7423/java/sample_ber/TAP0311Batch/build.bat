..\..\..\bin\asn1c TAP-0311.asn -ber -java -compact -stream -print -pkgname sample_ber.TAP0311Batch
call ..\..\setenv.bat
javac -g *.java
java sample_ber.TAP0311Batch.Writer > writer.log
java sample_ber.TAP0311Batch.Reader > reader.log
