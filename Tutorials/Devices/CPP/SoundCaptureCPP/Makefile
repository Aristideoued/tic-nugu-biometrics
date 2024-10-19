include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = SoundCaptureCPP

### Objects, sources ###

# CPP source files

CXXSRCS = \
	SoundCaptureCPP.cpp

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NDevices -framework NBiometrics -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNDevices -lNBiometrics -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

