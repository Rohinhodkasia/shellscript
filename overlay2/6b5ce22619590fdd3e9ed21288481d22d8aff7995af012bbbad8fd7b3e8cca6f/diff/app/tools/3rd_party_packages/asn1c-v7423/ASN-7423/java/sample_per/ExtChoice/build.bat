..\..\..\bin\asn1c extChoice.asn -per -java -print -pkgpfx sample_per -trace
call ..\..\setenv.bat
javac *.java
java sample_per.ExtChoice.Writer -a > writer_a.log
java sample_per.ExtChoice.Reader -a > reader_a.log
java sample_per.ExtChoice.Writer -u > writer_u.log
java sample_per.ExtChoice.Reader -u > reader_u.log
