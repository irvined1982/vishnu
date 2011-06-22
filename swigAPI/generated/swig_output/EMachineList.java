/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class EMachineList {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected EMachineList(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(EMachineList obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_EMachineList(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void insert_all(EMachineList _q) {
    VISHNUJNI.EMachineList_insert_all(swigCPtr, this, EMachineList.getCPtr(_q), _q);
  }

  public void insert_at(long _pos, Machine _obj) {
    VISHNUJNI.EMachineList_insert_at(swigCPtr, this, _pos, Machine.getCPtr(_obj), _obj);
  }

  public Machine get(long _index) {
    long cPtr = VISHNUJNI.EMachineList_get(swigCPtr, this, _index);
    return (cPtr == 0) ? null : new Machine(cPtr, false);
  }

  public void push_back(Machine _obj) {
    VISHNUJNI.EMachineList_push_back(swigCPtr, this, Machine.getCPtr(_obj), _obj);
  }

  public long size() {
    return VISHNUJNI.EMachineList_size(swigCPtr, this);
  }

  public void clear() {
    VISHNUJNI.EMachineList_clear(swigCPtr, this);
  }

}