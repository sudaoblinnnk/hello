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
//void  Java_com_google_android_exoplayer2_demo_PlayerActivity_<init>39797(JNIEnv * env, jobject  v0)
//{
////LOCAL_VARIABLE LL0 ~ LL1 v0 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
////LABEL               |  LL0: line 59
//L0: ;
////INVOKE_DIRECT       |     |v0.<init>()  //Landroid/app/Activity;.<init>()V
//jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
//jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "<init>", "()V");
//(*env)->CallVoidMethod(env, v0, methodId0);
////RETURN_VOID         |     |return
//return;
////LABEL               |  LL1:
//L1: ;
//}


//method:0001  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
jobject  Java_com_google_android_exoplayer2_demo_PlayerActivity_buildDataSourceFactory1578816035(JNIEnv * env, jobject  v2, jboolean v3)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LOCAL_VARIABLE LL0 ~ LL1 v3 -> useBandwidthMeter // Z
//LABEL               |  LL0: line 187
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
//LABEL               |  LL3: line 188
    L3: ;
//INVOKE_VIRTUAL      |     |TEMP=v0.buildDataSourceFactory(v1_0)  //Lcom/google/android/exoplayer2/demo/DemoApplication;.buildDataSourceFactory(Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/DemoApplication");
    jmethodID methodId1 = (*env)->GetMethodID(env, localClass2, "buildDataSourceFactory", "(Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject TEMP1 = (*env)->CallObjectMethod(env, v0_0, methodId1, v1_0);
//MOVE_RESULT         |     |v0=TEMP1
    jobject v0_1 = TEMP1;
//LABEL               |  LL4: line 187
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
jobject  Java_com_google_android_exoplayer2_demo_PlayerActivity_buildMediaSource1776506356(JNIEnv * env, jobject  v6, jobject v7, jstring v8)
{
//LOCAL_VARIABLE LL0 ~ LL1 v6 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LOCAL_VARIABLE LL0 ~ LL1 v7 -> uri // Landroid/net/Uri;
//LOCAL_VARIABLE LL0 ~ LL1 v8 -> overrideExtension // Ljava/lang/String;
//LABEL               |  LL0: line 182
    L0: ;
//NEW_INSTANCE        |     |v0=NEW Lcom/google/android/exoplayer2/source/dash/DashMediaSource;
    jobject v0_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DashMediaSource"));

//CONST               |     |v1=0x00000000  // int:0   float:0.000000
    jint v1_0 = 0x00000000;
//INVOKE_DIRECT       |     |TEMP=v6.buildDataSourceFactory(v1_0)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.buildDataSourceFactory(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject TEMP0 = (*env)->CallObjectMethod(env, v6, methodId0, v1_0);
//MOVE_RESULT         |     |v2=TEMP0
    jobject v2_0 = TEMP0;
//NEW_INSTANCE        |     |v3=NEW Lcom/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory;
    jobject v3_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory"));

//IGET                |     |v1=v6.mediaDataSourceFactory  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
    jclass localClass1 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId0 = (*env)->GetFieldID(env, localClass1, "mediaDataSourceFactory", "Lcom/google/android/exoplayer2/upstream/DataSource$Factory;");
    jobject v1_1 = (*env)->GetObjectField(env, v6, fieldId0);

//INVOKE_DIRECT       |     |v3.<init>(v1_1)  //Lcom/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory;.<init>(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V
    jclass localClass2 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DefaultDashChunkSource$Factory");
    jmethodID methodId1 = (*env)->GetMethodID(env, localClass2, "<init>", "(Lcom/google/android/exoplayer2/upstream/DataSource$Factory;)V");
    (*env)->CallVoidMethod(env, v3_0, methodId1, v1_1);
//IGET                |     |v4=v6.mainHandler  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
    jclass localClass3 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId1 = (*env)->GetFieldID(env, localClass3, "mainHandler", "Landroid/os/Handler;");
    jobject v4_0 = (*env)->GetObjectField(env, v6, fieldId1);

//IGET                |     |v5=v6.eventLogger  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
    jclass localClass4 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId2 = (*env)->GetFieldID(env, localClass4, "eventLogger", "Lcom/google/android/exoplayer2/demo/EventLogger;");
    jobject v5_0 = (*env)->GetObjectField(env, v6, fieldId2);

//MOVE                |     |v1 = v7
    jobject v1_2 = v7;
//INVOKE_DIRECT       |     |v0.<init>(v1_2,v2_0,v3_0,v4_0,v5_0)  //Lcom/google/android/exoplayer2/source/dash/DashMediaSource;.<init>(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/dash/DashChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V
    jclass localClass5 = (*env)->FindClass(env, "com/google/android/exoplayer2/source/dash/DashMediaSource");
    jmethodID methodId2 = (*env)->GetMethodID(env, localClass5, "<init>", "(Landroid/net/Uri;Lcom/google/android/exoplayer2/upstream/DataSource$Factory;Lcom/google/android/exoplayer2/source/dash/DashChunkSource$Factory;Landroid/os/Handler;Lcom/google/android/exoplayer2/source/AdaptiveMediaSourceEventListener;)V");
    (*env)->CallVoidMethod(env, v0_0, methodId2, v1_2,v2_0,v3_0,v4_0,v5_0);
//RETURN              |     |return v0
    return v0_0;
//LABEL               |  LL1:
    L1: ;
}


//method:0003  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.initializePlayer()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_initializePlayer39797(JNIEnv * env, jobject  v18)
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
//LABEL               | LL17: line 134
    L17: ;
//INVOKE_VIRTUAL      |     |TEMP=v18.getIntent()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.getIntent()Landroid/content/Intent;
    jclass localClass0 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "getIntent", "()Landroid/content/Intent;");
    jobject TEMP0 = (*env)->CallObjectMethod(env, v18, methodId0);
//MOVE_RESULT         |     |v6=TEMP0
    jobject v6_0 = TEMP0;
//LABEL               | LL16: line 135
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
//LABEL               | LL10: line 136
    L10: ;
//IF_EQZ              |     |if (v9 == 0) { goto L1; }
    if (v9_0 == 0) { goto L1; }
//LABEL               | LL18: line 137
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
//LABEL               |  LL0: line 139
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

//LABEL               | LL19: line 140
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

//LABEL               | LL20: line 141
    L20: ;
//CONST               |     |v13=0x00000000  // int:0   float:0.000000
    v13_3 = 0x00000000;
//MOVE                |     |v0 = v18
    v0_0 = v18;
//IPUT                |     |v0.lastSeenTrackGroupArray=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.lastSeenTrackGroupArray Lcom/google/android/exoplayer2/source/TrackGroupArray;
    jclass localClass9 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId5 = (*env)->GetFieldID(env, localClass9, "lastSeenTrackGroupArray", "Lcom/google/android/exoplayer2/source/TrackGroupArray;");
    (*env)->SetObjectField(env, v0_0, fieldId5, v13_3);

//LABEL               | LL21: line 142
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

//LABEL               | LL22: line 144
    L22: ;
//CONST               |     |v3=0x00000000  // int:0   float:0.000000
    jint v3_0 = 0x00000000;
//LABEL               |  LL2: line 146
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
//LABEL               |  LL4: line 148
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
//LABEL               |  LL3: line 152
    L3: ;
//NEW_INSTANCE        |     |v11=NEW Lcom/google/android/exoplayer2/DefaultRenderersFactory;
    jobject v11_0 = (*env)->AllocObject(env, (*env)->FindClass(env, "com/google/android/exoplayer2/DefaultRenderersFactory"));

//MOVE                |     |v0 = v18
    v0_0 = v18;
//INVOKE_DIRECT       |     |v11.<init>(v0_0,v3_0,v4_0)  //Lcom/google/android/exoplayer2/DefaultRenderersFactory;.<init>(Landroid/content/Context;Lcom/google/android/exoplayer2/drm/DrmSessionManager;I)V
    jclass localClass16 = (*env)->FindClass(env, "com/google/android/exoplayer2/DefaultRenderersFactory");
    jmethodID methodId8 = (*env)->GetMethodID(env, localClass16, "<init>", "(Landroid/content/Context;Lcom/google/android/exoplayer2/drm/DrmSessionManager;I)V");
    (*env)->CallVoidMethod(env, v11_0, methodId8, v0_0,v3_0,v4_0);
//LABEL               |  LL5: line 155
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

//LABEL               | LL24: line 156
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
//LABEL               | LL25: line 157
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
//LABEL               | LL26: line 158
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
//LABEL               | LL27: line 159
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
//LABEL               | LL28: line 161
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
//LABEL               | LL29: line 162
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
//LABEL               | LL30: line 163
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
//LABEL               |  LL1: line 167
    L1: ;
//CONST_STRING        |     |v13="http://www.youtube.com/api/manifest/dash/id/3aa39fa2cc27967f/source/youtube?as=fmp4_audio_clear,fmp4_sd_hd_clear&sparams=ip,ipbits,expire,source,id,as&ip=0.0.0.0&ipbits=0&expire=19000000000&signature=A2716F75795F5D2AF0E88962FFCD10DB79384F29.84308FF04844498CE6FBCE4731507882B8307798&key=ik0"
    jstring v13_13 = (*env)->NewStringUTF(env, "http://www.youtube.com/api/manifest/dash/id/3aa39fa2cc27967f/source/youtube?as=fmp4_audio_clear,fmp4_sd_hd_clear&sparams=ip,ipbits,expire,source,id,as&ip=0.0.0.0&ipbits=0&expire=19000000000&signature=A2716F75795F5D2AF0E88962FFCD10DB79384F29.84308FF04844498CE6FBCE4731507882B8307798&key=ik0");
//INVOKE_STATIC       |     |TEMP=android.net.Uri.parse(v13_13)  //Landroid/net/Uri;.parse(Ljava/lang/String;)Landroid/net/Uri;
    jclass localClass44 = (*env)->FindClass(env, "android/net/Uri");
    jmethodID methodId18 = (*env)->GetStaticMethodID(env, localClass44, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    jobject TEMP5 = (*env)->CallStaticObjectMethod(env, localClass44, methodId18, v13_13);
//MOVE_RESULT         |     |v12=TEMP5
    jobject v12_0 = TEMP5;
//LABEL               | LL11: line 169
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
//LABEL               |  LL9: line 171
    L9: ;
//MOVE                |     |v7 = v8
    jobject v7_0 = v8_0;
//LABEL               |  LL8: line 173
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
//LABEL               |  LL6: line 174
    L6: ;
//IF_EQZ              |     |if (v5 == 0) { goto L31; }
    if (v5_0 == 0) { goto L31; }
//LABEL               | LL32: line 175
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
//LABEL               | LL34: line 178
    L34: ;
//CONST               |     |v13=0x00000000  // int:0   float:0.000000
    v13_16 = 0x00000000;
//MOVE                |     |v0 = v18
    v0_2 = v18;
//IPUT                |     |v0.inErrorState=v13  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.inErrorState Z
    jclass localClass53 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId31 = (*env)->GetFieldID(env, localClass53, "inErrorState", "Z");
    (*env)->SetBooleanField(env, v0_2, fieldId31, v13_16);

//LABEL               | LL35: line 179
    L35: ;
//RETURN_VOID         |     |return
    return;
//LABEL               |  LL7: line 263
    L7: ;
//CONST               |     |v9=0x00000000  // int:0   float:0.000000
    v9_0 = 0x00000000;
//GOTO                |     |goto L10;
    goto L10;
//LABEL               | LL12: line 276
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
//LABEL               | LL13: line 301
    L13: ;
//CONST               |     |v5=0x00000000  // int:0   float:0.000000
    v5_0 = 0x00000000;
//GOTO                |     |goto L6;
    goto L6;
//LABEL               | LL14: line 305
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
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast1263150(JNIEnv * env, jobject  v1, jint v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v1 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> messageId // I
//LABEL               |  LL0: line 192
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
//LABEL               |  LL2: line 193
    L2: ;
//RETURN_VOID         |     |return
    return;
//LABEL               |  LL1:
    L1: ;
}


//method:0005  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.showToast(Ljava/lang/String;)V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast1428966913(JNIEnv * env, jobject  v2, jstring v3)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LOCAL_VARIABLE LL0 ~ LL1 v3 -> message // Ljava/lang/String;
//LABEL               |  LL0: line 196
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
//LABEL               |  LL2: line 197
    L2: ;
//RETURN_VOID         |     |return
    return;
//LABEL               |  LL1:
    L1: ;
}


//method:0006  access:0x0001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.onCreate(Landroid/os/Bundle;)V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_onCreate2045109055(JNIEnv * env, jobject  v3, jobject v4)
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

//LABEL               |  LL4: line 104
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

//LABEL               |  LL5: line 105
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
//LABEL               |  LL6: line 107
    L6: ;
//IPUT                |     |v3.shouldAutoPlay=v2  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.shouldAutoPlay Z
    jclass localClass8 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId4 = (*env)->GetFieldID(env, localClass8, "shouldAutoPlay", "Z");
    (*env)->SetBooleanField(env, v3, fieldId4, v2_0);

//LABEL               |  LL7: line 109
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

//LABEL               |  LL8: line 110
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

//LABEL               |  LL9: line 111
    L9: ;
//INVOKE_STATIC       |     |TEMP=java.net.CookieHandler.getDefault()  //Ljava/net/CookieHandler;.getDefault()Ljava/net/CookieHandler;
    jclass localClass13 = (*env)->FindClass(env, "java/net/CookieHandler");
    jmethodID methodId6 = (*env)->GetStaticMethodID(env, localClass13, "getDefault", "()Ljava/net/CookieHandler;");
    jobject TEMP1 = (*env)->CallStaticObjectMethod(env, localClass13, methodId6);
//MOVE_RESULT         |     |v0=TEMP1
    jobject v0_4 = TEMP1;
//SGET                |     |v1=com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
    jclass localClass14 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId7 = (*env)->GetStaticFieldID(env, localClass14, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
    jobject v1_1 = (*env)->GetStaticObjectField(env, localClass14, fieldId7);
//IF_EQ               |     |if (v0 == v1) {  goto L10; }
    if (v0_4 == v1_1) {  goto L10; }
//LABEL               | LL11: line 112
    L11: ;
//SGET                |     |v0=com.google.android.exoplayer2.demo.PlayerActivity.DEFAULT_COOKIE_MANAGER  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
    jclass localClass15 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId8 = (*env)->GetStaticFieldID(env, localClass15, "DEFAULT_COOKIE_MANAGER", "Ljava/net/CookieManager;");
    jobject v0_5 = (*env)->GetStaticObjectField(env, localClass15, fieldId8);
//INVOKE_STATIC       |     |java.net.CookieHandler.setDefault(v0_5)  //Ljava/net/CookieHandler;.setDefault(Ljava/net/CookieHandler;)V
    jclass localClass16 = (*env)->FindClass(env, "java/net/CookieHandler");
    jmethodID methodId7 = (*env)->GetStaticMethodID(env, localClass16, "setDefault", "(Ljava/net/CookieHandler;)V");
    (*env)->CallStaticVoidMethod(env, localClass16, methodId7, v0_5);
//LABEL               | LL10: line 115
    L10: ;
//CONST               |     |v0=0x7f040003  // int:2130968579   float:175458156290837700000000000000000000000.000000
    jint v0_6 = 0x7f040003;
//INVOKE_VIRTUAL      |     |v3.setContentView(v0_6)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.setContentView(I)V
    jclass localClass17 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId8 = (*env)->GetMethodID(env, localClass17, "setContentView", "(I)V");
    (*env)->CallVoidMethod(env, v3, methodId8, v0_6);
//LABEL               | LL12: line 117
    L12: ;
//CONST               |     |v0=0x7f09001d  // int:2131296285   float:182104823612411980000000000000000000000.000000
    v0_6 = 0x7f09001d;
//INVOKE_VIRTUAL      |     |TEMP=v3.findViewById(v0_6)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
    jclass localClass18 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId9 = (*env)->GetMethodID(env, localClass18, "findViewById", "(I)Landroid/view/View;");
    jobject TEMP2 = (*env)->CallObjectMethod(env, v3, methodId9, v0_6);
//MOVE_RESULT         |     |v0=TEMP2
    jobject v0_7 = TEMP2;
//CHECK_CAST          |     |v0=(android.widget.LinearLayout) v0
//IPUT                |     |v3.debugRootView=v0  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugRootView Landroid/widget/LinearLayout;
    jclass localClass19 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId9 = (*env)->GetFieldID(env, localClass19, "debugRootView", "Landroid/widget/LinearLayout;");
    (*env)->SetObjectField(env, v3, fieldId9, v0_7);

//LABEL               | LL13: line 118
    L13: ;
//CONST               |     |v0=0x7f09001c  // int:2131296284   float:182104803330002380000000000000000000000.000000
    jint v0_8 = 0x7f09001c;
//INVOKE_VIRTUAL      |     |TEMP=v3.findViewById(v0_8)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
    jclass localClass20 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId10 = (*env)->GetMethodID(env, localClass20, "findViewById", "(I)Landroid/view/View;");
    jobject TEMP3 = (*env)->CallObjectMethod(env, v3, methodId10, v0_8);
//MOVE_RESULT         |     |v0=TEMP3
    jobject v0_9 = TEMP3;
//CHECK_CAST          |     |v0=(android.widget.TextView) v0
//IPUT                |     |v3.debugTextView=v0  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugTextView Landroid/widget/TextView;
    jclass localClass21 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId10 = (*env)->GetFieldID(env, localClass21, "debugTextView", "Landroid/widget/TextView;");
    (*env)->SetObjectField(env, v3, fieldId10, v0_9);

//LABEL               | LL14: line 119
    L14: ;
//CONST               |     |v0=0x7f09001e  // int:2131296286   float:182104843894821600000000000000000000000.000000
    jint v0_10 = 0x7f09001e;
//INVOKE_VIRTUAL      |     |TEMP=v3.findViewById(v0_10)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
    jclass localClass22 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId11 = (*env)->GetMethodID(env, localClass22, "findViewById", "(I)Landroid/view/View;");
    jobject TEMP4 = (*env)->CallObjectMethod(env, v3, methodId11, v0_10);
//MOVE_RESULT         |     |v0=TEMP4
    jobject v0_11 = TEMP4;
//CHECK_CAST          |     |v0=(android.widget.Button) v0
//IPUT                |     |v3.retryButton=v0  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.retryButton Landroid/widget/Button;
    jclass localClass23 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId11 = (*env)->GetFieldID(env, localClass23, "retryButton", "Landroid/widget/Button;");
    (*env)->SetObjectField(env, v3, fieldId11, v0_11);

//LABEL               | LL15: line 121
    L15: ;
//CONST               |     |v0=0x7f09001b  // int:2131296283   float:182104783047592770000000000000000000000.000000
    jint v0_12 = 0x7f09001b;
//INVOKE_VIRTUAL      |     |TEMP=v3.findViewById(v0_12)  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.findViewById(I)Landroid/view/View;
    jclass localClass24 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId12 = (*env)->GetMethodID(env, localClass24, "findViewById", "(I)Landroid/view/View;");
    jobject TEMP5 = (*env)->CallObjectMethod(env, v3, methodId12, v0_12);
//MOVE_RESULT         |     |v0=TEMP5
    jobject v0_13 = TEMP5;
//CHECK_CAST          |     |v0=(com.google.android.exoplayer2.ui.SimpleExoPlayerView) v0
//IPUT                |     |v3.simpleExoPlayerView=v0  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
    jclass localClass25 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId12 = (*env)->GetFieldID(env, localClass25, "simpleExoPlayerView", "Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;");
    (*env)->SetObjectField(env, v3, fieldId12, v0_13);

//LABEL               | LL16: line 122
    L16: ;
//IGET                |     |v0=v3.simpleExoPlayerView  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
    jclass localClass26 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jfieldID fieldId13 = (*env)->GetFieldID(env, localClass26, "simpleExoPlayerView", "Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;");
    jobject v0_14 = (*env)->GetObjectField(env, v3, fieldId13);

//INVOKE_VIRTUAL      |     |TEMP=v0.requestFocus()  //Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;.requestFocus()Z
    jclass localClass27 = (*env)->FindClass(env, "com/google/android/exoplayer2/ui/SimpleExoPlayerView");
    jmethodID methodId13 = (*env)->GetMethodID(env, localClass27, "requestFocus", "()Z");
    jboolean TEMP6 = (*env)->CallBooleanMethod(env, v0_14, methodId13);
//LABEL               | LL17: line 123
    L17: ;
//RETURN_VOID         |     |return
    return;
//LABEL               |  LL1:
    L1: ;
}


//method:0007  access:0x0001
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.onResume()V
void  Java_com_google_android_exoplayer2_demo_PlayerActivity_onResume39797(JNIEnv * env, jobject  v2)
{
//LOCAL_VARIABLE LL0 ~ LL1 v2 -> this // Lcom/google/android/exoplayer2/demo/PlayerActivity;
//LABEL               |  LL0: line 127
    L0: ;
//INVOKE_SUPER        |     |v2.onResume()  //Landroid/app/Activity;.onResume()V
    jclass localClass0 = (*env)->FindClass(env, "android/app/Activity");
    jmethodID methodId0 = (*env)->GetMethodID(env, localClass0, "onResume", "()V");
    (*env)->CallNonvirtualVoidMethod(env, v2, localClass0, methodId0);
//LABEL               |  LL2: line 128
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
//LABEL               |  LL3: line 129
    L3: ;
//INVOKE_DIRECT       |     |v2.initializePlayer()  //Lcom/google/android/exoplayer2/demo/PlayerActivity;.initializePlayer()V
    jclass localClass3 = (*env)->FindClass(env, "com/google/android/exoplayer2/demo/PlayerActivity");
    jmethodID methodId1 = (*env)->GetMethodID(env, localClass3, "initializePlayer", "()V");
    (*env)->CallVoidMethod(env, v2, methodId1);
//LABEL               |  LL4: line 131
    L4: ;
//RETURN_VOID         |     |return
    return;
//LABEL               |  LL1:
    L1: ;
}

int registerNativeSymbols420217909_442(JNIEnv * env) {
    int returnVal = JNI_TRUE; JNINativeMethod symbolListApi[] = {
        //{"<init>", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_<init>39797 },
        {"buildDataSourceFactory", "(Z)Lcom/google/android/exoplayer2/upstream/DataSource$Factory;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_buildDataSourceFactory1578816035 },
        {"buildMediaSource", "(Landroid/net/Uri;Ljava/lang/String;)Lcom/google/android/exoplayer2/source/MediaSource;",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_buildMediaSource1776506356 },
        {"initializePlayer", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_initializePlayer39797 },
        {"showToast", "(I)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast1263150 },
        {"showToast", "(Ljava/lang/String;)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_showToast1428966913 },
        {"onCreate", "(Landroid/os/Bundle;)V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_onCreate2045109055 },
        {"onResume", "()V",  (void *)Java_com_google_android_exoplayer2_demo_PlayerActivity_onResume39797 },
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
