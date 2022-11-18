..\..\..\bin\asn1c setOfInt.asn -ber -java -print -pkgname sample_der.CanSort
call ..\..\setenv.bat
javac *.java
java sample_der.CanSort.Writer > writer.log
java sample_der.CanSort.Reader > reader.log
