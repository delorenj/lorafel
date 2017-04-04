#import <UIKit/UIKit.h>
#import "Firebase.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    
}

@property(nonatomic, readonly) RootViewController* viewController;
@property (strong, nonatomic) FIRDatabaseReference *db;

@end

