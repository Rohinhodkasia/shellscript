include ../../../platform.mk
include ../../sample.mk

ASN1FILES = employee.asn
GOFILES = asn1gen$(PS)Employee.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per 
	.$(PS)employee3 reader > reader.log

writer.log message.per : employee3$(EXE)
	.$(PS)employee3 writer > writer.log

employee3$(EXE) : $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -trace -no-go-main -genprint

clean:
	$(RM) employee3$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
