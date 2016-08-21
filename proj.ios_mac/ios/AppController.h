#import <UIKit/UIKit.h>
#import <SignIn.h>
#import "Firebase.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, GIDSignInDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;
@property (strong, nonatomic) FIRDatabaseReference *db;

@end

