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
