.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = BigIntType.java Dss_Parms.java

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_der.BigInteger.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_der.BigInteger.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : bigInt.asn
	$(ASN1C) bigInt.asn -der -java -print -pkgname sample_der.BigInteger -config bigInt.cfg

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

