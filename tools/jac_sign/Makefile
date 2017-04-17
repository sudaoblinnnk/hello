#ifeq ($(CUSTOMER), Standard)
#INSTANCE_DIR ?= evaluation
#else
INSTANCE_DIR ?= i$(RANDOMSEED)
#endif

BUILD_ROOT = ../..
#IAC_DIST ?= $(IACKIT_DIST)
JAC_DIST=$(BUILD_ROOT)/dist/$(PLATFORM)
include $(BUILD_ROOT)/build/platforms/Makefile.linux_x86

# build jac_sign only if the libac.a for linux_x86 exist
ifneq ("$(wildcard $(IAC_DIST)/lib/i$(RANDOMSEED)/$(HOST_PLATFORM)/$(LIB_PREFIX)ac.$(LIB_EXT))", "")

AC_AGENT = $(IAC_DIST)/lib/i$(RANDOMSEED)/$(HOST_PLATFORM)/$(LIB_PREFIX)ac_shim.$(LIB_EXT) \
            $(IAC_DIST)/lib/i$(RANDOMSEED)/$(HOST_PLATFORM)/$(LIB_PREFIX)ac.$(LIB_EXT)

HEADER_PATH = -I $(IAC_DIST)/include

SOURCES = jac_sign.c

all: clean jac_sign$(EXE_EXT) pub_jac_sign

jac_sign$(EXE_EXT) : $(SOURCES) $(EXTRA_SOURCES)
	$(CC) $(HEADER_PATH) $^ $(LDFLAGS) $(AC_AGENT) $(EXE_FLAG)$@

pub_jac_sign:
	@mkdir -p $(JAC_DIST)/bin
	$(CP) jac_sign$(EXE_EXT)  $(JAC_DIST)/bin

else

$(warning library $(IAC_DIST)/lib/i$(RANDOMSEED)/$(HOST_PLATFORM)/$(LIB_PREFIX)ac.$(LIB_EXT) does not exist. Cannot create jac_sign)

endif

	
clean:
	rm -rf *.pri *.dat *pem jac_sign$(EXE_EXT) $(EXTRA_CLEAN_FILES) 
