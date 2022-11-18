# makefile to build sample program

include ../../platform.mk
include ../../../sample.mk

SOURCES = \
Remote-Operations-Information-Objects.c \
Remote-Operations-Information-Objects.h \
Remote-Operations-Generic-ROS-PDUs.c \
Remote-Operations-Generic-ROS-PDUs.h

OBJECTS = \
Remote-Operations-Generic-ROS-PDUs$(OBJ) \
Remote-Operations-Information-Objects$(OBJ)

all : $(SOURCES) $(OBJECTS)

include rules.mk

# .c -> .o dependencies
# these can be updated by executing 'make depends'
include depends.mk

Remote-Operations-Information-Objects.c \
Remote-Operations-Information-Objects.h \
: ROS1.asn
	$(ASN1C) ROS1.asn -c -der -config rose.cfg \
	-cfile Remote-Operations-Information-Objects.c

Remote-Operations-Generic-ROS-PDUs.c \
Remote-Operations-Generic-ROS-PDUs.h \
: ROS2.asn
	$(ASN1C) ROS2.asn -c -der -config rose.cfg \
	-cfile Remote-Operations-Generic-ROS-PDUs.c

Remote-Operations-Useful-Definitions.h : ROS3.asn
	$(ASN1C) ROS3.asn -c -der -config rose.cfg

depends: Remote-Operations-Information-Objects.c \
Remote-Operations-Generic-ROS-PDUs.c Remote-Operations-Useful-Definitions.h
	gcc *.c -E -MM $(IPATHS) > depends.mk
	sed -i 's/\.o/\$$(OBJ)/' depends.mk

clean:
	$(RM) Remote-*.*
	$(RM) *~
	$(RM_MSVC_FILES)
	$(RM) rtkey.h
