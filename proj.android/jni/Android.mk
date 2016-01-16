LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/AvocadoFactory.cpp \
                   ../../Classes/AvocadoTile.cpp \
                   ../../Classes/BasicPlayerMove.cpp \
                   ../../Classes/BearFactory.cpp \
                   ../../Classes/BearTile.cpp \
                   ../../Classes/CarrotFactory.cpp \
                   ../../Classes/CarrotTile.cpp \
                   ../../Classes/GameStateMachine.cpp \
                   ../../Classes/GrapeFactory.cpp \
                   ../../Classes/GrapeTile.cpp \
                   ../../Classes/GridTestUI.cpp \
                   ../../Classes/Level.cpp \
                   ../../Classes/Level__TestLevelOne.cpp \
                   ../../Classes/Level__TestLevelTwo.cpp \
                   ../../Classes/Level__TestRandom.cpp \
                   ../../Classes/Match.cpp \
                   ../../Classes/NormalDistributionRandomizer.cpp \
                   ../../Classes/SwappyGrid.cpp \
                   ../../Classes/TestScene.cpp \
                   ../../Classes/Tile.cpp \
                   ../../Classes/TileFactory.cpp \
                   ../../Classes/TileMatcher.cpp \
                   ../../Classes/XPMatchResult.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
