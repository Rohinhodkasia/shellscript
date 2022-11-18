..\..\..\bin\asn1c time.asn -der -java -print -pkgpfx sample_der
javac -classpath "../../asn1rt.jar;../..;%CLASSPATH%" *.java
java  -classpath "../../asn1rt.jar;../..;%CLASSPATH%" sample_der.TimeString.Writer > writer.log
java  -classpath "../../asn1rt.jar;../..;%CLASSPATH%" sample_der.TimeString.Reader > reader.log
