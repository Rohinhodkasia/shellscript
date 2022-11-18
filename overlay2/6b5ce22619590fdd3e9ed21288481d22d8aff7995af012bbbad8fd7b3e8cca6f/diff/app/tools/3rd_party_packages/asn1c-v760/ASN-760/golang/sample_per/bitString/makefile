include ../../../platform.mk
include ../../sample.mk

ASN1FILES = test.asn
GOFILES = asn1gen$(PS)BitString.go asn1gen$(PS)Marshal.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per 
	.$(PS)bitString reader > reader.log

writer.log message.per : bitString$(EXE)
	.$(PS)bitString writer > writer.log

bitString$(EXE) : $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -trace -print -no-go-main

clean:
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
