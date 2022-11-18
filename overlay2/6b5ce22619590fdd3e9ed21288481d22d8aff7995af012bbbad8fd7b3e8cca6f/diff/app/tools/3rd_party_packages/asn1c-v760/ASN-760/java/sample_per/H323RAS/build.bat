..\..\..\bin\asn1c H323RAS.asn -per -java -print -pkgpfx sample_per -trace
call ..\..\setenv.bat
javac *.java
java sample_per.H323RAS.Writer -a > writer_a.log
java sample_per.H323RAS.Reader -a > reader_a.log
java sample_per.H323RAS.Writer -u > writer_u.log
java sample_per.H323RAS.Reader -u > reader_u.log
