include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = LicenseActivationFromDongleCPP

### Objects, sources ###

# CPP source files

CXXSRCS = \
	LicenseActivationFromDongleCPP.cpp

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NLicensing -framework NCore
else
  LDLIBS ?= -lNLicensing -lNCore
endif

include ../../../Common/Build/rules.mk

