cd ..\AIN
call .\build.bat
cd ..\TCAP
call .\build.bat
cd ..\TcapInvoke
call ..\..\setenv.bat
javac *.java
java sample_ber.TcapInvoke.Writer > writer.log
java sample_ber.TcapInvoke.Reader > reader.log
