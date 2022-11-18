# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = extChoice.asn
GOFILES = \
.$(PS)asn1gen$(PS)ExtChoice.go \
.$(PS)asn1gen$(PS)Marshal.go \
$(GORTFILES)

all : message.uper writer.log reader.log

reader.log : message.uper
	.$(PS)extChoice reader > reader.log

writer.log message.uper : extChoice$(EXE)
	.$(PS)extChoice writer > writer.log

extChoice$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -uper -print -trace -o "."

clean:
	$(RM) extChoice$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
