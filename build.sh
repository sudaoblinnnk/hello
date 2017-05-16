
pushd .
#cd OriginalApp/FirstApplication/app
#../gradlew assembleRelease
#cp build/outputs/apk/app-release.apk ../../../repackage/
popd

pushd .

cd repackage
rm -rf app-repackage.apk
rm -rf app-release
rm -rf target
rm -rf source

apktool d app-release.apk
mv app-release target
popd


pushd .
cd FirstApp/FirstApplication/app
../gradlew assembleRelease
cp build/outputs/apk/app-release.apk ../../../repackage/app-native.apk
popd

pushd .
cd repackage
apktool d app-native.apk
mv app-native source

cp source/smali/com/irdeto/j2n/firstapplication/MainActivity.smali target/smali/com/irdeto/j2n/firstapplication/MainActivity.smali
cp -r source/lib target

apktool b target -o app-repackage.apk
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore signkey.jks -storepass irdeto app-repackage.apk customer.key.alias
adb uninstall  com.irdeto.j2n.firstapplication && adb install -r app-repackage.apk
popd
