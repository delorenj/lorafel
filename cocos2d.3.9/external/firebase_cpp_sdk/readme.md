Firebase C++ SDK
================

The Firebase C++ SDK provides C++ interfaces for the following Firebase
services on *iOS* and *Android*:

* AdMob
* Firebase Analytics
* Firebase App Invites
* Firebase Authentication
* Firebase Cloud Messaging
* Firebase Dynamic Links
* Firebase Remote Config

## Stub Implementations

Stub (non-functional) implementations are provided for convenience when
building for Windows, OSX and Linux so the developer does not need to
conditionally compile code when also targeting the desktop.

Directory Structure
-------------------

The following table provides an overview of the Firebase C++ SDK directory
structure.

| Directories                   | Contents                                    |
|-------------------------------|---------------------------------------------|
| include                       | C++ headers                                 |
| frameworks/ios/ARCH           | iOS frameworks (compiled against libc++)    |
|                               | A multi-architecture framework is \         |
|                               | provided in the *universal* directory.      |
| libs/ios/ARCH                 | OSX static libraries (compiled against \    |
|                               | libc++)                                     |
|                               | Multi-architecture libraries are  \         |
|                               | provided in the *universal* directory.      |
| libs/android/ARCH/STL         | Android (GCC 4.8+ compatible) static \      |
|                               | libraries for each architecture and STL \   |
|                               | variant.                                    |
|                               | _STL variants available:_                   |
|                               | * `c++`: LLVM libc++ runtime (recommended)  |
|                               | * `gnustl`: GNU STL                         |
|                               | * `stlport`: STLport runtime                |
|                               | More information can be found in the \      |
|                               | [NDK C++ Helper Runtimes](https://developer.android.com/ndk/guides/cpp-support.html#runtimes) \ |
|                               | documentation.                              |
| *Stub Implementations*        |                                             |
| libs/darwin                   | OSX static libraries (stub \                |
|                               | implementation, compiled against libc++)    |
| frameworks/darwin             | OSX frameworks (stub implementations, \     |
|                               | compiled against libc++)                    |
| libs/linux                    | Linux static libraries (GCC 4.7+, libc++).  |
| libs/windows                  | Windows static libraries \                  |
|                               | (stub implementation, MSVC 2015+)           |

Library / Framework Dependencies
--------------------------------

Each feature has dependencies upon libraries in this SDK and components
distributed as part of the core Firebase
[iOS SDK](https://firebase.google.com/docs/ios/setup) and
[Android SDK](https://firebase.google.com/docs/android/setup).

### Android Dependencies

| Feature                  | Required Libraries and Gradle Packages           |
|--------------------------|--------------------------------------------------|
| Firebase AdMob           | libadmob.a<bt> \                                 |
|                          | libapp.a<br> \                                   |
|                          | com.google.android.gms:play-services-ads \       |
|                          | Maven package                                    |
| Firebase Analytics       | libanalytics.a<br> \                             |
|                          | libapp.a<br> \                                   |
|                          | com.google.android.gms:firebase-analytics \      |
|                          | Maven package                                    |
| Firebase Authentication  | libauth.a<br>  \                                 |
|                          | libapp.a<br> \                                   |
|                          | com.google.android.gms:firebase-auth \           |
|                          | Maven package                                    |
| Firebase Invites and \   | libinvites.a<br> \                               |
| Dynamic Links            | libapp.a<br> \                                   |
|                          | com.google.android.gms:firebase-invites \        |
|                          | Maven package                                    |
| Firebase Messaging       | libmessaging.a<br> \                             |
|                          | libapp.a<br> \                                   |
|                          | com.google.android.gms:firebase-messaging \      |
|                          | (Maven package)<br> \                            |
|                          | libmessaging_java.jar (Android service)          |
| Firebase Remote Config   | libremote_config.a<br> \                         |
|                          | libapp.a<br> \                                   |
|                          | com.google.android.gms:firebase-config \         |
|                          | (Maven package)                                  |

### iOS Dependencies

iOS users can include either frameworks or static libraries depending upon
their preferred build environment.

#### Frameworks

| Feature                      | Required Frameworks and Cocoapods            |
|------------------------------|----------------------------------------------|
| Firebase AdMob               | firebase_admob.framework<br> \               |
|                              | firebase.framework<br> \                     |
|                              | Firebase/Core Cocoapod<br> \                 |
|                              | Google-Mobile-Ads-SDK Cocoapod               |
| Firebase Analytics           | firebase_analytics.framework<br> \           |
|                              | firebase.framework<br> \                     |
|                              | Firebase/Core Cocoapod                       |
| Firebase Authentication      | firebase_auth.framework<br>  \               |
|                              | firebase.framework<br> \                     |
|                              | Firebase/Auth Cocoapod                       |
| Firebase Invites and \       | firebase_invites.framework<br> \             |
| Dynamic Links                | firebase.framework<br> \                     |
|                              | Firebase/Invites Cocoapod                    |
| Firebase Cloud Messaging     | firebase_messaging.framework<br> \           |
|                              | firebase.framework<br> \                     |
|                              | Firebase/Messaging Cocoapod                  |
| Firebase Remote Config       | firebase_remote_config.framework<br> \       |
|                              | firebase.framework<br> \                     |
|                              | Firebase/RemoteConfig Cocoapod               |


#### Libraries

If you prefer to link against static libraries instead of frameworks (see the
previous section) the following table describes the libraries and Cocoapods
required for each SDK feature.

| Feature                      | Required Libraries and Cocoapods             |
|------------------------------|----------------------------------------------|
| Firebase AdMob               | libadmob.a<br> \                             |
|                              | libapp.a<br> \                               |
|                              | Firebase/Core Cocoapod<br> \                 |
|                              | Google-Mobile-Ads-SDK Cocoapod               |
| Firebase Analytics           | libanalytics.a<br> \                         |
|                              | libapp.a<br> \                               |
|                              | Firebase/Core Cocoapod                       |
| Firebase Authentication      | libauth.a<br>  \                             |
|                              | libapp.a<br> \                               |
|                              | FirebaseAuth Cocoapod                        |
| Firebase Invites and \       | libinvites.a<br> \                           |
| Dynamic Links                | libapp.a<br> \                               |
|                              | Firebase/AppInvites Cocoapod                 |
| Firebase Cloud Messaging     | libmessaging.a<br> \                         |
|                              | libapp.a<br> \                               |
|                              | Firebase/CloudMessaging Cocoapod             |
| Firebase Remote Config       | libremote_config.a<br> \                     |
|                              | libapp.a<br> \                               |
|                              | Firebase/RemoteConfig Cocoapod               |


### Stub Implementation Dependencies

| Feature                      | Required Libraries and Gradle Packages       |
|------------------------------|----------------------------------------------|
| Firebase AdMob               | libadmob.a<br> \                             |
|                              | libapp.a<br>                                 |
| Firebase Analytics           | libanalytics.a<br> \                         |
|                              | libapp.a<br>                                 |
| Firebase Authentication      | libauth.a<br>  \                             |
|                              | libapp.a<br>                                 |
| Firebase Invites and \       | libinvites.a<br> \                           |
| Dynamic Links                | libapp.a<br>                                 |
| Firebase Cloud Messaging     | libmessaging.a<br> \                         |
|                              | libapp.a<br>                                 |
| Firebase Remote Config       | libremote_config.a<br> \                     |
|                              | libapp.a<br>                                 |

Getting Started
---------------

See our [setup guide](https://firebase.google.com/docs/cpp/setup) to get
started.

### Custom Android Build Systems

We currently provide generate\_xml\_from\_google\_services\_json.py to convert
google-services.json to .xml resources to be included in an application.  This
script applies the same transformation that the Google Play Services Gradle
plug-in performs when building Android applications.  Users who don't use
Gradle (e.g ndk-build, makefiles, Visual Studio etc.) can use this script
to automate the generation of string resources.

### ProGuard on Android ###

Many Android build systems use
[ProGuard](https://developer.android.com/studio/build/shrink-code.html) for
builds in Release mode to shrink application sizes and protect Java source code.
If you use ProGuard, you will need to add the files in libs/android/*.pro
corresponding to the Firebase C++ libraries you are using to your ProGuard
configuration.

For example, with Gradle, build.gradle would contain:
~~~
  android {
    [...other stuff...]
    buildTypes {
      release {
        minifyEnabled true
        proguardFile getDefaultProguardFile('your-project-proguard-config.txt')
        proguardFile file(project.ext.firebase_cpp_sdk_dir + "/libs/android/app.pro")
        proguardFile file(project.ext.firebase_cpp_sdk_dir + "/libs/android/analytics.pro")
        [...and so on, for each Firebase C++ library you are using.]
      }
    }
  }
~~~

### Requiring Google Play services on Android

Many Firebase C++ libraries require
[Google Play services](https://developers.google.com/android/guides/overview) on
the user's Android device. If a Firebase C++ library returns
[`kInitResultFailedMissingDependency`](http://firebase.google.com/docs/reference/cpp/namespace/firebase)
on initialization, it means Google Play services is not available on the device
(it needs to be updated, reactivated, permissions fixed, etc.) and that Firebase
library cannot be used until the situation is corrected.

You can find out why Google Play services is unavailable (and try to fix it) by
using the functions in [`google_play_services/availability.h`](http://firebase.google.com/docs/reference/cpp/namespace/google-play-services).

Note: Some libraries do not require Google Play services and don't return any
initialization status. These can be used without Google Play services. The table
below summarizes whether Google Play services is required by each Firebase C++
library.

| Firebase C++ Library    | Google Play services required?    |
| ----------------------- |:---------------------------------:|
| Analytics               | Not required                      |
| AdMob                   | Not required (usually; see below) |
| Cloud Messaging         | Required                          |
| Auth                    | Required                          |
| Invites / Dynamic Links | Required                          |
| Remote Config           | Required                          |

#### A note on AdMob and Google Play services

Most versions of the Google Mobile Ads SDK for Android can work properly without
Google Play services. However, if you are using the
`com.google.android.gms:play-services-ads-lite` dependency instead of the
standard `com.google.firebase:firebase-ads` dependency, Google Play services
WILL be required in your specific case.

AdMob initialization will only return `kInitResultFailedMissingDependency` when
Google Play services is unavailable AND you are using
`com.google.android.gms:play-services-ads-lite`.


Release Notes
-------------

### 1.1.0
  - Overview
    - Minor bug fixes and new way of checking Google Play services availability.
  - Changes
    - Reverted the firebase::App changes from version 1.0.1 relating to Google
      Play services; this has been replaced with a new API.
    - Each Firebase C++ library that requires Google Play services now checks
      for its availability at initialization time. See "Requiring Google Play
      services on Android".
      - firebase::auth::GetAuth() now has an optional output parameter that
        indicates whether initialization was successful, and will return
        nullptr if not.
      - firebase::messaging::Initialize() now returns a result that indicates
        whether initialization was successful.
      - Added firebase::invites::Initialize(), which you must call once prior to
        creating InvitesSender or InvitesReceiver instances. This function
        returns a result that indicates whether initialization was successful.
      - firebase::remote_config::Initialize() now returns a result that
        indicates whether initialization was successful.
      - firebase::admob::Initialize() now returns a result that indicates
        whether initialization was successful.
    - Added utility functions to check whether Google Play services is
      available. See google_play_services::CheckAvailability() and
      google_play_services::MakeAvailable() for more information.

### 1.0.1
  - Overview
    - Minor bug fixes.
  - Changes
    - Modified firebase::App to check for the required version of Google Play
      services on creation to prevent firebase::App creation failing if a
      user's device is out of date.  If Google Play services is out of date,
      a dialog will prompt the user to install a new version.  See
      "Requiring Google Play services on Android".  With the previous version
      (version 1.0.0) the developer needed to manually check for an up to date
      Google Play services using GoogleApiClient.
    - Fixed potential deadlock when using SetListener from a notification
      callback in firebase::admob::InterstitialAd and
      firebase::admob::BannerView on iOS.
    - Fixed race condition on destruction of admob::BannerView on Android.
    - Fixed Future handle leak.  An internal memory leak would manifest for
      objects or modules that use futures for the lifetime of the object or
      module.  For example, during the lifetime of BannerView each call to a
      method which returns a Future could potentially allocate memory which
      wouldn't be reclaimed until the BannerView is destroyed.

### 1.0.0
  - Overview
     - First public release.
       See our [setup guide](https://firebase.google.com/docs/cpp/setup) to get
       started.
  - Known Issues
     - Android armeabi libraries must be linked with gcc 4.8.
