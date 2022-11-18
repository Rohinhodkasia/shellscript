..\..\..\bin\asn1c realTest.asn -per -java -print -pkgpfx sample_per -trace
call ..\..\setenv.bat
javac *.java
java sample_per.Real.Writer -a > writer_a.log
java sample_per.Real.Reader -a > reader_a.log
java sample_per.Real.Writer -u > writer_u.log
java sample_per.Real.Reader -u > reader_u.log
