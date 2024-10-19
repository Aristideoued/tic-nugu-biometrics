include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = DongleUpdate

### Objects, sources ###

# C source files

CSRCS = \
	DongleUpdate.c

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NLicensing -framework NCore
else
  LDLIBS ?= -lNLicensing -lNCore
endif

include ../../../Common/Build/rules.mk

