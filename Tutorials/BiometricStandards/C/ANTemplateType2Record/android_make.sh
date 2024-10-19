#!/bin/sh

if [ "${ANDROID_NDK_HOME}" = "" ]; then
	echo ERROR: please set ANDROID_NDK_HOME variable to Android ndk home directory
	exit
fi

${ANDROID_NDK_HOME}/ndk-build \
	APP_STL=gnustl_static \
	NDK_PROJECT_PATH=./ \
	APP_PLATFORM=android-9 \
	APP_STL=gnustl_static \
	APP_BUILD_SCRIPT=Android.mk \
	APP_ABI="armeabi armeabi-v7a"

mkdir -p ../../../../Bin/Android/armeabi/
mkdir -p ../../../../Bin/Android/armeabi-v7a/

cp ./libs/armeabi/ANTemplateType2Record ../../../../Bin/Android/armeabi/.

cp ./libs/armeabi-v7a/ANTemplateType2Record ../../../../Bin/Android/armeabi-v7a/.

rm -fr ./libs/
