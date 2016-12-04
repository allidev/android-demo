- symbolic link: prebuilt
app/prebuilt: ln -s ../../prebuilt/android/19/ ./app/prebuilt

- link in jni directory

prebuilt -> ../../../../../prebuilt/android/19/

- setup build environment for windows, vault-deps\example_android
 Unfortunately, symbolic link is not supported on windows, so you have to copy the whole prebuilt directory to the project
  * create prebuilt directory under app/
  * copy vault-deps\prebuilt\android\19\armeabi  to app/prebuilt
     app/prebuilt/armeabi
                      /armeabi-v7a
  * copy  app/prebuilt/armeabi app/prebuilt/armeabi-v7a
  * open Android studio project under vault-deps\example_android, set the path to ndk
  * I am using ndk r10e, here is the download address for windows, 
https://dl.google.com/android/ndk/android-ndk-r10e-windows-x86_64.exe

NOTE: it can only be complile for armeabi, so you have to start emulator or connect to a physical device with arm chip.
