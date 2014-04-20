# put common definitions in here
CC  = gcc
PRJCFLAGS = -g
LD  = gcc
LDFLAGS =
AR  = ar
ARFLAGS =
RANLIB  = ranlib
RM = rm -rf
ECHO  = echo
CS = coffee

SHELL = /bin/sh

.PHONY: all clean

define coffee-command
$(CS) -cbo $(BUILDDIR) $<
endef

define coffee-join-command
$(CS) -cb -j $@ $<
endef


.SILENT :
