#include <jni.h>
#include <stdio.h>
//class:0649  access:0x0001
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
//LABEL               |  LL0: line 59
L0: ;
//INVOKE_DIRECT       |     |v0.<init>()  //Landroid/app/Activity;.<init>()V
jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
(*env)->CallVoidMethod(env, v0, methodId0);
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
//LABEL               |  LL0: line 215
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
//LABEL               |  LL3: line 216
L3: ;
//INVOKE_VIRTUAL      |     |TEMP=v0.buildDataSourceFactory(v1_0)  //Lcom/google/android/exoplayer2/demo/DemoApplication;.buildDataSourceFactory(Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/DemoApplication");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass2, "buildDataSourceFactory", "(Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject TEMP1 = (*env)->CallObjectMethod(env, v0_0, methodId1, v1_0);
//MOVE_RESULT         |     |v0=TEMP1
jobject v0_1 = TEMP1;
//LABEL               |  LL4: line 215
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
//LABEL               |  LL4: line 194
L4: ;
//CONST               |     |v2=0x00000000  // int:0   float:0.000000
jint v2_0 = 0x00000000;
//LABEL               |  LL5: line 194
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
//LABEL               |  LL0: line 196
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
//LABEL               |  LL9: line 209
L9: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_1 = 0x00000000;
//LABEL               | LL10:
L10: ;
//RETURN              |     |return v0
return v0_1;
//LABEL               |  LL1: line 322
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
//LABEL               |  LL2: line 326
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
//LABEL               |  LL8: line 334
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
//LABEL               | LL17: line 146
L17: ;
//INVOKE_VIRTUAL      |     |TEMP=v18.getIntent()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.getIntent()Landroid/content/Intent;
jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "getIntent", "()Landroid/content/Intent;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v18, methodId0);
//MOVE_RESULT         |     |v6=TEMP0
jobject v6_0 = TEMP0;
//LABEL               | LL16: line 147
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
//LABEL               | LL10: line 148
L10: ;
//IF_EQZ              |     |if (v9 == 0) { goto L1; }
if (v9_0 == 0) { goto L1; }
//LABEL               | LL18: line 149
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
//LABEL               |  LL0: line 151
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

//LABEL               | LL19: line 152
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

//LABEL               | LL20: line 153
L20: ;
//CONST               |     |v13=0x00000000  // int:0   float:0.000000
v13_3 = 0x00000000;
//MOVE                |     |v0 = v18
v0_0 = v18;
//IPUT                |     |v0.lastSeenTrackGroupArray=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.lastSeenTrackGroupArray Lcom/google/android/exoplayer2/source/TrackGroupArray;
jclass localClass9 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId5 = (*env)->GetFieldID(env, localClass9, "lastSeenTrackGroupArray", "Lcom/google/android/exoplayer2/source/TrackGroupArray;");
(*env)->SetObjectField(env, v0_0, fieldId5, v13_3);

//LABEL               | LL21: line 154
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

//LABEL               | LL22: line 156
L22: ;
//CONST               |     |v3=0x00000000  // int:0   float:0.000000
jint v3_0 = 0x00000000;
//LABEL               |  LL2: line 158
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
//LABEL               |  LL4: line 160
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
//LABEL               |  LL3: line 164
L3: ;
//NEW_INSTANCE        |     |v11=NEW Lcom/google/android/exoplayer2/DefaultRenderersFactory;
jobject v11_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/DefaultRenderersFactory"));

//MOVE                |     |v0 = v18
v0_0 = v18;
//INVOKE_DIRECT       |     |v11.<init>(v0_0,v3_0,v4_0)  //Lcom/google/android/exoplayer2/DefaultRenderersFactory;.<init>(Landroid/content/Context;Lcom/google/android/exoplayer2/drm/DrmSessionManager;I)V
jclass localClass16 = (*env)->FindClass(env, "com/google/android/exoplayer2/DefaultRenderersFactory");
jmethodID methodId8 = (*env)->GetMethodID(env, localClass16, "<init>", "(Landroid/content/Context;Lcom/google/android/exoplayer2/drm/DrmSessionManager;I)V");
(*env)->CallVoidMethod(env, v11_0, methodId8, v0_0,v3_0,v4_0);
//LABEL               |  LL5: line 167
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

//LABEL               | LL24: line 168
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
//LABEL               | LL25: line 169
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
//LABEL               | LL26: line 170
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
//LABEL               | LL27: line 171
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
//LABEL               | LL28: line 173
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
//LABEL               | LL29: line 174
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
//LABEL               | LL30: line 175
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
//LABEL               |  LL1: line 179
L1: ;
//CONST_STRING        |     |v13="http://www.youtube.com/api/manifest/dash/id/3aa39fa2cc27967f/source/youtube?as=fmp4_audio_clear,fmp4_sd_hd_clear&sparams=ip,ipbits,expire,source,id,as&ip=0.0.0.0&ipbits=0&expire=19000000000&signature=A2716F75795F5D2AF0E88962FFCD10DB79384F29.84308FF04844498CE6FBCE4731507882B8307798&key=ik0"
jstring v13_13 = (*env)->NewStringUTF(env, "http://www.youtube.com/api/manifest/dash/id/3aa39fa2cc27967f/source/youtube?as=fmp4_audio_clear,fmp4_sd_hd_clear&sparams=ip,ipbits,expire,source,id,as&ip=0.0.0.0&ipbits=0&expire=19000000000&signature=A2716F75795F5D2AF0E88962FFCD10DB79384F29.84308FF04844498CE6FBCE4731507882B8307798&key=ik0");
//INVOKE_STATIC       |     |TEMP=android.net.Uri.parse(v13_13)  //Landroid/net/Uri;.parse(Ljava/lang/String;)Landroid/net/Uri;
jclass localClass44 = (*env)->FindClass(env, "android/net/Uri");
jmethodID methodId18 = (*env)->GetStaticMethodID(env, localClass44, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
jobject TEMP5 = (*env)->CallStaticObjectMethod(env, localClass44, methodId18, v13_13);
//MOVE_RESULT         |     |v12=TEMP5
jobject v12_0 = TEMP5;
//LABEL               | LL11: line 181
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
//LABEL               |  LL9: line 183
L9: ;
//MOVE                |     |v7 = v8
jobject v7_0 = v8_0;
//LABEL               |  LL8: line 185
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
//LABEL               |  LL6: line 186
L6: ;
//IF_EQZ              |     |if (v5 == 0) { goto L31; }
if (v5_0 == 0) { goto L31; }
//LABEL               | LL32: line 187
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
//LABEL               | LL34: line 190
L34: ;
//CONST               |     |v13=0x00000000  // int:0   float:0.000000
v13_16 = 0x00000000;
//MOVE                |     |v0 = v18
v0_2 = v18;
//IPUT                |     |v0.inErrorState=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.inErrorState Z
jclass localClass53 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId31 = (*env)->GetFieldID(env, localClass53, "inErrorState", "Z");
(*env)->SetBooleanField(env, v0_2, fieldId31, v13_16);

//LABEL               | LL35: line 191
L35: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL7: line 275
L7: ;
//CONST               |     |v9=0x00000000  // int:0   float:0.000000
v9_0 = 0x00000000;
//GOTO                |     |goto L10;
goto L10;
//LABEL               | LL12: line 288
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
//LABEL               | LL13: line 313
L13: ;
//CONST               |     |v5=0x00000000  // int:0   float:0.000000
v5_0 = 0x00000000;
//GOTO                |     |goto L6;
goto L6;
//LABEL               | LL14: line 317
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
//LABEL               |  LL0: line 220
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
//LABEL               |  LL2: line 221
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
//LABEL               |  LL0: line 224
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
//LABEL               |  LL2: line 225
L2: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0006  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumNumber(I)I
jint  Java_com_google_android_exoplayer2_demo_PlayerActivity_sumNumber_1263137(JNIEnv * env, jobject  v2, jint v3)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> i // I 
//LOCAL_VARIABLE LL2 ~ LL1 v1 -> sum // I 
//LOCAL_VARIABLE LL3 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL3 ~ LL1 v3 -> count // I 
//LABEL               |  LL3: line 129
L3: ;
//CONST               |     |v1=0x00000000  // int:0   float:0.000000
jint v1_0 = 0x00000000;
//LABEL               |  LL2: line 131
L2: ;
//CONST               |     |v0=0x00000000  // int:0   float:0.000000
jint v0_0 = 0x00000000;
//LABEL               |  LL0:
L0: ;
//IF_GT               |     |if (v0 >  v3) {  goto L4; }
if (v0_0 > v3) {  goto L4; }
//LABEL               |  LL5: line 132
L5: ;
//ADD                 |     |v1 = v1 + v0;
v1_0 = v1_0 + v0_0;
//LABEL               |  LL6: line 131
L6: ;
//ADD_INT_LIT_X       |     |v0 = v0 + 1;
v0_0 = v0_0 + 1;
//GOTO                |     |goto L0;
goto L0;
//LABEL               |  LL4: line 134
L4: ;
//RETURN              |     |return v1
return v1_0;
//LABEL               |  LL1:
L1: ;
}


//method:0007  access:0x0001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.onCreate(Landroid/os/Bundle;)V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_onCreate_2045109055(JNIEnv * env, jobject  v4, jobject v5)
{
//LOCAL_VARIABLE LL0 ~ LL1 v0 -> b // Landroid/widget/Button; 
//LOCAL_VARIABLE LL2 ~ LL1 v4 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LOCAL_VARIABLE LL2 ~ LL1 v5 -> savedInstanceState // Landroid/os/Bundle; 
//LABEL               |  LL2: line 101
L2: ;
//CONST               |     |v3=0x00000001  // int:1   float:0.000000
jint v3_0 = 0x00000001;
//LABEL               |  LL3: line 101
L3: ;
//INVOKE_SUPER        |     |v4.onCreate(v5)  //Landroid/app/Activity;.onCreate(Landroid/os/Bundle;)V
jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "onCreate", "(Landroid/os/Bundle;)V");
(*env)->CallNonvirtualVoidMethod(env, v4, localClass0, methodId0, v5);
//LABEL               |  LL4: line 103
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

//LABEL               |  LL5: line 104
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

//LABEL               |  LL6: line 105
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
//LABEL               |  LL7: line 107
L7: ;
//IPUT                |     |v4.shouldAutoPlay=v3  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.shouldAutoPlay Z
jclass localClass8 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId4 = (*env)->GetFieldID(env, localClass8, "shouldAutoPlay", "Z");
(*env)->SetBooleanField(env, v4, fieldId4, v3_0);

//LABEL               |  LL8: line 109
L8: ;
//INVOKE_DIRECT       |     |TEMP=v4.buildDataSourceFactory(v3_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass9 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId4 = (*env)->GetMethodID(env, localClass9, "buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
jobject TEMP0 = (*env)->CallObjectMethod(env, v4, methodId4, v3_0);
//MOVE_RESULT         |     |v1=TEMP0
jobject v1_2 = TEMP0;
//IPUT                |     |v4.mediaDataSourceFactory=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jclass localClass10 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId5 = (*env)->GetFieldID(env, localClass10, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
(*env)->SetObjectField(env, v4, fieldId5, v1_2);

//LABEL               |  LL9: line 110
L9: ;
//NEW_INSTANCE        |     |v1=NEW Landroid/os/Handler;
jobject v1_3 = (*env)->AllocObject(env, (*env)->FindClass(env, "android/os/Handler"));

//INVOKE_DIRECT       |     |v1.<init>()  //Landroid/os/Handler;.<init>()V
jclass localClass11 = (*env)->FindClass(env, "android/os/Handler");
jmethodID methodId5 = (*env)->GetMethodID(env, localClass11, "<init>", "()V");
(*env)->CallVoidMethod(env, v1_3, methodId5);
//IPUT                |     |v4.mainHandler=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
jclass localClass12 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId6 = (*env)->GetFieldID(env, localClass12, "mainHandler", "Landroid/os/Handler;");
(*env)->SetObjectField(env, v4, fieldId6, v1_3);

//LABEL               | LL10: line 111
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
//LABEL               | LL12: line 112
L12: ;
//SGET                |     |v1=com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
jclass localClass15 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId8 = (*env)->GetStaticFieldID(env, localClass15, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
jobject v1_5 = (*env)->GetStaticObjectField(env, localClass15, fieldId8);
//INVOKE_STATIC       |     |java.net.CookieHandler.setDefault(v1_5)  //Ljava/net/CookieHandler;.setDefault(Ljava/net/CookieHandler;)V
jclass localClass16 = (*env)->FindClass(env, "java/net/CookieHandler");
jmethodID methodId7 = (*env)->GetStaticMethodID(env, localClass16, "setDefault", "(Ljava/net/CookieHandler;)V");
(*env)->CallStaticVoidMethod(env, localClass16, methodId7, v1_5);
//LABEL               | LL11: line 115
L11: ;
//CONST               |     |v1=0x7f040003  // int:2130968579   float:175458156290837700000000000000000000000.000000
jint v1_6 = 0x7f040003;
//INVOKE_VIRTUAL      |     |v4.setContentView(v1_6)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.setContentView(I)V
jclass localClass17 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId8 = (*env)->GetMethodID(env, localClass17, "setContentView", "(I)V");
(*env)->CallVoidMethod(env, v4, methodId8, v1_6);
//LABEL               | LL13: line 117
L13: ;
//CONST               |     |v1=0x7f09001b  // int:2131296283   float:182104783047592770000000000000000000000.000000
v1_6 = 0x7f09001b;
//INVOKE_VIRTUAL      |     |TEMP=v4.findViewById(v1_6)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass18 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId9 = (*env)->GetMethodID(env, localClass18, "findViewById", "(I)Landroid/view/View;");
jobject TEMP2 = (*env)->CallObjectMethod(env, v4, methodId9, v1_6);
//MOVE_RESULT         |     |v0=TEMP2
jobject v0_0 = TEMP2;
//CHECK_CAST          |     |v0=(android.widget.Button) v0
//LABEL               |  LL0: line 118
L0: ;
//NEW_INSTANCE        |     |v1=NEW Ljava/lang/StringBuilder;
jobject v1_7 = (*env)->AllocObject(env, (*env)->FindClass(env, "java/lang/StringBuilder"));

//INVOKE_DIRECT       |     |v1.<init>()  //Ljava/lang/StringBuilder;.<init>()V
jclass localClass19 = (*env)->FindClass(env, "java/lang/StringBuilder");
jmethodID methodId10 = (*env)->GetMethodID(env, localClass19, "<init>", "()V");
(*env)->CallVoidMethod(env, v1_7, methodId10);
//CONST               |     |v2=0x00000064  // int:100   float:0.000000
jint v2_2 = 0x00000064;
//INVOKE_DIRECT       |     |TEMP=v4.sumNumber(v2_2)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.sumNumber(I)I
jclass localClass20 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId11 = (*env)->GetMethodID(env, localClass20, "sumNumber", "(I)I");
jint TEMP3 = (*env)->CallIntMethod(env, v4, methodId11, v2_2);
//MOVE_RESULT         |     |v2=TEMP3
v2_2 = TEMP3;
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
//CONST               |     |v1=0x7f09001e  // int:2131296286   float:182104843894821600000000000000000000000.000000
jint v1_9 = 0x7f09001e;
//INVOKE_VIRTUAL      |     |TEMP=v4.findViewById(v1_9)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass25 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId16 = (*env)->GetMethodID(env, localClass25, "findViewById", "(I)Landroid/view/View;");
jobject TEMP7 = (*env)->CallObjectMethod(env, v4, methodId16, v1_9);
//MOVE_RESULT         |     |v1=TEMP7
jobject v1_10 = TEMP7;
//CHECK_CAST          |     |v1=(android.widget.LinearLayout) v1
//IPUT                |     |v4.debugRootView=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugRootView Landroid/widget/LinearLayout;
jclass localClass26 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId9 = (*env)->GetFieldID(env, localClass26, "debugRootView", "Landroid/widget/LinearLayout;");
(*env)->SetObjectField(env, v4, fieldId9, v1_10);

//LABEL               | LL14: line 121
L14: ;
//CONST               |     |v1=0x7f09001d  // int:2131296285   float:182104823612411980000000000000000000000.000000
jint v1_11 = 0x7f09001d;
//INVOKE_VIRTUAL      |     |TEMP=v4.findViewById(v1_11)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass27 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId17 = (*env)->GetMethodID(env, localClass27, "findViewById", "(I)Landroid/view/View;");
jobject TEMP8 = (*env)->CallObjectMethod(env, v4, methodId17, v1_11);
//MOVE_RESULT         |     |v1=TEMP8
jobject v1_12 = TEMP8;
//CHECK_CAST          |     |v1=(android.widget.TextView) v1
//IPUT                |     |v4.debugTextView=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugTextView Landroid/widget/TextView;
jclass localClass28 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId10 = (*env)->GetFieldID(env, localClass28, "debugTextView", "Landroid/widget/TextView;");
(*env)->SetObjectField(env, v4, fieldId10, v1_12);

//LABEL               | LL15: line 122
L15: ;
//CONST               |     |v1=0x7f09001f  // int:2131296287   float:182104864177231200000000000000000000000.000000
jint v1_13 = 0x7f09001f;
//INVOKE_VIRTUAL      |     |TEMP=v4.findViewById(v1_13)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass29 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId18 = (*env)->GetMethodID(env, localClass29, "findViewById", "(I)Landroid/view/View;");
jobject TEMP9 = (*env)->CallObjectMethod(env, v4, methodId18, v1_13);
//MOVE_RESULT         |     |v1=TEMP9
jobject v1_14 = TEMP9;
//CHECK_CAST          |     |v1=(android.widget.Button) v1
//IPUT                |     |v4.retryButton=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.retryButton Landroid/widget/Button;
jclass localClass30 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId11 = (*env)->GetFieldID(env, localClass30, "retryButton", "Landroid/widget/Button;");
(*env)->SetObjectField(env, v4, fieldId11, v1_14);

//LABEL               | LL16: line 124
L16: ;
//CONST               |     |v1=0x7f09001c  // int:2131296284   float:182104803330002380000000000000000000000.000000
jint v1_15 = 0x7f09001c;
//INVOKE_VIRTUAL      |     |TEMP=v4.findViewById(v1_15)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
jclass localClass31 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId19 = (*env)->GetMethodID(env, localClass31, "findViewById", "(I)Landroid/view/View;");
jobject TEMP10 = (*env)->CallObjectMethod(env, v4, methodId19, v1_15);
//MOVE_RESULT         |     |v1=TEMP10
jobject v1_16 = TEMP10;
//CHECK_CAST          |     |v1=(com.google.android.exoplayer2.ui.SimpleExoPlayerView) v1
//IPUT                |     |v4.simpleExoPlayerView=v1  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
jclass localClass32 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId12 = (*env)->GetFieldID(env, localClass32, "simpleExoPlayerView", "Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;");
(*env)->SetObjectField(env, v4, fieldId12, v1_16);

//LABEL               | LL17: line 125
L17: ;
//IGET                |     |v1=v4.simpleExoPlayerView  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
jclass localClass33 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jfieldID fieldId13 = (*env)->GetFieldID(env, localClass33, "simpleExoPlayerView", "Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;");
jobject v1_17 = (*env)->GetObjectField(env, v4, fieldId13);

//INVOKE_VIRTUAL      |     |TEMP=v1.requestFocus()  //Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;.requestFocus()Z
jclass localClass34 = (*env)->FindClass(env, "com/google/android/exoplayer2/ui/SimpleExoPlayerView");
jmethodID methodId20 = (*env)->GetMethodID(env, localClass34, "requestFocus", "()Z");
jboolean TEMP11 = (*env)->CallBooleanMethod(env, v1_17, methodId20);
//LABEL               | LL18: line 126
L18: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}


//method:0008  access:0x0001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.onResume()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_onResume_39797(JNIEnv * env, jobject  v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity; 
//LABEL               |  LL0: line 139
L0: ;
//INVOKE_SUPER        |     |v2.onResume()  //Landroid/app/Activity;.onResume()V
jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "onResume", "()V");
(*env)->CallNonvirtualVoidMethod(env, v2, localClass0, methodId0);
//LABEL               |  LL2: line 140
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
//LABEL               |  LL3: line 141
L3: ;
//INVOKE_DIRECT       |     |v2.initializePlayer()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.initializePlayer()V
jclass localClass3 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
jmethodID methodId1 = (*env)->GetMethodID(env, localClass3, "initializePlayer", "()V");
(*env)->CallVoidMethod(env, v2, methodId1);
//LABEL               |  LL4: line 143
L4: ;
//RETURN_VOID         |     |return
return;
//LABEL               |  LL1:
L1: ;
}

int registerNativeSymbols420217909_442(JNIEnv * env) { 
int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = { 
{"__initNative", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity___initNative_39797 },
{"buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_buildDataSourceFactory_1578816035 },
{"buildMediaSource", "(Landroid/net/Uri;Ljava/lang/String;)Lcom/google/android/exoplayer2/source/MediaSource;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_buildMediaSource_1776506356 },
{"initializePlayer", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_initializePlayer_39797 },
{"showToast", "(I)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast_1263150 },
{"showToast", "(Ljava/lang/String;)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast_1428966913 },
{"sumNumber", "(I)I",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_sumNumber_1263137 },
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
