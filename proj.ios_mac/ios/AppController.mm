/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "FIRAuth.h"
#import "FIRUser.h"
#import "Firebase.h"
#import "FIRGoogleAuthProvider.h"
#import "IOSNDKHelper.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];
    [eaglView layoutSubviews];

    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    // Use Firebase library to configure APIs
//    [FIRApp configure];
//
    [GIDSignIn sharedInstance].clientID = @"517389322164-qfbodp7f8o571q9kppl1d4nqtmanuifp.apps.googleusercontent.com";
    [GIDSignIn sharedInstance].delegate = self;
  
    app->run();

    _db = [[FIRDatabase database] reference];

    [[_db child:@"item_tree"] observeSingleEventOfType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
        if(snapshot.exists) {
            NSDictionary *itemTree = snapshot.value;
            [IOSNDKHelper sendMessage:@"onCompleteItemTreeQuery" withParameters:itemTree];
        }

    } withCancelBlock:^(NSError * _Nonnull error) {
        NSLog(@"%@", error.localizedDescription);
    }];

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)app
            openURL:(NSURL *)url
            options:(NSDictionary<NSString *, id> *)options {
    return [[GIDSignIn sharedInstance] handleURL:url
                               sourceApplication:options[UIApplicationOpenURLOptionsSourceApplicationKey]
                                      annotation:options[UIApplicationOpenURLOptionsAnnotationKey]];
}

- (BOOL)application:(UIApplication *)application
        openURL:(NSURL *)url
        sourceApplication:(NSString *)sourceApplication
        annotation:(id)annotation {
    return [[GIDSignIn sharedInstance] handleURL:url
                               sourceApplication:sourceApplication
                                      annotation:annotation];
}

- (void)signIn:(GIDSignIn *)signIn
        didSignInForUser:(GIDGoogleUser *)user
        withError:(NSError *)error {

    NSDictionary *parameters;

    if (error == nil) {
        NSLog(@"Signed In =D");
        GIDAuthentication *authentication = user.authentication;
        FIRAuthCredential *credential =
                [FIRGoogleAuthProvider credentialWithIDToken:authentication.idToken
                                                 accessToken:authentication.accessToken];

        [[FIRAuth auth] signInWithCredential:credential
                                  completion:^(FIRUser *u, NSError *e) {
                                      NSDictionary *p = @{@"state" : @"LoggedInState"};
                                      [IOSNDKHelper sendMessage:@"changeStateSelector" withParameters:p];
                                      NSString *userID = u.uid;
                                      _db = [[FIRDatabase database] reference];

                                      [[[_db child:@"users"] child:userID] observeSingleEventOfType:FIRDataEventTypeValue withBlock:^(FIRDataSnapshot * _Nonnull snapshot) {
                                          if(snapshot.exists) {
                                              NSDictionary *user = snapshot.value;
                                              [IOSNDKHelper sendMessage:@"onCompleteUserQuery" withParameters:user];
                                          }

                                      } withCancelBlock:^(NSError * _Nonnull error) {
                                          NSLog(@"%@", error.localizedDescription);
                                      }];

                                      [[[[_db child:@"users"]
											  child:userID]
											  child:@"items"]
											  observeSingleEventOfType:FIRDataEventTypeChildAdded
                                       withBlock:^(FIRDataSnapshot* _Nonnull snapshot) {
                                           if (snapshot.exists) {
                                               NSDictionary* keyval = snapshot.value;
                                               [keyval setValue:snapshot.key forKey:@"id"];
                                               [IOSNDKHelper sendMessage:@"onCompleteAddItem" withParameters:keyval];
                                           }
                                           
                                       } withCancelBlock:^(NSError* _Nonnull error) {
                                           NSLog(@"%@", error.localizedDescription);
                                       }];
                                      
                                  }];
        parameters = @{@"state" : @"AuthenticatingState"};


    } else {
        NSLog(@"%@", error.localizedDescription);
        parameters = @{@"state" : @"AuthenticationFailedState"};
    }

    // Send C++ a message with parameters
    // C++ will receive this message only if the selector list has a method
    // of the same name as specified - in this case, "gameTestMethod"
    [IOSNDKHelper sendMessage:@"changeStateSelector" withParameters:parameters];

}

- (void)signIn:(GIDSignIn *)signIn
        didDisconnectWithUser:(GIDGoogleUser *)user
        withError:(NSError *)error {
    NSLog(@"Signed Out");
    NSDictionary*parameters = @{@"state" : @"AuthenticationFailedState"};
    [IOSNDKHelper sendMessage:@"changeStateSelector" withParameters:parameters];
}

@end
