LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Main

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
        $(wildcard $(LOCAL_PATH)/include/*) \
        $(wildcard $(LOCAL_PATH)/../sinen/include) \
        $(wildcard $(LOCAL_PATH)/../sinen/include/Nen) \

LOCAL_CFLAGS := -DSDL_MAIN_HANDLED

# Add your application source files here...
LOCAL_SRC_FILES := \
			$(wildcard $(LOCAL_PATH)/src/*.cpp) \
			$(wildcard $(LOCAL_PATH)/src/*/*.cpp)
LOCAL_STATIC_LIBRARIES :=
LOCAL_SHARED_LIBRARIES := Sinen

include $(BUILD_SHARED_LIBRARIES)
