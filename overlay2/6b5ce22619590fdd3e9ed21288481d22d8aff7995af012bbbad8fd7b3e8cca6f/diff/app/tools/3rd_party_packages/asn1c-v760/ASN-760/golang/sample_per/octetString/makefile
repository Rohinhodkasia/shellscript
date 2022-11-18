include ../../../platform.mk
include ../../sample.mk

ASN1FILES = test.asn
GOFILES = asn1gen$(PS)MyModule.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per 
	.$(PS)octetString reader > reader.log

writer.log message.per : octetString$(EXE)
	.$(PS)octetString writer > writer.log

octetString$(EXE) : $(GOFILES)
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -trace -no-go-main

clean:
	$(RM) octetString$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
