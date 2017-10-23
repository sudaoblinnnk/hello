package com.google.android.exoplayer2.demo;
//class:0669  access:0x0001
public class Wine
{



//field:0000  access:0x0002
//Lcom/google/android/exoplayer2/demo/Wine;.name Ljava/lang/String;
private  java.lang.String name;

public  Wine()
{
__initNative();
};  native void   __initNative();

public  native  java.lang.String  drink();

private java.lang.String invokeFromNative__drink(com.google.android.exoplayer2.demo.Wine obj) {
  return obj.drink();
 }


public  native  java.lang.String  getName();

private java.lang.String invokeFromNative__getName(com.google.android.exoplayer2.demo.Wine obj) {
  return obj.getName();
 }


public  native  void  setName(java.lang.String p0);

private void invokeFromNative__setName(com.google.android.exoplayer2.demo.Wine obj, java.lang.String p0) {
  obj.setName( p0);
 }


public  native  java.lang.String  toString();

private java.lang.String invokeFromNative__toString(com.google.android.exoplayer2.demo.Wine obj) {
  return obj.toString();
 }

}
