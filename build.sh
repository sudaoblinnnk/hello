#remove previous auto generated files
NATIVE_CODE_DIR=/home/kurt/company/workspace.eclipse/J2NConverter
#NATIVE_CODE_DIR=/home/kurt/innovation/hello/tools/poisoner/samples
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
../gradlew clean
../gradlew assembleRelease
cp build/outputs/apk/app-release.apk ../../../repackage/
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

pushd .
cd tools/poisoner/samples/
#. run_dex_poisoner_test.sh
popd

#copy machine translated source code
pushd .
cd FirstApp/FirstApplication/app

#copy all machine generated cpp files

cd src/main/cpp/
touch code.txt

find $NATIVE_CODE_DIR/native/com/irdeto/j2n/firstapplication/ -name '*.cpp' | xargs cat >> code.txt
mv code.txt native-lib.cpp
cd ../../../

#copy all machine generated java files
cp $NATIVE_CODE_DIR/java/com/irdeto/j2n/firstapplication/*  src/main/java/com/irdeto/j2n/firstapplication/

#compile machine translated source code
../gradlew clean
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
#adb uninstall  com.irdeto.j2n.firstapplication && adb install -r app-repackage.apk
popd

