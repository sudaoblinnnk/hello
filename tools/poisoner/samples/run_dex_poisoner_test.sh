#!/bin/bash

#export PATH="/cygdrive/c/Program Files (x86)/Java/jdk1.6.0_26/bin":$PATH
export PATH=/home/kurt/Work/tools/jdk/jdk1.6.0_45:$PATH

#cp -r ../src/java/classesgenerated/iac.jar iac.jar

class_path="../../poisoner/libs/commons-codec-1.6.jar:../../poisoner/libs/commons-io-2.1.jar:iac.jar"
#class_path="../../poisoner/libs/commons-codec-1.6.jar:../../poisoner/libs/commons-io-2.1.jar:../../poisoner/libs/DexConvertor.jar"

cmd="/home/kurt/Work/tools/jdk/jdk1.6.0_45/bin/java  -DConfigureFilePath="./hello_dexconfig.xml"   -classpath "$class_path" com.irdeto.secureaccess.android.dexreader.IrdetoDexConvertor classes.dex  out.jar"
#cmd="/home/kurt/Work/tools/jdk/jdk1.6.0_45/bin/java -classpath "$class_path" com.googlecode.dex2jar.util.Dump classes.dex out.jar"

echo $cmd
$cmd

