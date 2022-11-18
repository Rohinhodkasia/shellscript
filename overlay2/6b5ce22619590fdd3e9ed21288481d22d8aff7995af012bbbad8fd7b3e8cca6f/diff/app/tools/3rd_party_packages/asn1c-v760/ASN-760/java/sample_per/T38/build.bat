..\..\..\bin\asn1c t38.asn -per -java -print -pkgpfx sample_per -trace
call ..\..\setenv.bat
javac *.java
java sample_per.T38.Writer -a > writer_a.log
java sample_per.T38.Reader -a > reader_a.log
java sample_per.T38.Writer -u > writer_u.log
java sample_per.T38.Reader -u > reader_u.log
