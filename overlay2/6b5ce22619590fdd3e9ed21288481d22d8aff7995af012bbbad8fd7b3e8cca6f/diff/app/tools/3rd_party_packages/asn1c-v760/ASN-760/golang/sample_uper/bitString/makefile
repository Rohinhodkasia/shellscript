include ../../../platform.mk
include ../../sample.mk

ASN1FILES = ../../sample_per/bitString/test.asn
GOFILES = asn1gen$(PS)BitString.go $(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per 
	.$(PS)bitString reader > reader.log

writer.log message.per : bitString$(EXE)
	.$(PS)bitString writer > writer.log

bitString$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

main.go : ../../sample_per/bitString/main.go
	$(COPY) ..$(PS)..$(PS)sample_per$(PS)bitString$(PS)main.go .

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -uper -trace -prttostr -no-go-main

clean:
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
