include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = ReadAudioFromDevice

### Objects, sources ###

# C source files

CSRCS = \
	ReadAudioFromDevice.c

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

