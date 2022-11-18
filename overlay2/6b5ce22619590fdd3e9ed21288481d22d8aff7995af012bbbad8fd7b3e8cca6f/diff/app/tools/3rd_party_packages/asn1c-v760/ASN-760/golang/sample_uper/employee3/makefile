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
	.$(PS)employee3 reader > reader.log

writer.log message.uper : employee3$(EXE)
	.$(PS)employee3 writer > writer.log

employee3$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -uper -print -trace -o "."

clean:
	$(RM) employee3$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
