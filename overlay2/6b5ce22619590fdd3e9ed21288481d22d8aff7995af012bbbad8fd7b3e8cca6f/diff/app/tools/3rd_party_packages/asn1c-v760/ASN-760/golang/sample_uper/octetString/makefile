# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = \
../../sample_per/octetString/test.asn
GOFILES = \
.$(PS)asn1gen$(PS)MyModule.go \
.$(PS)asn1gen$(PS)Marshal.go \
$(GORTFILES)

all : message.uper writer.log reader.log

reader.log : message.uper
	.$(PS)octetString reader > reader.log

writer.log message.uper : octetString$(EXE)
	.$(PS)octetString writer > writer.log

octetString$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -uper -print -trace -I "../../sample_per/octetString" -o "."

clean:
	$(RM) octetString$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
