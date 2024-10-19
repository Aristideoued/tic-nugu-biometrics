include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = DongleInfoCPP

### Objects, sources ###

# CCPP source files

CXXSRCS = \
	DongleInfoCPP.cpp

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NLicensing -framework NCore
else
  LDLIBS ?= -lNLicensing -lNCore
endif

include ../../../Common/Build/rules.mk

