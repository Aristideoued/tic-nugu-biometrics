include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = ImageCaptureCPP

### Objects, sources ###

# CPP source files

CXXSRCS = \
	ImageCaptureCPP.cpp

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NDevices -framework NBiometrics -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNDevices -lNBiometrics -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

