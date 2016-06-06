LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/Achievements.cpp \
                   ../../Classes/ActionTile.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/BasicPlayerMove.cpp \
                   ../../Classes/BasicTurnManager.cpp \
                   ../../Classes/DragDropSwapPlayerMove.cpp \
                   ../../Classes/EnemyHitFloatie.cpp \
                   ../../Classes/EnemyTile.cpp \
                   ../../Classes/FireballAction.cpp \
                   ../../Classes/FireballActionTile.cpp \
                   ../../Classes/Floatie.cpp \
                   ../../Classes/GameOverUI.cpp \
                   ../../Classes/GameStateMachine.cpp \
                   ../../Classes/GlyphFactory.cpp \
                   ../../Classes/GlyphTile.cpp \
                   ../../Classes/GoldStatResult.cpp \
                   ../../Classes/GoldUI.cpp \
                   ../../Classes/GridTestUI.cpp \
                   ../../Classes/GridTransparency.cpp \
                   ../../Classes/GridUI.cpp \
                   ../../Classes/HealthPotionPlayerMove.cpp \
                   ../../Classes/HeroTile.cpp \
                   ../../Classes/HookActionTile.cpp \
                   ../../Classes/HpUI.cpp \
                   ../../Classes/InGameSettings.cpp \
                   ../../Classes/Inventory.cpp \
                   ../../Classes/Level.cpp \
                   ../../Classes/Match.cpp \
                   ../../Classes/MeleeAttackTile.cpp \
                   ../../Classes/MoveActionTile.cpp \
                   ../../Classes/NormalDistributionRandomizer.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/PlayerManager.cpp \
                   ../../Classes/PoisonGlyph.cpp \
                   ../../Classes/Progress.cpp \
                   ../../Classes/RandomAIStrategy.cpp \
                   ../../Classes/SeededLevel.cpp \
                   ../../Classes/StatGuage.cpp \
                   ../../Classes/StickMan.cpp \
                   ../../Classes/StormGlyph.cpp \
                   ../../Classes/StupidRandomizer.cpp \
                   ../../Classes/SwappyGrid.cpp \
                   ../../Classes/SwappyGridScene.cpp \
                   ../../Classes/TestScene.cpp \
                   ../../Classes/Tile.cpp \
                   ../../Classes/TileFactory.cpp \
                   ../../Classes/TileMatcher.cpp \
                   ../../Classes/TrajectoryParticle.cpp \
                   ../../Classes/XpFloatie.cpp \
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
