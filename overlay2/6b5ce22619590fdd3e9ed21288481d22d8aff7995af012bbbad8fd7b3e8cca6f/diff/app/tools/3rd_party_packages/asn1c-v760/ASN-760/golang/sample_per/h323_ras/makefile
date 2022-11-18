# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = H323RAS.asn
GOFILES = \
.$(PS)asn1gen$(PS)H323RAS.go \
.$(PS)asn1gen$(PS)Marshal.go \
$(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per
	.$(PS)h323_ras reader > reader.log

writer.log message.per : h323_ras$(EXE)
	.$(PS)h323_ras writer > writer.log

h323_ras$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -per -print -trace -o "."

clean:
	$(RM) h323_ras$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
