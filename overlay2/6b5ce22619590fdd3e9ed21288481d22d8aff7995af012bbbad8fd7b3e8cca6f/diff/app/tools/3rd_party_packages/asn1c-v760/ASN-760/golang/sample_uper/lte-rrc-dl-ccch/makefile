# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = \
../../../specs/lte-rrc/rel15/EUTRA-InterNodeDefinitions.asn \
../../../specs/lte-rrc/rel15/EUTRA-RRC-Definitions.asn \
../../../specs/lte-rrc/rel15/EUTRA-Sidelink-Preconf.asn \
../../../specs/lte-rrc/rel15/EUTRA-UE-Variables.asn \
../../../specs/lte-rrc/rel15/NBIOT-InterNodeDefinitions.asn \
../../../specs/lte-rrc/rel15/NBIOT-RRC-Definitions.asn \
../../../specs/lte-rrc/rel15/NBIOT-UE-Variables.asn \
../../../specs/lte-rrc/rel15/PC5-RRC-Definitions.asn
GOFILES = \
.$(PS)asn1gen$(PS)EUTRA_InterNodeDefinitions.go \
.$(PS)asn1gen$(PS)EUTRA_RRC_Definitions.go \
.$(PS)asn1gen$(PS)EUTRA_Sidelink_Preconf.go \
.$(PS)asn1gen$(PS)EUTRA_UE_Variables.go \
.$(PS)asn1gen$(PS)NBIOT_InterNodeDefinitions.go \
.$(PS)asn1gen$(PS)NBIOT_RRC_Definitions.go \
.$(PS)asn1gen$(PS)NBIOT_UE_Variables.go \
.$(PS)asn1gen$(PS)PC5_RRC_Definitions.go \
.$(PS)asn1gen$(PS)Marshal.go \
$(GORTFILES)

all : message.uper writer.log reader.log

reader.log : message.uper
	.$(PS)lte-rrc-dl-ccch reader > reader.log

writer.log message.uper : lte-rrc-dl-ccch$(EXE)
	.$(PS)lte-rrc-dl-ccch writer > writer.log

lte-rrc-dl-ccch$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -uper -print -trace -I "../../../specs/lte-rrc/rel15" -o "."

clean:
	$(RM) lte-rrc-dl-ccch$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
