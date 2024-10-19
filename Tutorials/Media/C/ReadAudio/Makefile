include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = ReadAudio

### Objects, sources ###

# C source files

CSRCS = \
	ReadAudio.c

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

