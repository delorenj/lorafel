LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/Achievements.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/AvocadoFactory.cpp \
                   ../../Classes/AvocadoTile.cpp \
                   ../../Classes/BasicPlayerMove.cpp \
                   ../../Classes/BearFactory.cpp \
                   ../../Classes/BearTile.cpp \
                   ../../Classes/CarrotFactory.cpp \
                   ../../Classes/CarrotTile.cpp \
                   ../../Classes/Floaties.cpp \
                   ../../Classes/GameStateMachine.cpp \
                   ../../Classes/GrapeFactory.cpp \
                   ../../Classes/GrapeTile.cpp \
                   ../../Classes/GridTestUI.cpp \
                   ../../Classes/GridUI.cpp \
                   ../../Classes/Inventory.cpp \
                   ../../Classes/Level.cpp \
                   ../../Classes/Match.cpp \
                   ../../Classes/NormalDistributionRandomizer.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/PlayerManager.cpp \
                   ../../Classes/Progress.cpp \
                   ../../Classes/SwappyGrid.cpp \
                   ../../Classes/TestScene.cpp \
                   ../../Classes/Tile.cpp \
                   ../../Classes/TileFactory.cpp \
                   ../../Classes/TileMatcher.cpp \
                   ../../Classes/XPStatResult.cpp \
                   ../../Classes/XpUI.cpp


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
