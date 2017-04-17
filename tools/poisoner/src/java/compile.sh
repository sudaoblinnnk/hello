#!/bin/bash

for afile in `find ./ -name "*.java"`; do  
        #echo $afile;
        if [ -f "$afile" ]; then  
                JAVA_SOURCE=$JAVA_SOURCE" $afile";  
        fi
done
#echo $JAVA_SOURCE

OUTPUT=classesgenerated
rm -rf $OUTPUT
mkdir -p $OUTPUT
/home/kurt/Work/tools/jdk/jdk1.6.0_45/bin/javac -classpath ../../../poisoner/libs/commons-codec-1.6.jar:../../../poisoner/libs/commons-io-2.1.jar  $JAVA_SOURCE -d $OUTPUT

pushd .
cd $OUTPUT
for cfile in `find ./ -name "*.class"`; do  
        #echo $cfile;
        if [ -f "$cfile" ]; then  
                JAVA_CLASSES=$JAVA_CLASSES" $cfile";  
        fi
done
#echo $JAVA_CLASSES

rm -rf iac.jar
/home/kurt/Work/tools/jdk/jdk1.6.0_45/bin/jar cvf iac.jar $JAVA_CLASSES
popd

