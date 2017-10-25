#include <jni.h>
#include <stdio.h>
//class:0650  access:0x0001
//public class com.google.android.exoplayer2.demo.PlayerActivity extends android.app.Activity
//field:0000  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.ACTION_VIEW Ljava/lang/String;
//field:0001  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.ACTION_VIEW_LIST Ljava/lang/String;
//field:0002  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.AD_TAG_URI_EXTRA Ljava/lang/String;
//field:0003  access:0x000a
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.BANDWIDTH_METER Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;
//field:0004  access:0x000a
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
//field:0005  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.DRM_KEY_REQUEST_PROPERTIES Ljava/lang/String;
//field:0006  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.DRM_LICENSE_URL Ljava/lang/String;
//field:0007  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.DRM_SCHEME_UUID_EXTRA Ljava/lang/String;
//field:0008  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.EXTENSION_EXTRA Ljava/lang/String;
//field:0009  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.EXTENSION_LIST_EXTRA Ljava/lang/String;
//field:0010  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.PREFER_EXTENSION_DECODERS Ljava/lang/String;
//field:0011  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.URI_LIST_EXTRA Ljava/lang/String;
//field:0012  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugRootView Landroid/widget/LinearLayout;
//field:0013  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugTextView Landroid/widget/TextView;
//field:0014  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugViewHelper Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;
//field:0015  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
//field:0016  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.inErrorState Z
//field:0017  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.lastSeenTrackGroupArray Lcom/google/android/exoplayer2/source/TrackGroupArray;
//field:0018  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
//field:0019  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
//field:0020  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
//field:0021  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.resumePosition J
//field:0022  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.resumeWindow I
//field:0023  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.retryButton Landroid/widget/Button;
//field:0024  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.shouldAutoPlay Z
//field:0025  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
//field:0026  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelectionHelper Lcom/google/android/exoplayer2/demo/TrackSelectionHelper;
//field:0027  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelector Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;

//method:0000  access:0x10001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.<init>()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity___initNative_39797(JNIEnv * env, jobject  v0)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LABEL               |  LL0: line 62
L0: ;
//INVOKE_DIRECT       |     |v0.<init>()  //Landroid/app/Activity;.<init>()V
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0001  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jobject  Java_com_google_android_exoplayer2_demo_PlayerActivity_buildDataSourceFactory_1578816035(JNIEnv * env, jobject  v2, jboolean v3)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL0 ~ LL1 v3 -> useBandwidthMeter // Z 
//LABEL               |  LL0: line 315
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
//LABEL               |  LL3: line 316
L3: ;
//INVOKE_VIRTUAL      |     |TEMP=v0.buildDataSourceFactory(v1_0)  //Lcom/google/android/exoplayer2/demo/DemoApplication;.buildDataSourceFactory(Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/DemoApplication");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass2, "buildDataSourceFactory", "(Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject TEMP1 = (*env)->CallObjectMethod(env, v0_0, methodId1, v1_0);
//MOVE_RESULT         |     |v0=TEMP1
jobject v0_1 = TEMP1;
//LABEL               |  LL4: line 315
L4: ;
//RETURN              |     |return v0
return v0_1;
//LABEL               |  LL2:
L2: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
v1_0 = 0x00000000;
//GOTO                |     |goto L3;
goto L3;
//LABEL               |  LL1:
L1: ;
}


//method:0002  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildMediaSource(Landroid/net/Uri;Ljava/lang/String;)Lcom/google/android/exoplayer2/source/MediaSource;
jobject  Java_com_google_android_exoplayer2_demo_PlayerActivity_buildMediaSource_1776506356(JNIEnv * env, jobject  v7, jobject v8, jstring v9)
{
//LOCAL_VARIABLE LL0 ~ LL1 v6 -> type // I 
//LOCAL_VARIABLE LL2 ~ LL3 v6 -> type // I 
//LOCAL_VARIABLE LL4 ~ LL3 v7 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL4 ~ LL3 v8 -> uri // Landroid/net/Uri; 
//LOCAL_VARIABLE LL4 ~ LL3 v9 -> overrideExtension // Ljava/lang/String; 
//LABEL               |  LL4: line 294
L4: ;
//CONST               |     |v2=0x00000000  // int:0   float:0.000000
jint v2_0 = 0x00000000;
//LABEL               |  LL5: line 294
L5: ;
//INVOKE_STATIC       |     |TEMP=android.text.TextUtils.isEmpty(v9)  //Landroid/text/TextUtils;.isEmpty(Ljava/lang/CharSequence;)Z
jclass localClass0 = (*env)->FindClass(env, "android/text/TextUtils");
jmethodID methodId0 = (*env)->GetStaticMethodID(env, localClass0, "isEmpty", "(Ljava/lang/CharSequence;)Z");
jboolean TEMP0 = (*env)->CallStaticBooleanMethod(env, localClass0, methodId0, v9);
//MOVE_RESULT         |     |v0=TEMP0
jboolean v0_0 = TEMP0;
//IF_EQZ              |     |if (v0 == 0) { goto L1; }
if (v0_0 == 0) { goto L1; }
//INVOKE_STATIC       |     |TEMP=com.google.android.exoplayer2.util.Util.inferContentType(v8)  //Lcom/google/android/exoplayer2/util/Util;.inferContentType(Landroid/net/Uri;)I
jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/util/Util");
jmethodID methodId1 = (*env)->GetStaticMethodID(env, localClass1, "inferContentType", "(Landroid/net/Uri;)I");
jint TEMP1 = (*env)->CallStaticIntMethod(env, localClass1, methodId1, v8);
//MOVE_RESULT         |     |v6=TEMP1
jint v6_0 = TEMP1;
//LABEL               |  LL0: line 296
L0: ;
//PACKED_SWITCH       |     |switch(v2)
//PACKED_SWITCH       |     |case 0: goto L6;
//PACKED_SWITCH       |     |case 1: goto L2;
//PACKED_SWITCH       |     |case 2: goto L7;
//PACKED_SWITCH       |     |case 3: goto L8;
//PACKED_SWITCH       |     |default: goto L9;
switch(v2_0)
{
case 0: goto L6;
case 1: goto L2;
case 2: goto L7;
case 3: goto L8;
default: goto L9;
}
//LABEL               |  LL9: line 309
L9: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_1 = 0x00000000;
//LABEL               | LL10:
L10: ;
//RETURN              |     |return v0
return v0_1;
//LABEL               |  LL1: line 422
L1: ;
//NEW_INSTANCE        |     |v0=NEW Ljava/lang/StringBuilder;
jobject v0_2 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v0.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass2 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "<init>", "()V");
(*env)->CallVoidMethod(env, v0_2, methodId2);
//CONST_STRING        |     |v1="."
jstring v1_0 = (*env)->NewStringUTF(env, ".");
//INVOKE_VIRTUAL      |     |TEMP=v0.append(v1_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP2 = (*env)->CallObjectMethod(env, v0_2, methodId3, v1_0);
//MOVE_RESULT         |     |v0=TEMP2
v0_2 = TEMP2;
//INVOKE_VIRTUAL      |     |TEMP=v0.append(v9)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass4 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId4 = (*env)->GetMethodID(env, localClass4, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP3 = (*env)->CallObjectMethod(env, v0_2, methodId4, v9);
//MOVE_RESULT         |     |v0=TEMP3
v0_2 = TEMP3;
//INVOKE_VIRTUAL      |     |TEMP=v0.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass5 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId5 = (*env)->GetMethodID(env, localClass5, "toString", "()Ljava/lang/String;");
jstring TEMP4 =  (jstring) (*env)->CallObjectMethod(env, v0_2, methodId5);
//MOVE_RESULT         |     |v0=TEMP4
jstring v0_3 = TEMP4;
//INVOKE_STATIC       |     |TEMP=com.google.android.exoplayer2.util.Util.inferContentType(v0_3)  //Lcom/google/android/exoplayer2/util/Util;.inferContentType(Ljava/lang/String;)I
jclass localClass6 = (*env)->FindClass(env, "com/google/android/exoplayer2/util/Util");
jmethodID methodId6 = (*env)->GetStaticMethodID(env, localClass6, "inferContentType", "(Ljava/lang/String;)I");
jint TEMP5 = (*env)->CallStaticIntMethod(env, localClass6, methodId6, v0_3);
//MOVE_RESULT         |     |v6=TEMP5
v6_0 = TEMP5;
//GOTO                |     |goto L0;
goto L0;
//LABEL               |  LL2: line 426
L2: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/smoothstreaming/SsMediaSource;
jobject v0_4 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/smoothstreaming/SsMediaSource"));

//INVOKE_DIRECT       |     |TEMP=v7.buildDataSourceFactory(v2_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass7 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId7 = (*env)->GetMethodID(env, localClass7, "buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject TEMP6 = (*env)->CallObjectMethod(env, v7, methodId7, v2_0);
//MOVE_RESULT         |     |v2=TEMP6
jobject v2_1 = TEMP6;
//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/source/smoothstreaming/DefaultSsChunkSource$Factory;
jobject v3_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/smoothstreaming/DefaultSsChunkSource$Factory"));

//IGET                |     |v1=v7.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass8 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId0 = (*env)->GetFieldID(env, localClass8, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject v1_1 = (*env)->GetObjectField(env, v7, fieldId0);

//INVOKE_DIRECT       |     |v3.<init>(v1_1)  //Lcom/google/android/exoplayer2/source/smoothstreaming/DefaultSsChunkSource$Factory;.<init>(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V
jclass localClass9 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/smoothstreaming/DefaultSsChunkSource$Factory");
jmethodID methodId8 = (*env)->GetMethodID(env, localClass9, "<init>", "(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V");
(*env)->CallVoidMethod(env, v3_0, methodId8, v1_1);
//IGET                |     |v4=v7.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
jclass localClass10 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId1 = (*env)->GetFieldID(env, localClass10, "mainHandler", "Landroid/os/Handler;");
jobject v4_0 = (*env)->GetObjectField(env, v7, fieldId1);

//IGET                |     |v5=v7.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass11 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId2 = (*env)->GetFieldID(env, localClass11, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
jobject v5_0 = (*env)->GetObjectField(env, v7, fieldId2);

//MOVE                |     |v1 = v8
jobject v1_2 = v8;
//INVOKE_DIRECT       |     |v0.<init>(v1_2,v2_1,v3_0,v4_0,v5_0)  //Lcom/google/android/exoplayer2/source/smoothstreaming/SsMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/smoothstreaming/SsChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V
jclass localClass12 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/smoothstreaming/SsMediaSource");
jmethodID methodId9 = (*env)->GetMethodID(env, localClass12, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/smoothstreaming/SsChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V");
(*env)->CallVoidMethod(env, v0_4, methodId9, v1_2,v2_1,v3_0,v4_0,v5_0);
//GOTO                |     |goto L10;
v0_1 = v0_4;

goto L10;
//LABEL               |  LL6:
L6: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/dash/DashMediaSource;
jobject v0_5 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DashMediaSource"));

//INVOKE_DIRECT       |     |TEMP=v7.buildDataSourceFactory(v2_1)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass13 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId10 = (*env)->GetMethodID(env, localClass13, "buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject TEMP7 = (*env)->CallObjectMethod(env, v7, methodId10, v2_1);
//MOVE_RESULT         |     |v2=TEMP7
v2_1 = TEMP7;
//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory;
jobject v3_1 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory"));

//IGET                |     |v1=v7.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass14 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId3 = (*env)->GetFieldID(env, localClass14, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject v1_3 = (*env)->GetObjectField(env, v7, fieldId3);

//INVOKE_DIRECT       |     |v3.<init>(v1_3)  //Lcom/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory;.<init>(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V
jclass localClass15 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory");
jmethodID methodId11 = (*env)->GetMethodID(env, localClass15, "<init>", "(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V");
(*env)->CallVoidMethod(env, v3_1, methodId11, v1_3);
//IGET                |     |v4=v7.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
jclass localClass16 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId4 = (*env)->GetFieldID(env, localClass16, "mainHandler", "Landroid/os/Handler;");
v4_0 = (*env)->GetObjectField(env, v7, fieldId4);

//IGET                |     |v5=v7.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass17 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId5 = (*env)->GetFieldID(env, localClass17, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
v5_0 = (*env)->GetObjectField(env, v7, fieldId5);

//MOVE                |     |v1 = v8
jobject v1_4 = v8;
//INVOKE_DIRECT       |     |v0.<init>(v1_4,v2_1,v3_1,v4_0,v5_0)  //Lcom/google/android/exoplayer2/source/dash/DashMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/dash/DashChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V
jclass localClass18 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DashMediaSource");
jmethodID methodId12 = (*env)->GetMethodID(env, localClass18, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/dash/DashChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V");
(*env)->CallVoidMethod(env, v0_5, methodId12, v1_4,v2_1,v3_1,v4_0,v5_0);
//GOTO                |     |goto L10;
v0_1 = v0_5;

goto L10;
//LABEL               |  LL7:
L7: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/hls/HlsMediaSource;
jobject v0_6 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/hls/HlsMediaSource"));

//IGET                |     |v1=v7.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass19 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId6 = (*env)->GetFieldID(env, localClass19, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject v1_5 = (*env)->GetObjectField(env, v7, fieldId6);

//IGET                |     |v2=v7.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
jclass localClass20 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId7 = (*env)->GetFieldID(env, localClass20, "mainHandler", "Landroid/os/Handler;");
jobject v2_2 = (*env)->GetObjectField(env, v7, fieldId7);

//IGET                |     |v3=v7.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass21 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId8 = (*env)->GetFieldID(env, localClass21, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
jobject v3_2 = (*env)->GetObjectField(env, v7, fieldId8);

//INVOKE_DIRECT       |     |v0.<init>(v8,v1_5,v2_2,v3_2)  //Lcom/google/android/exoplayer2/source/hls/HlsMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V
jclass localClass22 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/hls/HlsMediaSource");
jmethodID methodId13 = (*env)->GetMethodID(env, localClass22, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V");
(*env)->CallVoidMethod(env, v0_6, methodId13, v8,v1_5,v2_2,v3_2);
//GOTO                |     |goto L10;
v0_1 = v0_6;

goto L10;
//LABEL               |  LL8: line 434
L8: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/ExtractorMediaSource;
jobject v0_7 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/ExtractorMediaSource"));

//IGET                |     |v2=v7.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass23 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId9 = (*env)->GetFieldID(env, localClass23, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject v2_3 = (*env)->GetObjectField(env, v7, fieldId9);

//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/extractor/DefaultExtractorsFactory;
jobject v3_3 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/extractor/DefaultExtractorsFactory"));

//INVOKE_DIRECT       |     |v3.<init>()  //Lcom/google/android/exoplayer2/extractor/DefaultExtractorsFactory;.<init>()V
jclass localClass24 = (*env)->FindClass(env, "com/google/android/exoplayer2/extractor/DefaultExtractorsFactory");
jmethodID methodId14 = (*env)->GetMethodID(env, localClass24, "<init>", "()V");
(*env)->CallVoidMethod(env, v3_3, methodId14);
//IGET                |     |v4=v7.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
jclass localClass25 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId10 = (*env)->GetFieldID(env, localClass25, "mainHandler", "Landroid/os/Handler;");
v4_0 = (*env)->GetObjectField(env, v7, fieldId10);

//IGET                |     |v5=v7.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass26 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId11 = (*env)->GetFieldID(env, localClass26, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
v5_0 = (*env)->GetObjectField(env, v7, fieldId11);

//MOVE                |     |v1 = v8
jobject v1_6 = v8;
//INVOKE_DIRECT       |     |v0.<init>(v1_6,v2_3,v3_3,v4_0,v5_0)  //Lcom/google/android/exoplayer2/source/ExtractorMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/extractor/ExtractorsFactory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/ExtractorMediaSource$EventListener;)V
jclass localClass27 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/ExtractorMediaSource");
jmethodID methodId15 = (*env)->GetMethodID(env, localClass27, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/extractor/ExtractorsFactory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/ExtractorMediaSource$EventListener;)V");
(*env)->CallVoidMethod(env, v0_7, methodId15, v1_6,v2_3,v3_3,v4_0,v5_0);
//GOTO                |     |goto L10;
v0_1 = v0_7;

goto L10;
//LABEL               |  LL3:
L3: ;
}


//method:0003  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.initializePlayer()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_initializePlayer_39797(JNIEnv * env, jobject  v18)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> adaptiveTrackSelectionFactory // Lcom/google/android/exoplayer2/trackselection/TrackSelection$Factory; 
//LOCAL_VARIABLE LL2 ~ LL1 v3 -> drmSessionManager // Lcom/google/android/exoplayer2/drm/DrmSessionManager; 
//LOCAL_VARIABLE LL3 ~ LL1 v4 -> extensionRendererMode // I 
//LOCAL_VARIABLE LL4 ~ LL1 v10 -> preferExtensionDecoders // Z 
//LOCAL_VARIABLE LL5 ~ LL1 v11 -> renderersFactory // Lcom/google/android/exoplayer2/DefaultRenderersFactory; 
//LOCAL_VARIABLE LL6 ~ LL7 v5 -> haveResumePosition // Z 
//LOCAL_VARIABLE LL8 ~ LL7 v7 -> mediaSource // Lcom/google/android/exoplayer2/source/MediaSource; 
//LOCAL_VARIABLE LL9 ~ LL7 v8 -> mediaSources // Lcom/google/android/exoplayer2/source/MediaSource; 
//LOCAL_VARIABLE LL10 ~ LL7 v9 -> needNewPlayer // Z 
//LOCAL_VARIABLE LL11 ~ LL7 v12 -> uris // Landroid/net/Uri; 
//LOCAL_VARIABLE LL12 ~ LL13 v2 -> adaptiveTrackSelectionFactory // Lcom/google/android/exoplayer2/trackselection/TrackSelection$Factory; 
//LOCAL_VARIABLE LL12 ~ LL13 v3 -> drmSessionManager // Lcom/google/android/exoplayer2/drm/DrmSessionManager; 
//LOCAL_VARIABLE LL12 ~ LL13 v10 -> preferExtensionDecoders // Z 
//LOCAL_VARIABLE LL14 ~ LL15 v5 -> haveResumePosition // Z 
//LOCAL_VARIABLE LL16 ~ LL15 v6 -> intent // Landroid/content/Intent; 
//LOCAL_VARIABLE LL13 ~ LL15 v7 -> mediaSource // Lcom/google/android/exoplayer2/source/MediaSource; 
//LOCAL_VARIABLE LL13 ~ LL15 v8 -> mediaSources // Lcom/google/android/exoplayer2/source/MediaSource; 
//LOCAL_VARIABLE LL12 ~ LL15 v9 -> needNewPlayer // Z 
//LOCAL_VARIABLE LL13 ~ LL15 v12 -> uris // Landroid/net/Uri; 
//LOCAL_VARIABLE LL17 ~ LL15 v18 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LABEL               | LL17: line 246
L17: ;
//INVOKE_VIRTUAL      |     |TEMP=v18.getIntent()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.getIntent()Landroid/content/Intent;
jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "getIntent", "()Landroid/content/Intent;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v18, methodId0);
//MOVE_RESULT         |     |v6=TEMP0
jobject v6_0 = TEMP0;
//LABEL               | LL16: line 247
L16: ;
//MOVE                |     |v0 = v18
jobject v0_0 = v18;
//IGET                |     |v13=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId0 = (*env)->GetFieldID(env, localClass1, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
jobject v13_0 = (*env)->GetObjectField(env, v0_0, fieldId0);

//IF_NEZ              |     |if (v13 != 0) { goto L7; }
if (v13_0 != 0) { goto L7; }
//CONST               |     |v9=0x00000001  // int:1   float:0.000000
jint v9_0 = 0x00000001;
//LABEL               | LL10: line 248
L10: ;
//IF_EQZ              |     |if (v9 == 0) { goto L1; }
if (v9_0 == 0) { goto L1; }
//LABEL               | LL18: line 249
L18: ;
//NEW_INSTANCE        |     |v2=NEW Lcom/google/android/exoplayer2/trackselection/AdaptiveTrackSelection$Factory;
jobject v2_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/trackselection/AdaptiveTrackSelection$Factory"));

//SGET                |     |v13=com.google.android.exoplayer2.demo.PlayerActivity.BANDWIDTH_METER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.BANDWIDTH_METER Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;
jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId1 = (*env)->GetStaticFieldID(env, localClass2, "BANDWIDTH_METER", "Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;");
jobject v13_1 = (*env)->GetStaticObjectField(env, localClass2, fieldId1);
//INVOKE_DIRECT       |     |v2.<init>(v13_1)  //Lcom/google/android/exoplayer2/trackselection/AdaptiveTrackSelection$Factory;.<init>(Lcom/google/android/exoplayer2/upstream/BandwidthMeter;)V
jclass localClass3 = (*env)->FindClass(env, "com/google/android/exoplayer2/trackselection/AdaptiveTrackSelection$Factory");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass3, "<init>", "(Lcom/google/android/exoplayer2/upstream/BandwidthMeter;)V");
(*env)->CallVoidMethod(env, v2_0, methodId1, v13_1);
//LABEL               |  LL0: line 251
L0: ;
//NEW_INSTANCE        |     |v13=NEW Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;
jobject v13_2 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/trackselection/DefaultTrackSelector"));

//INVOKE_DIRECT       |     |v13.<init>(v2_0)  //Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;.<init>(Lcom/google/android/exoplayer2/trackselection/TrackSelection$Factory;)V
jclass localClass4 = (*env)->FindClass(env, "com/google/android/exoplayer2/trackselection/DefaultTrackSelector");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass4, "<init>", "(Lcom/google/android/exoplayer2/trackselection/TrackSelection$Factory;)V");
(*env)->CallVoidMethod(env, v13_2, methodId2, v2_0);
//MOVE                |     |v0 = v18
v0_0 = v18;
//IPUT                |     |v0.trackSelector=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelector Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;
jclass localClass5 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId2 = (*env)->GetFieldID(env, localClass5, "trackSelector", "Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;");
(*env)->SetObjectField(env, v0_0, fieldId2, v13_2);

//LABEL               | LL19: line 252
L19: ;
//NEW_INSTANCE        |     |v13=NEW Lcom/google/android/exoplayer2/demo/TrackSelectionHelper;
jobject v13_3 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/TrackSelectionHelper"));

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.trackSelector  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelector Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;
jclass localClass6 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId3 = (*env)->GetFieldID(env, localClass6, "trackSelector", "Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;");
jobject v14_0 = (*env)->GetObjectField(env, v0_0, fieldId3);

//INVOKE_DIRECT       |     |v13.<init>(v14_0,v2_0)  //Lcom/google/android/exoplayer2/demo/TrackSelectionHelper;.<init>(Lcom/google/android/exoplayer2/trackselection/MappingTrackSelector;Lcom/google/android/exoplayer2/trackselection/TrackSelection$Factory;)V
jclass localClass7 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/TrackSelectionHelper");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass7, "<init>", "(Lcom/google/android/exoplayer2/trackselection/MappingTrackSelector;Lcom/google/android/exoplayer2/trackselection/TrackSelection$Factory;)V");
(*env)->CallVoidMethod(env, v13_3, methodId3, v14_0,v2_0);
//MOVE                |     |v0 = v18
v0_0 = v18;
//IPUT                |     |v0.trackSelectionHelper=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelectionHelper Lcom/google/android/exoplayer2/demo/TrackSelectionHelper;
jclass localClass8 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId4 = (*env)->GetFieldID(env, localClass8, "trackSelectionHelper", "Lcom/google/android/exoplayer2/demo/TrackSelectionHelper;");
(*env)->SetObjectField(env, v0_0, fieldId4, v13_3);

//LABEL               | LL20: line 253
L20: ;
//CONST               |     |v13=0x00000000  // int:0   float:0.000000
v13_3 = 0x00000000;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IPUT                |     |v0.lastSeenTrackGroupArray=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.lastSeenTrackGroupArray Lcom/google/android/exoplayer2/source/TrackGroupArray;
jclass localClass9 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId5 = (*env)->GetFieldID(env, localClass9, "lastSeenTrackGroupArray", "Lcom/google/android/exoplayer2/source/TrackGroupArray;");
(*env)->SetObjectField(env, v0_0, fieldId5, v13_3);

//LABEL               | LL21: line 254
L21: ;
//NEW_INSTANCE        |     |v13=NEW Lcom/google/android/exoplayer2/demo/EventLogger;
jobject v13_4 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/EventLogger"));

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.trackSelector  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelector Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;
jclass localClass10 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId6 = (*env)->GetFieldID(env, localClass10, "trackSelector", "Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;");
v14_0 = (*env)->GetObjectField(env, v0_0, fieldId6);

//INVOKE_DIRECT       |     |v13.<init>(v14_0)  //Lcom/google/android/exoplayer2/demo/EventLogger;.<init>(Lcom/google/android/exoplayer2/trackselection/MappingTrackSelector;)V
jclass localClass11 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/EventLogger");
jmethodID methodId4 = (*env)->GetMethodID(env, localClass11, "<init>", "(Lcom/google/android/exoplayer2/trackselection/MappingTrackSelector;)V");
(*env)->CallVoidMethod(env, v13_4, methodId4, v14_0);
//MOVE                |     |v0 = v18
v0_0 = v18;
//IPUT                |     |v0.eventLogger=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass12 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId7 = (*env)->GetFieldID(env, localClass12, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
(*env)->SetObjectField(env, v0_0, fieldId7, v13_4);

//LABEL               | LL22: line 256
L22: ;
//CONST               |     |v3=0x00000000  // int:0   float:0.000000
jint v3_0 = 0x00000000;
//LABEL               |  LL2: line 258
L2: ;
//CONST_STRING        |     |v13="prefer_extension_decoders"
jstring v13_5 = (*env)->NewStringUTF(env, "prefer_extension_decoders");
//CONST               |     |v14=0x00000000  // int:0   float:0.000000
v14_0 = 0x00000000;
//INVOKE_VIRTUAL      |     |TEMP=v6.getBooleanExtra(v13_5,v14_0)  //Landroid/content/Intent;.getBooleanExtra(Ljava/lang/String;Z)Z
jclass localClass13 = (*env)->FindClass(env, "android/content/Intent");
jmethodID methodId5 = (*env)->GetMethodID(env, localClass13, "getBooleanExtra", "(Ljava/lang/String;Z)Z");
jboolean TEMP1 = (*env)->CallBooleanMethod(env, v6_0, methodId5, v13_5,v14_0);
//MOVE_RESULT         |     |v10=TEMP1
jboolean v10_0 = TEMP1;
//LABEL               |  LL4: line 260
L4: ;
//INVOKE_VIRTUAL      |     |TEMP=v18.getApplication()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.getApplication()Landroid/app/Application;
jclass localClass14 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId6 = (*env)->GetMethodID(env, localClass14, "getApplication", "()Landroid/app/Application;");
jobject TEMP2 = (*env)->CallObjectMethod(env, v18, methodId6);
//MOVE_RESULT         |     |v13=TEMP2
jobject v13_6 = TEMP2;
//CHECK_CAST          |     |v13=(com.google.android.exoplayer2.demo.DemoApplication) v13
//INVOKE_VIRTUAL      |     |TEMP=v13.useExtensionRenderers()  //Lcom/google/android/exoplayer2/demo/DemoApplication;.useExtensionRenderers()Z
jclass localClass15 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/DemoApplication");
jmethodID methodId7 = (*env)->GetMethodID(env, localClass15, "useExtensionRenderers", "()Z");
jboolean TEMP3 = (*env)->CallBooleanMethod(env, v13_6, methodId7);
//MOVE_RESULT         |     |v13=TEMP3
jboolean v13_7 = TEMP3;
//IF_EQZ              |     |if (v13 == 0) { goto L23; }
if (v13_7 == 0) { goto L23; }
//IF_EQZ              |     |if (v10 == 0) { goto L12; }
if (v10_0 == 0) { goto L12; }
//CONST               |     |v4=0x00000002  // int:2   float:0.000000
jint v4_0 = 0x00000002;
//LABEL               |  LL3: line 264
L3: ;
//NEW_INSTANCE        |     |v11=NEW Lcom/google/android/exoplayer2/DefaultRenderersFactory;
jobject v11_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/DefaultRenderersFactory"));

//MOVE                |     |v0 = v18
v0_0 = v18;
//INVOKE_DIRECT       |     |v11.<init>(v0_0,v3_0,v4_0)  //Lcom/google/android/exoplayer2/DefaultRenderersFactory;.<init>(Landroid/content/Context;Lcom/google/android/exoplayer2/drm/DrmSessionManager;I)V
jclass localClass16 = (*env)->FindClass(env, "com/google/android/exoplayer2/DefaultRenderersFactory");
jmethodID methodId8 = (*env)->GetMethodID(env, localClass16, "<init>", "(Landroid/content/Context;Lcom/google/android/exoplayer2/drm/DrmSessionManager;I)V");
(*env)->CallVoidMethod(env, v11_0, methodId8, v0_0,v3_0,v4_0);
//LABEL               |  LL5: line 267
L5: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.trackSelector  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelector Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;
jclass localClass17 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId8 = (*env)->GetFieldID(env, localClass17, "trackSelector", "Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;");
jobject v13_8 = (*env)->GetObjectField(env, v0_0, fieldId8);

//INVOKE_STATIC       |     |TEMP=com.google.android.exoplayer2.ExoPlayerFactory.newSimpleInstance(v11_0,v13_8)  //Lcom/google/android/exoplayer2/ExoPlayerFactory;.newSimpleInstance(Lcom/google/android/exoplayer2/RenderersFactory;Lcom/google/android/exoplayer2/trackselection/TrackSelector;)Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass18 = (*env)->FindClass(env, "com/google/android/exoplayer2/ExoPlayerFactory");
jmethodID methodId9 = (*env)->GetStaticMethodID(env, localClass18, "newSimpleInstance", "(Lcom/google/android/exoplayer2/RenderersFactory;Lcom/google/android/exoplayer2/trackselection/TrackSelector;)Lcom/google/android/exoplayer2/SimpleExoPlayer;");
jobject TEMP4 = (*env)->CallStaticObjectMethod(env, localClass18, methodId9, v11_0,v13_8);
//MOVE_RESULT         |     |v13=TEMP4
jobject v13_9 = TEMP4;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IPUT                |     |v0.player=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass19 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId9 = (*env)->GetFieldID(env, localClass19, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
(*env)->SetObjectField(env, v0_0, fieldId9, v13_9);

//LABEL               | LL24: line 268
L24: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass20 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId10 = (*env)->GetFieldID(env, localClass20, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
v13_9 = (*env)->GetObjectField(env, v0_0, fieldId10);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass21 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId11 = (*env)->GetFieldID(env, localClass21, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
jobject v14_1 = (*env)->GetObjectField(env, v0_0, fieldId11);

//INVOKE_VIRTUAL      |     |v13.addListener(v14_1)  //Lcom/google/android/exoplayer2/SimpleExoPlayer;.addListener(Lcom/google/android/exoplayer2/Player$EventListener;)V
jclass localClass22 = (*env)->FindClass(env, "com/google/android/exoplayer2/SimpleExoPlayer");
jmethodID methodId10 = (*env)->GetMethodID(env, localClass22, "addListener", "(Lcom/google/android/exoplayer2/Player$EventListener;)V");
(*env)->CallVoidMethod(env, v13_9, methodId10, v14_1);
//LABEL               | LL25: line 269
L25: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass23 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId12 = (*env)->GetFieldID(env, localClass23, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
v13_9 = (*env)->GetObjectField(env, v0_0, fieldId12);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass24 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId13 = (*env)->GetFieldID(env, localClass24, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
v14_1 = (*env)->GetObjectField(env, v0_0, fieldId13);

//INVOKE_VIRTUAL      |     |v13.setAudioDebugListener(v14_1)  //Lcom/google/android/exoplayer2/SimpleExoPlayer;.setAudioDebugListener(Lcom/google/android/exoplayer2/audio/AudioRendererEventListener;)V
jclass localClass25 = (*env)->FindClass(env, "com/google/android/exoplayer2/SimpleExoPlayer");
jmethodID methodId11 = (*env)->GetMethodID(env, localClass25, "setAudioDebugListener", "(Lcom/google/android/exoplayer2/audio/AudioRendererEventListener;)V");
(*env)->CallVoidMethod(env, v13_9, methodId11, v14_1);
//LABEL               | LL26: line 270
L26: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass26 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId14 = (*env)->GetFieldID(env, localClass26, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
v13_9 = (*env)->GetObjectField(env, v0_0, fieldId14);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass27 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId15 = (*env)->GetFieldID(env, localClass27, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
v14_1 = (*env)->GetObjectField(env, v0_0, fieldId15);

//INVOKE_VIRTUAL      |     |v13.setVideoDebugListener(v14_1)  //Lcom/google/android/exoplayer2/SimpleExoPlayer;.setVideoDebugListener(Lcom/google/android/exoplayer2/video/VideoRendererEventListener;)V
jclass localClass28 = (*env)->FindClass(env, "com/google/android/exoplayer2/SimpleExoPlayer");
jmethodID methodId12 = (*env)->GetMethodID(env, localClass28, "setVideoDebugListener", "(Lcom/google/android/exoplayer2/video/VideoRendererEventListener;)V");
(*env)->CallVoidMethod(env, v13_9, methodId12, v14_1);
//LABEL               | LL27: line 271
L27: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass29 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId16 = (*env)->GetFieldID(env, localClass29, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
v13_9 = (*env)->GetObjectField(env, v0_0, fieldId16);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
jclass localClass30 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId17 = (*env)->GetFieldID(env, localClass30, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
v14_1 = (*env)->GetObjectField(env, v0_0, fieldId17);

//INVOKE_VIRTUAL      |     |v13.setMetadataOutput(v14_1)  //Lcom/google/android/exoplayer2/SimpleExoPlayer;.setMetadataOutput(Lcom/google/android/exoplayer2/metadata/MetadataRenderer$Output;)V
jclass localClass31 = (*env)->FindClass(env, "com/google/android/exoplayer2/SimpleExoPlayer");
jmethodID methodId13 = (*env)->GetMethodID(env, localClass31, "setMetadataOutput", "(Lcom/google/android/exoplayer2/metadata/MetadataRenderer$Output;)V");
(*env)->CallVoidMethod(env, v13_9, methodId13, v14_1);
//LABEL               | LL28: line 273
L28: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.simpleExoPlayerView  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
jclass localClass32 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId18 = (*env)->GetFieldID(env, localClass32, "simpleExoPlayerView", "Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;");
jobject v13_10 = (*env)->GetObjectField(env, v0_0, fieldId18);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass33 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId19 = (*env)->GetFieldID(env, localClass33, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
jobject v14_2 = (*env)->GetObjectField(env, v0_0, fieldId19);

//INVOKE_VIRTUAL      |     |v13.setPlayer(v14_2)  //Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;.setPlayer(Lcom/google/android/exoplayer2/SimpleExoPlayer;)V
jclass localClass34 = (*env)->FindClass(env, "com/google/android/exoplayer2/ui/SimpleExoPlayerView");
jmethodID methodId14 = (*env)->GetMethodID(env, localClass34, "setPlayer", "(Lcom/google/android/exoplayer2/SimpleExoPlayer;)V");
(*env)->CallVoidMethod(env, v13_10, methodId14, v14_2);
//LABEL               | LL29: line 274
L29: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass35 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId20 = (*env)->GetFieldID(env, localClass35, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
jobject v13_11 = (*env)->GetObjectField(env, v0_0, fieldId20);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.shouldAutoPlay  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.shouldAutoPlay Z
jclass localClass36 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId21 = (*env)->GetFieldID(env, localClass36, "shouldAutoPlay", "Z");
jboolean v14_3 = (*env)->GetBooleanField(env, v0_0, fieldId21);

//INVOKE_VIRTUAL      |     |v13.setPlayWhenReady(v14_3)  //Lcom/google/android/exoplayer2/SimpleExoPlayer;.setPlayWhenReady(Z)V
jclass localClass37 = (*env)->FindClass(env, "com/google/android/exoplayer2/SimpleExoPlayer");
jmethodID methodId15 = (*env)->GetMethodID(env, localClass37, "setPlayWhenReady", "(Z)V");
(*env)->CallVoidMethod(env, v13_11, methodId15, v14_3);
//LABEL               | LL30: line 275
L30: ;
//NEW_INSTANCE        |     |v13=NEW Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;
jobject v13_12 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/ui/DebugTextViewHelper"));

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass38 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId22 = (*env)->GetFieldID(env, localClass38, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
jobject v14_4 = (*env)->GetObjectField(env, v0_0, fieldId22);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v15=v0.debugTextView  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugTextView Landroid/widget/TextView;
jclass localClass39 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId23 = (*env)->GetFieldID(env, localClass39, "debugTextView", "Landroid/widget/TextView;");
jobject v15_0 = (*env)->GetObjectField(env, v0_0, fieldId23);

//INVOKE_DIRECT       |     |v13.<init>(v14_4,v15_0)  //Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;.<init>(Lcom/google/android/exoplayer2/SimpleExoPlayer;Landroid/widget/TextView;)V
jclass localClass40 = (*env)->FindClass(env, "com/google/android/exoplayer2/ui/DebugTextViewHelper");
jmethodID methodId16 = (*env)->GetMethodID(env, localClass40, "<init>", "(Lcom/google/android/exoplayer2/SimpleExoPlayer;Landroid/widget/TextView;)V");
(*env)->CallVoidMethod(env, v13_12, methodId16, v14_4,v15_0);
//MOVE                |     |v0 = v18
v0_0 = v18;
//IPUT                |     |v0.debugViewHelper=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugViewHelper Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;
jclass localClass41 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId24 = (*env)->GetFieldID(env, localClass41, "debugViewHelper", "Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;");
(*env)->SetObjectField(env, v0_0, fieldId24, v13_12);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.debugViewHelper  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugViewHelper Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;
jclass localClass42 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId25 = (*env)->GetFieldID(env, localClass42, "debugViewHelper", "Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;");
v13_12 = (*env)->GetObjectField(env, v0_0, fieldId25);

//INVOKE_VIRTUAL      |     |v13.start()  //Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;.start()V
jclass localClass43 = (*env)->FindClass(env, "com/google/android/exoplayer2/ui/DebugTextViewHelper");
jmethodID methodId17 = (*env)->GetMethodID(env, localClass43, "start", "()V");
(*env)->CallVoidMethod(env, v13_12, methodId17);
//LABEL               |  LL1: line 279
L1: ;
//CONST_STRING        |     |v13="http://www.youtube.com/api/manifest/dash/id/3aa39fa2cc27967f/source/youtube?as=fmp4_audio_clear,fmp4_sd_hd_clear&sparams=ip,ipbits,expire,source,id,as&ip=0.0.0.0&ipbits=0&expire=19000000000&signature=A2716F75795F5D2AF0E88962FFCD10DB79384F29.84308FF04844498CE6FBCE4731507882B8307798&key=ik0"
jstring v13_13 = (*env)->NewStringUTF(env, "http://www.youtube.com/api/manifest/dash/id/3aa39fa2cc27967f/source/youtube?as=fmp4_audio_clear,fmp4_sd_hd_clear&sparams=ip,ipbits,expire,source,id,as&ip=0.0.0.0&ipbits=0&expire=19000000000&signature=A2716F75795F5D2AF0E88962FFCD10DB79384F29.84308FF04844498CE6FBCE4731507882B8307798&key=ik0");
//INVOKE_STATIC       |     |TEMP=android.net.Uri.parse(v13_13)  //Landroid/net/Uri;.parse(Ljava/lang/String;)Landroid/net/Uri;
jclass localClass44 = (*env)->FindClass(env, "android/net/Uri");
jmethodID methodId18 = (*env)->GetStaticMethodID(env, localClass44, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
jobject TEMP5 = (*env)->CallStaticObjectMethod(env, localClass44, methodId18, v13_13);
//MOVE_RESULT         |     |v12=TEMP5
jobject v12_0 = TEMP5;
//LABEL               | LL11: line 281
L11: ;
//CONST               |     |v13=0x00000000  // int:0   float:0.000000
v13_13 = 0x00000000;
//MOVE                |     |v0 = v18
v0_0 = v18;
//INVOKE_DIRECT       |     |TEMP=v0.buildMediaSource(v12_0,v13_13)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildMediaSource(Landroid/net/Uri;Ljava/lang/String;)Lcom/google/android/exoplayer2/source/MediaSource;
jclass localClass45 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId19 = (*env)->GetMethodID(env, localClass45, "buildMediaSource", "(Landroid/net/Uri;Ljava/lang/String;)Lcom/google/android/exoplayer2/source/MediaSource;");
jobject TEMP6 = (*env)->CallObjectMethod(env, v0_0, methodId19, v12_0,v13_13);
//MOVE_RESULT         |     |v8=TEMP6
jobject v8_0 = TEMP6;
//LABEL               |  LL9: line 283
L9: ;
//MOVE                |     |v7 = v8
jobject v7_0 = v8_0;
//LABEL               |  LL8: line 285
L8: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.resumeWindow  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.resumeWindow I
jclass localClass46 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId26 = (*env)->GetFieldID(env, localClass46, "resumeWindow", "I");
jint v13_14 = (*env)->GetIntField(env, v0_0, fieldId26);

//CONST               |     |v14=0xffffffff  // int:-1   float:NaN
jint v14_5 = 0xffffffff;
//IF_EQ               |     |if (v13 == v14) {  goto L13; }
if (v13_14 == v14_5) {  goto L13; }
//CONST               |     |v5=0x00000001  // int:1   float:0.000000
jint v5_0 = 0x00000001;
//LABEL               |  LL6: line 286
L6: ;
//IF_EQZ              |     |if (v5 == 0) { goto L31; }
if (v5_0 == 0) { goto L31; }
//LABEL               | LL32: line 287
L32: ;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v13=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass47 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId27 = (*env)->GetFieldID(env, localClass47, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
jobject v13_15 = (*env)->GetObjectField(env, v0_0, fieldId27);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v14=v0.resumeWindow  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.resumeWindow I
jclass localClass48 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId28 = (*env)->GetFieldID(env, localClass48, "resumeWindow", "I");
v14_5 = (*env)->GetIntField(env, v0_0, fieldId28);

//MOVE                |     |v0 = v18
v0_0 = v18;
//IGET                |     |v0=v0.resumePosition  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.resumePosition J
jclass localClass49 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId29 = (*env)->GetFieldID(env, localClass49, "resumePosition", "J");
jlong v0_1 = (*env)->GetLongField(env, v0_0, fieldId29);

//MOVE                |     |v16 = v0
jlong v16_0 = v0_1;
//MOVE                |     |v0 = v16
v0_1 = v16_0;
//INVOKE_VIRTUAL      |     |v13.seekTo(v14_5,v0_1)  //Lcom/google/android/exoplayer2/SimpleExoPlayer;.seekTo(IJ)V
jclass localClass50 = (*env)->FindClass(env, "com/google/android/exoplayer2/SimpleExoPlayer");
jmethodID methodId20 = (*env)->GetMethodID(env, localClass50, "seekTo", "(IJ)V");
(*env)->CallVoidMethod(env, v13_15, methodId20, v14_5,v0_1);
//LABEL               | LL31:
L31: ;
//MOVE                |     |v0 = v18
jobject v0_2 = v18;
//IGET                |     |v14=v0.player  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
jclass localClass51 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId30 = (*env)->GetFieldID(env, localClass51, "player", "Lcom/google/android/exoplayer2/SimpleExoPlayer;");
jobject v14_6 = (*env)->GetObjectField(env, v0_2, fieldId30);

//IF_NEZ              |     |if (v5 != 0) { goto L14; }
if (v5_0 != 0) { goto L14; }
//CONST               |     |v13=0x00000001  // int:1   float:0.000000
jint v13_16 = 0x00000001;
//LABEL               | LL33:
L33: ;
//CONST               |     |v15=0x00000000  // int:0   float:0.000000
v15_0 = 0x00000000;
//INVOKE_VIRTUAL      |     |v14.prepare(v7_0,v13_16,v15_0)  //Lcom/google/android/exoplayer2/SimpleExoPlayer;.prepare(Lcom/google/android/exoplayer2/source/MediaSource;ZZ)V
jclass localClass52 = (*env)->FindClass(env, "com/google/android/exoplayer2/SimpleExoPlayer");
jmethodID methodId21 = (*env)->GetMethodID(env, localClass52, "prepare", "(Lcom/google/android/exoplayer2/source/MediaSource;ZZ)V");
(*env)->CallVoidMethod(env, v14_6, methodId21, v7_0,v13_16,v15_0);
//LABEL               | LL34: line 290
L34: ;
//CONST               |     |v13=0x00000000  // int:0   float:0.000000
v13_16 = 0x00000000;
//MOVE                |     |v0 = v18
v0_2 = v18;
//IPUT                |     |v0.inErrorState=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.inErrorState Z
jclass localClass53 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId31 = (*env)->GetFieldID(env, localClass53, "inErrorState", "Z");
(*env)->SetBooleanField(env, v0_2, fieldId31, v13_16);

//LABEL               | LL35: line 291
L35: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL7: line 375
L7: ;
//CONST               |     |v9=0x00000000  // int:0   float:0.000000
v9_0 = 0x00000000;
//GOTO                |     |goto L10;
goto L10;
//LABEL               | LL12: line 388
L12: ;
//CONST               |     |v4=0x00000001  // int:1   float:0.000000
v4_0 = 0x00000001;
//GOTO                |     |goto L3;
goto L3;
//LABEL               | LL23:
L23: ;
//CONST               |     |v4=0x00000000  // int:0   float:0.000000
v4_0 = 0x00000000;
//GOTO                |     |goto L3;
goto L3;
//LABEL               | LL13: line 413
L13: ;
//CONST               |     |v5=0x00000000  // int:0   float:0.000000
v5_0 = 0x00000000;
//GOTO                |     |goto L6;
goto L6;
//LABEL               | LL14: line 417
L14: ;
//CONST               |     |v13=0x00000000  // int:0   float:0.000000
v13_16 = 0x00000000;
//GOTO                |     |goto L33;
goto L33;
//LABEL               | LL15:
L15: ;
}


//method:0004  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.showToast(I)V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast_1263150(JNIEnv * env, jobject  v1, jint v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> messageId // I 
//LABEL               |  LL0: line 320
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
//LABEL               |  LL2: line 321
L2: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0005  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.showToast(Ljava/lang/String;)V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast_1428966913(JNIEnv * env, jobject  v2, jstring v3)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL0 ~ LL1 v3 -> message // Ljava/lang/String; 
//LABEL               |  LL0: line 324
L0: ;
//INVOKE_VIRTUAL      |     |TEMP=v2.getApplicationContext()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.getApplicationContext()Landroid/content/Context;
jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "getApplicationContext", "()Landroid/content/Context;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v2, methodId0);
//MOVE_RESULT         |     |v0=TEMP0
jobject v0_0 = TEMP0;
//CONST               |     |v1=0x00000001  // int:1   float:0.000000
jint v1_0 = 0x00000001;
//INVOKE_STATIC       |     |TEMP=android.widget.Toast.makeText(v0_0,v3,v1_0)  //Landroid/widget/Toast;.makeText(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;
jclass localClass1 = (*env)->FindClass(env, "android/widget/Toast");
jmethodID methodId1 = (*env)->GetStaticMethodID(env, localClass1, "makeText", "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
jobject TEMP1 = (*env)->CallStaticObjectMethod(env, localClass1, methodId1, v0_0,v3,v1_0);
//MOVE_RESULT         |     |v0=TEMP1
jobject v0_1 = TEMP1;
//INVOKE_VIRTUAL      |     |v0.show()  //Landroid/widget/Toast;.show()V
jclass localClass2 = (*env)->FindClass(env, "android/widget/Toast");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "show", "()V");
(*env)->CallVoidMethod(env, v0_1, methodId2);
//LABEL               |  LL2: line 325
L2: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0006  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.sum2DIntArray(I)I
jint  Java_com_google_android_exoplayer2_demo_PlayerActivity_sum2DIntArray_1263137(JNIEnv * env, jobject  v7, jint v8)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> j // I 
//LOCAL_VARIABLE LL2 ~ LL3 v0 -> all // I 
//LOCAL_VARIABLE LL4 ~ LL3 v1 -> i // I 
//LOCAL_VARIABLE LL5 ~ LL3 v3 -> num // [[I 
//LOCAL_VARIABLE LL6 ~ LL3 v7 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL6 ~ LL3 v8 -> count // I 
//LABEL               |  LL6: line 194
L6: ;
//CONST               |     |v5=0x00000002  // int:2   float:0.000000
jint v5_0 = 0x00000002;
//CONST               |     |v6=0x00000000  // int:0   float:0.000000
jint v6_0 = 0x00000000;
//LABEL               |  LL7: line 194
L7: ;
//NEW_ARRAY           |     |v3=new int[][][v5]
//type :[[I XXX: Object  arrayType : [
jintArray v3_0 = (*env)->NewObjectArray(env, v5_0, (*env)->FindClass(env, "[I"), NULL);
//NEW_ARRAY           |     |v4=new int[][v5]
//type :[I XXX: Int  arrayType : I
jintArray v4_0 = (*env)->NewIntArray(env, v5_0);
//FILL_ARRAY_DATA     |     |v4[0..1]=[1,2]
jint ___values_v4_0[] = {1,2};
(*env)->SetIntArrayRegion(env, v4_0 , 0, 2, ___values_v4_0);
//APUT                |     |v3[v6]=v4;
//input sig: [I register sig: [I
//input sig: [I changed register sig: [I
(*env)->SetObjectArrayElement(env, v3_0, v6_0, v4_0);
//CONST               |     |v4=0x00000001  // int:1   float:0.000000
jint v4_1 = 0x00000001;
//NEW_ARRAY           |     |v5=new int[][v5]
//type :[I XXX: Int  arrayType : I
jintArray v5_1 = (*env)->NewIntArray(env, v5_0);
//FILL_ARRAY_DATA     |     |v5[0..1]=[3,4]
jint ___values_v5_1[] = {3,4};
(*env)->SetIntArrayRegion(env, v5_1 , 0, 2, ___values_v5_1);
//APUT                |     |v3[v4]=v5;
//input sig: [I register sig: [I
//input sig: [I changed register sig: [I
(*env)->SetObjectArrayElement(env, v3_0, v4_1, v5_1);
//LABEL               |  LL5:
L5: ;
//AGET                |     |v4=v3[v6];
//input sig: [I register sig: I
//input sig: [I changed register sig: [I
jobject v4_2 = (*env)->GetObjectArrayElement(env, v3_0, v6_0);
//CONST               |     |v5=0xfffffff7  // int:-9   float:NaN
jint v5_2 = 0xfffffff7;
//APUT                |     |v4[v6]=v5;
//input sig: I register sig: I
(*env)->SetIntArrayRegion(env, v4_2, v6_0, 1, &v5_2);
//LABEL               |  LL8: line 196
L8: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_0 = 0x00000000;
//LABEL               |  LL2: line 197
L2: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
jint v1_0 = 0x00000000;
//LABEL               |  LL4:
L4: ;
//ARRAY_LENGTH        |     |v4 = v3.length
jint v4_3 = (*env)->GetArrayLength(env, v3_0);
//IF_GE               |     |if (v1 >= v4) {  goto L1; }
if (v1_0 >= v4_3) {  goto L1; }
//LABEL               |  LL9: line 198
L9: ;
//CONST               |     |v2=0x00000000  // int:0   float:0.000000
jint v2_0 = 0x00000000;
//LABEL               |  LL0:
L0: ;
//AGET                |     |v4=v3[v6];
//input sig: [I register sig: I
//input sig: [I changed register sig: [I
jobject v4_4 = (*env)->GetObjectArrayElement(env, v3_0, v6_0);
//ARRAY_LENGTH        |     |v4 = v4.length
jint v4_5 = (*env)->GetArrayLength(env, v4_4);
//IF_GE               |     |if (v2 >= v4) {  goto L10; }
if (v2_0 >= v4_5) {  goto L10; }
//LABEL               | LL11: line 199
L11: ;
//AGET                |     |v4=v3[v1];
//input sig: [I register sig: I
//input sig: [I changed register sig: [I
jobject v4_6 = (*env)->GetObjectArrayElement(env, v3_0, v1_0);
//AGET                |     |v4=v4[v2];
//input sig: I register sig: [I
jint v4_7;
(*env)->GetIntArrayRegion(env, v4_6, v2_0, 1, &v4_7);
//ADD                 |     |v0 = v0 + v4;
v0_0 = v0_0 + v4_7;
//LABEL               | LL12: line 198
L12: ;
//ADD_INT_LIT_X       |     |v2 = v2 + 1;
v2_0 = v2_0 + 1;
//GOTO                |     |goto L0;
goto L0;
//LABEL               | LL10: line 197
L10: ;
//ADD_INT_LIT_X       |     |v1 = v1 + 1;
v1_0 = v1_0 + 1;
//GOTO                |     |goto L4;
goto L4;
//LABEL               |  LL1: line 202
L1: ;
//CONST_STRING        |     |v4="MediaCodecInfo"
jstring v4_8 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v5=NEW Ljava/lang/StringBuilder;
jobject v5_3 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v5.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v5_3, methodId0);
//CONST_STRING        |     |v6="sum2DIntArray : "
jstring v6_1 = (*env)->NewStringUTF(env, "sum2DIntArray : ");
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_1)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass1 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v5_3, methodId1, v6_1);
//MOVE_RESULT         |     |v5=TEMP0
v5_3 = TEMP0;
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v0_0)  //Ljava/lang/StringBuilder;.append(I)Ljava/lang/StringBuilder;
jclass localClass2 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "append", "(I)Ljava/lang/StringBuilder;");
jobject TEMP1 = (*env)->CallObjectMethod(env, v5_3, methodId2, v0_0);
//MOVE_RESULT         |     |v5=TEMP1
v5_3 = TEMP1;
//INVOKE_VIRTUAL      |     |TEMP=v5.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "toString", "()Ljava/lang/String;");
jstring TEMP2 =  (jstring) (*env)->CallObjectMethod(env, v5_3, methodId3);
//MOVE_RESULT         |     |v5=TEMP2
jstring v5_4 = TEMP2;
//INVOKE_STATIC       |     |TEMP=android.util.Log.e(v4_8,v5_4)  //Landroid/util/Log;.e(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass4 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId4 = (*env)->GetStaticMethodID(env, localClass4, "e", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP3 = (*env)->CallStaticIntMethod(env, localClass4, methodId4, v4_8,v5_4);
//RETURN              |     |return v0
return v0_0;
//LABEL               | LL13: line 322
L13: ;
//LABEL               |  LL3:
L3: ;
}


//method:0007  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumDoubleArray(I)D
jdouble  Java_com_google_android_exoplayer2_demo_PlayerActivity_sumDoubleArray_1263132(JNIEnv * env, jobject  v7, jint v8)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> all // D 
//LOCAL_VARIABLE LL2 ~ LL1 v2 -> i // I 
//LOCAL_VARIABLE LL3 ~ LL1 v3 -> num // [D 
//LOCAL_VARIABLE LL4 ~ LL1 v7 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL4 ~ LL1 v8 -> count // I 
//LABEL               |  LL4: line 217
L4: ;
//CONST               |     |v4=0x00000004  // int:4   float:0.000000
jint v4_0 = 0x00000004;
//NEW_ARRAY           |     |v3=new double[][v4]
//type :[D XXX: Double  arrayType : D
jdoubleArray v3_0 = (*env)->NewDoubleArray(env, v4_0);
//FILL_ARRAY_DATA     |     |v3[0..3]=[4607182418800017408,4611686018427387904,4613937818241073152,4616189618054758400]
jlong ___values_v3_0[] = {4607182418800017408,4611686018427387904,4613937818241073152,4616189618054758400};
(*env)->SetLongArrayRegion(env, v3_0 , 0, 4, ___values_v3_0);
//LABEL               |  LL3: line 218
L3: ;
//CONST               |     |v0=0x0000000000000000  // long:0   double:0.000000
jint v0_0 = 0x0000000000000000;
//LABEL               |  LL0: line 219
L0: ;
//CONST               |     |v2=0x00000000  // int:0   float:0.000000
jint v2_0 = 0x00000000;
//LABEL               |  LL2:
L2: ;
//ARRAY_LENGTH        |     |v4 = v3.length
v4_0 = (*env)->GetArrayLength(env, v3_0);
//IF_GE               |     |if (v2 >= v4) {  goto L5; }
if (v2_0 >= v4_0) {  goto L5; }
//LABEL               |  LL6: line 220
L6: ;
//AGET                |     |v4=v3[v2];
//input sig: D register sig: I
jdouble v4_1;
(*env)->GetDoubleArrayRegion(env, v3_0, v2_0, 1, &v4_1);
//ADD                 |     |v0 = v0 + v4;
v0_0 = v0_0 + v4_1;
//LABEL               |  LL7: line 219
L7: ;
//ADD_INT_LIT_X       |     |v2 = v2 + 1;
v2_0 = v2_0 + 1;
//GOTO                |     |goto L2;
goto L2;
//LABEL               |  LL5: line 222
L5: ;
//CONST_STRING        |     |v4="MediaCodecInfo"
jstring v4_2 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v5=NEW Ljava/lang/StringBuilder;
jobject v5_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v5.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v5_0, methodId0);
//CONST_STRING        |     |v6="sumDoubleArray : "
jstring v6_0 = (*env)->NewStringUTF(env, "sumDoubleArray : ");
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass1 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v5_0, methodId1, v6_0);
//MOVE_RESULT         |     |v5=TEMP0
v5_0 = TEMP0;
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v0_0)  //Ljava/lang/StringBuilder;.append(D)Ljava/lang/StringBuilder;
jclass localClass2 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "append", "(D)Ljava/lang/StringBuilder;");
jobject TEMP1 = (*env)->CallObjectMethod(env, v5_0, methodId2, v0_0);
//MOVE_RESULT         |     |v5=TEMP1
v5_0 = TEMP1;
//INVOKE_VIRTUAL      |     |TEMP=v5.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "toString", "()Ljava/lang/String;");
jstring TEMP2 =  (jstring) (*env)->CallObjectMethod(env, v5_0, methodId3);
//MOVE_RESULT         |     |v5=TEMP2
jstring v5_1 = TEMP2;
//INVOKE_STATIC       |     |TEMP=android.util.Log.e(v4_2,v5_1)  //Landroid/util/Log;.e(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass4 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId4 = (*env)->GetStaticMethodID(env, localClass4, "e", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP3 = (*env)->CallStaticIntMethod(env, localClass4, methodId4, v4_2,v5_1);
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL8: line 345
L8: ;
//LABEL               |  LL1:
L1: ;
}


//method:0008  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumIntArray(I)I
jint  Java_com_google_android_exoplayer2_demo_PlayerActivity_sumIntArray_1263137(JNIEnv * env, jobject  v6, jint v7)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> all // I 
//LOCAL_VARIABLE LL2 ~ LL1 v1 -> i // I 
//LOCAL_VARIABLE LL3 ~ LL1 v2 -> num // [I 
//LOCAL_VARIABLE LL4 ~ LL1 v6 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL4 ~ LL1 v7 -> count // I 
//LABEL               |  LL4: line 183
L4: ;
//CONST               |     |v3=0x00000003  // int:3   float:0.000000
jint v3_0 = 0x00000003;
//NEW_ARRAY           |     |v2=new int[][v3]
//type :[I XXX: Int  arrayType : I
jintArray v2_0 = (*env)->NewIntArray(env, v3_0);
//FILL_ARRAY_DATA     |     |v2[0..2]=[1,2,3]
jint ___values_v2_0[] = {1,2,3};
(*env)->SetIntArrayRegion(env, v2_0 , 0, 3, ___values_v2_0);
//LABEL               |  LL3: line 184
L3: ;
//CONST               |     |v3=0x00000000  // int:0   float:0.000000
v3_0 = 0x00000000;
//CONST               |     |v4=0xfffffffb  // int:-5   float:NaN
jint v4_0 = 0xfffffffb;
//APUT                |     |v2[v3]=v4;
//input sig: I register sig: I
(*env)->SetIntArrayRegion(env, v2_0, v3_0, 1, &v4_0);
//LABEL               |  LL5: line 185
L5: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_0 = 0x00000000;
//LABEL               |  LL0: line 186
L0: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
jint v1_0 = 0x00000000;
//LABEL               |  LL2:
L2: ;
//ARRAY_LENGTH        |     |v3 = v2.length
v3_0 = (*env)->GetArrayLength(env, v2_0);
//IF_GE               |     |if (v1 >= v3) {  goto L6; }
if (v1_0 >= v3_0) {  goto L6; }
//LABEL               |  LL7: line 187
L7: ;
//AGET                |     |v3=v2[v1];
//input sig: I register sig: I
(*env)->GetIntArrayRegion(env, v2_0, v1_0, 1, &v3_0);
//ADD                 |     |v0 = v0 + v3;
v0_0 = v0_0 + v3_0;
//LABEL               |  LL8: line 186
L8: ;
//ADD_INT_LIT_X       |     |v1 = v1 + 1;
v1_0 = v1_0 + 1;
//GOTO                |     |goto L2;
goto L2;
//LABEL               |  LL6: line 189
L6: ;
//CONST_STRING        |     |v3="MediaCodecInfo"
jstring v3_1 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v4=NEW Ljava/lang/StringBuilder;
jobject v4_1 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v4.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v4_1, methodId0);
//CONST_STRING        |     |v5="sumArray : "
jstring v5_0 = (*env)->NewStringUTF(env, "sumArray : ");
//INVOKE_VIRTUAL      |     |TEMP=v4.append(v5_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass1 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v4_1, methodId1, v5_0);
//MOVE_RESULT         |     |v4=TEMP0
v4_1 = TEMP0;
//INVOKE_VIRTUAL      |     |TEMP=v4.append(v0_0)  //Ljava/lang/StringBuilder;.append(I)Ljava/lang/StringBuilder;
jclass localClass2 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "append", "(I)Ljava/lang/StringBuilder;");
jobject TEMP1 = (*env)->CallObjectMethod(env, v4_1, methodId2, v0_0);
//MOVE_RESULT         |     |v4=TEMP1
v4_1 = TEMP1;
//INVOKE_VIRTUAL      |     |TEMP=v4.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "toString", "()Ljava/lang/String;");
jstring TEMP2 =  (jstring) (*env)->CallObjectMethod(env, v4_1, methodId3);
//MOVE_RESULT         |     |v4=TEMP2
jstring v4_2 = TEMP2;
//INVOKE_STATIC       |     |TEMP=android.util.Log.e(v3_1,v4_2)  //Landroid/util/Log;.e(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass4 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId4 = (*env)->GetStaticMethodID(env, localClass4, "e", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP3 = (*env)->CallStaticIntMethod(env, localClass4, methodId4, v3_1,v4_2);
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL9: line 311
L9: ;
//LABEL               |  LL1:
L1: ;
}


//method:0009  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumLongArray(I)J
jlong  Java_com_google_android_exoplayer2_demo_PlayerActivity_sumLongArray_1263138(JNIEnv * env, jobject  v7, jint v8)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> all // J 
//LOCAL_VARIABLE LL2 ~ LL1 v2 -> i // I 
//LOCAL_VARIABLE LL3 ~ LL1 v3 -> num // [I 
//LOCAL_VARIABLE LL4 ~ LL1 v7 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL4 ~ LL1 v8 -> count // I 
//LABEL               |  LL4: line 207
L4: ;
//CONST               |     |v4=0x00000004  // int:4   float:0.000000
jint v4_0 = 0x00000004;
//NEW_ARRAY           |     |v3=new int[][v4]
//type :[I XXX: Int  arrayType : I
jintArray v3_0 = (*env)->NewIntArray(env, v4_0);
//FILL_ARRAY_DATA     |     |v3[0..3]=[1,2,3,4]
jint ___values_v3_0[] = {1,2,3,4};
(*env)->SetIntArrayRegion(env, v3_0 , 0, 4, ___values_v3_0);
//LABEL               |  LL3: line 208
L3: ;
//CONST               |     |v0=0x0000000000000000  // long:0   double:0.000000
jint v0_0 = 0x0000000000000000;
//LABEL               |  LL0: line 209
L0: ;
//CONST               |     |v2=0x00000000  // int:0   float:0.000000
jint v2_0 = 0x00000000;
//LABEL               |  LL2:
L2: ;
//ARRAY_LENGTH        |     |v4 = v3.length
v4_0 = (*env)->GetArrayLength(env, v3_0);
//IF_GE               |     |if (v2 >= v4) {  goto L5; }
if (v2_0 >= v4_0) {  goto L5; }
//LABEL               |  LL6: line 210
L6: ;
//AGET                |     |v4=v3[v2];
//input sig: I register sig: I
(*env)->GetIntArrayRegion(env, v3_0, v2_0, 1, &v4_0);
//X_TO_Y              |     |v4 = (long)v4
jlong v4_1 = (long) v4_0;
//ADD                 |     |v0 = v0 + v4;
v0_0 = v0_0 + v4_1;
//LABEL               |  LL7: line 209
L7: ;
//ADD_INT_LIT_X       |     |v2 = v2 + 1;
v2_0 = v2_0 + 1;
//GOTO                |     |goto L2;
goto L2;
//LABEL               |  LL5: line 212
L5: ;
//CONST_STRING        |     |v4="MediaCodecInfo"
jstring v4_2 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v5=NEW Ljava/lang/StringBuilder;
jobject v5_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v5.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v5_0, methodId0);
//CONST_STRING        |     |v6="sumArray : "
jstring v6_0 = (*env)->NewStringUTF(env, "sumArray : ");
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass1 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v5_0, methodId1, v6_0);
//MOVE_RESULT         |     |v5=TEMP0
v5_0 = TEMP0;
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v0_0)  //Ljava/lang/StringBuilder;.append(J)Ljava/lang/StringBuilder;
jclass localClass2 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "append", "(J)Ljava/lang/StringBuilder;");
jobject TEMP1 = (*env)->CallObjectMethod(env, v5_0, methodId2, v0_0);
//MOVE_RESULT         |     |v5=TEMP1
v5_0 = TEMP1;
//INVOKE_VIRTUAL      |     |TEMP=v5.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "toString", "()Ljava/lang/String;");
jstring TEMP2 =  (jstring) (*env)->CallObjectMethod(env, v5_0, methodId3);
//MOVE_RESULT         |     |v5=TEMP2
jstring v5_1 = TEMP2;
//INVOKE_STATIC       |     |TEMP=android.util.Log.e(v4_2,v5_1)  //Landroid/util/Log;.e(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass4 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId4 = (*env)->GetStaticMethodID(env, localClass4, "e", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP3 = (*env)->CallStaticIntMethod(env, localClass4, methodId4, v4_2,v5_1);
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL8: line 335
L8: ;
//LABEL               |  LL1:
L1: ;
}


//method:0010  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumNumber(I)I
jint  Java_com_google_android_exoplayer2_demo_PlayerActivity_sumNumber_1263137(JNIEnv * env, jobject  v2, jint v3)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> i // I 
//LOCAL_VARIABLE LL2 ~ LL1 v1 -> sum // I 
//LOCAL_VARIABLE LL3 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL3 ~ LL1 v3 -> count // I 
//LABEL               |  LL3: line 174
L3: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
jint v1_0 = 0x00000000;
//LABEL               |  LL2: line 176
L2: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_0 = 0x00000000;
//LABEL               |  LL0:
L0: ;
//IF_GT               |     |if (v0 >  v3) {  goto L4; }
if (v0_0 > v3) {  goto L4; }
//LABEL               |  LL5: line 177
L5: ;
//ADD                 |     |v1 = v1 + v0;
v1_0 = v1_0 + v0_0;
//LABEL               |  LL6: line 176
L6: ;
//ADD_INT_LIT_X       |     |v0 = v0 + 1;
v0_0 = v0_0 + 1;
//GOTO                |     |goto L0;
goto L0;
//LABEL               |  LL4: line 179
L4: ;
//RETURN              |     |return v1
return v1_0;
//LABEL               |  LL1:
L1: ;
}


//method:0011  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumStringArray(I)Ljava/lang/String;
jstring  Java_com_google_android_exoplayer2_demo_PlayerActivity_sumStringArray_1200754738(JNIEnv * env, jobject  v6, jint v7)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> all // Ljava/lang/String; 
//LOCAL_VARIABLE LL2 ~ LL1 v1 -> i // I 
//LOCAL_VARIABLE LL3 ~ LL1 v2 -> num // [Ljava/lang/String; 
//LOCAL_VARIABLE LL4 ~ LL1 v6 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL4 ~ LL1 v7 -> count // I 
//LABEL               |  LL4: line 228
L4: ;
//CONST               |     |v3=0x00000003  // int:3   float:0.000000
jint v3_0 = 0x00000003;
//NEW_ARRAY           |     |v2=new java.lang.String[][v3]
//type :[Ljava/lang/String; XXX: Object  arrayType : L
jobjectArray v2_0 = (*env)->NewObjectArray(env, v3_0, (*env)->FindClass(env, "java/lang/String"), NULL);
//CONST               |     |v3=0x00000000  // int:0   float:0.000000
v3_0 = 0x00000000;
//CONST_STRING        |     |v4="a"
jstring v4_0 = (*env)->NewStringUTF(env, "a");
//APUT                |     |v2[v3]=v4;
//input sig: Ljava/lang/String; register sig: Ljava/lang/String;
//input sig: Ljava/lang/String; changed register sig: Ljava/lang/String;
(*env)->SetObjectArrayElement(env, v2_0, v3_0, v4_0);
//CONST               |     |v3=0x00000001  // int:1   float:0.000000
v3_0 = 0x00000001;
//CONST_STRING        |     |v4="b"
v4_0 = (*env)->NewStringUTF(env, "b");
//APUT                |     |v2[v3]=v4;
//input sig: Ljava/lang/String; register sig: Ljava/lang/String;
//input sig: Ljava/lang/String; changed register sig: Ljava/lang/String;
(*env)->SetObjectArrayElement(env, v2_0, v3_0, v4_0);
//CONST               |     |v3=0x00000002  // int:2   float:0.000000
v3_0 = 0x00000002;
//CONST_STRING        |     |v4="c"
v4_0 = (*env)->NewStringUTF(env, "c");
//APUT                |     |v2[v3]=v4;
//input sig: Ljava/lang/String; register sig: Ljava/lang/String;
//input sig: Ljava/lang/String; changed register sig: Ljava/lang/String;
(*env)->SetObjectArrayElement(env, v2_0, v3_0, v4_0);
//LABEL               |  LL3:
L3: ;
//CONST_STRING        |     |v0="hello "
jstring v0_0 = (*env)->NewStringUTF(env, "hello ");
//LABEL               |  LL0: line 230
L0: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
jint v1_0 = 0x00000000;
//LABEL               |  LL2:
L2: ;
//ARRAY_LENGTH        |     |v3 = v2.length
v3_0 = (*env)->GetArrayLength(env, v2_0);
//IF_GE               |     |if (v1 >= v3) {  goto L5; }
if (v1_0 >= v3_0) {  goto L5; }
//LABEL               |  LL6: line 231
L6: ;
//NEW_INSTANCE        |     |v3=NEW Ljava/lang/StringBuilder;
jobject v3_1 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v3.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v3_1, methodId0);
//INVOKE_VIRTUAL      |     |TEMP=v3.append(v0_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass1 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v3_1, methodId1, v0_0);
//MOVE_RESULT         |     |v3=TEMP0
v3_1 = TEMP0;
//AGET                |     |v4=v2[v1];
//input sig: Ljava/lang/String; register sig: Ljava/lang/String;
//input sig: Ljava/lang/String; changed register sig: Ljava/lang/String;
v4_0 = (*env)->GetObjectArrayElement(env, v2_0, v1_0);
//INVOKE_VIRTUAL      |     |TEMP=v3.append(v4_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass2 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP1 = (*env)->CallObjectMethod(env, v3_1, methodId2, v4_0);
//MOVE_RESULT         |     |v3=TEMP1
v3_1 = TEMP1;
//INVOKE_VIRTUAL      |     |TEMP=v3.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass3 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "toString", "()Ljava/lang/String;");
jstring TEMP2 =  (jstring) (*env)->CallObjectMethod(env, v3_1, methodId3);
//MOVE_RESULT         |     |v0=TEMP2
v0_0 = TEMP2;
//ADD_INT_LIT_X       |     |v1 = v1 + 1;
v1_0 = v1_0 + 1;
//GOTO                |     |goto L2;
goto L2;
//LABEL               |  LL5: line 233
L5: ;
//CONST_STRING        |     |v3="MediaCodecInfo"
jstring v3_2 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v4=NEW Ljava/lang/StringBuilder;
jobject v4_1 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v4.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass4 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId4 = (*env)->GetMethodID(env, localClass4, "<init>", "()V");
(*env)->CallVoidMethod(env, v4_1, methodId4);
//CONST_STRING        |     |v5="sumArray : "
jstring v5_0 = (*env)->NewStringUTF(env, "sumArray : ");
//INVOKE_VIRTUAL      |     |TEMP=v4.append(v5_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass5 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId5 = (*env)->GetMethodID(env, localClass5, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP3 = (*env)->CallObjectMethod(env, v4_1, methodId5, v5_0);
//MOVE_RESULT         |     |v4=TEMP3
v4_1 = TEMP3;
//INVOKE_VIRTUAL      |     |TEMP=v4.append(v0_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass6 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId6 = (*env)->GetMethodID(env, localClass6, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP4 = (*env)->CallObjectMethod(env, v4_1, methodId6, v0_0);
//MOVE_RESULT         |     |v4=TEMP4
v4_1 = TEMP4;
//INVOKE_VIRTUAL      |     |TEMP=v4.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass7 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId7 = (*env)->GetMethodID(env, localClass7, "toString", "()Ljava/lang/String;");
jstring TEMP5 =  (jstring) (*env)->CallObjectMethod(env, v4_1, methodId7);
//MOVE_RESULT         |     |v4=TEMP5
jstring v4_2 = TEMP5;
//INVOKE_STATIC       |     |TEMP=android.util.Log.e(v3_2,v4_2)  //Landroid/util/Log;.e(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass8 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId8 = (*env)->GetStaticMethodID(env, localClass8, "e", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP6 = (*env)->CallStaticIntMethod(env, localClass8, methodId8, v3_2,v4_2);
//RETURN              |     |return v0
return v0_0;
//LABEL               |  LL1:
L1: ;
}


//method:0012  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.testABCD()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_testABCD_39797(JNIEnv * env, jobject  v8)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> a1 // Lcom/google/android/exoplayer2/demo/A; 
//LOCAL_VARIABLE LL2 ~ LL1 v1 -> a2 // Lcom/google/android/exoplayer2/demo/A; 
//LOCAL_VARIABLE LL3 ~ LL1 v2 -> b // Lcom/google/android/exoplayer2/demo/B; 
//LOCAL_VARIABLE LL4 ~ LL1 v3 -> c // Lcom/google/android/exoplayer2/demo/CC; 
//LOCAL_VARIABLE LL5 ~ LL1 v4 -> d // Lcom/google/android/exoplayer2/demo/D; 
//LOCAL_VARIABLE LL6 ~ LL1 v8 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LABEL               |  LL6: line 156
L6: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/demo/A;
jobject v0_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A"));

//INVOKE_DIRECT       |     |v0.<init>()  //Lcom/google/android/exoplayer2/demo/A;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v0_0, methodId0);
//LABEL               |  LL0: line 157
L0: ;
//NEW_INSTANCE        |     |v1=NEW Lcom/google/android/exoplayer2/demo/B;
jobject v1_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/B"));

//INVOKE_DIRECT       |     |v1.<init>()  //Lcom/google/android/exoplayer2/demo/B;.<init>()V
jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/B");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "<init>", "()V");
(*env)->CallVoidMethod(env, v1_0, methodId1);
//LABEL               |  LL2: line 158
L2: ;
//NEW_INSTANCE        |     |v2=NEW Lcom/google/android/exoplayer2/demo/B;
jobject v2_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/B"));

//INVOKE_DIRECT       |     |v2.<init>()  //Lcom/google/android/exoplayer2/demo/B;.<init>()V
jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/B");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "<init>", "()V");
(*env)->CallVoidMethod(env, v2_0, methodId2);
//LABEL               |  LL3: line 159
L3: ;
//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/demo/CC;
jobject v3_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/CC"));

//INVOKE_DIRECT       |     |v3.<init>()  //Lcom/google/android/exoplayer2/demo/CC;.<init>()V
jclass localClass3 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/CC");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "<init>", "()V");
(*env)->CallVoidMethod(env, v3_0, methodId3);
//LABEL               |  LL4: line 160
L4: ;
//NEW_INSTANCE        |     |v4=NEW Lcom/google/android/exoplayer2/demo/D;
jobject v4_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/D"));

//INVOKE_DIRECT       |     |v4.<init>()  //Lcom/google/android/exoplayer2/demo/D;.<init>()V
jclass localClass4 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/D");
jmethodID methodId4 = (*env)->GetMethodID(env, localClass4, "<init>", "()V");
(*env)->CallVoidMethod(env, v4_0, methodId4);
//LABEL               |  LL5: line 162
L5: ;
//CONST_STRING        |     |v5="MediaCodecInfo"
jstring v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass5 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId5 = (*env)->GetMethodID(env, localClass5, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_0, methodId5);
//CONST_STRING        |     |v7="1--"
jstring v7_0 = (*env)->NewStringUTF(env, "1--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass6 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId6 = (*env)->GetMethodID(env, localClass6, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v6_0, methodId6, v7_0);
//MOVE_RESULT         |     |v6=TEMP0
v6_0 = TEMP0;
//INVOKE_VIRTUAL      |     |TEMP=v0.show(v2_0)  //Lcom/google/android/exoplayer2/demo/A;.show(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;
jclass localClass7 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A");
jmethodID methodId7 = (*env)->GetMethodID(env, localClass7, "show", "(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;");
jstring TEMP1 =  (jstring) (*env)->CallObjectMethod(env, v0_0, methodId7, v2_0);
//MOVE_RESULT         |     |v7=TEMP1
v7_0 = TEMP1;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass8 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId8 = (*env)->GetMethodID(env, localClass8, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP2 = (*env)->CallObjectMethod(env, v6_0, methodId8, v7_0);
//MOVE_RESULT         |     |v6=TEMP2
v6_0 = TEMP2;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass9 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId9 = (*env)->GetMethodID(env, localClass9, "toString", "()Ljava/lang/String;");
jstring TEMP3 =  (jstring) (*env)->CallObjectMethod(env, v6_0, methodId9);
//MOVE_RESULT         |     |v6=TEMP3
jstring v6_1 = TEMP3;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_1)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass10 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId10 = (*env)->GetStaticMethodID(env, localClass10, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP4 = (*env)->CallStaticIntMethod(env, localClass10, methodId10, v5_0,v6_1);
//CONST_STRING        |     |v5="MediaCodecInfo"
v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_2 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass11 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId11 = (*env)->GetMethodID(env, localClass11, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_2, methodId11);
//CONST_STRING        |     |v7="2--"
v7_0 = (*env)->NewStringUTF(env, "2--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass12 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId12 = (*env)->GetMethodID(env, localClass12, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP5 = (*env)->CallObjectMethod(env, v6_2, methodId12, v7_0);
//MOVE_RESULT         |     |v6=TEMP5
v6_2 = TEMP5;
//INVOKE_VIRTUAL      |     |TEMP=v0.show(v3_0)  //Lcom/google/android/exoplayer2/demo/A;.show(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;
jclass localClass13 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A");
jmethodID methodId13 = (*env)->GetMethodID(env, localClass13, "show", "(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;");
jstring TEMP6 =  (jstring) (*env)->CallObjectMethod(env, v0_0, methodId13, v3_0);
//MOVE_RESULT         |     |v7=TEMP6
v7_0 = TEMP6;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass14 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId14 = (*env)->GetMethodID(env, localClass14, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP7 = (*env)->CallObjectMethod(env, v6_2, methodId14, v7_0);
//MOVE_RESULT         |     |v6=TEMP7
v6_2 = TEMP7;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass15 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId15 = (*env)->GetMethodID(env, localClass15, "toString", "()Ljava/lang/String;");
jstring TEMP8 =  (jstring) (*env)->CallObjectMethod(env, v6_2, methodId15);
//MOVE_RESULT         |     |v6=TEMP8
jstring v6_3 = TEMP8;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_3)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass16 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId16 = (*env)->GetStaticMethodID(env, localClass16, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP9 = (*env)->CallStaticIntMethod(env, localClass16, methodId16, v5_0,v6_3);
//CONST_STRING        |     |v5="MediaCodecInfo"
v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_4 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass17 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId17 = (*env)->GetMethodID(env, localClass17, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_4, methodId17);
//CONST_STRING        |     |v7="3--"
v7_0 = (*env)->NewStringUTF(env, "3--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass18 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId18 = (*env)->GetMethodID(env, localClass18, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP10 = (*env)->CallObjectMethod(env, v6_4, methodId18, v7_0);
//MOVE_RESULT         |     |v6=TEMP10
v6_4 = TEMP10;
//INVOKE_VIRTUAL      |     |TEMP=v0.show(v4_0)  //Lcom/google/android/exoplayer2/demo/A;.show(Lcom/google/android/exoplayer2/demo/D;)Ljava/lang/String;
jclass localClass19 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A");
jmethodID methodId19 = (*env)->GetMethodID(env, localClass19, "show", "(Lcom/google/android/exoplayer2/demo/D;)Ljava/lang/String;");
jstring TEMP11 =  (jstring) (*env)->CallObjectMethod(env, v0_0, methodId19, v4_0);
//MOVE_RESULT         |     |v7=TEMP11
v7_0 = TEMP11;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass20 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId20 = (*env)->GetMethodID(env, localClass20, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP12 = (*env)->CallObjectMethod(env, v6_4, methodId20, v7_0);
//MOVE_RESULT         |     |v6=TEMP12
v6_4 = TEMP12;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass21 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId21 = (*env)->GetMethodID(env, localClass21, "toString", "()Ljava/lang/String;");
jstring TEMP13 =  (jstring) (*env)->CallObjectMethod(env, v6_4, methodId21);
//MOVE_RESULT         |     |v6=TEMP13
jstring v6_5 = TEMP13;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_5)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass22 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId22 = (*env)->GetStaticMethodID(env, localClass22, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP14 = (*env)->CallStaticIntMethod(env, localClass22, methodId22, v5_0,v6_5);
//CONST_STRING        |     |v5="MediaCodecInfo"
v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_6 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass23 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId23 = (*env)->GetMethodID(env, localClass23, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_6, methodId23);
//CONST_STRING        |     |v7="4--"
v7_0 = (*env)->NewStringUTF(env, "4--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass24 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId24 = (*env)->GetMethodID(env, localClass24, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP15 = (*env)->CallObjectMethod(env, v6_6, methodId24, v7_0);
//MOVE_RESULT         |     |v6=TEMP15
v6_6 = TEMP15;
//INVOKE_VIRTUAL      |     |TEMP=v1.show(v2_0)  //Lcom/google/android/exoplayer2/demo/A;.show(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;
jclass localClass25 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A");
jmethodID methodId25 = (*env)->GetMethodID(env, localClass25, "show", "(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;");
jstring TEMP16 =  (jstring) (*env)->CallObjectMethod(env, v1_0, methodId25, v2_0);
//MOVE_RESULT         |     |v7=TEMP16
v7_0 = TEMP16;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass26 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId26 = (*env)->GetMethodID(env, localClass26, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP17 = (*env)->CallObjectMethod(env, v6_6, methodId26, v7_0);
//MOVE_RESULT         |     |v6=TEMP17
v6_6 = TEMP17;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass27 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId27 = (*env)->GetMethodID(env, localClass27, "toString", "()Ljava/lang/String;");
jstring TEMP18 =  (jstring) (*env)->CallObjectMethod(env, v6_6, methodId27);
//MOVE_RESULT         |     |v6=TEMP18
jstring v6_7 = TEMP18;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_7)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass28 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId28 = (*env)->GetStaticMethodID(env, localClass28, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP19 = (*env)->CallStaticIntMethod(env, localClass28, methodId28, v5_0,v6_7);
//CONST_STRING        |     |v5="MediaCodecInfo"
v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_8 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass29 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId29 = (*env)->GetMethodID(env, localClass29, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_8, methodId29);
//CONST_STRING        |     |v7="5--"
v7_0 = (*env)->NewStringUTF(env, "5--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass30 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId30 = (*env)->GetMethodID(env, localClass30, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP20 = (*env)->CallObjectMethod(env, v6_8, methodId30, v7_0);
//MOVE_RESULT         |     |v6=TEMP20
v6_8 = TEMP20;
//INVOKE_VIRTUAL      |     |TEMP=v1.show(v3_0)  //Lcom/google/android/exoplayer2/demo/A;.show(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;
jclass localClass31 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A");
jmethodID methodId31 = (*env)->GetMethodID(env, localClass31, "show", "(Lcom/google/android/exoplayer2/demo/A;)Ljava/lang/String;");
jstring TEMP21 =  (jstring) (*env)->CallObjectMethod(env, v1_0, methodId31, v3_0);
//MOVE_RESULT         |     |v7=TEMP21
v7_0 = TEMP21;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass32 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId32 = (*env)->GetMethodID(env, localClass32, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP22 = (*env)->CallObjectMethod(env, v6_8, methodId32, v7_0);
//MOVE_RESULT         |     |v6=TEMP22
v6_8 = TEMP22;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass33 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId33 = (*env)->GetMethodID(env, localClass33, "toString", "()Ljava/lang/String;");
jstring TEMP23 =  (jstring) (*env)->CallObjectMethod(env, v6_8, methodId33);
//MOVE_RESULT         |     |v6=TEMP23
jstring v6_9 = TEMP23;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_9)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass34 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId34 = (*env)->GetStaticMethodID(env, localClass34, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP24 = (*env)->CallStaticIntMethod(env, localClass34, methodId34, v5_0,v6_9);
//CONST_STRING        |     |v5="MediaCodecInfo"
v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_10 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass35 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId35 = (*env)->GetMethodID(env, localClass35, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_10, methodId35);
//CONST_STRING        |     |v7="6--"
v7_0 = (*env)->NewStringUTF(env, "6--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass36 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId36 = (*env)->GetMethodID(env, localClass36, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP25 = (*env)->CallObjectMethod(env, v6_10, methodId36, v7_0);
//MOVE_RESULT         |     |v6=TEMP25
v6_10 = TEMP25;
//INVOKE_VIRTUAL      |     |TEMP=v1.show(v4_0)  //Lcom/google/android/exoplayer2/demo/A;.show(Lcom/google/android/exoplayer2/demo/D;)Ljava/lang/String;
jclass localClass37 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/A");
jmethodID methodId37 = (*env)->GetMethodID(env, localClass37, "show", "(Lcom/google/android/exoplayer2/demo/D;)Ljava/lang/String;");
jstring TEMP26 =  (jstring) (*env)->CallObjectMethod(env, v1_0, methodId37, v4_0);
//MOVE_RESULT         |     |v7=TEMP26
v7_0 = TEMP26;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass38 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId38 = (*env)->GetMethodID(env, localClass38, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP27 = (*env)->CallObjectMethod(env, v6_10, methodId38, v7_0);
//MOVE_RESULT         |     |v6=TEMP27
v6_10 = TEMP27;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass39 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId39 = (*env)->GetMethodID(env, localClass39, "toString", "()Ljava/lang/String;");
jstring TEMP28 =  (jstring) (*env)->CallObjectMethod(env, v6_10, methodId39);
//MOVE_RESULT         |     |v6=TEMP28
jstring v6_11 = TEMP28;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_11)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass40 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId40 = (*env)->GetStaticMethodID(env, localClass40, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP29 = (*env)->CallStaticIntMethod(env, localClass40, methodId40, v5_0,v6_11);
//CONST_STRING        |     |v5="MediaCodecInfo"
v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_12 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass41 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId41 = (*env)->GetMethodID(env, localClass41, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_12, methodId41);
//CONST_STRING        |     |v7="7--"
v7_0 = (*env)->NewStringUTF(env, "7--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass42 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId42 = (*env)->GetMethodID(env, localClass42, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP30 = (*env)->CallObjectMethod(env, v6_12, methodId42, v7_0);
//MOVE_RESULT         |     |v6=TEMP30
v6_12 = TEMP30;
//INVOKE_VIRTUAL      |     |TEMP=v2.show(v2_0)  //Lcom/google/android/exoplayer2/demo/B;.show(Lcom/google/android/exoplayer2/demo/B;)Ljava/lang/String;
jclass localClass43 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/B");
jmethodID methodId43 = (*env)->GetMethodID(env, localClass43, "show", "(Lcom/google/android/exoplayer2/demo/B;)Ljava/lang/String;");
jstring TEMP31 =  (jstring) (*env)->CallObjectMethod(env, v2_0, methodId43, v2_0);
//MOVE_RESULT         |     |v7=TEMP31
v7_0 = TEMP31;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass44 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId44 = (*env)->GetMethodID(env, localClass44, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP32 = (*env)->CallObjectMethod(env, v6_12, methodId44, v7_0);
//MOVE_RESULT         |     |v6=TEMP32
v6_12 = TEMP32;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass45 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId45 = (*env)->GetMethodID(env, localClass45, "toString", "()Ljava/lang/String;");
jstring TEMP33 =  (jstring) (*env)->CallObjectMethod(env, v6_12, methodId45);
//MOVE_RESULT         |     |v6=TEMP33
jstring v6_13 = TEMP33;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_13)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass46 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId46 = (*env)->GetStaticMethodID(env, localClass46, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP34 = (*env)->CallStaticIntMethod(env, localClass46, methodId46, v5_0,v6_13);
//CONST_STRING        |     |v5="MediaCodecInfo"
v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_14 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass47 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId47 = (*env)->GetMethodID(env, localClass47, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_14, methodId47);
//CONST_STRING        |     |v7="8--"
v7_0 = (*env)->NewStringUTF(env, "8--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass48 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId48 = (*env)->GetMethodID(env, localClass48, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP35 = (*env)->CallObjectMethod(env, v6_14, methodId48, v7_0);
//MOVE_RESULT         |     |v6=TEMP35
v6_14 = TEMP35;
//INVOKE_VIRTUAL      |     |TEMP=v2.show(v3_0)  //Lcom/google/android/exoplayer2/demo/B;.show(Lcom/google/android/exoplayer2/demo/B;)Ljava/lang/String;
jclass localClass49 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/B");
jmethodID methodId49 = (*env)->GetMethodID(env, localClass49, "show", "(Lcom/google/android/exoplayer2/demo/B;)Ljava/lang/String;");
jstring TEMP36 =  (jstring) (*env)->CallObjectMethod(env, v2_0, methodId49, v3_0);
//MOVE_RESULT         |     |v7=TEMP36
v7_0 = TEMP36;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass50 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId50 = (*env)->GetMethodID(env, localClass50, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP37 = (*env)->CallObjectMethod(env, v6_14, methodId50, v7_0);
//MOVE_RESULT         |     |v6=TEMP37
v6_14 = TEMP37;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass51 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId51 = (*env)->GetMethodID(env, localClass51, "toString", "()Ljava/lang/String;");
jstring TEMP38 =  (jstring) (*env)->CallObjectMethod(env, v6_14, methodId51);
//MOVE_RESULT         |     |v6=TEMP38
jstring v6_15 = TEMP38;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_15)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass52 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId52 = (*env)->GetStaticMethodID(env, localClass52, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP39 = (*env)->CallStaticIntMethod(env, localClass52, methodId52, v5_0,v6_15);
//CONST_STRING        |     |v5="MediaCodecInfo"
v5_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v6=NEW Ljava/lang/StringBuilder;
jobject v6_16 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v6.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass53 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId53 = (*env)->GetMethodID(env, localClass53, "<init>", "()V");
(*env)->CallVoidMethod(env, v6_16, methodId53);
//CONST_STRING        |     |v7="9--"
v7_0 = (*env)->NewStringUTF(env, "9--");
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass54 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId54 = (*env)->GetMethodID(env, localClass54, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP40 = (*env)->CallObjectMethod(env, v6_16, methodId54, v7_0);
//MOVE_RESULT         |     |v6=TEMP40
v6_16 = TEMP40;
//INVOKE_VIRTUAL      |     |TEMP=v2.show(v4_0)  //Lcom/google/android/exoplayer2/demo/B;.show(Lcom/google/android/exoplayer2/demo/D;)Ljava/lang/String;
jclass localClass55 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/B");
jmethodID methodId55 = (*env)->GetMethodID(env, localClass55, "show", "(Lcom/google/android/exoplayer2/demo/D;)Ljava/lang/String;");
jstring TEMP41 =  (jstring) (*env)->CallObjectMethod(env, v2_0, methodId55, v4_0);
//MOVE_RESULT         |     |v7=TEMP41
v7_0 = TEMP41;
//INVOKE_VIRTUAL      |     |TEMP=v6.append(v7_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass56 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId56 = (*env)->GetMethodID(env, localClass56, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP42 = (*env)->CallObjectMethod(env, v6_16, methodId56, v7_0);
//MOVE_RESULT         |     |v6=TEMP42
v6_16 = TEMP42;
//INVOKE_VIRTUAL      |     |TEMP=v6.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass57 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId57 = (*env)->GetMethodID(env, localClass57, "toString", "()Ljava/lang/String;");
jstring TEMP43 =  (jstring) (*env)->CallObjectMethod(env, v6_16, methodId57);
//MOVE_RESULT         |     |v6=TEMP43
jstring v6_17 = TEMP43;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v5_0,v6_17)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass58 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId58 = (*env)->GetStaticMethodID(env, localClass58, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP44 = (*env)->CallStaticIntMethod(env, localClass58, methodId58, v5_0,v6_17);
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0013  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.testWine()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_testWine_39797(JNIEnv * env, jobject  v7)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> a // Lcom/google/android/exoplayer2/demo/Wine; 
//LOCAL_VARIABLE LL2 ~ LL1 v1 -> b // Lcom/google/android/exoplayer2/demo/Wine; 
//LOCAL_VARIABLE LL3 ~ LL1 v2 -> jgj // Lcom/google/android/exoplayer2/demo/JGJ; 
//LOCAL_VARIABLE LL4 ~ LL1 v3 -> jnc // Lcom/google/android/exoplayer2/demo/JNC; 
//LOCAL_VARIABLE LL5 ~ LL1 v7 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LABEL               |  LL5: line 140
L5: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/demo/JNC;
jobject v0_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/JNC"));

//INVOKE_DIRECT       |     |v0.<init>()  //Lcom/google/android/exoplayer2/demo/JNC;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/JNC");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v0_0, methodId0);
//LABEL               |  LL0: line 141
L0: ;
//NEW_INSTANCE        |     |v1=NEW Lcom/google/android/exoplayer2/demo/JNC;
jobject v1_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/JNC"));

//INVOKE_DIRECT       |     |v1.<init>()  //Lcom/google/android/exoplayer2/demo/JNC;.<init>()V
jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/JNC");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "<init>", "()V");
(*env)->CallVoidMethod(env, v1_0, methodId1);
//LABEL               |  LL2: line 143
L2: ;
//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/demo/JNC;
jobject v3_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/JNC"));

//INVOKE_DIRECT       |     |v3.<init>()  //Lcom/google/android/exoplayer2/demo/JNC;.<init>()V
jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/JNC");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass2, "<init>", "()V");
(*env)->CallVoidMethod(env, v3_0, methodId2);
//LABEL               |  LL4: line 144
L4: ;
//NEW_INSTANCE        |     |v2=NEW Lcom/google/android/exoplayer2/demo/JGJ;
jobject v2_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/demo/JGJ"));

//INVOKE_DIRECT       |     |v2.<init>()  //Lcom/google/android/exoplayer2/demo/JGJ;.<init>()V
jclass localClass3 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/JGJ");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass3, "<init>", "()V");
(*env)->CallVoidMethod(env, v2_0, methodId3);
//LABEL               |  LL3: line 147
L3: ;
//MOVE                |     |v0 = v3
v0_0 = v3_0;
//LABEL               |  LL6: line 148
L6: ;
//MOVE                |     |v1 = v2
jobject v1_1 = v2_0;
//LABEL               |  LL7: line 150
L7: ;
//CONST_STRING        |     |v4="MediaCodecInfo"
jstring v4_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v5=NEW Ljava/lang/StringBuilder;
jobject v5_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v5.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass4 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId4 = (*env)->GetMethodID(env, localClass4, "<init>", "()V");
(*env)->CallVoidMethod(env, v5_0, methodId4);
//INVOKE_VIRTUAL      |     |TEMP=v0.toString()  //Lcom/google/android/exoplayer2/demo/Wine;.toString()Ljava/lang/String;
jclass localClass5 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/Wine");
jmethodID methodId5 = (*env)->GetMethodID(env, localClass5, "toString", "()Ljava/lang/String;");
jstring TEMP0 =  (jstring) (*env)->CallObjectMethod(env, v0_0, methodId5);
//MOVE_RESULT         |     |v6=TEMP0
jstring v6_0 = TEMP0;
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass6 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId6 = (*env)->GetMethodID(env, localClass6, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP1 = (*env)->CallObjectMethod(env, v5_0, methodId6, v6_0);
//MOVE_RESULT         |     |v5=TEMP1
v5_0 = TEMP1;
//CONST_STRING        |     |v6="--"
v6_0 = (*env)->NewStringUTF(env, "--");
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass7 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId7 = (*env)->GetMethodID(env, localClass7, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP2 = (*env)->CallObjectMethod(env, v5_0, methodId7, v6_0);
//MOVE_RESULT         |     |v5=TEMP2
v5_0 = TEMP2;
//INVOKE_VIRTUAL      |     |TEMP=v0.drink()  //Lcom/google/android/exoplayer2/demo/Wine;.drink()Ljava/lang/String;
jclass localClass8 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/Wine");
jmethodID methodId8 = (*env)->GetMethodID(env, localClass8, "drink", "()Ljava/lang/String;");
jstring TEMP3 =  (jstring) (*env)->CallObjectMethod(env, v0_0, methodId8);
//MOVE_RESULT         |     |v6=TEMP3
v6_0 = TEMP3;
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass9 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId9 = (*env)->GetMethodID(env, localClass9, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP4 = (*env)->CallObjectMethod(env, v5_0, methodId9, v6_0);
//MOVE_RESULT         |     |v5=TEMP4
v5_0 = TEMP4;
//INVOKE_VIRTUAL      |     |TEMP=v5.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass10 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId10 = (*env)->GetMethodID(env, localClass10, "toString", "()Ljava/lang/String;");
jstring TEMP5 =  (jstring) (*env)->CallObjectMethod(env, v5_0, methodId10);
//MOVE_RESULT         |     |v5=TEMP5
jstring v5_1 = TEMP5;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v4_0,v5_1)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass11 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId11 = (*env)->GetStaticMethodID(env, localClass11, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP6 = (*env)->CallStaticIntMethod(env, localClass11, methodId11, v4_0,v5_1);
//CONST_STRING        |     |v4="MediaCodecInfo"
v4_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//NEW_INSTANCE        |     |v5=NEW Ljava/lang/StringBuilder;
jobject v5_2 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v5.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass12 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId12 = (*env)->GetMethodID(env, localClass12, "<init>", "()V");
(*env)->CallVoidMethod(env, v5_2, methodId12);
//INVOKE_VIRTUAL      |     |TEMP=v1.toString()  //Lcom/google/android/exoplayer2/demo/Wine;.toString()Ljava/lang/String;
jclass localClass13 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/Wine");
jmethodID methodId13 = (*env)->GetMethodID(env, localClass13, "toString", "()Ljava/lang/String;");
jstring TEMP7 =  (jstring) (*env)->CallObjectMethod(env, v1_1, methodId13);
//MOVE_RESULT         |     |v6=TEMP7
v6_0 = TEMP7;
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass14 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId14 = (*env)->GetMethodID(env, localClass14, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP8 = (*env)->CallObjectMethod(env, v5_2, methodId14, v6_0);
//MOVE_RESULT         |     |v5=TEMP8
v5_2 = TEMP8;
//CONST_STRING        |     |v6="--"
v6_0 = (*env)->NewStringUTF(env, "--");
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass15 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId15 = (*env)->GetMethodID(env, localClass15, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP9 = (*env)->CallObjectMethod(env, v5_2, methodId15, v6_0);
//MOVE_RESULT         |     |v5=TEMP9
v5_2 = TEMP9;
//INVOKE_VIRTUAL      |     |TEMP=v1.drink()  //Lcom/google/android/exoplayer2/demo/Wine;.drink()Ljava/lang/String;
jclass localClass16 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/Wine");
jmethodID methodId16 = (*env)->GetMethodID(env, localClass16, "drink", "()Ljava/lang/String;");
jstring TEMP10 =  (jstring) (*env)->CallObjectMethod(env, v1_1, methodId16);
//MOVE_RESULT         |     |v6=TEMP10
v6_0 = TEMP10;
//INVOKE_VIRTUAL      |     |TEMP=v5.append(v6_0)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass17 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId17 = (*env)->GetMethodID(env, localClass17, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP11 = (*env)->CallObjectMethod(env, v5_2, methodId17, v6_0);
//MOVE_RESULT         |     |v5=TEMP11
v5_2 = TEMP11;
//INVOKE_VIRTUAL      |     |TEMP=v5.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass18 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId18 = (*env)->GetMethodID(env, localClass18, "toString", "()Ljava/lang/String;");
jstring TEMP12 =  (jstring) (*env)->CallObjectMethod(env, v5_2, methodId18);
//MOVE_RESULT         |     |v5=TEMP12
jstring v5_3 = TEMP12;
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v4_0,v5_3)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass19 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId19 = (*env)->GetStaticMethodID(env, localClass19, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP13 = (*env)->CallStaticIntMethod(env, localClass19, methodId19, v4_0,v5_3);
//CONST_STRING        |     |v4="MediaCodecInfo"
v4_0 = (*env)->NewStringUTF(env, "MediaCodecInfo");
//CONST_STRING        |     |v5="-------------------------------"
v5_3 = (*env)->NewStringUTF(env, "-------------------------------");
//INVOKE_STATIC       |     |TEMP=android.util.Log.d(v4_0,v5_3)  //Landroid/util/Log;.d(Ljava/lang/String;Ljava/lang/String;)I
jclass localClass20 = (*env)->FindClass(env, "android/util/Log");
jmethodID methodId20 = (*env)->GetStaticMethodID(env, localClass20, "d", "(Ljava/lang/String;Ljava/lang/String;)I");
jint TEMP14 = (*env)->CallStaticIntMethod(env, localClass20, methodId20, v4_0,v5_3);
//LABEL               |  LL8: line 153
L8: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0014  access:0x0001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.onCreate(Landroid/os/Bundle;)V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_onCreate_2045109055(JNIEnv * env, jobject  v5, jobject v6)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> b // Landroid/widget/Button; 
//LOCAL_VARIABLE LL2 ~ LL1 v5 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL2 ~ LL1 v6 -> savedInstanceState // Landroid/os/Bundle; 
//LABEL               |  LL2: line 104
L2: ;
//CONST               |     |v4=0x00000001  // int:1   float:0.000000
jint v4_0 = 0x00000001;
//CONST               |     |v3=0x00000064  // int:100   float:0.000000
jint v3_0 = 0x00000064;
//LABEL               |  LL3: line 104
L3: ;
//INVOKE_SUPER        |     |v5.onCreate(v6)  //Landroid/app/Activity;.onCreate(Landroid/os/Bundle;)V
jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "onCreate", "(Landroid/os/Bundle;)V");
(*env)->CallNonvirtualVoidMethod(env, v5, localClass0, methodId0, v6);
//LABEL               |  LL4: line 106
L4: ;
//NEW_INSTANCE        |     |v1=NEW Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;
jobject v1_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/upstream/DefaultBandwidthMeter"));

//INVOKE_DIRECT       |     |v1.<init>()  //Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;.<init>()V
jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/upstream/DefaultBandwidthMeter");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass1, "<init>", "()V");
(*env)->CallVoidMethod(env, v1_0, methodId1);
//SPUT                |     |com.google.android.exoplayer2.demo.PlayerActivity.BANDWIDTH_METER=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.BANDWIDTH_METER Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;
jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId0 = (*env)->GetStaticFieldID(env, localClass2, "BANDWIDTH_METER", "Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;");
(*env)->SetStaticObjectField(env, localClass2, fieldId0, v1_0);

//LABEL               |  LL5: line 107
L5: ;
//NEW_INSTANCE        |     |v1=NEW Ljava/net/CookieManager;
jobject v1_1 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/net/CookieManager"));

//INVOKE_DIRECT       |     |v1.<init>()  //Ljava/net/CookieManager;.<init>()V
jclass localClass3 = (*env)->FindClass(env, "java/net/CookieManager");
jmethodID methodId2 = (*env)->GetMethodID(env, localClass3, "<init>", "()V");
(*env)->CallVoidMethod(env, v1_1, methodId2);
//SPUT                |     |com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
jclass localClass4 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId1 = (*env)->GetStaticFieldID(env, localClass4, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
(*env)->SetStaticObjectField(env, localClass4, fieldId1, v1_1);

//LABEL               |  LL6: line 108
L6: ;
//SGET                |     |v1=com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
jclass localClass5 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId2 = (*env)->GetStaticFieldID(env, localClass5, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
v1_1 = (*env)->GetStaticObjectField(env, localClass5, fieldId2);
//SGET                |     |v2=java.net.CookiePolicy.ACCEPT_ORIGINAL_SERVER  //Ljava/net/CookiePolicy;.ACCEPT_ORIGINAL_SERVER Ljava/net/CookiePolicy;
jclass localClass6 = (*env)->FindClass(env, "java/net/CookiePolicy");
jfieldID fieldId3 = (*env)->GetStaticFieldID(env, localClass6, "ACCEPT_ORIGINAL_SERVER", "Ljava/net/CookiePolicy;");
jobject v2_0 = (*env)->GetStaticObjectField(env, localClass6, fieldId3);
//INVOKE_VIRTUAL      |     |v1.setCookiePolicy(v2_0)  //Ljava/net/CookieManager;.setCookiePolicy(Ljava/net/CookiePolicy;)V
jclass localClass7 = (*env)->FindClass(env, "java/net/CookieManager");
jmethodID methodId3 = (*env)->GetMethodID(env, localClass7, "setCookiePolicy", "(Ljava/net/CookiePolicy;)V");
(*env)->CallVoidMethod(env, v1_1, methodId3, v2_0);
//LABEL               |  LL7: line 110
L7: ;
//IPUT                |     |v5.shouldAutoPlay=v4  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.shouldAutoPlay Z
jclass localClass8 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId4 = (*env)->GetFieldID(env, localClass8, "shouldAutoPlay", "Z");
(*env)->SetBooleanField(env, v5, fieldId4, v4_0);

//LABEL               |  LL8: line 112
L8: ;
//INVOKE_DIRECT       |     |TEMP=v5.buildDataSourceFactory(v4_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass9 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId4 = (*env)->GetMethodID(env, localClass9, "buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v5, methodId4, v4_0);
//MOVE_RESULT         |     |v1=TEMP0
jobject v1_2 = TEMP0;
//IPUT                |     |v5.mediaDataSourceFactory=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass10 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId5 = (*env)->GetFieldID(env, localClass10, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
(*env)->SetObjectField(env, v5, fieldId5, v1_2);

//LABEL               |  LL9: line 113
L9: ;
//NEW_INSTANCE        |     |v1=NEW Landroid/os/Handler;
jobject v1_3 = (*env)->AllocObject(env, (*env)->FindClass(env, "android/os/Handler"));

//INVOKE_DIRECT       |     |v1.<init>()  //Landroid/os/Handler;.<init>()V
jclass localClass11 = (*env)->FindClass(env, "android/os/Handler");
jmethodID methodId5 = (*env)->GetMethodID(env, localClass11, "<init>", "()V");
(*env)->CallVoidMethod(env, v1_3, methodId5);
//IPUT                |     |v5.mainHandler=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
jclass localClass12 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId6 = (*env)->GetFieldID(env, localClass12, "mainHandler", "Landroid/os/Handler;");
(*env)->SetObjectField(env, v5, fieldId6, v1_3);

//LABEL               | LL10: line 114
L10: ;
//INVOKE_STATIC       |     |TEMP=java.net.CookieHandler.getDefault()  //Ljava/net/CookieHandler;.getDefault()Ljava/net/CookieHandler;
jclass localClass13 = (*env)->FindClass(env, "java/net/CookieHandler");
jmethodID methodId6 = (*env)->GetStaticMethodID(env, localClass13, "getDefault", "()Ljava/net/CookieHandler;");
jobject TEMP1 = (*env)->CallStaticObjectMethod(env, localClass13, methodId6);
//MOVE_RESULT         |     |v1=TEMP1
jobject v1_4 = TEMP1;
//SGET                |     |v2=com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
jclass localClass14 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId7 = (*env)->GetStaticFieldID(env, localClass14, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
jobject v2_1 = (*env)->GetStaticObjectField(env, localClass14, fieldId7);
//IF_EQ               |     |if (v1 == v2) {  goto L11; }
if (v1_4 == v2_1) {  goto L11; }
//LABEL               | LL12: line 115
L12: ;
//SGET                |     |v1=com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
jclass localClass15 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId8 = (*env)->GetStaticFieldID(env, localClass15, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
jobject v1_5 = (*env)->GetStaticObjectField(env, localClass15, fieldId8);
//INVOKE_STATIC       |     |java.net.CookieHandler.setDefault(v1_5)  //Ljava/net/CookieHandler;.setDefault(Ljava/net/CookieHandler;)V
jclass localClass16 = (*env)->FindClass(env, "java/net/CookieHandler");
jmethodID methodId7 = (*env)->GetStaticMethodID(env, localClass16, "setDefault", "(Ljava/net/CookieHandler;)V");
(*env)->CallStaticVoidMethod(env, localClass16, methodId7, v1_5);
//LABEL               | LL11: line 118
L11: ;
//CONST               |     |v1=0x7f040003  // int:2130968579   float:175458156290837700000000000000000000000.000000
jint v1_6 = 0x7f040003;
//INVOKE_VIRTUAL      |     |v5.setContentView(v1_6)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.setContentView(I)V
jclass localClass17 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId8 = (*env)->GetMethodID(env, localClass17, "setContentView", "(I)V");
(*env)->CallVoidMethod(env, v5, methodId8, v1_6);
//LABEL               | LL13: line 120
L13: ;
//CONST               |     |v1=0x7f09001b  // int:2131296283   float:182104783047592770000000000000000000000.000000
v1_6 = 0x7f09001b;
//INVOKE_VIRTUAL      |     |TEMP=v5.findViewById(v1_6)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass18 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId9 = (*env)->GetMethodID(env, localClass18, "findViewById", "(I)Landroid/view/View;");
jobject TEMP2 = (*env)->CallObjectMethod(env, v5, methodId9, v1_6);
//MOVE_RESULT         |     |v0=TEMP2
jobject v0_0 = TEMP2;
//CHECK_CAST          |     |v0=(android.widget.Button) v0
//LABEL               |  LL0: line 121
L0: ;
//NEW_INSTANCE        |     |v1=NEW Ljava/lang/StringBuilder;
jobject v1_7 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v1.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass19 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId10 = (*env)->GetMethodID(env, localClass19, "<init>", "()V");
(*env)->CallVoidMethod(env, v1_7, methodId10);
//INVOKE_DIRECT       |     |TEMP=v5.sumNumber(v3_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumNumber(I)I
jclass localClass20 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId11 = (*env)->GetMethodID(env, localClass20, "sumNumber", "(I)I");
jint TEMP3 = (*env)->CallIntMethod(env, v5, methodId11, v3_0);
//MOVE_RESULT         |     |v2=TEMP3
jint v2_2 = TEMP3;
//INVOKE_VIRTUAL      |     |TEMP=v1.append(v2_2)  //Ljava/lang/StringBuilder;.append(I)Ljava/lang/StringBuilder;
jclass localClass21 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId12 = (*env)->GetMethodID(env, localClass21, "append", "(I)Ljava/lang/StringBuilder;");
jobject TEMP4 = (*env)->CallObjectMethod(env, v1_7, methodId12, v2_2);
//MOVE_RESULT         |     |v1=TEMP4
v1_7 = TEMP4;
//CONST_STRING        |     |v2=""
jstring v2_3 = (*env)->NewStringUTF(env, "");
//INVOKE_VIRTUAL      |     |TEMP=v1.append(v2_3)  //Ljava/lang/StringBuilder;.append(Ljava/lang/String;)Ljava/lang/StringBuilder;
jclass localClass22 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId13 = (*env)->GetMethodID(env, localClass22, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
jobject TEMP5 = (*env)->CallObjectMethod(env, v1_7, methodId13, v2_3);
//MOVE_RESULT         |     |v1=TEMP5
v1_7 = TEMP5;
//INVOKE_VIRTUAL      |     |TEMP=v1.toString()  //Ljava/lang/StringBuilder;.toString()Ljava/lang/String;
jclass localClass23 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId14 = (*env)->GetMethodID(env, localClass23, "toString", "()Ljava/lang/String;");
jstring TEMP6 =  (jstring) (*env)->CallObjectMethod(env, v1_7, methodId14);
//MOVE_RESULT         |     |v1=TEMP6
jstring v1_8 = TEMP6;
//INVOKE_VIRTUAL      |     |v0.setText(v1_8)  //Landroid/widget/Button;.setText(Ljava/lang/CharSequence;)V
jclass localClass24 = (*env)->FindClass(env, "android/widget/Button");
jmethodID methodId15 = (*env)->GetMethodID(env, localClass24, "setText", "(Ljava/lang/CharSequence;)V");
(*env)->CallVoidMethod(env, v0_0, methodId15, v1_8);
//INVOKE_DIRECT       |     |v5.testWine()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.testWine()V
jclass localClass25 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId16 = (*env)->GetMethodID(env, localClass25, "testWine", "()V");
(*env)->CallVoidMethod(env, v5, methodId16);
//LABEL               | LL14: line 123
L14: ;
//INVOKE_DIRECT       |     |v5.testABCD()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.testABCD()V
jclass localClass26 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId17 = (*env)->GetMethodID(env, localClass26, "testABCD", "()V");
(*env)->CallVoidMethod(env, v5, methodId17);
//LABEL               | LL15: line 125
L15: ;
//INVOKE_DIRECT       |     |TEMP=v5.sumIntArray(v3_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumIntArray(I)I
jclass localClass27 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId18 = (*env)->GetMethodID(env, localClass27, "sumIntArray", "(I)I");
jint TEMP7 = (*env)->CallIntMethod(env, v5, methodId18, v3_0);
//LABEL               | LL16: line 126
L16: ;
//INVOKE_DIRECT       |     |TEMP=v5.sumStringArray(v3_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumStringArray(I)Ljava/lang/String;
jclass localClass28 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId19 = (*env)->GetMethodID(env, localClass28, "sumStringArray", "(I)Ljava/lang/String;");
jstring TEMP8 =  (jstring) (*env)->CallObjectMethod(env, v5, methodId19, v3_0);
//LABEL               | LL17: line 127
L17: ;
//INVOKE_DIRECT       |     |TEMP=v5.sumLongArray(v3_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumLongArray(I)J
jclass localClass29 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId20 = (*env)->GetMethodID(env, localClass29, "sumLongArray", "(I)J");
jlong TEMP9 = (*env)->CallLongMethod(env, v5, methodId20, v3_0);
//LABEL               | LL18: line 128
L18: ;
//INVOKE_DIRECT       |     |TEMP=v5.sumDoubleArray(v3_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumDoubleArray(I)D
jclass localClass30 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId21 = (*env)->GetMethodID(env, localClass30, "sumDoubleArray", "(I)D");
jdouble TEMP10 = (*env)->CallDoubleMethod(env, v5, methodId21, v3_0);
//LABEL               | LL19: line 129
L19: ;
//INVOKE_DIRECT       |     |TEMP=v5.sum2DIntArray(v3_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.sum2DIntArray(I)I
jclass localClass31 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId22 = (*env)->GetMethodID(env, localClass31, "sum2DIntArray", "(I)I");
jint TEMP11 = (*env)->CallIntMethod(env, v5, methodId22, v3_0);
//LABEL               | LL20: line 131
L20: ;
//CONST               |     |v1=0x7f09001e  // int:2131296286   float:182104843894821600000000000000000000000.000000
jint v1_9 = 0x7f09001e;
//INVOKE_VIRTUAL      |     |TEMP=v5.findViewById(v1_9)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass32 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId23 = (*env)->GetMethodID(env, localClass32, "findViewById", "(I)Landroid/view/View;");
jobject TEMP12 = (*env)->CallObjectMethod(env, v5, methodId23, v1_9);
//MOVE_RESULT         |     |v1=TEMP12
jobject v1_10 = TEMP12;
//CHECK_CAST          |     |v1=(android.widget.LinearLayout) v1
//IPUT                |     |v5.debugRootView=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugRootView Landroid/widget/LinearLayout;
jclass localClass33 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId9 = (*env)->GetFieldID(env, localClass33, "debugRootView", "Landroid/widget/LinearLayout;");
(*env)->SetObjectField(env, v5, fieldId9, v1_10);

//LABEL               | LL21: line 132
L21: ;
//CONST               |     |v1=0x7f09001d  // int:2131296285   float:182104823612411980000000000000000000000.000000
jint v1_11 = 0x7f09001d;
//INVOKE_VIRTUAL      |     |TEMP=v5.findViewById(v1_11)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass34 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId24 = (*env)->GetMethodID(env, localClass34, "findViewById", "(I)Landroid/view/View;");
jobject TEMP13 = (*env)->CallObjectMethod(env, v5, methodId24, v1_11);
//MOVE_RESULT         |     |v1=TEMP13
jobject v1_12 = TEMP13;
//CHECK_CAST          |     |v1=(android.widget.TextView) v1
//IPUT                |     |v5.debugTextView=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugTextView Landroid/widget/TextView;
jclass localClass35 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId10 = (*env)->GetFieldID(env, localClass35, "debugTextView", "Landroid/widget/TextView;");
(*env)->SetObjectField(env, v5, fieldId10, v1_12);

//LABEL               | LL22: line 133
L22: ;
//CONST               |     |v1=0x7f09001f  // int:2131296287   float:182104864177231200000000000000000000000.000000
jint v1_13 = 0x7f09001f;
//INVOKE_VIRTUAL      |     |TEMP=v5.findViewById(v1_13)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass36 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId25 = (*env)->GetMethodID(env, localClass36, "findViewById", "(I)Landroid/view/View;");
jobject TEMP14 = (*env)->CallObjectMethod(env, v5, methodId25, v1_13);
//MOVE_RESULT         |     |v1=TEMP14
jobject v1_14 = TEMP14;
//CHECK_CAST          |     |v1=(android.widget.Button) v1
//IPUT                |     |v5.retryButton=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.retryButton Landroid/widget/Button;
jclass localClass37 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId11 = (*env)->GetFieldID(env, localClass37, "retryButton", "Landroid/widget/Button;");
(*env)->SetObjectField(env, v5, fieldId11, v1_14);

//LABEL               | LL23: line 135
L23: ;
//CONST               |     |v1=0x7f09001c  // int:2131296284   float:182104803330002380000000000000000000000.000000
jint v1_15 = 0x7f09001c;
//INVOKE_VIRTUAL      |     |TEMP=v5.findViewById(v1_15)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass38 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId26 = (*env)->GetMethodID(env, localClass38, "findViewById", "(I)Landroid/view/View;");
jobject TEMP15 = (*env)->CallObjectMethod(env, v5, methodId26, v1_15);
//MOVE_RESULT         |     |v1=TEMP15
jobject v1_16 = TEMP15;
//CHECK_CAST          |     |v1=(com.google.android.exoplayer2.ui.SimpleExoPlayerView) v1
//IPUT                |     |v5.simpleExoPlayerView=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
jclass localClass39 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId12 = (*env)->GetFieldID(env, localClass39, "simpleExoPlayerView", "Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;");
(*env)->SetObjectField(env, v5, fieldId12, v1_16);

//LABEL               | LL24: line 136
L24: ;
//IGET                |     |v1=v5.simpleExoPlayerView  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
jclass localClass40 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId13 = (*env)->GetFieldID(env, localClass40, "simpleExoPlayerView", "Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;");
jobject v1_17 = (*env)->GetObjectField(env, v5, fieldId13);

//INVOKE_VIRTUAL      |     |TEMP=v1.requestFocus()  //Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;.requestFocus()Z
jclass localClass41 = (*env)->FindClass(env, "com/google/android/exoplayer2/ui/SimpleExoPlayerView");
jmethodID methodId27 = (*env)->GetMethodID(env, localClass41, "requestFocus", "()Z");
jboolean TEMP16 = (*env)->CallBooleanMethod(env, v1_17, methodId27);
//LABEL               | LL25: line 137
L25: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0015  access:0x0001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.onResume()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_onResume_39797(JNIEnv * env, jobject  v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LABEL               |  LL0: line 239
L0: ;
//INVOKE_SUPER        |     |v2.onResume()  //Landroid/app/Activity;.onResume()V
jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "onResume", "()V");
(*env)->CallNonvirtualVoidMethod(env, v2, localClass0, methodId0);
//LABEL               |  LL2: line 240
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
//LABEL               |  LL3: line 241
L3: ;
//INVOKE_DIRECT       |     |v2.initializePlayer()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.initializePlayer()V
jclass localClass3 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass3, "initializePlayer", "()V");
(*env)->CallVoidMethod(env, v2, methodId1);
//LABEL               |  LL4: line 243
L4: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}

int registerNativeSymbols420217909_443(JNIEnv * env) { 
int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = { 
{"__initNative", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity___initNative_39797 },
{"buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_buildDataSourceFactory_1578816035 },
{"buildMediaSource", "(Landroid/net/Uri;Ljava/lang/String;)Lcom/google/android/exoplayer2/source/MediaSource;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_buildMediaSource_1776506356 },
{"initializePlayer", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_initializePlayer_39797 },
{"showToast", "(I)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast_1263150 },
{"showToast", "(Ljava/lang/String;)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast_1428966913 },
{"sum2DIntArray", "(I)I",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_sum2DIntArray_1263137 },
{"sumDoubleArray", "(I)D",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_sumDoubleArray_1263132 },
{"sumIntArray", "(I)I",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_sumIntArray_1263137 },
{"sumLongArray", "(I)J",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_sumLongArray_1263138 },
{"sumNumber", "(I)I",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_sumNumber_1263137 },
{"sumStringArray", "(I)Ljava/lang/String;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_sumStringArray_1200754738 },
{"testABCD", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_testABCD_39797 },
{"testWine", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_testWine_39797 },
{"onCreate", "(Landroid/os/Bundle;)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_onCreate_2045109055 },
{"onResume", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_onResume_39797 }, 
}; 
jclass clazz = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
if (clazz == NULL) { 
 returnVal = JNI_FALSE; 
}
if ((*env)->RegisterNatives(env, clazz, symbolListApi, sizeof(symbolListApi) / sizeof(symbolListApi[0])) < 0) {
returnVal = JNI_FALSE; 
}
return returnVal;
}
