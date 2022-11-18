include ../../../platform.mk
include ../../sample.mk

ASN1FILES = extChoice.asn
GOFILES = asn1gen$(PS)ExtChoice.go $(GORTFILES)

all : message2.per reader.log writer.log

reader.log message2.per : extChoiceOpen$(EXE) message.per
	.$(PS)extChoiceOpen > reader.log

writer.log message.per : ../extChoice/extChoice$(EXE)
	..$(PS)extChoice$(PS)extChoice writer -t 3 > writer.log

extChoiceOpen$(EXE) : $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -per -trace -print -no-go-main

clean:
	$(RM) extChoiceOpen$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
	$(RM) message*.per

