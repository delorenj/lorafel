#import <UIKit/UIKit.h>
#import <SignIn.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, GIDSignInDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

