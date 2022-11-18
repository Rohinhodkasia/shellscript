# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = employee.asn
GOFILES = \
.$(PS)asn1gen$(PS)Employee.go \
.$(PS)asn1gen$(PS)Marshal.go \
$(GORTFILES)

all : message.uper writer.log reader.log

reader.log : message.uper
	.$(PS)employee reader > reader.log

writer.log message.uper : employee$(EXE)
	.$(PS)employee writer > writer.log

employee$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -uper -print -trace -o "."

clean:
	$(RM) employee$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
