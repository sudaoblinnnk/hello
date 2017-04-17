LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libmegjb

LOCAL_SRC_FILES := antiDebug.cpp  \
	classWalker.cpp \
	dexOperator9.cpp \
	networkManager.cpp \
	dexAdaptor.cpp \
	dexOperator.cpp \
	irdetoJavaSecurityExtension.cpp \
	classWalker8.cpp  \
	dexOperator10_above.cpp \
	dexOptimize.cpp \
	JACCommonModule.cpp \
	threadManager.cpp \
	classWalker9.cpp \
	dexOperator8.cpp \
	jniInterface.cpp \
	irdetoJavaSecurity.cpp

LOCAL_C_INCLUDES += include asm_include ../../../IrdetoToolChain/include/ \
	$(BK_DIST)/include/ \
	$(XCODE_HOME)/include/ 


LOCAL_STATIC_LIBRARIES:= log miniunzip
LOCAL_STATIC_LIBRARIES += z
LOCAL_CFLAGS := -fdata-sections \
             	-ffunction-sections \
			   	-fvisibility=hidden \
				-Wno-write-strings \
				-Wno-format-contains-nul \
				-Wno-format-extra-args \
				-D _JAC_STANDALONE

LOCAL_CFLAGS += -D _JAC_DEBUG_ANDROID
LOCAL_CFLAGS += -D _CC_ENHANCE_
LOCAL_CFLAGS += -D _ARM_VERSION_LIBRARY
#LOCAL_CFLAGS += -D _ASM_BUILD

LOCAL_LDLIBS := -llog

LOCAL_CXXFLAGS:=$(LOCAL_CFLAGS)

LOCAL_PRELINK_MODULE:=false
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
