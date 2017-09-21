export XC_DIST=/home/kurt/Work/code/merge/amy5/components/Transcoder/4.2/gcc_linux/dist

ROOT_PATH=..

#TODO Add new component ROOT folder
ROOT_DETECTION_COMPONENT=$(ROOT_PATH)/RootDetection
SECURE_STORE_COMPONENT=$(ROOT_PATH)/SecureStore
IV_COMPONENT=$(ROOT_PATH)/IV
CK_COMPONENT=$(ROOT_PATH)/CK
TBAD_COMPONENT=$(ROOT_PATH)/TBAD

ANDROID_SRC=$(ROOT_PATH)/exoplayer/demo/src/main/cpp/

#TODO Add new component include
INCLUDES = \
    -I$(ANDROID_SRC)       \
    -I$(XC_DIST)/include \
    -I$(ANDROID_NDK_DIR)/platforms/android-9/arch-arm/usr/include

    #-I$(ROOT_DETECTION_COMPONENT)/include \
    #-I$(SECURE_STORE_COMPONENT)/include \
    #-I$(IV_COMPONENT)/include   \
    #-I$(CK_COMPONENT)/include   \
    #-I$(TBAD_COMPONENT)/include   

#TODO Add new component library
ROOT_DETECTION_LIB_PATH=$(ROOT_DETECTION_COMPONENT)/lib
SECURE_STORE_LIB_PATH=$(SECURE_STORE_COMPONENT)/lib
IV_LIB_PATH=$(IV_COMPONENT)/lib
CK_LIB_PATH=$(CK_COMPONENT)/lib
TBAD_LIB_PATH=$(TBAD_COMPONENT)/lib

#X86=on
#PS=on
ARCH=
JBP_XLIB=
OUTPUT_DIR=
THRID_PARTY_ARM_LIBS_LINK=
XCODE_PATH=$(XC_DIST)/bin
PROVISION_XLIB=libiac.xlib
PROVISION_SHARED_LIB=libiac_prov.so

#TODO add new component flexlib platform
ROOT_DETECTION_PLATFORM=
SECURE_STORE_PLATFORM=
IV_PLATFORM=
CK_PLATFORM=
TBAD_PLATFORM=

ifeq ($(X86), on)
ARCH=x86
ANDROID_BIN := $(shell find -L $(ANDROID_NDK_DIR) -name bin    | grep 'linux-x86_64/bin' | grep x86- |sort -r | head -n 1 | cat)
AR = $(ANDROID_BIN)/i686-linux-android-ar
CPP = $(ANDROID_BIN)/i686-linux-android-g++
#TODO add x86 platform
ROOT_DETECTION_PLATFORM=androidgcc_4.4_x86_android
SECURE_STORE_PLATFORM=androidgcc_4.4_x86_android
IV_PLATFORM=androidgcc_4.4_x86_android
CK_PLATFORM=androidgcc_4.4_x86_android
TBAD_PLATFORM=androidgcc_4.4_x86_android
else
ARCH=arm
ANDROID_BIN := $(shell find -L $(ANDROID_NDK_DIR) -name bin    | grep 'linux-x86_64/bin' | grep arm- |sort -r | head -n 1 | cat)
AR = $(ANDROID_BIN)/arm-linux-androideabi-ar
CPP = $(ANDROID_BIN)/arm-linux-androideabi-g++
#TODO add arm platform
ROOT_DETECTION_PLATFORM=androidgcc_4.9_arm32_android
SECURE_STORE_PLATFORM=androidgcc_4.9_arm32_android
IV_PLATFORM=androidgcc_4.9_arm32_android
CK_PLATFORM=androidgcc_4.9_arm32_android
TBAD_PLATFORM=androidgcc_4.9_arm32_android
endif

ANDROID_HOME = $(ANDROID_NDK_DIR)/platforms/android-9/arch-$(ARCH)
export PATH=$(ANDROID_BIN):$(shell printenv PATH)
JBP_XLIB=libjbp_$(ARCH).xlib
BUILD_ROOT = ./$(ARCH)
OUTPUT_DIR=output_$(ARCH)
SMOOTH_A_LIB = $(BUILD_ROOT)/libiac_$(ARCH).a
NDK_INCLUDE = -I$(ANDROID_NDK_DIR)/platforms/android-9/arch-$(ARCH)/usr/include
FLEXLIB_OUTPUT_DIR=$(ROOT_PATH)/flexlib_output

$(info "=========compile arch : $(ARCH)")
$(info "CPP=$(CPP)")
$(info "ANDROID_BIN=$(ANDROID_BIN)")

$(shell mkdir -p $(BUILD_ROOT))
$(shell mkdir -p $(OUTPUT_DIR))
$(shell mkdir -p $(FLEXLIB_OUTPUT_DIR))


ANDROID_CFLAGS = \
    -fPIC \
    -ffunction-sections \
    -funwind-tables \
    -Wno-psabi \
    -fno-exceptions \
    -fno-rtti \
    -Os \
    -fomit-frame-pointer \
    -fno-strict-aliasing \
    -finline-limit=64 \
    -fdata-sections \
    -msoft-float

ANDROID_CFLAGS_ARM = \
    -mtune=xscale \
    -mthumb \
    -march=armv5te \
    -D__ARM_ARCH_5__ \
    -D__ARM_ARCH_5T__ \
    -D__ARM_ARCH_5E__ \
    -D__ARM_ARCH_5TE__ \

ITAC_FLAGS = -DANDROID -DDISABLE_FUNCTION_NAME_OBFUSCATION

#TODO specify flexlib
ifeq ($(PS), on)
ROOT_DETECTION_FLEX_LIB=CW_RootDetection.fxlib
SECURE_STORE_FLEX_LIB=CW_SecureStore.fxlib
IV_FLEX_LIB=CW_IntegrityVerification.fxlib
TBAD_FLEX_LIB=CW_TimeBasedAD.fxlib
ITAC_FLAGS += -DPSLIB
else
ROOT_DETECTION_FLEX_LIB=CW_RootDetection.fxlib
SECURE_STORE_FLEX_LIB=CW_SecureStore.fxlib
IV_FLEX_LIB=CW_IntegrityVerification.fxlib
TBAD_FLEX_LIB=CW_TimeBasedAD.fxlib
ITAC_FLAGS += -DPSLIB
endif


ifneq ($(X86), on)
	ANDROID_CFLAGS += $(ANDROID_CFLAGS_ARM)
else
	ANDROID_CFLAGS += -fwrapv 
endif

$(info "ANDROID_CFLAGS =$(ANDROID_CFLAGS)")

XCC_OPTS = 
ifeq ($(X86), on)
CC = $(ANDROID_BIN)/i686-linux-android-gcc
AR = $(ANDROID_BIN)/i686-linux-android-ar
COMPILER_TARGET = androidgcc_x86
XPP_OPT_ISO98 = -DXC_ISO98
XCODE_TARGET = $(COMPILER_TARGET)
XPP 	  = $(XCODE_PATH)/xpp -reset -compiler $(XCODE_TARGET) -verboselevel error -ea $(XCC_OPTS) $(XPP_OPT_ISO98) $(ITAC_FLAGS)
else
CC = $(ANDROID_BIN)/arm-linux-androideabi-gcc
AR = $(ANDROID_BIN)/arm-linux-androideabi-ar
COMPILER_TARGET = androidgcc_arm32
XCODE_TARGET = $(COMPILER_TARGET)
XPP_OPT_ISO98 = -DXC_ISO98
XPP 	  = $(XCODE_PATH)/xpp -reset -compiler $(XCODE_TARGET) -verboselevel error -ea $(XCC_OPTS) $(XPP_OPT_ISO98) $(ITAC_FLAGS)
endif

$(info "CC=$(CC)")

$(shell export "PATH=$(ANDROID_BIN):$(PATH)")
$(info "PATH is : $(PATH)")

RANDOMSEED:=A900BBEA49C91620A91B0D18FB350AC2
$(info "random seed is : $(RANDOMSEED)")

TARGET_FLEXLIB   = $(BUILD_ROOT)/$(PROVISION_XLIB)

XPP_LEVELS = -datatransformlevel 25 -controlflowlevel 20 
XCLOAK    = $(XCODE_PATH)/xcloak -ea
MKFLEXLIB = $(XCLOAK) -create_flexlib
XPROV     = $(XCODE_PATH)/xprov -reportlevel all -set_native_compiler $(CC)

INSTANCE=i$(RANDOMSEED)
$(info "instance is : $(INSTANCE)")

SOURCES = \

C_SOURCES = \
	exoplayer/demo/src/main/cpp/PlayerActivity.c \
	exoplayer/demo/src/main/cpp/native-lib.c

ALL_SOURCE_CPP_CODE_OBJS = $(addprefix $(BUILD_ROOT)/../../, $(patsubst %.cpp, %_debug.o, $(SOURCES)))
ALL_SOURCE_CPP_CODE_XIFS = $(addprefix $(BUILD_ROOT)/../../, $(patsubst %.cpp, %.xif, $(SOURCES)))

ALL_SOURCE_C_CODE_OBJS += $(addprefix $(BUILD_ROOT)/../../, $(patsubst %.c, %_debug.o, $(C_SOURCES)))
ALL_SOURCE_C_CODE_XIFS += $(addprefix $(BUILD_ROOT)/../../, $(patsubst %.c, %.xif, $(C_SOURCES)))

$(info "ALL_SOURCE_C_CODE_OBJS is : $(ALL_SOURCE_C_CODE_OBJS)")
$(info "ALL_SOURCE_C_CODE_XIFS is : $(ALL_SOURCE_C_CODE_XIFS)")
$(info "C_SOURCES is : $(C_SOURCES)")
#$(info "SOURCES is : $(SOURCES)")

all: $(TARGET_FLEXLIB)

clean:
	-rm -rf sib*
	-rm -rf _xpp*
	-rm -rf predefined*
	-rm -rf $(ALL_SOURCE_C_CODE_OBJS)
	-rm -rf $(ALL_SOURCE_C_CODE_XIFS)
	-rm -rf $(ALL_SOURCE_CPP_CODE_OBJS)
	-rm -rf $(ALL_SOURCE_CPP_CODE_XIFS)
	-rm -rf $(OUTPUT_DIR)
	-rm -rf $(BUILD_ROOT)
	-rm -rf report
	-rm -rf xcode_report.html 
	-rm -rf $(PROVISION_XLIB)
	#-rm -rf $(FLEXLIB_OUTPUT_DIR)


$(SMOOTH_A_LIB): $(ALL_SOURCE_C_CODE_OBJS) $(ALL_SOURCE_CPP_CODE_OBJS)
	$(AR) -r -v $@ $(ALL_SOURCE_C_CODE_OBJS) $(ALL_SOURCE_CPP_CODE_OBJS)

$(ALL_SOURCE_CPP_CODE_OBJS): $(BUILD_ROOT)/%_debug.o: $(BUILD_ROOT)/%.cpp
	$(CPP) -c $(INCLUDES) $(ANDROID_CFLAGS) -w $(ITAC_FLAGS) -lc -lm -lz --sysroot $(ANDROID_HOME) $< -o $@

$(ALL_SOURCE_C_CODE_OBJS): $(BUILD_ROOT)/%_debug.o: $(BUILD_ROOT)/%.c
	$(CC)  -c $(INCLUDES) $(ANDROID_CFLAGS) -w $(ITAC_FLAGS) -lc -lm -lz --sysroot $(ANDROID_HOME) $< -o $@

$(ALL_SOURCE_C_CODE_XIFS): %.xif: %.c
	$(XPP) $(INCLUDES) $(XPP_LEVELS) $< -o $@

#$(TARGET_FLEXLIB): $(ALL_SOURCE_CPP_CODE_XIFS) $(ALL_SOURCE_C_CODE_XIFS)
$(TARGET_FLEXLIB): $(ALL_SOURCE_C_CODE_XIFS)
	$(MKFLEXLIB) $(PROVISION_XLIB) $(ALL_SOURCE_C_CODE_XIFS)

	$(XPROV) $(PROVISION_XLIB) -instance $(INSTANCE) -randomseed $(RANDOMSEED) -llvm_optimization off -Xcc "$(ANDROID_CFLAGS)" -Xpp $(NDK_INCLUDE) -Xcc $(NDK_INCLUDE)

	$(XCODE_PATH)/xlink ---create_static_lib $(OUTPUT_DIR)/libiac_$(ARCH)_prov.a   ---flexlib $(PROVISION_XLIB):$(INSTANCE) ---set_native_librarian $(AR) ---set_native_linker $(CC) ---set_native_family GCC

	$(CPP) -shared -fPIC -o $(OUTPUT_DIR)/$(PROVISION_SHARED_LIB) -llog -lz -Wl,--whole-archive $(OUTPUT_DIR)/libiac_$(ARCH)_prov.a -Wl,--no-whole-archive --sysroot $(ANDROID_HOME)
