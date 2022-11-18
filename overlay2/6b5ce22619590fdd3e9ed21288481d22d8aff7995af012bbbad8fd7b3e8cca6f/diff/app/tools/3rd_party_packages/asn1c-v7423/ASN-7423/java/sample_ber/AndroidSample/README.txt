Objective System's Android Sample Project
------------------------------------------

Prerequisites:
- Have the Android Application Development Tools (ADT) installed
- Create an Android virtual device to run the application on
- Adjust/define the ASN1C_RUNTIME classpath variable to point to asn1rt.jar
  This runtime should be an unexpired evaluation runtime or else an
  unlimited runtime.

The project has an external build tool configured.  It is named "ASN1C builder"
and uses Ant to run ASN1C to generate code from the ASN.1.  As long as you
do not move the sample, it should be able to locate the asn1c executable.  If
you move the sample or if the asn1c executable is not found, you may need to
adjust the ASN1C_HOME property in the configuration for the "ASN1C builder"
external tool.  This is done by viewing the project properties and then choosing
  Builders > ASN1C Builder > Edit > Properties

You should be able to run the sample in the Android emulator.  The program
simply populates a sample PDU, encodes that to BER, and then decodes the
encoded message to a new PDU.  The encoded message is displayed (in hex) and
the decoded PDU's print output is also displayed.  
