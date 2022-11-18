..\..\..\bin\asn1c employee.asn -per -java -print -pkgname sample_per.Employee2 -trace
call ..\..\setenv.bat
javac *.java
java sample_per.Employee2.Writer -a > writer_a.log
java sample_per.Employee2.Reader -a > reader_a.log
java sample_per.Employee2.Writer -u > writer_u.log
java sample_per.Employee2.Reader -u > reader_u.log
