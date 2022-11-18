.\..\..\bin\asn1c employee.asn -per -java -print -events -pkgname sample_per.ToXML -trace -genant -reader -writer
call ..\..\setenv.bat
javac *.java
java sample_per.ToXML.Writer -a > writer_a.log
java sample_per.ToXML.Reader -a > reader_a.log
java sample_per.ToXML.Writer -u > writer_u.log
java sample_per.ToXML.Reader -u > reader_u.log
