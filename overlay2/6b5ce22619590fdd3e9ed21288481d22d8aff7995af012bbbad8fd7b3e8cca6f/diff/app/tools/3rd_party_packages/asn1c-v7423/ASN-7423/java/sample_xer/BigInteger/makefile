.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = BigIntType.java Dss_Parms.java
XCLASSPATHS = $(CLASSPATHS)$(FS)../../xmlpull/kxml2-2.3.0.tiny.jar

all: writer.log reader.log

reader.log : Reader.class
	java $(XCLASSPATHS) sample_xer.BigInteger.Reader > reader.log

writer.log : Writer.class
	java $(XCLASSPATHS) sample_xer.BigInteger.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(XCLASSPATHS) *.java

$(JSOURCES) : bigInt.asn
	$(ASN1C) bigInt.asn -xer -xmlpull -java -print -pkgname sample_xer.BigInteger -config bigInt.cfg

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) writer.log 
	$(RM) reader.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

