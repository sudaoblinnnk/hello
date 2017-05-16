#remove previous auto generated files
NATIVE_CODE_DIR=/home/kurt/company/workspace.eclipse/J2NConverter
pushd .
cd $NATIVE_CODE_DIR
rm -rf native
rm -rf java
unzip native.jar -d native
unzip java.jar -d   java
popd

#compile apk need to protect
pushd .
cd OriginalApp/FirstApplication/app
../gradlew assembleRelease
cp build/outputs/apk/app-release.apk ../../../repackage/
popd

#remove auto generated files
pushd .
cd repackage
rm -rf app-repackage.apk
rm -rf app-release
rm -rf target
rm -rf source

#use apktool to extract apk need to protected
apktool d app-release.apk              
mv app-release target
popd

#copy machine translated source code
pushd .
cd FirstApp/FirstApplication/app
cp $NATIVE_CODE_DIR/native/com/irdeto/j2n/firstapplication/MainActivity.cpp src/main/cpp/native-lib.cpp
cp $NATIVE_CODE_DIR/java/com/irdeto/j2n/firstapplication/MainActivity.java  src/main/java/com/irdeto/j2n/firstapplication/MainActivity.java

#compile machine translated source code
../gradlew assembleRelease
cp build/outputs/apk/app-release.apk ../../../repackage/app-native.apk
popd

#copy machine generated smail to protected apk's bin dir
pushd .
cd repackage
apktool d app-native.apk
mv app-native source

cp source/smali/com/irdeto/j2n/firstapplication/MainActivity.smali target/smali/com/irdeto/j2n/firstapplication/MainActivity.smali
cp -r source/lib target

#repackage protected apk
apktool b target -o app-repackage.apk
#java sign
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore signkey.jks -storepass irdeto app-repackage.apk customer.key.alias
#run
adb uninstall  com.irdeto.j2n.firstapplication && adb install -r app-repackage.apk
popd

