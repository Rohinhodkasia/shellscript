include ../../../platform.mk
include ../../sample.mk

ASN1FILES = employee.asn
GOFILES = asn1gen$(PS)Employee.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per 
	.$(PS)employee2 reader > reader.log

writer.log message.per : employee2$(EXE)
	.$(PS)employee2 writer > writer.log

employee2$(EXE) : $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -trace -no-go-main -genprint

clean:
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
