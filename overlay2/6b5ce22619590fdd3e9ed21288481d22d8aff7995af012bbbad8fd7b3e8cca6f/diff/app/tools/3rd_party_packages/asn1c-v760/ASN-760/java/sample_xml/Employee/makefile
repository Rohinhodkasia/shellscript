.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = PersonnelRecord.java
XCLASSPATHS = $(CLASSPATHS)$(FS)../../xmlpull/kxml2-2.3.0.tiny.jar

all: message.xml reader.log 

message.xml : Writer.class
	java $(XCLASSPATHS) sample_xml.Employee.Writer > writer.log

reader.log : Reader.class message.xml
	java $(XCLASSPATHS) sample_xml.Employee.Reader > reader.log

Writer.class Reader.class : Writer.java Reader.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java


$(JSOURCES) : employee.asn
	$(ASN1C) employee.asn -xml -xmlpull -java -print -pkgpfx sample_xml
	$(ASN1C) employee.asn -xsd

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

