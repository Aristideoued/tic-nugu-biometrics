include ../../../Common/Build/config.mk

### target ###

TARGET_NAME   = NTemplateToANTemplate

CFLAGS += -w

### Objects, sources ###

# C source files

CSRCS = \
	NTemplateToANTemplate.c

ifeq ($(N_APPLE_FRAMEWORKS),yes)
  LDLIBS ?= -framework NBiometricClient -framework NBiometrics -framework NMedia -framework NCore -framework NLicensing
else
  LDLIBS ?= -lNBiometricClient -lNBiometrics -lNMedia -lNCore -lNLicensing
endif

include ../../../Common/Build/rules.mk

