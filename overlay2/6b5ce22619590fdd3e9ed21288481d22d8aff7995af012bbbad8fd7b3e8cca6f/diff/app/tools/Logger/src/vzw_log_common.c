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

/*****************************************************************************
@ Description: This is common source file for postprocessor and log library.
*****************************************************************************/

#include <stdio.h>
#include "vzw_log_common.h"


Void hextostr(S8* p, PSTR h, S32 hexlen)
{
   S32 index;
   for(index = 0; index < hexlen; index++, p+=3, h++)
      sprintf(p, "%02x ", *h);
}

