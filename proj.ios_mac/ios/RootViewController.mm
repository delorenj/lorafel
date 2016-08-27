/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#import "RootViewController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import <GoogleSignIn/GoogleSignIn.h>
#import "IOSNDKHelper.h"
#import "FIRDatabaseReference.h"
#import "FIRUser.h"

@implementation RootViewController


 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
        /* Let the helper know that this class wants to receive data from your game */
        [IOSNDKHelper setNDKReceiver:self];

    }
    return self;
}


/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];

    // TODO(developer) Configure the sign-in button look/feel

    [GIDSignIn sharedInstance].uiDelegate = self;

    // Uncomment to automatically sign in the user.
    [[GIDSignIn sharedInstance] signInSilently];
}

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsPortrait( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskPortrait;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    auto glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

- (void)signIn:(NSObject *)parametersObject {
    [[GIDSignIn sharedInstance] signIn];
}

- (void)enableOfflineDatabase:(NSObject *)parametersObject {
    [FIRDatabase database].persistenceEnabled = YES;
}

- (void)setStringForKey:(NSObject *)parametersObject {
    NSDictionary *parameters = (NSDictionary *)parametersObject;
    _db = [[FIRDatabase database] reference];
    FIRUser *user = [[FIRAuth auth] currentUser];

    if (parameters != nil) {
        NSString* key = (NSString*) parameters[@"key"];
        NSString* value = (NSString*) parameters[@"value"];
        NSString* child = (NSString*) parameters[@"child"];

        [[[[[_db child:@"users"] child:user.uid] child:child] child:key] setValue:value];
    }
}

- (void)addItem:(NSObject *)parametersObject {
    NSDictionary *parameters = (NSDictionary *)parametersObject;
    _db = [[FIRDatabase database] reference];
    FIRUser *user = [[FIRAuth auth] currentUser];
    
    if (parameters != nil) {
        NSString* tempId = (NSString*) parameters[@"tempId"];
        NSString* className = (NSString*) parameters[@"class"];
        NSArray* arguments = (NSArray*) parameters[@"args"];
        NSString* quantity = (NSString*) parameters[@"quantity"];
        
        NSString *newId = [[[_db child:@"users"] child:@"items"] childByAutoId].key;

        if(arguments == nil) {
            NSDictionary *item = @{@"class": className,
                                   @"quantity": quantity};
            [[[[[_db child:@"users"] child:user.uid] child:@"items"] child:newId] setValue:item];
        } else {
            NSDictionary *item = @{@"class": className,
                                   @"arguments": arguments,
                                   @"quantity": quantity};
            [[[[[_db child:@"users"] child:user.uid] child:@"items"] child:newId] setValue:item];
        }

        NSDictionary *parameters = @{@"oldId" : tempId, @"newId" : newId};
        [IOSNDKHelper sendMessage:@"onCompleteAddItem" withParameters:parameters];
    }
}

- (void)getStringForKey:(NSObject *)parametersObject {
    NSDictionary *parameters = (NSDictionary *)parametersObject;
    _db = [[FIRDatabase database] reference];
    FIRUser *user = [[FIRAuth auth] currentUser];

    if (parameters != nil) {
        NSString* key = (NSString*) parameters[@"key"];
        NSString* child = (NSString*) parameters[@"child"];

        [[[[[_db child:@"users"]
                child:user.uid]
                child:child]
                child:key]
                observeSingleEventOfType:FIRDataEventTypeValue
                               withBlock:^(FIRDataSnapshot* _Nonnull snapshot) {
                                   if (snapshot.exists) {
                                       NSDictionary* keyval = snapshot.value;
                                       [IOSNDKHelper sendMessage:@"onCompleteGetStringForKeyQuery" withParameters:keyval];
                                   }

                               } withCancelBlock:^(NSError* _Nonnull error) {
                    NSLog(@"%@", error.localizedDescription);
                }];
    }

}

- (void)deleteKey:(NSObject *)parametersObject {
    NSDictionary *parameters = (NSDictionary *)parametersObject;
    _db = [[FIRDatabase database] reference];
    FIRUser *user = [[FIRAuth auth] currentUser];

    if (parameters != nil) {
        NSString* key = (NSString*) parameters[@"key"];
        NSString* child = (NSString*) parameters[@"child"];

        [[[[[_db child:@"users"] child:user.uid] child:child] child:key] setValue:nil];
    }
}

- (void)loadInventoryItemGrid:(NSObject *)parametersObject {
    _db = [[FIRDatabase database] reference];
    FIRUser *user = [[FIRAuth auth] currentUser];

    [[[[_db child:@"users"]
            child:user.uid]
            child:@"inventory_item_grid"]
            observeSingleEventOfType:FIRDataEventTypeValue
                           withBlock:^(FIRDataSnapshot* _Nonnull snapshot) {
                               if (snapshot.exists) {
                                   NSDictionary* keyval = snapshot.value;
                                   [IOSNDKHelper sendMessage:@"onCompleteLoadInventoryItemGrid" withParameters:keyval];
                               } else {
                                   [IOSNDKHelper sendMessage:@"onCompleteLoadInventoryItemGrid" withParameters:nullptr];
                               }

                           } withCancelBlock:^(NSError* _Nonnull error) {
                NSLog(@"%@", error.localizedDescription);
            }];

}

- (void)loadInventoryEquipGrid:(NSObject *)parametersObject {
    _db = [[FIRDatabase database] reference];
    FIRUser *user = [[FIRAuth auth] currentUser];

    [[[[_db child:@"users"]
            child:user.uid]
            child:@"inventory_equip_grid"]
            observeSingleEventOfType:FIRDataEventTypeValue
                           withBlock:^(FIRDataSnapshot* _Nonnull snapshot) {
                               if (snapshot.exists) {
                                   NSDictionary* keyval = snapshot.value;
                                   [IOSNDKHelper sendMessage:@"onCompleteLoadInventoryEquipGrid" withParameters:keyval];
                               }

                           } withCancelBlock:^(NSError* _Nonnull error) {
                NSLog(@"%@", error.localizedDescription);
            }];

}
@end
