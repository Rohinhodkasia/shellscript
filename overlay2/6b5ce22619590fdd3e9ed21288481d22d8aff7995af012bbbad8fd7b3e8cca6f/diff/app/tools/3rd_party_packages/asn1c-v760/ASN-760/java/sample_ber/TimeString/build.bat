..\..\..\bin\asn1c time.asn -ber -java -print -pkgpfx sample_ber
javac -classpath "../../asn1rt.jar;../..;%CLASSPATH%" *.java
java  -classpath "../../asn1rt.jar;../..;%CLASSPATH%" sample_ber.TimeString.Writer > writer.log
java  -classpath "../../asn1rt.jar;../..;%CLASSPATH%" sample_ber.TimeString.Reader > reader.log
