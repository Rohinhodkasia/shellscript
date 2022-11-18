..\..\..\bin\asn1c employee.asn -per -java -print -pkgname sample_per.Employee3 -trace
call ..\..\setenv.bat
javac *.java
java sample_per.Employee3.Writer -a > writer_a.log
java sample_per.Employee3.Reader -a > reader_a.log
java sample_per.Employee3.Writer -u > writer_u.log
java sample_per.Employee3.Reader -u > reader_u.log
