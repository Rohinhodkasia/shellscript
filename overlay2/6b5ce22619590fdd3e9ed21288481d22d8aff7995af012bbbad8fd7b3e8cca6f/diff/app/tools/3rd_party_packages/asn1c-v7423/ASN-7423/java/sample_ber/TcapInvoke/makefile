.SUFFIXES : .java .class

include ../../../platform.mk
include ../../../sample.mk
include ../../jsample.mk

all: writer.log reader.log

reader.log : Reader.class
	java $(CLASSPATHS) sample_ber.TcapInvoke.Reader > reader.log

writer.log : Writer.class
	java $(CLASSPATHS) sample_ber.TcapInvoke.Writer > writer.log

Reader.class Writer.class : Reader.java Writer.java
	cd ../AIN  ; $(MAKE)
	cd ../TCAP ; $(MAKE)
	javac $(CLASSPATHS) *.java

clean:
	$(RM) *.class
	$(RM) *~
	$(RM) writer.log 
	$(RM) reader.log

