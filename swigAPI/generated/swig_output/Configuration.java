/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class Configuration extends EObject {
  private long swigCPtr;

  protected Configuration(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.SWIGConfigurationUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Configuration obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_Configuration(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Configuration() {
    this(VISHNUJNI.new_Configuration(), true);
  }

  public void _initialize() {
    VISHNUJNI.Configuration__initialize(swigCPtr, this);
  }

  public String getFilePath() {
    return VISHNUJNI.Configuration_getFilePath(swigCPtr, this);
  }

  public void setFilePath(String _filePath) {
    VISHNUJNI.Configuration_setFilePath(swigCPtr, this, _filePath);
  }

  public EUserList getListConfUsers() {
    return new EUserList(VISHNUJNI.Configuration_getListConfUsers(swigCPtr, this), false);
  }

  public EMachineList getListConfMachines() {
    return new EMachineList(VISHNUJNI.Configuration_getListConfMachines(swigCPtr, this), false);
  }

  public ELocalAccList getListConfLocalAccounts() {
    return new ELocalAccList(VISHNUJNI.Configuration_getListConfLocalAccounts(swigCPtr, this), false);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.Configuration_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.Configuration_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.Configuration_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.Configuration_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.Configuration__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}