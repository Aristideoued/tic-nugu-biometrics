include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = IdGenerationCPP

### Objects, sources ###

# CPP source files

CXXSRCS = \
	IdGenerationCPP.cpp

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NLicensing -framework NCore
else
  LDLIBS ?= -lNLicensing -lNCore
endif

include ../../../Common/Build/rules.mk

