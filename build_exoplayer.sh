#remove previous auto generated files
export NATIVE_CODE_DIR=/home/kurt/company/workspace.eclipse/J2NConverter
#export NATIVE_CODE_DIR=/home/kurt/innovation/hello/tools/poisoner/samples

if [ "$1" == "app" ]; then
    echo "build exoplayer"

#compile apk need to protect
pushd .
cd exoplayer_clean
./gradlew assembleNoExtensionsDebug
cp demo/buildout/outputs/apk/demo-noExtensions-debug.apk ../repackage/app-release.apk
popd

#extract protected apk classes.dex
mkdir temp
cp repackage/app-release.apk temp
pushd .
cd temp
unzip app-release.apk -d apkdir
cp apkdir/classes.dex ../tools/poisoner/samples/classes.dex
popd
rm -rf temp

else

#remove NATIVE_CODE_DIR auto generated files
#pushd .
#cd $NATIVE_CODE_DIR
#rm -rf native
#rm -rf java
#unzip native.jar -d native
#unzip java.jar -d   java
#popd


pushd .
cd repackage
rm -rf app-repackage.apk
rm -rf app-release
rm -rf target
rm -rf source

apktool d app-release.apk              
mv app-release target
popd

#remove auto generated files
pushd .
cd exoplayer
cp $NATIVE_CODE_DIR/java/com/google/android/exoplayer2/demo/PlayerActivity.java demo/src/main/java/com/google/android/exoplayer2/demo/PlayerActivity.java
cp $NATIVE_CODE_DIR/native/com/google/android/exoplayer2/demo/PlayerActivity.c  demo/src/main/cpp/PlayerActivity.c

cp $NATIVE_CODE_DIR/java/com/google/android/exoplayer2/demo/Wine.java demo/src/main/java/com/google/android/exoplayer2/demo/Wine.java
cp $NATIVE_CODE_DIR/native/com/google/android/exoplayer2/demo/Wine.c  demo/src/main/cpp/Wine.c

cp $NATIVE_CODE_DIR/java/com/google/android/exoplayer2/demo/JNC.java demo/src/main/java/com/google/android/exoplayer2/demo/JNC.java
cp $NATIVE_CODE_DIR/native/com/google/android/exoplayer2/demo/JNC.c  demo/src/main/cpp/JNC.c

cp $NATIVE_CODE_DIR/java/com/google/android/exoplayer2/demo/JGJ.java demo/src/main/java/com/google/android/exoplayer2/demo/JGJ.java
cp $NATIVE_CODE_DIR/native/com/google/android/exoplayer2/demo/JGJ.c  demo/src/main/cpp/JGJ.c

############################################################
cp $NATIVE_CODE_DIR/java/com/google/android/exoplayer2/demo/A.java demo/src/main/java/com/google/android/exoplayer2/demo/A.java
cp $NATIVE_CODE_DIR/native/com/google/android/exoplayer2/demo/A.c  demo/src/main/cpp/A.c

cp $NATIVE_CODE_DIR/java/com/google/android/exoplayer2/demo/B.java demo/src/main/java/com/google/android/exoplayer2/demo/B.java
cp $NATIVE_CODE_DIR/native/com/google/android/exoplayer2/demo/B.c  demo/src/main/cpp/B.c

cp $NATIVE_CODE_DIR/java/com/google/android/exoplayer2/demo/CC.java demo/src/main/java/com/google/android/exoplayer2/demo/CC.java
cp $NATIVE_CODE_DIR/native/com/google/android/exoplayer2/demo/CC.c  demo/src/main/cpp/CC.c

cp $NATIVE_CODE_DIR/java/com/google/android/exoplayer2/demo/D.java demo/src/main/java/com/google/android/exoplayer2/demo/D.java
cp $NATIVE_CODE_DIR/native/com/google/android/exoplayer2/demo/D.c  demo/src/main/cpp/D.c
############################################################

./gradlew assembleNoExtensionsDebug
cp demo/buildout/outputs/apk/demo-noExtensions-debug.apk ../repackage/app-native.apk
popd

#copy machine generated smail to protected apk's bin dir
pushd .
cd repackage
apktool d app-native.apk
mv app-native source

cp source/smali/com/google/android/exoplayer2/demo/PlayerActivity.smali target/smali/com/google/android/exoplayer2/demo/PlayerActivity.smali
cp -r source/lib target

#repackage protected apk
apktool b target -o app-repackage.apk
#java sign
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore signkey.jks -storepass irdeto app-repackage.apk customer.key.alias
#run
adb uninstall com.google.android.exoplayer2.demo && adb install -r app-repackage.apk
popd

fi
