..\..\..\bin\asn1c employee.asn -per -java -print -pkgpfx sample_per -trace
call ..\..\setenv.bat
javac *.java
java sample_per.Employee.Writer -a > writer_a.log
java sample_per.Employee.Reader -a > reader_a.log
java sample_per.Employee.Writer -u > writer_u.log
java sample_per.Employee.Reader -u > reader_u.log
