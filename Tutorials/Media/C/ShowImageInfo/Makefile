include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = ShowImageInfo

### Objects, sources ###

# C source files

CSRCS = \
	ShowImageInfo.c

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

