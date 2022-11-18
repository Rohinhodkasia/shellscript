# makefile to build the employee sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = PersonnelRecord.java

all: writer_a.log reader_a.log writer_u.log reader_u.log

reader_a.log : Reader.class 
	java $(CLASSPATHS) sample_per.ToXML.Reader -a > reader_a.log

writer_a.log : Writer.class 
	java $(CLASSPATHS) sample_per.ToXML.Writer -a > writer_a.log

reader_u.log : Reader.class 
	java $(CLASSPATHS) sample_per.ToXML.Reader -u > reader_u.log

writer_u.log : Writer.class 
	java $(CLASSPATHS) sample_per.ToXML.Writer -u > writer_u.log

Reader.class Writer.class XMLHandler.class: \
Reader.java Writer.java XMLHandler.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : employee.asn
	$(ASN1C) employee.asn -per -java -print -events -pkgname sample_per.ToXML -trace

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(MV) XMLHandler.java XMLHandler.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java
	$(MV) XMLHandler.java_save XMLHandler.java

