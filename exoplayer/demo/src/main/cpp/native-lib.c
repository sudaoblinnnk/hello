#include <jni.h>
#include <stdio.h>
#include <android/log.h>

char * AC_DEBUG = "kurt";

#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  AC_DEBUG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, AC_DEBUG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, AC_DEBUG, fmt, ##args)

//method:0001  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jobject  Java_com_google_android_exoplayer2_demo_PlayerActivity_buildDataSourceFactory(JNIEnv * env, jobject  v2, jboolean v3)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LOCAL_VARIABLE LL0 ~ LL1 v3 -> useBandwidthMeter // Z
//LABEL               |  LL0: line 250
    L0: ;
//INVOKE_VIRTUAL      |     |TEMP=v2.getApplication()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.getApplication()Landroid/app/Application;
    jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "getApplication", "()Landroid/app/Application;");
    jobject TEMP0 = (*env)->CallObjectMethod(env, v2, methodId0);
//MOVE_RESULT         |     |v0=TEMP0
    jobject v0_0 = TEMP0;
//CHECK_CAST          |     |v0=(com.google.android.exoplayer2.demo.DemoApplication) v0
//IF_EQZ              |     |if (v3 == 0) { goto L2; }
    if (v3 == 0) { goto L2; }
//SGET                |     |v1=com.google.android.exoplayer2.demo.PlayerActivity.BANDWIDTH_METER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.BANDWIDTH_METER Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;
    jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId0 = (*env)->GetStaticFieldID(env, localClass1, "BANDWIDTH_METER", "Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;");
    jobject v1_0 = (*env)->GetStaticObjectField(env, localClass1, fieldId0);
//LABEL               |  LL3: line 251
    L3: ;
//INVOKE_VIRTUAL      |     |TEMP=v0.buildDataSourceFactory(v1_0)  //Lcom/google/android/exoplayer2/demo/DemoApplication;.buildDataSourceFactory(Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/DemoApplication");
    jmethodID methodId1 = (*env)->GetMethodID(env, localClass2, "buildDataSourceFactory", "(Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject TEMP1 = (*env)->CallObjectMethod(env, v0_0, methodId1, v1_0);
//MOVE_RESULT         |     |v0=TEMP1
    jobject v0_1 = TEMP1;
//LABEL               |  LL4: line 250
    L4: ;
//RETURN              |     |return v0
    return v0_1;
//LABEL               |  LL2:
    L2: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
    jint v1_1 = 0x00000000;
//GOTO                |     |goto L3;
    goto L3;
//LABEL               |  LL1:
    L1: ;
}


//method:0002  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildMediaSource(Landroid/net/Uri;Ljava/lang/String;)Lcom/google/android/exoplayer2/source/MediaSource;
jobject  Java_com_google_android_exoplayer2_demo_PlayerActivity_buildMediaSource(JNIEnv * env, jobject  v7, jobject v8, jstring v9)
{
//LOCAL_VARIABLE LL0 ~ LL1 v6 -> type // I
//LOCAL_VARIABLE LL2 ~ LL3 v6 -> type // I
//LOCAL_VARIABLE LL4 ~ LL3 v7 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LOCAL_VARIABLE LL4 ~ LL3 v8 -> uri // Landroid/net/Uri;
//LOCAL_VARIABLE LL4 ~ LL3 v9 -> overrideExtension // Ljava/lang/String;
//LABEL               |  LL4: line 229
    L4: ;
//CONST               |     |v2=0x00000000  // int:0   float:0.000000
    jint v2_0 = 0x00000000;
//LABEL               |  LL5: line 229
    L5: ;
//INVOKE_STATIC       |     |TEMP=android.text.TextUtils.isEmpty(v9)  //Landroid/text/TextUtils;.isEmpty(Ljava/lang/CharSequence;)Z
    jclass localClass0 = (*env)->FindClass(env, "android/text/TextUtils");
    jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "isEmpty", "(Ljava/lang/CharSequence;)Z");
    jboolean TEMP0 = (*env)->CallStaticBooleanMethod(env, localClass0, methodId0, v9);
//MOVE_RESULT         |     |v0=TEMP0
    jboolean v0_0 = TEMP0;
//IF_EQZ              |     |if (v0 == 0) { goto L1; }
    if (v0_0 == 0) { goto L1; }
//INVOKE_STATIC       |     |TEMP=com.google.android.exoplayer2.util.Util.inferContentType(v8)  //Lcom/google/android/exoplayer2/util/Util;.inferContentType(Landroid/net/Uri;)I
    jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/util/Util");
    jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "inferContentType", "(Landroid/net/Uri;)I");
    jint TEMP1 = (*env)->CallStaticIntMethod(env, localClass1, methodId1, v8);
//MOVE_RESULT         |     |v6=TEMP1
    jint v6_0 = TEMP1;
//LABEL               |  LL0: line 231
    L0: ;
//PACKED_SWITCH       |     |switch(v6)
//PACKED_SWITCH       |     |case 0: goto L6
//PACKED_SWITCH       |     |case 1: goto L2
//PACKED_SWITCH       |     |case 2: goto L7
//PACKED_SWITCH       |     |case 3: goto L8
//PACKED_SWITCH       |     |default: goto L9
//LABEL               |  LL9: line 244
    L9: ;
//NEW_INSTANCE        |     |v0=NEW Ljava/lang/IllegalStateException;
    jobject v0_1 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/IllegalStateException"));

//NEW_INSTANCE        |     |v1=NEW Ljava/lang/StringBuilder;
    jobject v1_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v1.<init>()  //Ljava/lang/StringBuilder;.<init>()V
    jclass localClass2 = (*env)->FindClass(env, "java/lang/StringBuilder");
    jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "<init>", "()V");
    (*env)->CallVoidMethod(env, v1_0, methodId2);
//CONST_STRING        |     |v2="Unsupported type: "
    jstring v2_1 = (*env)->NewStringUTF(env, "Unsupported type: ");
//INVOKE_VIRTUAL      |     |TEMP=v1.append(v2_1)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
    jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
    jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
    jobject TEMP2 = (*env)->CallObjectMethod(env, v1_0, methodId3, v2_1);
//MOVE_RESULT         |     |v1=TEMP2
    v1_0 = TEMP2;
//INVOKE_VIRTUAL      |     |TEMP=v1.append(v6_0)  //Ljava/lang/StringBuilder;.append(I)Ljava/lang/StringBuilder;
    jclass localClass4 = (*env)->FindClass(env, "java/lang/StringBuilder");
    jmethodID methodId4 = (*env)->GetMethodID(env, localClass4, "append", "(I)Ljava/lang/StringBuilder;");
    jobject TEMP3 = (*env)->CallObjectMethod(env, v1_0, methodId4, v6_0);
//MOVE_RESULT         |     |v1=TEMP3
    v1_0 = TEMP3;
//INVOKE_VIRTUAL      |     |TEMP=v1.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
    jclass localClass5 = (*env)->FindClass(env, "java/lang/StringBuilder");
    jmethodID methodId5 = (*env)->GetMethodID(env, localClass5, "toString", "()Ljava/lang/String;");
    jstring TEMP4 =  (jstring) (*env)->CallObjectMethod(env, v1_0, methodId5);
//MOVE_RESULT         |     |v1=TEMP4
    jstring v1_1 = TEMP4;
//INVOKE_DIRECT       |     |v0.<init>(v1_1)  //Ljava/lang/IllegalStateException;.<init>(Ljava/lang/String;)V
    jclass localClass6 = (*env)->FindClass(env, "java/lang/IllegalStateException");
    jmethodID methodId6 = (*env)->GetMethodID(env, localClass6, "<init>", "(Ljava/lang/String;)V");
    (*env)->CallVoidMethod(env, v0_1, methodId6, v1_1);
//THROW               |     |throw v0
//LABEL               |  LL1:
    L1: ;
//NEW_INSTANCE        |     |v0=NEW Ljava/lang/StringBuilder;
    jobject v0_2 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v0.<init>()  //Ljava/lang/StringBuilder;.<init>()V
    jclass localClass7 = (*env)->FindClass(env, "java/lang/StringBuilder");
    jmethodID methodId7 = (*env)->GetMethodID(env, localClass7, "<init>", "()V");
    (*env)->CallVoidMethod(env, v0_2, methodId7);
//CONST_STRING        |     |v1="."
    v1_1 = (*env)->NewStringUTF(env, ".");
//INVOKE_VIRTUAL      |     |TEMP=v0.append(v1_1)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
    jclass localClass8 = (*env)->FindClass(env, "java/lang/StringBuilder");
    jmethodID methodId8 = (*env)->GetMethodID(env, localClass8, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
    jobject TEMP5 = (*env)->CallObjectMethod(env, v0_2, methodId8, v1_1);
//MOVE_RESULT         |     |v0=TEMP5
    v0_2 = TEMP5;
//INVOKE_VIRTUAL      |     |TEMP=v0.append(v9)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
    jclass localClass9 = (*env)->FindClass(env, "java/lang/StringBuilder");
    jmethodID methodId9 = (*env)->GetMethodID(env, localClass9, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
    jobject TEMP6 = (*env)->CallObjectMethod(env, v0_2, methodId9, v9);
//MOVE_RESULT         |     |v0=TEMP6
    v0_2 = TEMP6;
//INVOKE_VIRTUAL      |     |TEMP=v0.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
    jclass localClass10 = (*env)->FindClass(env, "java/lang/StringBuilder");
    jmethodID methodId10 = (*env)->GetMethodID(env, localClass10, "toString", "()Ljava/lang/String;");
    jstring TEMP7 =  (jstring) (*env)->CallObjectMethod(env, v0_2, methodId10);
//MOVE_RESULT         |     |v0=TEMP7
    jstring v0_3 = TEMP7;
//INVOKE_STATIC       |     |TEMP=com.google.android.exoplayer2.util.Util.inferContentType(v0_3)  //Lcom/google/android/exoplayer2/util/Util;.inferContentType(Ljava/lang/String;)I
    jclass localClass11 = (*env)->FindClass(env, "com/google/android/exoplayer2/util/Util");
    jmethodID methodId11 = (*env)->GetMethodID(env, localClass11, "inferContentType", "(Ljava/lang/String;)I");
    jint TEMP8 = (*env)->CallStaticIntMethod(env, localClass11, methodId11, v0_3);
//MOVE_RESULT         |     |v6=TEMP8
    v6_0 = TEMP8;
//GOTO                |     |goto L0;
    goto L0;
//LABEL               |  LL2: line 361
    L2: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/smoothstreaming/SsMediaSource;
    jobject v0_4 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/smoothstreaming/SsMediaSource"));

//INVOKE_DIRECT       |     |TEMP=v7.buildDataSourceFactory(v2_1)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass12 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId12 = (*env)->GetMethodID(env, localClass12, "buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject TEMP9 = (*env)->CallObjectMethod(env, v7, methodId12, v2_1);
//MOVE_RESULT         |     |v2=TEMP9
    jobject v2_2 = TEMP9;
//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/source/smoothstreaming/DefaultSsChunkSource$Factory;
    jobject v3_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/smoothstreaming/DefaultSsChunkSource$Factory"));

//IGET                |     |v1=v7.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass13 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId0 = (*env)->GetFieldID(env, localClass13, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject v1_2 = (*env)->GetObjectField(env, v7, fieldId0);

//INVOKE_DIRECT       |     |v3.<init>(v1_2)  //Lcom/google/android/exoplayer2/source/smoothstreaming/DefaultSsChunkSource$Factory;.<init>(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V
    jclass localClass14 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/smoothstreaming/DefaultSsChunkSource$Factory");
    jmethodID methodId13 = (*env)->GetMethodID(env, localClass14, "<init>", "(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V");
    (*env)->CallVoidMethod(env, v3_0, methodId13, v1_2);
//IGET                |     |v4=v7.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
    jclass localClass15 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId1 = (*env)->GetFieldID(env, localClass15, "mainHandler", "Landroid/os/Handler;");
    jobject v4_0 = (*env)->GetObjectField(env, v7, fieldId1);

//IGET                |     |v5=v7.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
    jclass localClass16 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId2 = (*env)->GetFieldID(env, localClass16, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
    jobject v5_0 = (*env)->GetObjectField(env, v7, fieldId2);

//MOVE                |     |v1 = v8
    jobject v1_3 = v8;
//INVOKE_DIRECT       |     |v0.<init>(v1_3,v2_2,v3_0,v4_0,v5_0)  //Lcom/google/android/exoplayer2/source/smoothstreaming/SsMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/smoothstreaming/SsChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V
    jclass localClass17 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/smoothstreaming/SsMediaSource");
    jmethodID methodId14 = (*env)->GetMethodID(env, localClass17, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/smoothstreaming/SsChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V");
    (*env)->CallVoidMethod(env, v0_4, methodId14, v1_3,v2_2,v3_0,v4_0,v5_0);
//LABEL               | LL10:
    L10: ;
//RETURN              |     |return v0
    return v0_4;
//LABEL               |  LL6: line 492
    L6: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/dash/DashMediaSource;
    jobject v0_5 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DashMediaSource"));

//INVOKE_DIRECT       |     |TEMP=v7.buildDataSourceFactory(v2_2)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass18 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId15 = (*env)->GetMethodID(env, localClass18, "buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject TEMP10 = (*env)->CallObjectMethod(env, v7, methodId15, v2_2);
//MOVE_RESULT         |     |v2=TEMP10
    v2_2 = TEMP10;
//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory;
    jobject v3_1 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory"));

//IGET                |     |v1=v7.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass19 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId3 = (*env)->GetFieldID(env, localClass19, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject v1_4 = (*env)->GetObjectField(env, v7, fieldId3);

//INVOKE_DIRECT       |     |v3.<init>(v1_4)  //Lcom/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory;.<init>(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V
    jclass localClass20 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory");
    jmethodID methodId16 = (*env)->GetMethodID(env, localClass20, "<init>", "(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V");
    (*env)->CallVoidMethod(env, v3_1, methodId16, v1_4);
//IGET                |     |v4=v7.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
    jclass localClass21 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId4 = (*env)->GetFieldID(env, localClass21, "mainHandler", "Landroid/os/Handler;");
    v4_0 = (*env)->GetObjectField(env, v7, fieldId4);

//IGET                |     |v5=v7.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
    jclass localClass22 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId5 = (*env)->GetFieldID(env, localClass22, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
    v5_0 = (*env)->GetObjectField(env, v7, fieldId5);

//MOVE                |     |v1 = v8
    jobject v1_5 = v8;
//INVOKE_DIRECT       |     |v0.<init>(v1_5,v2_2,v3_1,v4_0,v5_0)  //Lcom/google/android/exoplayer2/source/dash/DashMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/dash/DashChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V
    jclass localClass23 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DashMediaSource");
    jmethodID methodId17 = (*env)->GetMethodID(env, localClass23, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/dash/DashChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V");
    (*env)->CallVoidMethod(env, v0_5, methodId17, v1_5,v2_2,v3_1,v4_0,v5_0);
//GOTO                |     |goto L10;
    goto L10;
//LABEL               |  LL7:
    L7: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/hls/HlsMediaSource;
    jobject v0_6 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/hls/HlsMediaSource"));

//IGET                |     |v1=v7.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass24 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId6 = (*env)->GetFieldID(env, localClass24, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject v1_6 = (*env)->GetObjectField(env, v7, fieldId6);

//IGET                |     |v2=v7.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
    jclass localClass25 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId7 = (*env)->GetFieldID(env, localClass25, "mainHandler", "Landroid/os/Handler;");
    jobject v2_3 = (*env)->GetObjectField(env, v7, fieldId7);

//IGET                |     |v3=v7.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
    jclass localClass26 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId8 = (*env)->GetFieldID(env, localClass26, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
    jobject v3_2 = (*env)->GetObjectField(env, v7, fieldId8);

//INVOKE_DIRECT       |     |v0.<init>(v8,v1_6,v2_3,v3_2)  //Lcom/google/android/exoplayer2/source/hls/HlsMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V
    jclass localClass27 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/hls/HlsMediaSource");
    jmethodID methodId18 = (*env)->GetMethodID(env, localClass27, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V");
    (*env)->CallVoidMethod(env, v0_6, methodId18, v8,v1_6,v2_3,v3_2);
//GOTO                |     |goto L10;
    goto L10;
//LABEL               |  LL8: line 497
    L8: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/ExtractorMediaSource;
    jobject v0_7 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/ExtractorMediaSource"));

//IGET                |     |v2=v7.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass28 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId9 = (*env)->GetFieldID(env, localClass28, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject v2_4 = (*env)->GetObjectField(env, v7, fieldId9);

//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/extractor/DefaultExtractorsFactory;
    jobject v3_3 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/extractor/DefaultExtractorsFactory"));

//INVOKE_DIRECT       |     |v3.<init>()  //Lcom/google/android/exoplayer2/extractor/DefaultExtractorsFactory;.<init>()V
    jclass localClass29 = (*env)->FindClass(env, "com/google/android/exoplayer2/extractor/DefaultExtractorsFactory");
    jmethodID methodId19 = (*env)->GetMethodID(env, localClass29, "<init>", "()V");
    (*env)->CallVoidMethod(env, v3_3, methodId19);
//IGET                |     |v4=v7.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
    jclass localClass30 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId10 = (*env)->GetFieldID(env, localClass30, "mainHandler", "Landroid/os/Handler;");
    v4_0 = (*env)->GetObjectField(env, v7, fieldId10);

//IGET                |     |v5=v7.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
    jclass localClass31 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId11 = (*env)->GetFieldID(env, localClass31, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
    v5_0 = (*env)->GetObjectField(env, v7, fieldId11);

//MOVE                |     |v1 = v8
    jobject v1_7 = v8;
//INVOKE_DIRECT       |     |v0.<init>(v1_7,v2_4,v3_3,v4_0,v5_0)  //Lcom/google/android/exoplayer2/source/ExtractorMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/extractor/ExtractorsFactory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/ExtractorMediaSource$EventListener;)V
    jclass localClass32 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/ExtractorMediaSource");
    jmethodID methodId20 = (*env)->GetMethodID(env, localClass32, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/extractor/ExtractorsFactory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/ExtractorMediaSource$EventListener;)V");
    (*env)->CallVoidMethod(env, v0_7, methodId20, v1_7,v2_4,v3_3,v4_0,v5_0);
//GOTO                |     |goto L10;
    goto L10;
//LABEL               |  LL3:
    L3: ;
}


//method:0003  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.initializePlayer()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_initializePlayer(JNIEnv * env, jobject  v28)
{
}


//method:0004  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.showToast(I)V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast(JNIEnv * env, jobject  v1, jint v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> messageId // I
//LABEL               |  LL0: line 255
    L0: ;
//INVOKE_VIRTUAL      |     |TEMP=v1.getString(v2)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.getString(I)Ljava/lang/String;
    jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "getString", "(I)Ljava/lang/String;");
    jstring TEMP0 =  (jstring) (*env)->CallObjectMethod(env, v1, methodId0, v2);
//MOVE_RESULT         |     |v0=TEMP0
    jstring v0_0 = TEMP0;
//INVOKE_DIRECT       |     |v1.showToast(v0_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.showToast(Ljava/lang/String;)V
    jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "showToast", "(Ljava/lang/String;)V");
    (*env)->CallVoidMethod(env, v1, methodId1, v0_0);
//LABEL               |  LL2: line 256
    L2: ;
//RETURN_VOID         |     |return
    return;
//LABEL               |  LL1:
    L1: ;
}




//method:0006  access:0x0001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.onCreate(Landroid/os/Bundle;)V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_onCreate(JNIEnv * env, jobject  v3, jobject v4)
{
//LOCAL_VARIABLE LL0 ~ LL1 v3 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LOCAL_VARIABLE LL0 ~ LL1 v4 -> savedInstanceState // Landroid/os/Bundle;
//LABEL               |  LL0: line 101
    L0: ;
//CONST               |     |v2=0x00000001  // int:1   float:0.000000
    jint v2_0 = 0x00000001;
//LABEL               |  LL2: line 101
    L2: ;
//INVOKE_SUPER        |     |v3.onCreate(v4)  //Landroid/app/Activity;.onCreate(Landroid/os/Bundle;)V
    jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
    jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "onCreate", "(Landroid/os/Bundle;)V");
    (*env)->CallNonvirtualVoidMethod(env, v3, localClass0, methodId0, v4);
//LABEL               |  LL3: line 103
    L3: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;
    jobject v0_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/upstream/DefaultBandwidthMeter"));

//INVOKE_DIRECT       |     |v0.<init>()  //Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;.<init>()V
    jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/upstream/DefaultBandwidthMeter");
    jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "<init>", "()V");
    (*env)->CallVoidMethod(env, v0_0, methodId1);
//SPUT                |     |com.google.android.exoplayer2.demo.PlayerActivity.BANDWIDTH_METER=v0  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.BANDWIDTH_METER Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;
    jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId0 = (*env)->GetStaticFieldID(env, localClass2, "BANDWIDTH_METER", "Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;");
    (*env)->SetStaticObjectField(env, localClass2, fieldId0, v0_0);

//LABEL               |  LL4: line 105
    L4: ;
//NEW_INSTANCE        |     |v0=NEW Ljava/net/CookieManager;
    jobject v0_1 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/net/CookieManager"));

//INVOKE_DIRECT       |     |v0.<init>()  //Ljava/net/CookieManager;.<init>()V
    jclass localClass3 = (*env)->FindClass(env, "java/net/CookieManager");
    jmethodID methodId2 = (*env)->GetMethodID(env, localClass3, "<init>", "()V");
    (*env)->CallVoidMethod(env, v0_1, methodId2);
//SPUT                |     |com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER=v0  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
    jclass localClass4 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId1 = (*env)->GetStaticFieldID(env, localClass4, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
    (*env)->SetStaticObjectField(env, localClass4, fieldId1, v0_1);

//LABEL               |  LL5: line 106
    L5: ;
//SGET                |     |v0=com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
    jclass localClass5 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId2 = (*env)->GetStaticFieldID(env, localClass5, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
    v0_1 = (*env)->GetStaticObjectField(env, localClass5, fieldId2);
//SGET                |     |v1=java.net.CookiePolicy.ACCEPT_ORIGINAL_SERVER  //Ljava/net/CookiePolicy;.ACCEPT_ORIGINAL_SERVER Ljava/net/CookiePolicy;
    jclass localClass6 = (*env)->FindClass(env, "java/net/CookiePolicy");
    jfieldID fieldId3 = (*env)->GetStaticFieldID(env, localClass6, "ACCEPT_ORIGINAL_SERVER", "Ljava/net/CookiePolicy;");
    jobject v1_0 = (*env)->GetStaticObjectField(env, localClass6, fieldId3);
//INVOKE_VIRTUAL      |     |v0.setCookiePolicy(v1_0)  //Ljava/net/CookieManager;.setCookiePolicy(Ljava/net/CookiePolicy;)V
    jclass localClass7 = (*env)->FindClass(env, "java/net/CookieManager");
    jmethodID methodId3 = (*env)->GetMethodID(env, localClass7, "setCookiePolicy", "(Ljava/net/CookiePolicy;)V");
    (*env)->CallVoidMethod(env, v0_1, methodId3, v1_0);
//LABEL               |  LL6: line 108
    L6: ;
//IPUT                |     |v3.shouldAutoPlay=v2  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.shouldAutoPlay Z
    jclass localClass8 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId4 = (*env)->GetFieldID(env, localClass8, "shouldAutoPlay", "Z");
    (*env)->SetBooleanField(env, v3, fieldId4, v2_0);

//LABEL               |  LL7: line 110
    L7: ;
//INVOKE_DIRECT       |     |TEMP=v3.buildDataSourceFactory(v2_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass9 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId4 = (*env)->GetMethodID(env, localClass9, "buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject TEMP0 = (*env)->CallObjectMethod(env, v3, methodId4, v2_0);
//MOVE_RESULT         |     |v0=TEMP0
    jobject v0_2 = TEMP0;
//IPUT                |     |v3.mediaDataSourceFactory=v0  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass10 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId5 = (*env)->GetFieldID(env, localClass10, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    (*env)->SetObjectField(env, v3, fieldId5, v0_2);

//LABEL               |  LL8: line 111
    L8: ;
//NEW_INSTANCE        |     |v0=NEW Landroid/os/Handler;
    jobject v0_3 = (*env)->AllocObject(env, (*env)->FindClass(env, "android/os/Handler"));

//INVOKE_DIRECT       |     |v0.<init>()  //Landroid/os/Handler;.<init>()V
    jclass localClass11 = (*env)->FindClass(env, "android/os/Handler");
    jmethodID methodId5 = (*env)->GetMethodID(env, localClass11, "<init>", "()V");
    (*env)->CallVoidMethod(env, v0_3, methodId5);
//IPUT                |     |v3.mainHandler=v0  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
    jclass localClass12 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId6 = (*env)->GetFieldID(env, localClass12, "mainHandler", "Landroid/os/Handler;");
    (*env)->SetObjectField(env, v3, fieldId6, v0_3);
//CONST               |     |v0=0x7f040003  // int:2130968579   float:175458156290837700000000000000000000000.000000
    jint v0_6 = 0x7f040003;
    jclass localClass17 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId8 = (*env)->GetMethodID(env, localClass17, "setContentView", "(I)V");
    (*env)->CallVoidMethod(env, v3, methodId8, v0_6);
    LOGD("kurt");
}


//method:0007  access:0x0001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.onResume()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_onResume(JNIEnv * env, jobject  v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LABEL               |  LL0: line 128
    L0: ;
//INVOKE_SUPER        |     |v2.onResume()  //Landroid/app/Activity;.onResume()V
    jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
    jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "onResume", "()V");
    (*env)->CallNonvirtualVoidMethod(env, v2, localClass0, methodId0);
//LABEL               |  LL2: line 129
    L2: ;
//SGET                |     |v0=com.google.android.exoplayer2.util.Util.SDK_INT  //Lcom/google/android/exoplayer2/util/Util;.SDK_INT I
    jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/util/Util");
    jfieldID fieldId0 = (*env)->GetStaticFieldID(env, localClass1, "SDK_INT", "I");
    jint v0_0 = (*env)->GetStaticIntField(env, localClass1, fieldId0);
//CONST               |     |v1=0x00000017  // int:23   float:0.000000
    jint v1_0 = 0x00000017;
//IF_LE               |     |if (v0 <= v1) {  goto L3; }
    if (v0_0 <= v1_0) {  goto L3; }
//IGET                |     |v0=v2.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
    jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId1 = (*env)->GetFieldID(env, localClass2, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
    jobject v0_1 = (*env)->GetObjectField(env, v2, fieldId1);

//IF_NEZ              |     |if (v0 != 0) { goto L4; }
    if (v0_1 != 0) { goto L4; }
//LABEL               |  LL3: line 130
    L3: ;
//INVOKE_DIRECT       |     |v2.initializePlayer()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.initializePlayer()V
    jclass localClass3 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId1 = (*env)->GetMethodID(env, localClass3, "initializePlayer", "()V");
    (*env)->CallVoidMethod(env, v2, methodId1);
//LABEL               |  LL4: line 132
    L4: ;
//RETURN_VOID         |     |return
    return;
//LABEL               |  LL1:
    L1: ;
}

static int registerNativeSymbols420217909_442(JNIEnv * env) {
    int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = {
        //{"<init>", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_<init> },
        {"buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_buildDataSourceFactory },
        {"buildMediaSource", "(Landroid/net/Uri;Ljava/lang/String;)Lcom/google/android/exoplayer2/source/MediaSource;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_buildMediaSource },
        {"initializePlayer", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_initializePlayer },
        {"showToast", "(I)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast },
        {"showToast", "(Ljava/lang/String;)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast },
        {"onCreate", "(Landroid/os/Bundle;)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_onCreate },
        {"onResume", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_onResume },
    };
    jclass clazz = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    if (clazz == NULL) {
        returnVal = JNI_FALSE;
    }
    if ((*env)->RegisterNatives (env, clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {
        returnVal = JNI_FALSE;
    }
    return returnVal;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env; jint registerResult = JNI_FALSE;
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) { return -1; }

    registerNativeSymbols420217909_442(env);

    return JNI_VERSION_1_4; }