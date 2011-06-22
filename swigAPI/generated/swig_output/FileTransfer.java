/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class FileTransfer extends EObject {
  private long swigCPtr;

  protected FileTransfer(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.SWIGFileTransferUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(FileTransfer obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_FileTransfer(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public FileTransfer() {
    this(VISHNUJNI.new_FileTransfer(), true);
  }

  public void _initialize() {
    VISHNUJNI.FileTransfer__initialize(swigCPtr, this);
  }

  public String getTransferId() {
    return VISHNUJNI.FileTransfer_getTransferId(swigCPtr, this);
  }

  public void setTransferId(String _transferId) {
    VISHNUJNI.FileTransfer_setTransferId(swigCPtr, this, _transferId);
  }

  public int getStatus() {
    return VISHNUJNI.FileTransfer_getStatus(swigCPtr, this);
  }

  public void setStatus(int _status) {
    VISHNUJNI.FileTransfer_setStatus(swigCPtr, this, _status);
  }

  public String getUserId() {
    return VISHNUJNI.FileTransfer_getUserId(swigCPtr, this);
  }

  public void setUserId(String _userId) {
    VISHNUJNI.FileTransfer_setUserId(swigCPtr, this, _userId);
  }

  public String getClientMachineId() {
    return VISHNUJNI.FileTransfer_getClientMachineId(swigCPtr, this);
  }

  public void setClientMachineId(String _clientMachineId) {
    VISHNUJNI.FileTransfer_setClientMachineId(swigCPtr, this, _clientMachineId);
  }

  public String getSourceMachineId() {
    return VISHNUJNI.FileTransfer_getSourceMachineId(swigCPtr, this);
  }

  public void setSourceMachineId(String _sourceMachineId) {
    VISHNUJNI.FileTransfer_setSourceMachineId(swigCPtr, this, _sourceMachineId);
  }

  public String getDestinationMachineId() {
    return VISHNUJNI.FileTransfer_getDestinationMachineId(swigCPtr, this);
  }

  public void setDestinationMachineId(String _destinationMachineId) {
    VISHNUJNI.FileTransfer_setDestinationMachineId(swigCPtr, this, _destinationMachineId);
  }

  public String getSourceFilePath() {
    return VISHNUJNI.FileTransfer_getSourceFilePath(swigCPtr, this);
  }

  public void setSourceFilePath(String _sourceFilePath) {
    VISHNUJNI.FileTransfer_setSourceFilePath(swigCPtr, this, _sourceFilePath);
  }

  public String getDestinationFilePath() {
    return VISHNUJNI.FileTransfer_getDestinationFilePath(swigCPtr, this);
  }

  public void setDestinationFilePath(String _destinationFilePath) {
    VISHNUJNI.FileTransfer_setDestinationFilePath(swigCPtr, this, _destinationFilePath);
  }

  public long getSize() {
    return VISHNUJNI.FileTransfer_getSize(swigCPtr, this);
  }

  public void setSize(long _size) {
    VISHNUJNI.FileTransfer_setSize(swigCPtr, this, _size);
  }

  public long getStart_time() {
    return VISHNUJNI.FileTransfer_getStart_time(swigCPtr, this);
  }

  public void setStart_time(long _start_time) {
    VISHNUJNI.FileTransfer_setStart_time(swigCPtr, this, _start_time);
  }

  public int getTrCommand() {
    return VISHNUJNI.FileTransfer_getTrCommand(swigCPtr, this);
  }

  public void setTrCommand(int _trCommand) {
    VISHNUJNI.FileTransfer_setTrCommand(swigCPtr, this, _trCommand);
  }

  public String getErrorMsg() {
    return VISHNUJNI.FileTransfer_getErrorMsg(swigCPtr, this);
  }

  public void setErrorMsg(String _errorMsg) {
    VISHNUJNI.FileTransfer_setErrorMsg(swigCPtr, this, _errorMsg);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.FileTransfer_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.FileTransfer_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.FileTransfer_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.FileTransfer_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.FileTransfer__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}