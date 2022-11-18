# makefile to build generated files

include ../../../platform.mk

# include directories
OSROOTDIR = ../../../..
LIBDIR = ..$(PS)lib
RTSRCDIR = $(OSROOTDIR)/rtsrc
RTXSRCDIR = $(OSROOTDIR)/rtxsrc
RT3GPPSRCDIR = $(OSROOTDIR)/rt3gppsrc
SRCDIR = ../../src
SRC2DIR = ../../src2

# compiler defs
CFLAGS = -c $(CVARS_) $(CFLAGS_) $(COPTIMIZE_)
IPATHS = -I$(SRCDIR) -I$(SRC2DIR) -I$(OSROOTDIR) -I$(RTSRCDIR) -I$(RTXSRCDIR) $(IPATHS_)
LINKOPT = $(LINKOPT_)

include ../../src/objects.mk
include ../../src2/objects.mk

$(LIBDIR)/$(LIBPFX)osys3gpp$(A) : $(ALLOBJECTS) $(SRC2OBJECTS)
	$(LIBCMD) $(ALLOBJECTS) $(SRC2OBJECTS)

# .c -> .obj rules
include ../../src/rules.mk
include ../../src2/rules.mk

clean:
	$(RM) *$(OBJ)
	$(RM) *.pdb
	$(RM) $(LIBDIR)$(PS)$(LIBPFX)osys3gpp$(A)

