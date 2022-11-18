# makefile to generate Go code

include ../../../platform.mk
include ../../../golang/sample.mk

ASN1FILES = \
../../../specs/SUPL/v2_1/ULP.asn
GOFILES = \
.$(PS)asn1gen$(PS)ULP.go \
.$(PS)asn1gen$(PS)SUPL_INIT.go \
.$(PS)asn1gen$(PS)ULP_Components.go \
.$(PS)asn1gen$(PS)ULP_Version_2_parameter_extensions.go \
.$(PS)asn1gen$(PS)ULP_Version_2_message_extensions.go \
.$(PS)asn1gen$(PS)Ver2_ULP_Components.go \
.$(PS)asn1gen$(PS)SUPL_TRIGGERED_START.go \
.$(PS)asn1gen$(PS)ULP_Version_3_message_extensions.go \
.$(PS)asn1gen$(PS)ULP_Version_3_parameter_extensions.go \
.$(PS)asn1gen$(PS)SUPL_START.go \
.$(PS)asn1gen$(PS)OMA_LPPE.go \
.$(PS)asn1gen$(PS)SUPL_RESPONSE.go \
.$(PS)asn1gen$(PS)SUPL_POS_INIT.go \
.$(PS)asn1gen$(PS)SUPL_POS.go \
.$(PS)asn1gen$(PS)SUPL_END.go \
.$(PS)asn1gen$(PS)SUPL_AUTH_REQ.go \
.$(PS)asn1gen$(PS)SUPL_AUTH_RESP.go \
.$(PS)asn1gen$(PS)SUPL_TRIGGERED_RESPONSE.go \
.$(PS)asn1gen$(PS)SUPL_TRIGGERED_STOP.go \
.$(PS)asn1gen$(PS)SUPL_NOTIFY.go \
.$(PS)asn1gen$(PS)SUPL_NOTIFY_RESPONSE.go \
.$(PS)asn1gen$(PS)SUPL_SET_INIT.go \
.$(PS)asn1gen$(PS)SUPL_REPORT.go \
.$(PS)asn1gen$(PS)Marshal.go \
$(GORTFILES)

all : message.uper writer.log reader.log

reader.log : message.uper
	.$(PS)supl-v21 reader > reader.log

writer.log message.uper : supl-v21$(EXE)
	.$(PS)supl-v21 writer > writer.log

supl-v21$(EXE) : main.go $(GOFILES)
	go get github.com/davecgh/go-spew/spew
	go build

$(GOFILES): $(ASN1FILES) $(ASN1C)
	$(ASN1C) $(ASN1FILES) -go -no-go-main -uper -print -depends -trace -I "../../../specs/SUPL/v2_1" -config ../../../specs/SUPL/v2_1/acconfig.xml -o "."

clean:
	$(RM) supl-v21$(EXE)
	$(RM) $(GOFILES)
	$(RM) *~
	$(RM) *.log
