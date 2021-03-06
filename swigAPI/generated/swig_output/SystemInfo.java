/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class SystemInfo extends EObject {
  private long swigCPtr;

  protected SystemInfo(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.SWIGSystemInfoUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(SystemInfo obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_SystemInfo(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public SystemInfo() {
    this(VISHNUJNI.new_SystemInfo(), true);
  }

  public void _initialize() {
    VISHNUJNI.SystemInfo__initialize(swigCPtr, this);
  }

  public long getMemory() {
    return VISHNUJNI.SystemInfo_getMemory(swigCPtr, this);
  }

  public void setMemory(long _memory) {
    VISHNUJNI.SystemInfo_setMemory(swigCPtr, this, _memory);
  }

  public long getDiskSpace() {
    return VISHNUJNI.SystemInfo_getDiskSpace(swigCPtr, this);
  }

  public void setDiskSpace(long _diskSpace) {
    VISHNUJNI.SystemInfo_setDiskSpace(swigCPtr, this, _diskSpace);
  }

  public String getMachineId() {
    return VISHNUJNI.SystemInfo_getMachineId(swigCPtr, this);
  }

  public void setMachineId(String _machineId) {
    VISHNUJNI.SystemInfo_setMachineId(swigCPtr, this, _machineId);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.SystemInfo_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.SystemInfo_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.SystemInfo_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.SystemInfo_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.SystemInfo__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
