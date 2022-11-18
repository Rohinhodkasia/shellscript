..\..\..\bin\asn1c H323UI.asn -per -java -print -pkgpfx sample_per -trace
call ..\..\setenv.bat
javac *.java
java sample_per.H323UI.Writer -a > writer_a.log
java sample_per.H323UI.Reader -a > reader_a.log
java sample_per.H323UI.Writer -u > writer_u.log
java sample_per.H323UI.Reader -u > reader_u.log
