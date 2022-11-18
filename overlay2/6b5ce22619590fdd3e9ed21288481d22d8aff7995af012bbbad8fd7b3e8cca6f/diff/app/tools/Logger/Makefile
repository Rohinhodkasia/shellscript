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


//CC = arm-none-linux-gnueabi-gcc
//AR = arm-none-linux-gnueabi-ar
CC = gcc
AR = ar

CFLAGS = -c -fPIC -Wall -DVZW_LOG_USE_CIRCULAR_BUFFER -DVZW_LOG_DEBUG_MODE -DVZW_LOG_ENABLE_TEXT_LOGGING -DSS_LINUX -DSS_VZW_BUF -std=gnu99  

# Project name
all:  liblogger

# Directories
OBJDIR = obj
SRCDIR = src
INCDIR = inc
LIBDIR = lib
BINDIR = bin

# Libraries
LIBS = -lpthread

# Files and folders
SRCS    = $(shell find $(SRCDIR) -name '*.c')
SRCDIRS = $(shell find . -name '*.c' | dirname {} | sort | uniq | sed 's/\/$(SRCDIR)//g' )
OBJS    = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
#OBJS    = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.i,$(SRCS))

# Targets
logger: buildrepo $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $@
	mv logger $(BINDIR)

liblogger: buildrepo $(OBJS)
	$(AR) -rsv liblogger.a $(OBJS)
	mv liblogger.a $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ -I$(INCDIR) 
#$(OBJDIR)/%.i: $(SRCDIR)/%.c
#	$(CC) $(CFLAGS) -E $< -o $@ -I$(INCDIR)

clean:
	rm $(BINDIR)/logger $(LIBDIR)/liblogger.a $(OBJDIR)/*.o -Rf

buildrepo:
	mkdir -p $(OBJDIR)
	mkdir -p $(LIBDIR)
	mkdir -p $(BINDIR)
	@$(call make-repo)

# Create obj directory structure
define make-repo
	mkdir -p $(OBJDIR)
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef
