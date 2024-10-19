include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = ShowImageInfoCPP

### Objects, sources ###

# CPP source files

CXXSRCS = \
	ShowImageInfoCPP.cpp

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

