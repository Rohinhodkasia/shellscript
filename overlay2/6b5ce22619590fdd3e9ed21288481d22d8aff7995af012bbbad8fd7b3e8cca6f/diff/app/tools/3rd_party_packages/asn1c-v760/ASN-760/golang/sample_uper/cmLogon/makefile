# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = acse-1.asn cm-v1.asn
GOFILES = \
.$(PS)asn1gen$(PS)ACSE_1.go \
.$(PS)asn1gen$(PS)CMMessageSetVersion1.go \
.$(PS)asn1gen$(PS)Asn1External.go \
.$(PS)asn1gen$(PS)Marshal.go \
$(GORTFILES)

all : message.uper writer.log reader.log

reader.log : message.uper
	.$(PS)cmLogon reader > reader.log

writer.log message.uper : cmLogon$(EXE)
	.$(PS)cmLogon writer > writer.log

cmLogon$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -uper -print -pdu CMAircraftMessage -trace -o "."

clean:
	$(RM) cmLogon$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
