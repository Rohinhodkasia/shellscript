# makefile to build sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = SignedName.java

all: writer_a.log reader_a.log writer_u.log reader_u.log

reader_a.log : Reader.class 
	java $(CLASSPATHS) sample_per.ParamType.Reader -a > reader_a.log

writer_a.log : Writer.class 
	java $(CLASSPATHS) sample_per.ParamType.Writer -a > writer_a.log

reader_u.log : Reader.class 
	java $(CLASSPATHS) sample_per.ParamType.Reader -u > reader_u.log

writer_u.log : Writer.class 
	java $(CLASSPATHS) sample_per.ParamType.Writer -u > writer_u.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : param.asn
	$(ASN1C) param.asn -per -java -print -pkgpfx sample_per -trace

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

