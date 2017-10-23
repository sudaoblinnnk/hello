package com.google.android.exoplayer2.demo;
//class:0650  access:0x0001
public class PlayerActivity extends android.app.Activity
{



//field:0000  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.ACTION_VIEW Ljava/lang/String;
public static final  java.lang.String ACTION_VIEW="com.google.android.exoplayer.demo.action.VIEW";
//field:0001  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.ACTION_VIEW_LIST Ljava/lang/String;
public static final  java.lang.String ACTION_VIEW_LIST="com.google.android.exoplayer.demo.action.VIEW_LIST";
//field:0002  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.AD_TAG_URI_EXTRA Ljava/lang/String;
public static final  java.lang.String AD_TAG_URI_EXTRA="ad_tag_uri";
//field:0003  access:0x000a
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.BANDWIDTH_METER Lcom/google/android/exoplayer2/upstream/DefaultBandwidthMeter;
private static  com.google.android.exoplayer2.upstream.DefaultBandwidthMeter BANDWIDTH_METER;
//field:0004  access:0x000a
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.DEFAULT_COOKIE_MANAGER Ljava/net/CookieManager;
private static  java.net.CookieManager DEFAULT_COOKIE_MANAGER;
//field:0005  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.DRM_KEY_REQUEST_PROPERTIES Ljava/lang/String;
public static final  java.lang.String DRM_KEY_REQUEST_PROPERTIES="drm_key_request_properties";
//field:0006  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.DRM_LICENSE_URL Ljava/lang/String;
public static final  java.lang.String DRM_LICENSE_URL="drm_license_url";
//field:0007  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.DRM_SCHEME_UUID_EXTRA Ljava/lang/String;
public static final  java.lang.String DRM_SCHEME_UUID_EXTRA="drm_scheme_uuid";
//field:0008  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.EXTENSION_EXTRA Ljava/lang/String;
public static final  java.lang.String EXTENSION_EXTRA="extension";
//field:0009  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.EXTENSION_LIST_EXTRA Ljava/lang/String;
public static final  java.lang.String EXTENSION_LIST_EXTRA="extension_list";
//field:0010  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.PREFER_EXTENSION_DECODERS Ljava/lang/String;
public static final  java.lang.String PREFER_EXTENSION_DECODERS="prefer_extension_decoders";
//field:0011  access:0x0019
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.URI_LIST_EXTRA Ljava/lang/String;
public static final  java.lang.String URI_LIST_EXTRA="uri_list";
//field:0012  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugRootView Landroid/widget/LinearLayout;
private  android.widget.LinearLayout debugRootView;
//field:0013  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugTextView Landroid/widget/TextView;
private  android.widget.TextView debugTextView;
//field:0014  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.debugViewHelper Lcom/google/android/exoplayer2/ui/DebugTextViewHelper;
private  com.google.android.exoplayer2.ui.DebugTextViewHelper debugViewHelper;
//field:0015  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.eventLogger Lcom/google/android/exoplayer2/demo/EventLogger;
private  com.google.android.exoplayer2.demo.EventLogger eventLogger;
//field:0016  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.inErrorState Z
private  boolean inErrorState;
//field:0017  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.lastSeenTrackGroupArray Lcom/google/android/exoplayer2/source/TrackGroupArray;
private  com.google.android.exoplayer2.source.TrackGroupArray lastSeenTrackGroupArray;
//field:0018  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.mainHandler Landroid/os/Handler;
private  android.os.Handler mainHandler;
//field:0019  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.mediaDataSourceFactory Lcom/google/android/exoplayer2/upstream/DataSource$Factory;
private  com.google.android.exoplayer2.upstream.DataSource.Factory mediaDataSourceFactory;
//field:0020  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.player Lcom/google/android/exoplayer2/SimpleExoPlayer;
private  com.google.android.exoplayer2.SimpleExoPlayer player;
//field:0021  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.resumePosition J
private  long resumePosition;
//field:0022  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.resumeWindow I
private  int resumeWindow;
//field:0023  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.retryButton Landroid/widget/Button;
private  android.widget.Button retryButton;
//field:0024  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.shouldAutoPlay Z
private  boolean shouldAutoPlay;
//field:0025  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.simpleExoPlayerView Lcom/google/android/exoplayer2/ui/SimpleExoPlayerView;
private  com.google.android.exoplayer2.ui.SimpleExoPlayerView simpleExoPlayerView;
//field:0026  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelectionHelper Lcom/google/android/exoplayer2/demo/TrackSelectionHelper;
private  com.google.android.exoplayer2.demo.TrackSelectionHelper trackSelectionHelper;
//field:0027  access:0x0002
//Lcom/google/android/exoplayer2/demo/PlayerActivity;.trackSelector Lcom/google/android/exoplayer2/trackselection/DefaultTrackSelector;
private  com.google.android.exoplayer2.trackselection.DefaultTrackSelector trackSelector;

public  PlayerActivity()
{
__initNative();
};  native void   __initNative();

private  native  com.google.android.exoplayer2.upstream.DataSource.Factory  buildDataSourceFactory(boolean p0);

private com.google.android.exoplayer2.upstream.DataSource.Factory invokeFromNative__buildDataSourceFactory(com.google.android.exoplayer2.demo.PlayerActivity obj, boolean p0) {
  return obj.buildDataSourceFactory( p0);
 }


private  native  com.google.android.exoplayer2.source.MediaSource  buildMediaSource(android.net.Uri p0,java.lang.String p1);

private com.google.android.exoplayer2.source.MediaSource invokeFromNative__buildMediaSource(com.google.android.exoplayer2.demo.PlayerActivity obj, android.net.Uri p0,java.lang.String p1) {
  return obj.buildMediaSource( p0, p1);
 }


private  native  void  initializePlayer();

private void invokeFromNative__initializePlayer(com.google.android.exoplayer2.demo.PlayerActivity obj) {
  obj.initializePlayer();
 }


private  native  void  showToast(int p0);

private void invokeFromNative__showToast(com.google.android.exoplayer2.demo.PlayerActivity obj, int p0) {
  obj.showToast( p0);
 }


private  native  void  showToast(java.lang.String p0);

private void invokeFromNative__showToast(com.google.android.exoplayer2.demo.PlayerActivity obj, java.lang.String p0) {
  obj.showToast( p0);
 }


private  native  int  sum2DIntArray(int p0);

private int invokeFromNative__sum2DIntArray(com.google.android.exoplayer2.demo.PlayerActivity obj, int p0) {
  return obj.sum2DIntArray( p0);
 }


private  native  int  sumIntArray(int p0);

private int invokeFromNative__sumIntArray(com.google.android.exoplayer2.demo.PlayerActivity obj, int p0) {
  return obj.sumIntArray( p0);
 }


private  native  long  sumLongArray(int p0);

private long invokeFromNative__sumLongArray(com.google.android.exoplayer2.demo.PlayerActivity obj, int p0) {
  return obj.sumLongArray( p0);
 }


private  native  int  sumNumber(int p0);

private int invokeFromNative__sumNumber(com.google.android.exoplayer2.demo.PlayerActivity obj, int p0) {
  return obj.sumNumber( p0);
 }


private  native  java.lang.String  sumStringArray(int p0);

private java.lang.String invokeFromNative__sumStringArray(com.google.android.exoplayer2.demo.PlayerActivity obj, int p0) {
  return obj.sumStringArray( p0);
 }


private  native  void  testABCD();

private void invokeFromNative__testABCD(com.google.android.exoplayer2.demo.PlayerActivity obj) {
  obj.testABCD();
 }


private  native  void  testWine();

private void invokeFromNative__testWine(com.google.android.exoplayer2.demo.PlayerActivity obj) {
  obj.testWine();
 }


public  native  void  onCreate(android.os.Bundle p0);

private void invokeFromNative__onCreate(com.google.android.exoplayer2.demo.PlayerActivity obj, android.os.Bundle p0) {
  obj.onCreate( p0);
 }


public  native  void  onResume();

private void invokeFromNative__onResume(com.google.android.exoplayer2.demo.PlayerActivity obj) {
  obj.onResume();
 }

}
