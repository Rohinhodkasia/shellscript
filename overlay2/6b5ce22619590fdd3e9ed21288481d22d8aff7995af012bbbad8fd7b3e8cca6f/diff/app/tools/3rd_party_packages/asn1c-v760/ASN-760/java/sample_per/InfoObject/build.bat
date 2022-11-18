..\..\..\bin\asn1c InfoObject.asn -per -java -print -pkgpfx sample_per -trace
call ..\..\setenv.bat
javac *.java
java sample_per.InfoObject.Writer -a > writer_a.log
java sample_per.InfoObject.Reader -a > reader_a.log
java sample_per.InfoObject.Writer -u > writer_u.log
java sample_per.InfoObject.Reader -u > reader_u.log
