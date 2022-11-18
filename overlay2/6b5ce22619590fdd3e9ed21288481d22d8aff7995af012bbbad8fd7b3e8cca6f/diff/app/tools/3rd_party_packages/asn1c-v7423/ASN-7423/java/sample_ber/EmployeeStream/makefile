.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = PersonnelRecord.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.EmployeeStream.Reader > reader.log

writer.log message.dat : Writer.class
	java $(CLASSPATHS) sample_ber.EmployeeStream.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : employee.asn
	$(ASN1C) employee.asn -ber -java -print -pkgpfx sample_ber -stream

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

