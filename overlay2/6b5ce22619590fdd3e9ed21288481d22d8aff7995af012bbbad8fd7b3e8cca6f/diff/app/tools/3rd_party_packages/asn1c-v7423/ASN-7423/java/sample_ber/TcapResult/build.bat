cd ..\AIN
call .\build.bat
cd ..\TCAP
call .\build.bat
cd ..\TcapResult
call ..\..\setenv.bat
javac *.java
java sample_ber.TcapResult.Writer > writer.log
java sample_ber.TcapResult.Reader > reader.log
