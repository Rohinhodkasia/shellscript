# makefile to build the employee sample program

.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = AliasAddress.java AliasAddressList.java \
AliasAddress_transportID.java EnumVal.java PartyNumber.java \
TransportAddress.java

XCLASSPATHS = $(CLASSPATHS)$(FS)../../xmlpull/kxml2-2.3.0.tiny.jar

all: writer.log reader.log 

reader.log : Reader.class 
	java $(XCLASSPATHS) sample_xml.ExtChoice.Reader > reader.log

writer.log : Writer.class 
	java $(XCLASSPATHS) sample_xml.ExtChoice.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java

$(JSOURCES) : extChoice.asn
	$(ASN1C) extChoice.asn -xml -xmlpull -java -xsd -print -pkgpfx sample_xml -trace

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) ExtChoice.xsd
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) writer*.log 
	$(RM) reader*.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

