/*
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
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "vzw_read_config.h"
#include "vzw_log_interface.h"
#include "vzwCommonDef.h"
#define isquote(c) ((c=='\"') || (c=='\'') || (c=='`'))
typedef Void (* setterfunc_t)(S8 *);

struct setterData {
        S8 *key;
        setterfunc_t func;
};

STATIC Void call_setter(S8 *key, S8 *value);

STATIC struct setterData setter[] = {
        { "LogPath", vzwSetLogPath },
        { "LogFileName", (setterfunc_t)(vzwSetLogFile)},
	{ "SetNumOfLogFiles" , vzwSetNumOfLogFiles },
	{ "SetLogFileSizeLimit" ,vzwSetLogFileSizeLimit },
        { "LogMask", vzwSetLogLevel }
};

// Finds and Calls the appropriate setter
STATIC Void call_setter(S8 *key, S8 *value)
{
        S32 index;
        S32 count = (sizeof(setter))/(sizeof(struct setterData));
        for (index = 0; index < count ; index++) {
                if (strcmp(key, setter[index].key) == 0) {
                        setter[index].func(value);
                }
        }
}



int read_config(S8 *file)
{
        FILE* fp;
        S8 buf[BUFSIZ];
        S8 *key, *value;
        S8 q;
        printf("%s\n ", file);
	fp = fopen(file, "r");
        if (fp == NULL){
                printf("File %s Open Failed\n", file);
                exit(1);
        }


        while (fgets(buf, BUFSIZ, fp) != NULL) {
                S8 *ptr = buf;
                while((isspace(*ptr)) && (*ptr != 0)) ptr++; // leading spaces
                if (*ptr == 0) continue;
                if (*ptr == '#') continue; // Skip lines with a leading #
                key = ptr;
                while((isalnum(*ptr)) && (*ptr != 0)) ptr++;
                if (*ptr == 0) continue; // malformed line
                *ptr = 0; 
		ptr++; // Mark end of Key
                while (!isquote(*ptr) && (*ptr != 0)) ptr++; // quotation mark
                if (*ptr == 0) continue; // malformed line
                q = *ptr; // save quotation mark 
                ptr++; 
		value = ptr; // save the string not including quote mark
                while ((q != *ptr) && (*ptr != 0)) ptr++; // ending quote
                if (*ptr == 0) continue; // malformed line
                *ptr = 0; // Mark end of value overwrite endquote

                call_setter(key, value);
        }
        fclose(fp);
return 0;
}
