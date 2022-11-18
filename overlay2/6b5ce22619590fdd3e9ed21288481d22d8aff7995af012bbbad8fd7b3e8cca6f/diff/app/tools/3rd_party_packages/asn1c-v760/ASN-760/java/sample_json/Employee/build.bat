..\..\..\bin\asn1c employee.asn -json -java -print -pkgpfx sample_json
call ..\..\setenv.bat
SET CLASSPATH=%XCLASSPATH%
javac *.java
java sample_json.Employee.Writer > writer.log
java sample_json.Employee.Reader > reader.log
