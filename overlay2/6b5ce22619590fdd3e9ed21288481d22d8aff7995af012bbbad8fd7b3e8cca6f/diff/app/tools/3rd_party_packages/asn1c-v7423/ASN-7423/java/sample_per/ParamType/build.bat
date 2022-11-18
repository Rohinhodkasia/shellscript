..\..\..\bin\asn1c param.asn -per -java -print -pkgpfx sample_per -trace
call ..\..\setenv.bat
javac *.java
java sample_per.ParamType.Writer -a > writer_a.log
java sample_per.ParamType.Reader -a > reader_a.log
java sample_per.ParamType.Writer -u > writer_u.log
java sample_per.ParamType.Reader -u > reader_u.log
