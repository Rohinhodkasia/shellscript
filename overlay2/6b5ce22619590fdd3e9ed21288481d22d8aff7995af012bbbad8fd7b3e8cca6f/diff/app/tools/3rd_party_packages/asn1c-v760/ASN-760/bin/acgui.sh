#!/bin/bash
##
# Runs the ASN1C GUI application. 
#
# Sets the LD_LIBRARY_PATH to point to the location of the ASN1VE binary to 
# help ensure that all Qt symbols are found.
##
ROOTDIR=$( cd `dirname $0` && pwd )
export QT_PLUGIN_PATH=""
export QTDIR=${ROOTDIR} 
export LD_LIBRARY_PATH=${ROOTDIR}
export DYLD_LIBRARY_PATH=${ROOTDIR} 
${ROOTDIR}/acgui "${@}"
