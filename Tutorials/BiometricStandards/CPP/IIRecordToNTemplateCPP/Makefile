include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = IIRecordToNTemplateCPP

### Objects, sources ###

# CPP source files

CXXSRCS = \
	IIRecordToNTemplateCPP.cpp

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NBiometricClient -framework NBiometrics -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNBiometricClient -lNBiometrics -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

