#! /bin/bash

################################################################################
#(c) Copyright 2021 by Amantya Technologies (Amantya) . All rights reserved.
#
#  This software is confidential and proprietary to Amantya.
#  No part of this software may be reproduced, stored, transmitted,
#  disclosed or used in any form or by any means other than as expressly
#  provided by the written Software License Agreement between Amantya
#  and its licensee.
#
#  AMANTYA MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
#  WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
#  A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED MATERIALS.
#
#  IN NO EVENT SHALL AMANTYA BE LIABLE FOR ANY INDIRECT, SPECIAL,
#  CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
#  OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
#  ON BREACH OF CONTRACT, PRODUCT LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#  Before any installation, use or transfer of this software, please
#  consult the written Software License Agreement or contact Amantya at
#  the location set forth below in order to confirm that you are
#  engaging in a permissible use of the software.
#
#  Amantya Technologies, Inc
#  Tel: +1 302 439 6030
#  Fax: +1 302 543 2691
#  Email: connect@amantyatech.com
#  Web: www.amantyatech.com
###########################################################################


#set -x
#From: https://gist.github.com/bradland/1690807

# Bash shell script for generating self-signed certs. Run this in a folder, as it
# generates a few files. 

# Script accepts no argument(s)

SCRIPTPATH=$(cd "$(dirname "$0")"; pwd -P)
source "$SCRIPTPATH"/cert_info

op_dir="$SCRIPTPATH"/../certs

if [ -d "$op_dir" ]
then
	if [[ -f "$op_dir"/5g_sim.crt && -f "$op_dir"/5g_sim.key ]]
	then
		echo "Certificates already generated"
		exit 0
	else
		echo "Certificates missing. Regenerating them"
		rm -f "$op_dir"/*.crt "$op_dir"/*.key
	fi
else
	mkdir -p "$op_dir"
fi

fail_if_error() {
  [ $1 != 0 ] && {
    unset PASSPHRASE
    exit 10
  }
}

# Remove random state error
rm -f ~/.rnd

# Generate a random passphrase
export PASSPHRASE=$(head -c 500 /dev/urandom | tr -dc a-z0-9A-Z | head -c 128; echo)

# Certificate details;
subj="
C=$COUNTRY
ST=$STATE
O=$ORG
localityName=$CITY
commonName=$DOMAIN
organizationalUnitName=$DEPARTMENT
emailAddress=$EMAIL
"

# Generate the server private key
openssl genrsa -des3 -out "$op_dir"/5g_sim.key -passout env:PASSPHRASE 2048
fail_if_error $?

# Generate the CSR
openssl req \
    -new \
    -batch \
    -subj "$(echo -n "$subj" | tr "\n" "/")" \
    -key "$op_dir"/5g_sim.key \
    -out "$op_dir"/5g_sim.csr \
    -passin env:PASSPHRASE
fail_if_error $?
cp "$op_dir"/5g_sim.key "$op_dir"/5g_sim.key.org
fail_if_error $?

# Remove passphrase
openssl rsa -in "$op_dir"/5g_sim.key.org -out "$op_dir"/5g_sim.key -passin env:PASSPHRASE
fail_if_error $?

# Generate the cert (good for 10 years)
openssl x509 -req -days 3650 -in "$op_dir"/5g_sim.csr -signkey "$op_dir"/5g_sim.key -out "$op_dir"/5g_sim.crt
fail_if_error $?
rm -f "$op_dir"/5g_sim.csr "$op_dir"/5g_sim.key.org
