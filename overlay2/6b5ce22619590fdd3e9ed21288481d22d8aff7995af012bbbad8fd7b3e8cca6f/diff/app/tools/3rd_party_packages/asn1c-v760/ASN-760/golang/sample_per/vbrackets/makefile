# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = vbrackets.asn

GOFILES = .$(PS)asn1gen$(PS)VersionBrackets.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per
	.$(PS)vbrackets reader > reader.log

writer.log message.per : vbrackets$(EXE)
	.$(PS)vbrackets writer > writer.log

vbrackets$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -print -trace -no-go-main

clean:
	$(RM) vbrackets$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
