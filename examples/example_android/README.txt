- symbolic link: prebuilt
app/prebuilt: ln -s ../../../prebuilt/android/19/ ./app/prebuilt

- setup build environment for windows, ${android-demo-root-folder}\examples\example_android
 Unfortunately, symbolic link is not supported on windows, so you have to copy the whole prebuilt directory to the project
  * create prebuilt directory under app/
  * copy ${android-demo-root-folder}\prebuilt\android\19\armeabi  to app/prebuilt
     app/prebuilt/armeabi

     app/prebuilt/armeabi-v7a
  * copy  app/prebuilt/armeabi app/prebuilt/armeabi-v7a
  * open Android studio project under ${android-demo-root-folder}\examples\example_android, 
  set the path to ndk
  * I am using crystax-ndk, here is the download address for windows, 
https://www.crystax.net/en/download

NOTE: it can only be compliled for armeabi, so you have to start emulator or connect to a physical device with arm chip.
