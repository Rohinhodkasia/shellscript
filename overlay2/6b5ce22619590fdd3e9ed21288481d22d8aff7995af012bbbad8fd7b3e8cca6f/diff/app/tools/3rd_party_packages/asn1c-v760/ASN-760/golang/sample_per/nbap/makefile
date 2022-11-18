# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = \
nbapSample.asn

GOFILES = \
.$(PS)asn1gen$(PS)NBAP_PDU_Descriptions.go \
.$(PS)asn1gen$(PS)NBAP_PDU_Contents.go \
.$(PS)asn1gen$(PS)NBAP_IEs.go \
.$(PS)asn1gen$(PS)NBAP_CommonDataTypes.go \
.$(PS)asn1gen$(PS)NBAP_Constants.go \
.$(PS)asn1gen$(PS)NBAP_Containers.go \
$(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per
	.$(PS)nbap reader > reader.log

writer.log message.per : nbap$(EXE)
	.$(PS)nbap writer > writer.log

nbap$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -print -tables -trace -no-go-main

clean:
	$(RM) nbap$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
