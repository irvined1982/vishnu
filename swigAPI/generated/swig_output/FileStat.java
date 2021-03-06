/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class FileStat extends EObject {
  private long swigCPtr;

  protected FileStat(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.SWIGFileStatUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(FileStat obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_FileStat(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public FileStat() {
    this(VISHNUJNI.new_FileStat(), true);
  }

  public void _initialize() {
    VISHNUJNI.FileStat__initialize(swigCPtr, this);
  }

  public String getPath() {
    return VISHNUJNI.FileStat_getPath(swigCPtr, this);
  }

  public void setPath(String _path) {
    VISHNUJNI.FileStat_setPath(swigCPtr, this, _path);
  }

  public String getOwner() {
    return VISHNUJNI.FileStat_getOwner(swigCPtr, this);
  }

  public void setOwner(String _owner) {
    VISHNUJNI.FileStat_setOwner(swigCPtr, this, _owner);
  }

  public String getGroup() {
    return VISHNUJNI.FileStat_getGroup(swigCPtr, this);
  }

  public void setGroup(String _group) {
    VISHNUJNI.FileStat_setGroup(swigCPtr, this, _group);
  }

  public int getPerms() {
    return VISHNUJNI.FileStat_getPerms(swigCPtr, this);
  }

  public void setPerms(int _perms) {
    VISHNUJNI.FileStat_setPerms(swigCPtr, this, _perms);
  }

  public long getUid() {
    return VISHNUJNI.FileStat_getUid(swigCPtr, this);
  }

  public void setUid(long _uid) {
    VISHNUJNI.FileStat_setUid(swigCPtr, this, _uid);
  }

  public long getGid() {
    return VISHNUJNI.FileStat_getGid(swigCPtr, this);
  }

  public void setGid(long _gid) {
    VISHNUJNI.FileStat_setGid(swigCPtr, this, _gid);
  }

  public long getSize() {
    return VISHNUJNI.FileStat_getSize(swigCPtr, this);
  }

  public void setSize(long _size) {
    VISHNUJNI.FileStat_setSize(swigCPtr, this, _size);
  }

  public long getAtime() {
    return VISHNUJNI.FileStat_getAtime(swigCPtr, this);
  }

  public void setAtime(long _atime) {
    VISHNUJNI.FileStat_setAtime(swigCPtr, this, _atime);
  }

  public long getMtime() {
    return VISHNUJNI.FileStat_getMtime(swigCPtr, this);
  }

  public void setMtime(long _mtime) {
    VISHNUJNI.FileStat_setMtime(swigCPtr, this, _mtime);
  }

  public long getCtime() {
    return VISHNUJNI.FileStat_getCtime(swigCPtr, this);
  }

  public void setCtime(long _ctime) {
    VISHNUJNI.FileStat_setCtime(swigCPtr, this, _ctime);
  }

  public int getType() {
    return VISHNUJNI.FileStat_getType(swigCPtr, this);
  }

  public void setType(int _type) {
    VISHNUJNI.FileStat_setType(swigCPtr, this, _type);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.FileStat_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.FileStat_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.FileStat_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.FileStat_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.FileStat__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
