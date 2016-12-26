LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := sqlite3
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/lib/libsqlite3.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := crypto
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/lib/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ssl
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/lib/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ssh2
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/lib/libssh2.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := git2
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/lib/libgit2.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := allivaultcore
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/lib/libALLIVaultCoreP.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boostsystem
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/lib/libboost_system-gcc-mt-1_58.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := boostfilesystem
LOCAL_SRC_FILES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/lib/libboost_filesystem-gcc-mt-1_58.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CFLAGS := -DGIT_SSL
LOCAL_MODULE := apis
LOCAL_SRC_FILES := com_allivault_cloudsafe_playground_Apis.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)/prebuilt/$(TARGET_ARCH_ABI)/include
LOCAL_STATIC_LIBRARIES := allivaultcore boostfilesystem boostsystem git2 ssh2 ssl crypto
LOCAL_LDLIBS := -lz -llog
include $(BUILD_SHARED_LIBRARY)



