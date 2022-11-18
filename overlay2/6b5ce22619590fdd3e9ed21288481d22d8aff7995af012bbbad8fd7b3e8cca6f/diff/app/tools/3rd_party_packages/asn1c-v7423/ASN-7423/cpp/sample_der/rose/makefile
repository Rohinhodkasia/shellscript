# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

SOURCES = \
Remote-Operations-Information-Objects.cpp \
Remote-Operations-Information-Objects.h \
Remote-Operations-Generic-ROS-PDUs.cpp \
Remote-Operations-Generic-ROS-PDUs.h \
Remote-Operations-Useful-Definitions.h

OBJECTS = \
Remote-Operations-Generic-ROS-PDUs$(OBJ) \
Remote-Operations-Information-Objects$(OBJ)

all : $(SOURCES) $(OBJECTS)

include rules.mk

Remote-Operations-Information-Objects.cpp \
Remote-Operations-Information-Objects.h \
: ROS1.asn
	$(ASN1C) ROS1.asn -c++ -der -config rose.cfg \
	-cfile Remote-Operations-Information-Objects.cpp

Remote-Operations-Generic-ROS-PDUs.cpp \
Remote-Operations-Generic-ROS-PDUs.h \
: ROS2.asn
	$(ASN1C) ROS2.asn -c++ -der -config rose.cfg \
	-cfile Remote-Operations-Generic-ROS-PDUs.cpp

Remote-Operations-Useful-Definitions.h : ROS3.asn
	$(ASN1C) ROS3.asn -c++ -der -config rose.cfg

clean:
	$(RM) Remote-*.*
	$(RM) *~
	$(RM_MSVC_FILES)
	$(RM) rtkey.h
