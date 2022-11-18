include ../../../platform.mk
include ../../sample.mk

ASN1FILES = infoObject.asn
GOFILES = asn1gen$(PS)infoObject.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per 
	.$(PS)infoObject reader > reader.log

writer.log message.per : infoObject$(EXE)
	.$(PS)infoObject writer > writer.log

infoObject$(EXE) : $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -trace -print -no-go-main

clean:
	$(RM) infoObject$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
