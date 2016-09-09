APP_STL := gnustl_static
NDK_DEBUG := 1
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic

ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif

#APP_PLATFORM:=android-14
#NDK_TOOLCHAIN_VERSION=clang
APP_ABI:=x86 armeabi
#APP_STL:=c++_static
APP_MODULES:=cocos2dcpp_shared
