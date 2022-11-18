..\..\..\bin\asn1c time.asn -per -java -print -pkgpfx sample_per
javac -classpath "../../asn1rt.jar;../..;%CLASSPATH%" *.java
java  -classpath "../../asn1rt.jar;../..;%CLASSPATH%" sample_per.TimeString.Writer -a > writer_a.log
java  -classpath "../../asn1rt.jar;../..;%CLASSPATH%" sample_per.TimeString.Reader -a > reader_a.log
java  -classpath "../../asn1rt.jar;../..;%CLASSPATH%" sample_per.TimeString.Writer -u > writer_u.log
java  -classpath "../../asn1rt.jar;../..;%CLASSPATH%" sample_per.TimeString.Reader -u > reader_u.log
