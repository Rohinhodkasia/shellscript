# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = param.asn

GOFILES = .$(PS)asn1gen$(PS)ParamType.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per
	.$(PS)paramType reader > reader.log

writer.log message.per : paramType$(EXE)
	.$(PS)paramType writer > writer.log

paramType$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -print -trace -no-go-main

clean:
	$(RM) paramType$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
