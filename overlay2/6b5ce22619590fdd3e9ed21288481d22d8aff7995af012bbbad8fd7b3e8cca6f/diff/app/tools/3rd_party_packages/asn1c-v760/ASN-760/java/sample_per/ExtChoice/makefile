# makefile to build the employee sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = AliasAddress.java

all: writer_a.log reader_a.log writer_u.log reader_u.log

reader_a.log : Reader.class 
	java $(CLASSPATHS) sample_per.ExtChoice.Reader -a > reader_a.log

writer_a.log : Writer.class 
	java $(CLASSPATHS) sample_per.ExtChoice.Writer -a > writer_a.log

reader_u.log : Reader.class 
	java $(CLASSPATHS) sample_per.ExtChoice.Reader -u > reader_u.log

writer_u.log : Writer.class 
	java $(CLASSPATHS) sample_per.ExtChoice.Writer -u > writer_u.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : extChoice.asn
	$(ASN1C) extChoice.asn -per -java -print -pkgpfx sample_per -trace

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

