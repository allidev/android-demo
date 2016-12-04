symbolic links fix
go to vault-deps root directory

a. fix the symbolic link: prebuilt
cd examples
cd example_android
cd app
rm prebuilt
ln -s ../../../prebuilt/android/19/ prebuilt

b. fix the symbolic link: armeabi-v7a
from the step above
cd prebuilt
rm armeabi-v7a
ln -s armeabi/ armeabi-v7a

c. fix the missing ndk platform issue on crystax
go to crystax root folder
cd platforms
ln -s android-19/ android-23
