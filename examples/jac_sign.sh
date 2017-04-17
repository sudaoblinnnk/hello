#!/bin/bash 
###########################################################################
#
# This sample script is only to demonstrate the logistic workflow of JAC 
# signing procedure. It is, by no means, a 'ready to use' tool. To make it 
# work, one needs to adjust environment to properly point to various tools, 
# distribution packages and JAC configuration file etc.  as well Android 
# device where JAC sign takes place.
#
##########################################################################

MY_HOME=`pwd`

#CAT_HOME=/home/test/jrong/iac/rpm/packages/iac_2_15_0-1_StandardTest-gcc_4.4_android_arm
#CAT_HOME=/home/test/jrong/git/build_iac/loadbuild/provision/release/linux
#CAT_HOME=/home/test/jrong/iac/rpm/packages/iac_2.17.2_StandardTest-gcc_4.4_android_arm

CAT_HOME=/home/test/jrong/git/local_build_packages/linux_android_after_fpcodegen_change_acd_change_platform_tolerant

#DEX_HOME=/home/test/jrong/tools/poisoner
DEX_HOME=/home/test/jrong/git/build_iac/Source/jac/tools/poisoner

WORK_SPACE_HOME=/home/test/workspace
EMULATOR_HOME=/data/app-private
RPM_HOME=/home/test/jrong/scripts/perl
MY_SIZE=""
OPERATION=""
JAVA_SIGNING_PACKAGE=""
JAVA_SIGNING_PACKAGE_ASSET_DIR=""
JAVA_SIGNING_CONFIG_FILE=""
SETUP_FILE=""

#this is a fixed name
HMACSHA256_HANDLE="YYT76H"
HMACSHA256_KEY="87c7e446787a827f9aa0a247eb32f3a987c7e446787a827f9aa0a247eb32f3a9";
STORE_KEY="87c7e446787a827f9aa0a247eb32f3a9"
STORE_IV="4bd74865f96326d8dd891a4c1fad2162"
VOCHER_HANDLE="PPOJUJ"
#Standard seed:
#RANDOM_SEED=ADAD57A20A409876ABCD5432EF123123
#CCA Eval
RANDOM_SEED=CCAC911D09C4FC8670F8105D7E3ABCCA
#This seed is from US3
#RANDOM_SEED=37FE6A76FB908BAB6543AB4CCFD8D939
#CMG seed
#RANDOM_SEED=B86AEA350A5823A9D245D3BD406D8409
#OMP seed
#RANDOM_SEED=89274890712BA8897C234EB563F45987
#OTT Eval
#RANDOM_SEED=A900BBEA49C91620A91B0D18FB350AC2

#For standard build
#INSTANCE_DIR=evaluation
#For tated build
INSTANCE_DIR=i$RANDOM_SEED

OPTIONS="-target-arch arm -target-os android"
#For standard build
#OPTION_STD="-evaluation"

OPTION_SL="-sl_disable"

#OPTION_NATIVE="-legacy"

#these are fixed names
MYSTORE="jac_store.dat"
MYSTORE_DATA="jac_store_data.dat"

MY_SHARED_LIB="libmegjb.so" 

MY_SIGN_SHARED_LIB="libjavasign.so" 
MY_SIGN_SHARED_LIB_PATH="$WORK_SPACE_HOME/commandLineSign/libs/armeabi" 
MY_SIGN_SHARED_LIB_TARGET_PATH="/data/data/com.irdeto.commandline.signing/lib"

CLASS_PATH=""
DEX_APK_FILE=""
ANDROID_TARGET_DEVICE=""

setupEnv()
{
    export XC_LICENSE=$MY_HOME/../../css/license_all_dialects.xml
    export PATH=/opt/toolchain/android/ndk/android-ndk-r5/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86/bin:/opt/toolchain/java/32/jdk1.6.0_22/bin:$PATH
    CLASS_PATH="$DEX_HOME/../../lib/DexConvertor.jar:$DEX_HOME/libs/commons-codec-1.6.jar:$DEX_HOME/libs/commons-io-2.1.jar"
}

runSigningProcOnDevice()
{

    rm -f $CAT_HOME/bin/irdeto_java_access.dat  > /dev/null 2>&1
    adb -s $ANDROID_TARGET_DEVICE shell rm /data/app-private/irdeto_java_access_ns.dat  > /dev/null 2>&1
    adb -s $ANDROID_TARGET_DEVICE shell rm /data/app-private/irdeto_java_access.dat  > /dev/null 2>&1

    echo "Copying $MYSTORE to Android emulator at $EMULATOR_HOME/local/"
    adb -s $ANDROID_TARGET_DEVICE push ./$MYSTORE $EMULATOR_HOME/local/

    echo "Copy runtime application: $JAVA_SIGNING_PACKAGE to emulator at $EMULATOR_HOME/local/ for signing"
    adb -s $ANDROID_TARGET_DEVICE push $JAVA_SIGNING_PACKAGE $EMULATOR_HOME/local/ 

    cd $CAT_HOME/bin
    ./ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTIONS -java_sign build -config_file $JAVA_SIGNING_CONFIG_FILE -sn $ANDROID_TARGET_DEVICE
     
}

checkForCompletion()
{
    echo ""
    echo "Perform voucher completion checking, wait if it is incomplete"
    while [  1 ]; do
        adb -s $ANDROID_TARGET_DEVICE pull /data/app-private/irdeto_java_access.dat .  > /dev/null 2>&1
        myTok=`cat ./irdeto_java_access.dat | grep "#EOF"`
        if [ "$myTok" = "#EOF" ]; then
        echo "Found 'end of file'"
        break;
        fi
        sleep 5
    done
    echo "Java sign completed"
}

usage()
{
    echo ""
    echo "Command line:"
    echo ""
    echo "Prompt> $0 -s -f setup_file"
    echo ""
    echo "where, -s sign operation, -f file containing config info" 
    echo ""
    exit 1
}

readFile()
{
    echo ""
    echo "Reading setup file contents"
    echo ""
    JAVA_SIGNING_PACKAGE=`cat $SETUP_FILE | grep "JAVA_SIGNING_PACKAGE" | awk '{print($2)}'`
    echo $JAVA_SIGNING_PACKAGE
    MY_SHARED_LIB_PATH=`cat $SETUP_FILE | grep "MY_SHARED_LIB_PATH" | awk '{print($2)}'`
    echo $MY_SHARED_LIB_PATH
    MY_SHARED_LIB_TARGET_PATH=`cat $SETUP_FILE | grep "MY_SHARED_LIB_TARGET_PATH" | awk '{print($2)}'`
    echo $MY_SHARED_LIB_TARGET_PATH
    JAVA_SIGNING_CONFIG_FILE=`cat $SETUP_FILE | grep "JAVA_SIGNING_CONFIG_FILE" | awk '{print($2)}'`
    echo $JAVA_SIGNING_CONFIG_FILE
    DEX_APK_FILE=`cat $SETUP_FILE | grep "DEX_APK_FILE" | awk '{print($2)}'`
    echo $DEX_APK_FILE
    ANDROID_TARGET_DEVICE=`cat $SETUP_FILE | grep "ANDROID_TARGET_DEVICE" | awk '{print($2)}'`
    echo $ANDROID_TARGET_DEVICE
    echo ""

}    
parseCommandLine(){

    while getopts sp:c:a:f: OPT; do
	case "$OPT" in
	    s) 	
		    OPERATION="1"
		    ;;
	    p)	
		    JAVA_SIGNING_PACKAGE=$OPTARG
		    ;;
	    c)
		    JAVA_SIGNING_CONFIG_FILE=$OPTARG
		    ;;
	    a)
            DEX_APK_FILE=$OPTARG
            ;;
        f)  SETUP_FILE=$OPTARG
            ;;
	    *)
		usage
		;;
	esac
    done

    if [ "$SETUP_FILE" = "" ];then
        echo "Setup file not exist, exit"
        usage
    fi
    readFile
    if [ "$JAVA_SIGNING_PACKAGE" = "" ]; then
        echo "JAVA_SIGNING_PACKAGE not exist"
	    usage
    elif  [ "$JAVA_SIGNING_CONFIG_FILE" = "" ]; then
        echo "JAVA_SIGNING_CONFIG_FILE not exist"
	    usgae
    elif  [ "$OPERATION" != "1" ]; then
	    usage
    elif  [ "$ANDROID_TARGET_DEVICE" = "" ]; then
        echo "ANDROID_TARGET_DEVICE invalid"
        usage
    fi
    JAVA_SIGNING_PACKAGE_ASSET_DIR=`echo ${JAVA_SIGNING_PACKAGE%/*}`
    JAVA_SIGNING_PACKAGE_ASSET_DIR=`echo ${JAVA_SIGNING_PACKAGE_ASSET_DIR%/*}`
    JAVA_SIGNING_PACKAGE_ASSET_DIR=$JAVA_SIGNING_PACKAGE_ASSET_DIR/assets
    echo ""
    if [ ! -f "$JAVA_SIGNING_PACKAGE" ]; then
	    echo "$JAVA_SIGNING_PACKAGE not exist..."
	    usage
    elif [ ! -f "$JAVA_SIGNING_CONFIG_FILE" ]; then
	    echo "$JAVA_SIGNING_CONFIG_FILE not exist..."
	    usage
    fi
}

initSecureStore(){

    echo ""
    echo "Initializing secure store"
    echo ""
    rm $MYSTORE  2>/dev/null

    echo "Creating Secure Store"
    $CAT_HOME/bin/ACResourceProtection  -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTIONS -create_secure_store $MYSTORE -algorithm aes -key_data $STORE_KEY -iv_data $STORE_IV -debug
    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    echo "OK. size: $MY_SIZE"

    echo "Inserting HAMC Key"
    $CAT_HOME/bin/ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED  $OPTIONS -protect_data $MYSTORE -handle $HMACSHA256_HANDLE -data $HMACSHA256_KEY
    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    echo "OK. size: $MY_SIZE"
}

initSecureStoreForData(){

    echo ""
    echo "initSecureStoreForData, removing $MYSTORE_DATA"
    echo ""

    rm $MYSTORE_DATA  2>/dev/null

    echo "Creating Data Store"
    $CAT_HOME/bin/ACResourceProtection  -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTIONS -create_secure_store $MYSTORE_DATA -algorithm aes -key_data $STORE_KEY -iv_data $STORE_IV
}    

generateBytecodeAndStore()
{
    echo ""
    echo "generateBytecodeAndStore"
    echo ""
    if [ -e $DEX_APK_FILE  ];then
   	    if [ "$DEX_APK_FILE" = "" ];then
	        echo "Empty Dex filename"
	        return 1
 	    fi
    	echo "File $DEX_APK_FILE exist"
    else 
     	echo "Poisoning dex/apk file, $DEX_APK_FILE not exist, ignore..."
	    return 1
    fi
    cmd="java -DConfigureFilePath="$MY_HOME/dexconfig.xml" -DIndexFilePath="$MY_HOME/data/index.txt" -DBytecodeFilePath="$MY_HOME/data/bytecode.dat" -DPoinsonedFilePath="$MY_HOME/data/classes.dex" -classpath $CLASS_PATH com.irdeto.secureaccess.android.dexreader.IrdetoDexConvertor $DEX_APK_FILE"
    echo "Executing: $cmd"
    $cmd
    if [ $? != 0 ];then
        echo "Failed to run JAC IrdetoDexConvertor"
        return  3
    fi    
    cp $MY_HOME/data/classes.dex .
    if [ $? != 0 ];then
   	    echo "unable to copy classes.dex"
	    return 1
    fi
    jar cvf $MY_HOME/data/Poisoned.jar classes.dex 
    if [ $? != 0 ];then
        echo "Unable to JAR classes.dex"
        return 1
    fi
    rm classes.dex
    if [ $? != 0 ]; then
        echo "Not able to find classes.dex, skip..."
        return 1
    fi    
    cmd="$MY_HOME/../../tools/zlib/useZlib $MY_HOME/data/bytecode.dat"
    echo ""
    echo "Executing $cmd"
    echo ""
    $cmd
    if [ $? != 0 ]; then
        echo "Failed to compress file"
        return 1
    fi    

    cmd="$MY_HOME/../../tools/zlib/useZlib $MY_HOME/data/index.txt"
    echo ""
    echo "Executing $cmd"
    echo ""
    $cmd
    if [ $? != 0 ]; then
        echo "Failed to compress file"
        return 1
    fi    
    if [ $? = 0 ];then
        initSecureStoreForData
	    echo ""
    	echo "Inserting poisoned JAR file"
	    $CAT_HOME/bin/ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTIONS  -protect_data $MYSTORE_DATA -handle Poisoned.jar -data_file $MY_HOME/data/Poisoned.jar
	MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    	echo "OK. size: $MY_SIZE"

	    echo ""
    	echo "Inserting index file"
	    $CAT_HOME/bin/ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTIONS  -protect_data $MYSTORE_DATA -handle index.txt -data_file $MY_HOME/data/index.txt_out
	    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    	echo "OK. size: $MY_SIZE"
	
	    echo ""
    	echo "Inserting bytecode file"
	    $CAT_HOME/bin/ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTIONS  -protect_data $MYSTORE_DATA -handle bytecode.dat -data_file $MY_HOME/data/bytecode.dat_out
	    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    	echo "OK. size: $MY_SIZE"
        echo ""
        echo "ACIndividualization the $MYSTORE_DATA"
        $CAT_HOME/bin/ACIndividualization -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR $MYSTORE_DATA -set_access_mode RW

        echo "Copying $MYSTORE_DATA to $JAVA_SIGNING_PACKAGE_ASSET_DIR"
        cp ./$MYSTORE_DATA $JAVA_SIGNING_PACKAGE_ASSET_DIR
    fi
    return 0
}

sign() {

#create secure store for signing
    initSecureStore
#have to sign the offline shared library
    myCommand="$CAT_HOME/bin/ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTION_SL $OPTION_STD $OPTION_NATIVE -target-arch arm -target-os android -protect_application jac_store.dat -module_signed_in_store 5 $MY_SIGN_SHARED_LIB_PATH/$MY_SIGN_SHARED_LIB $MY_SIGN_SHARED_LIB_TARGET_PATH/ -root_module $MY_SIGN_SHARED_LIB_PATH/$MY_SIGN_SHARED_LIB -ac_agent $MY_SIGN_SHARED_LIB_PATH/$MY_SIGN_SHARED_LIB -pfiv"
    echo "Executig $myCommand"
    $myCommand
    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    echo "OK. size: $MY_SIZE"

    echo "Run individualization tool"
#    $CAT_HOME/bin/ACIndividualization -compatible_agent $CAT_HOME/lib/i$RANDOM_SEED $MYSTORE -set_access_mode RW -set_nodelocking_mode Client 
    $CAT_HOME/bin/ACIndividualization -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR $MYSTORE -set_access_mode RW

    runSigningProcOnDevice
    checkForCompletion

# final delivery of secure store
    initSecureStore

    echo "Inserting JAVA voucher"
    $CAT_HOME/bin/ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTIONS -protect_data $MYSTORE -handle $VOCHER_HANDLE -data_file ./irdeto_java_access.dat 
    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    echo "OK. size: $MY_SIZE"

    echo ""
    echo "Inserting JAC config item:"
    cat $MY_HOME/data/JacConfigFile.txt
    $CAT_HOME/bin/ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTIONS  -protect_data $MYSTORE -handle JACConfigHandle -data_file $MY_HOME/data/JacConfigFile.txt
    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    echo "OK. size: $MY_SIZE"

    myCommand="$CAT_HOME/bin/ACResourceProtection -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR -randomseed $RANDOM_SEED $OPTION_STD $OPTION_SL $OPTION_NATIVE -target-arch arm -target-os android -protect_application jac_store.dat -module_signed_in_store 10 $MY_SHARED_LIB_PATH/$MY_SHARED_LIB $MY_SHARED_LIB_TARGET_PATH/ -root_module $MY_SHARED_LIB_PATH/$MY_SHARED_LIB -ac_agent $MY_SHARED_LIB_PATH/$MY_SHARED_LIB -pfiv"
    echo "Executig $myCommand" 
    $myCommand
    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    echo "OK. size: $MY_SIZE"

    echo "Run individualization tool"
#    $CAT_HOME/bin/ACIndividualization -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR $MYSTORE -set_access_mode RW -set_nodelocking_mode Client 
    $CAT_HOME/bin/ACIndividualization -compatible_agent $CAT_HOME/lib/$INSTANCE_DIR $MYSTORE -set_access_mode RW
    MY_SIZE=`ls -al |grep $MYSTORE | awk '{print($5)}'`
    echo "OK. size: $MY_SIZE"

    echo "Copying $MYSTORE to $JAVA_SIGNING_PACKAGE_ASSET_DIR"
    cp ./$MYSTORE $JAVA_SIGNING_PACKAGE_ASSET_DIR

    generateBytecodeAndStore
}

####################  main  ###########################

parseCommandLine $@
setupEnv
sign
