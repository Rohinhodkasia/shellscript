.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

JSOURCES = MakeCallArgument.java

all: writer.log reader.log readeri.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.CSTA.Reader > reader.log

writer.log message.dat : Writer.class
	java $(CLASSPATHS) sample_ber.CSTA.Writer > writer.log

# indefinite length test

readeri.log : Reader.class messagei.dat
	java $(CLASSPATHS) sample_ber.CSTA.Reader -i messagei.dat > readeri.log

messagei.dat : message.dat ../../../bin/ber2indef$(EXE)
	$(BER2INDEF) message.dat messagei.dat

Reader.class Writer.class : Reader.java Writer.java $(JSOURCES)
	cd ..$(PS)SimpleROSE; $(MAKE)
	javac $(CLASSPATHS) *.java

$(JSOURCES) : makeCallArgument.asn 
	$(ASN1C) makeCallArgument.asn -ber -java -print -pkgname sample_ber.CSTA

clean:
	$(MV) Reader.java Reader.java_save
	$(MV) Writer.java Writer.java_save
	$(RM) *.java 
	$(RM) *.class
	$(RM) *~
	$(RM) *.log
	$(MV) Reader.java_save Reader.java
	$(MV) Writer.java_save Writer.java

