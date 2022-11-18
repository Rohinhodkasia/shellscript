include ../../../platform.mk
include ../../sample.mk

ASN1FILES = extChoice.asn
GOFILES = asn1gen$(PS)extChoice.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per 
	.$(PS)extChoice reader > reader.log

writer.log message.per : extChoice$(EXE)
	.$(PS)extChoice writer > writer.log

extChoice$(EXE) : $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -trace -print -no-go-main

clean:
	$(RM) extChoice$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
