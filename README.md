Simple Flappy Bird Sample for Cocos2d-x v3.0
========================

Get Cocos2d-x
-------------

Download from http://www.cocos2d-x.org/download, or clone the repo:

```shell
$ git clone https://github.com/cocos2d-x/plugin-x.git
```

Create a new project
-------------

```shell
$ ./tools/cocos2d-console/bin/cocos new -p PACKAGE_NAME -d DIRECTORY -l cpp PROJECT_NAME
```

iOS build
-------------

+ Open DIRECTORY/PROJECT_NAME/proj.ios_mac/PROJECT_NAME.xcodeproj/
+ Copy Classes and Resources folders to DIRECTORY/PROJECT_NAME
+ Import all new files in Classes and Resources folder
+ Change Device Orientation to Portrait
+ Build & Run


Android build
-------------

```shell
$ cd DIRECTORY/PROJECT_NAME/proj.android
$ export NDK_ROOT=*path_to_ndk*
$ android list target
$ android update project -p . -t *device_type_id*
$ android update project -p ../../cocos2d-x/cocos/2d/platform/android/java/ -t *device_type_id*
$ ./build_native.sh
$ ant debug install
```

