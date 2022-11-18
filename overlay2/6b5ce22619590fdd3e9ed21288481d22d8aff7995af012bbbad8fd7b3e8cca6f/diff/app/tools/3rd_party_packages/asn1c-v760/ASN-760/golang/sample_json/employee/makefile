# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = \
../../../c/sample_json/Employee/employee.asn

GOFILES = \
.$(PS)asn1gen$(PS)Employee.go \
.$(PS)asn1gen$(PS)asn1rt$(PS)runtime.go \
.$(PS)asn1gen$(PS)Print.go

all : message.per writer.log reader.log

reader.log : message.per
	.$(PS)employee reader > reader.log

writer.log message.per : employee$(EXE)
	.$(PS)employee writer > writer.log

employee$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -json -print

clean:
	$(RM) employee$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
