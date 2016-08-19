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
                   ../../Classes/Arrow.cpp \
                   ../../Classes/AuthStateMachine.cpp \
                   ../../Classes/BasicPlayerMove.cpp \
                   ../../Classes/BasicTurnManager.cpp \
                   ../../Classes/Consumable.cpp \
                   ../../Classes/DragDropSwapPlayerMove.cpp \
                   ../../Classes/EnemyHitFloatie.cpp \
                   ../../Classes/EnemyTile.cpp \
                   ../../Classes/EquipItemSlot.cpp \
                   ../../Classes/FireballAction.cpp \
                   ../../Classes/FireballActionTile.cpp \
                   ../../Classes/FirebaseAuth.cpp \
                   ../../Classes/Floatie.cpp \
                   ../../Classes/GameOverUI.cpp \
                   ../../Classes/GameStateMachine.cpp \
                   ../../Classes/GlyphTile.cpp \
                   ../../Classes/GoldStatResult.cpp \
                   ../../Classes/GoldUI.cpp \
                   ../../Classes/GridTestUI.cpp \
                   ../../Classes/GridTransparency.cpp \
                   ../../Classes/GridUI.cpp \
                   ../../Classes/HealthPotion.cpp \
                   ../../Classes/HealthPotionPlayerMove.cpp \
                   ../../Classes/HeroTile.cpp \
                   ../../Classes/Hook.cpp \
                   ../../Classes/HookAction.cpp \
                   ../../Classes/HookActionTile.cpp \
                   ../../Classes/HpUI.cpp \
                   ../../Classes/InGameModal.cpp \
                   ../../Classes/InGameModalNavButton.cpp \
                   ../../Classes/InGameSettings.cpp \
                   ../../Classes/Inventory.cpp \
                   ../../Classes/InventoryEquipGrid.cpp \
                   ../../Classes/InventoryItemGrid.cpp \
                   ../../Classes/InventoryItemSlot.cpp \
                   ../../Classes/InventoryModal.cpp \
                   ../../Classes/Item.cpp \
                   ../../Classes/ItemSlot.cpp \
                   ../../Classes/Level.cpp \
                   ../../Classes/LootFactory.cpp \
                   ../../Classes/LootTile.cpp \
                   ../../Classes/Match.cpp \
                   ../../Classes/Match5.cpp \
                   ../../Classes/MatchSet.cpp \
                   ../../Classes/MeleeAttackTile.cpp \
                   ../../Classes/MoveActionTile.cpp \
                   ../../Classes/NonConsumable.cpp \
                   ../../Classes/NormalDistributionRandomizer.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/PlayerManager.cpp \
                   ../../Classes/PoisonGlyph.cpp \
                   ../../Classes/Progress.cpp \
                   ../../Classes/RandomAIStrategy.cpp \
                   ../../Classes/Rope.cpp \
                   ../../Classes/SeededLevel.cpp \
                   ../../Classes/StatGuage.cpp \
                   ../../Classes/StickMan.cpp \
                   ../../Classes/StormGlyph.cpp \
                   ../../Classes/StupidRandomizer.cpp \
                   ../../Classes/SwappyGrid.cpp \
                   ../../Classes/SwappyGridScene.cpp \
                   ../../Classes/TestScene.cpp \
                   ../../Classes/Tile.cpp \
                   ../../Classes/TileMatcher.cpp \
                   ../../Classes/TitleScene.cpp \
                   ../../Classes/ToggleActionTile.cpp \
                   ../../Classes/TrajectoryParticle.cpp \
                   ../../Classes/Weapon.cpp \
                   ../../Classes/XpFloatie.cpp \
                   ../../Classes/XPStatResult.cpp \
                   ../../Classes/XpUI.cpp \
                   ../../Classes/NDKHelper/CallFuncNV.cpp \
                   ../../Classes/NDKHelper/NDKCallbackNode.cpp \
                   ../../Classes/NDKHelper/NDKHelper.cpp \
                   ../../Classes/jansson/dump.c \
                   ../../Classes/jansson/error.c \
                   ../../Classes/jansson/hashtable.c \
                   ../../Classes/jansson/load.c \
                   ../../Classes/jansson/memory.c \
                   ../../Classes/jansson/pack_unpack.c \
                   ../../Classes/jansson/strbuffer.c \
                   ../../Classes/jansson/strconv.c \
                   ../../Classes/jansson/utf.c \
                   ../../Classes/jansson/value.c


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/NDKHelper \
                    $(LOCAL_PATH)/../../Classes/jansson

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static firebase-prebuilt firebase-analytics firebase-auth

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END