..\..\..\bin\asn1c acse-1.asn -per -java -print -pkgname sample_per.CMLogon -trace
..\..\..\bin\asn1c cm-v1.asn -per -java -print -pkgname sample_per.CMLogon -trace
call ..\..\setenv.bat
javac *.java
java sample_per.CMLogon.Writer -a > writer_a.log
java sample_per.CMLogon.Reader -a > reader_a.log
java sample_per.CMLogon.Writer -u > writer_u.log
java sample_per.CMLogon.Reader -u > reader_u.log
