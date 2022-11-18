..\..\..\bin\asn1c realTest.asn -per -java -print -pkgpfx sample_per -trace -genant -reader -writer
call ..\..\setenv.bat
javac *.java
java sample_per.RealDec.Writer -a > writer_a.log
java sample_per.RealDec.Reader -a > reader_a.log
java sample_per.RealDec.Writer -u > writer_u.log
java sample_per.RealDec.Reader -u > reader_u.log
