include ../../../platform.mk
include ../../sample.mk

ASN1FILES = megaco.asn
GOFILES = asn1gen$(PS)MEDIA_GATEWAY_CONTROL.go $(GORTFILES)

all : reader.log

reader.log : megaco$(EXE) message.per 
	.$(PS)megaco reader > reader.log

megaco$(EXE) : $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -trace -print -no-go-main

clean:
	$(RM) megaco$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
