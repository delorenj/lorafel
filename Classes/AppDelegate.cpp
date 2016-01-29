#include "AppDelegate.h"
#include "TestScene.h"
#include "PlayerManager.h"

USING_NS_CC;

static cocos2d::Size ultra4kResolutionSize = cocos2d::Size(2160,4096);
static cocos2d::Size ipadHDResolutionSize = cocos2d::Size(1536,2048);
static cocos2d::Size ipadResolutionSize = cocos2d::Size(768,1024);
static cocos2d::Size iphoneHD5ResolutionSize = cocos2d::Size(640,1136);
static cocos2d::Size iphoneHDResolutionSize = cocos2d::Size(640,960);
static cocos2d::Size iphoneResolutionSize = cocos2d::Size(320,480);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::create("Lorafel");
#else
        glview = GLViewImpl::create("Lorafel");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    auto screenSize = glview->getFrameSize();
    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> resDirOrders;
    CCLOG("%f, %f", screenSize.width, screenSize.height);

    if(screenSize.width == ultra4kResolutionSize.height || screenSize.height == ultra4kResolutionSize.height
       ) {
        CCLOG("ultra4kResolutionSize");

        resDirOrders.push_back("ultra4k");
        resDirOrders.push_back("ipadhd");
        resDirOrders.push_back("ipad");
        resDirOrders.push_back("iphonehd5");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");
        glview->setDesignResolutionSize(ultra4kResolutionSize.width, ultra4kResolutionSize.height, ResolutionPolicy::NO_BORDER);
    } else

    if(screenSize.width == ipadHDResolutionSize.height ||
       screenSize.height == ipadHDResolutionSize.height
//       ||
//       (screenSize.width < ipadHDResolutionSize.height && screenSize.width > ipadResolutionSize.height) ||
//       (screenSize.height < ipadHDResolutionSize.height && screenSize.height > ipadResolutionSize.height)
       ) {
        CCLOG("ipadHDResolutionSize");
        resDirOrders.push_back("ipadhd");
        resDirOrders.push_back("ipad");
        resDirOrders.push_back("iphonehd5");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");
        glview->setContentScaleFactor(screenSize.width/ipadHDResolutionSize.width);
        glview->setDesignResolutionSize(1366,2048, ResolutionPolicy::NO_BORDER);
    } else

    if(screenSize.width == ipadResolutionSize.height || screenSize.height == ipadResolutionSize.height
       ) {// iPad
        CCLOG("ipadResolutionSize");
        resDirOrders.push_back("ipad");
        resDirOrders.push_back("iphonehd5");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");
        glview->setContentScaleFactor(screenSize.width/ipadResolutionSize.width);
        glview->setDesignResolutionSize(911,1365, ResolutionPolicy::NO_BORDER);
    } else

    if(screenSize.width == iphoneHD5ResolutionSize.height || screenSize.height == iphoneHD5ResolutionSize.height
       ) {
        CCLOG("iphoneHD5ResolutionSize");
        resDirOrders.push_back("iphonehd5");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");
        glview->setContentScaleFactor(screenSize.width/iphoneHD5ResolutionSize.width);
        glview->setDesignResolutionSize(iphoneHD5ResolutionSize.width,iphoneHD5ResolutionSize.height, ResolutionPolicy::NO_BORDER);
    } else

    if(screenSize.width == iphoneHDResolutionSize.height || screenSize.height == iphoneHDResolutionSize.height
       ) {
        CCLOG("iphoneHDResolutionSize");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");
        glview->setContentScaleFactor(screenSize.width/iphoneHDResolutionSize.width);
        glview->setDesignResolutionSize(iphoneHDResolutionSize.width, iphoneHDResolutionSize.height, ResolutionPolicy::NO_BORDER);
    } else

    if(screenSize.width == iphoneResolutionSize.height || screenSize.height == iphoneResolutionSize.height
       ) {
        CCLOG("iphoneResolutionSize");
        resDirOrders.push_back("iphone");
        glview->setContentScaleFactor(screenSize.width/iphoneResolutionSize.width);
        glview->setDesignResolutionSize(iphoneResolutionSize.width, iphoneResolutionSize.height, ResolutionPolicy::NO_BORDER);
    } else {
        // If we got here, that means we've found a resolution that is not
        // explicitly defined. We need to now find the most perfectest ratio.
        CCLOG("Jojo. Not a pre-defined resolution. Calculating the best-fit.");
//        if(screenSize.width)
        resDirOrders.push_back("iphonehd");
        glview->setContentScaleFactor(screenSize.width/iphoneHDResolutionSize.width);
        glview->setDesignResolutionSize(iphoneHDResolutionSize.width, iphoneHDResolutionSize.height, ResolutionPolicy::NO_BORDER);

    }

    fileUtils->setSearchPaths(resDirOrders);

    register_all_packages();

    // load the Sprite Sheet
    auto spritecache = SpriteFrameCache::getInstance();
    
    // the .plist file can be generated with any of the tools mentioned below
    spritecache->addSpriteFramesWithFile("sprites.plist");

    auto userEmail = UserDefault::getInstance()->getStringForKey("email");

    // load the player data
    // TODO: Make secure using server-side code and encryption
    auto player = lorafel::PlayerManager::getInstance()->loadPlayer(userEmail);

    // No player found!
    // make a new one!
    // Or...wrong email?
    CCASSERT(player, "Player not found!");

    // create a scene. it's an autorelease object
    auto scene = TestScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
