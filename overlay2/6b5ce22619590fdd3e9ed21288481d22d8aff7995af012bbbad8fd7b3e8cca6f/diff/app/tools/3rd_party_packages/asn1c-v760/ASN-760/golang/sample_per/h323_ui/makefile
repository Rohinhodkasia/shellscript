# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = h225.asn h235.asn
GOFILES = \
.$(PS)asn1gen$(PS)H323_MESSAGES.go \
.$(PS)asn1gen$(PS)H235_SECURITY_MESSAGES.go \
.$(PS)asn1gen$(PS)Marshal.go \
$(GORTFILES)

all : message.per writer.log reader.log

reader.log : message.per
	.$(PS)h323_ui reader > reader.log

writer.log message.per : h323_ui$(EXE)
	.$(PS)h323_ui writer > writer.log

h323_ui$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -per -print -pdu H323-UserInformation -trace -config "h323.cfg" -o "."

clean:
	$(RM) h323_ui$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
