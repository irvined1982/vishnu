
/**
 * \file transferSrv.hpp
 * This file contains the declaration of the vishnu transfer file server
 */
#ifndef TRANSFERSRV_HPP
#define TRANSFERSRV_HPP
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <sstream>
#include <sys/types.h>

#include "FileFactory.hpp"

#include "DIET_client.h"
#include "UserServer.hpp"
#include "MachineServer.hpp"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include "ServerFMS.hpp"
#include "FMSMapper.hpp"
#include "ListFileTransfers.hpp"

#include "FileTransferServer.hpp"

using namespace std;


/**
 * \brief List file transfer solve function
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return 0 if the service succeeds
 */
int
solveGetListOfFileTransfers(diet_profile_t* pb);

/**
 * \brief File transfer stop solve function
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return 0 if the service succeeds or an error code otherwise
 */
int
solveFileTransferStop(diet_profile_t* pb);

/**
 * \brief Function to build the File transfer (local to remote) service profile
 * \param serviceName the name of the service
 * \return the service profile
 */

//diet_profile_desc_t* getTransferFileProfile(const std::string& serviceName);
//
///**
// * \brief Function to build the asynchronous File transfer (local to remote) service profile
// * \param serviceName the name of the service
// * \return the service profile
// */
//diet_profile_desc_t* getTransferFileAsyncProfile(const std::string& serviceName);
//
///**
// * \brief Function to build the File transfer (remote to local) service profile
// * \param serviceName the name of the service
// * \return the service profile
// */
//diet_profile_desc_t* getTransferRemoteFileProfile(const std::string& serviceName);
//
///**
// * \brief Function to build the File transfer (remote to local) service profile
// * \param serviceName the name of the service
// * \return the service profile
// */
//diet_profile_desc_t* getTransferRemoteFileAsyncProfile(const std::string& serviceName);
//
///**
// * \brief Function to build the File transfer list service profile
// * \return the service profile
// */
//
//diet_profile_desc_t* getFileTransfersListProfile();
//
///**
// * \brief Function to build the File transfer stop service profile
// * \return the service profile description
// */
//diet_profile_desc_t* getFileTransferStopProfile();


/**
 * \brief Implementation of file transfer (local to remote) solve function
 * \param profile the service profile
 * \return 0 if the service succeeds or an error code otherwise
 */
template < File::TransferType transferType, File::TransferMode transferMode> int solveTransferFile(diet_profile_t* profile){

  std::string srcUserKey = "";
  std::string destUser = "";
  std::string destMachineName = "";
  std::string fileTransferSerialized = "";
  std::string errMsg = "";
  std::string finishError = "";
  std::string srcPath = "";
  std::string srcUser = "";
  std::string srcHost = "";
  std::string sessionKey = "";
  std::string dest = "";
  std::string optionsSerialized = "";

  int mapperkey;
  std::string cmd = "";

  diet_string_get(profile, 0, sessionKey);
  diet_string_get(profile, 1, srcPath);
  diet_string_get(profile, 2, srcUser);
  diet_string_get(profile, 3, srcHost);
  diet_string_get(profile, 4, dest);
  diet_string_get(profile, 5, optionsSerialized);


  std:: string destPath=File::extName(dest);
  std:: string destHost=File::extHost(dest);
  SessionServer sessionServer (sessionKey);

  try {

    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(FMSMAPPERNAME);

    if (transferMode==File::sync){

      if(transferType==File::copy){
        mapperkey = mapper->code("vishnu_cp");
      }
      if(transferType==File::move){
        mapperkey = mapper->code("vishnu_mv");
      }
    }
    else{

      if(transferType==File::copy){
        mapperkey = mapper->code("vishnu_acp");
      }
      if(transferType==File::move){
        mapperkey = mapper->code("vishnu_amv");
      }

    }

    mapper->code(srcPath, mapperkey);
    mapper->code(dest, mapperkey);
    mapper->code(optionsSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    // check the sessionKey
    sessionServer.check();


    UMS_Data::Machine_ptr machine = new UMS_Data::Machine();
    machine->setMachineId(destHost);
    MachineServer machineServer(machine);

    // check the machine
    if (isNotIP(destHost)){
      machineServer.checkMachine();
    }

    // get the machineName
    destMachineName = machineServer.getMachineName();
    delete machine;

    // get the acLogin
    if (isNotIP(destHost)){
      destUser = UserServer(sessionServer).getUserAccountLogin(destHost);
    } else {
      destUser = destHost;
    }



    CpFileOptions* options_ptr= NULL;
    if(!vishnu::parseEmfObject(optionsSerialized, options_ptr) ) {
      throw SystemException(ERRCODE_INVDATA, "solve_Copy: CpFileOptions object is not well built");
    }

    int vishnuId=ServerFMS::getInstance()->getVishnuId();

    boost::shared_ptr<FileTransferServer> fileTransferServer(new FileTransferServer(sessionServer, srcHost, destHost, srcPath, destPath,vishnuId));

    // Perfor the transfer now
    if (transferMode==File::sync){

     if(transferType==File::copy){
        fileTransferServer->addCpThread(srcUser, srcHost, srcUserKey, destUser, destMachineName,*options_ptr);
      }

      if (transferType==File::move){

        fileTransferServer->addMvThread(srcUser,srcHost,srcUserKey,destUser,destMachineName,*options_ptr);
      }
    }
    else{

      if(transferType==File::copy){
        fileTransferServer->addCpAsyncThread(srcUser,srcHost,srcUserKey,destUser,destMachineName,*options_ptr);
      }

      if (transferType==File::move){

        fileTransferServer->addMvAsyncThread(srcUser,srcHost,srcUserKey,destUser,destMachineName,*options_ptr);
      }

      FMS_Data::FMS_DataFactory_ptr ecoreFactory = FMS_Data::FMS_DataFactory::_instance();

      FMS_Data::FileTransfer_ptr fileTransfer=ecoreFactory->createFileTransfer();

      *fileTransfer= fileTransferServer->getFileTransfer();


      ::ecorecpp::serializer::serializer _ser;

      fileTransferSerialized =  _ser.serialize_str(const_cast<FMS_Data::FileTransfer_ptr>(fileTransfer));


      delete fileTransfer;

    }
    //To register the command
    sessionServer.finish(cmd, FMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& err) {
    try {
      sessionServer.finish(cmd, FMS, vishnu::CMDFAILED);
    } catch (VishnuException& fe) {
      finishError =  fe.what();
      finishError +="\n";
    }
    err.appendMsgComp(finishError);

    errMsg = err.buildExceptionString();
  }

  if (transferMode==File::sync) {
    diet_string_set(profile, 6, errMsg.c_str());
  } else {
    diet_string_set(profile, 6, fileTransferSerialized.c_str());
    diet_string_set(profile, 7, errMsg.c_str());
  }

  return 0;

}

/**
 * \brief Implementation of file transfer (from remote to local or remote ) solve function
 * \param profile the service profile
 * \return 0 if the service succeeds or an error code otherwise
 */

template <File::TransferType transferType, File::TransferMode transferMode> int solveTransferRemoteFile(diet_profile_t* profile){


  std::string srcPath = "";
  std::string destUser = "";
  std::string srcHost = "";
  std::string sessionKey = "";
  std::string destHost = "";
  std::string destPath = "";
  std::string optionsSerialized = "";
  std::string srcUserKey = "";
  std::string srcUserLogin = "";
  std::string srcMachineName = "";
  std::string errMsg = "";
  std::string finishError = "";
  std::string fileTransferSerialized = "";
  int mapperkey;
  std::string cmd = "";

  diet_string_get(profile, 0, sessionKey);
  diet_string_get(profile, 1, destUser);
  diet_string_get(profile, 2, srcHost);
  diet_string_get(profile, 3, srcPath);
  diet_string_get(profile, 4, destHost);
  diet_string_get(profile, 5, destPath);
  diet_string_get(profile, 6, optionsSerialized);

  SessionServer sessionServer (sessionKey);

  try {

    string destUserLogin(destUser);
    string destMachineName(destHost);
    SessionServer sessionServer (sessionKey);

    //MAPPER CREATION
    string destCpltPath = destPath;
    if(destUser.size()==0){
      destCpltPath = destHost + ":" + destPath;
    }

    Mapper *mapper = MapperRegistry::getInstance()->getMapper(FMSMAPPERNAME);


    if (transferMode==File::sync){

     if(transferType==File::copy){
      mapperkey = mapper->code("vishnu_cp");
    }

      if(transferType==File::move){
      mapperkey = mapper->code("vishnu_mv");
    }

    }

    else{

      if(transferType==File::copy){
      mapperkey = mapper->code("vishnu_acp");
    }

      if(transferType==File::move){
      mapperkey = mapper->code("vishnu_amv");
    }

    }
    mapper->code(srcHost + ":" + srcPath, mapperkey);
    mapper->code(destCpltPath, mapperkey);
    mapper->code(optionsSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    // check the sessionKey
    sessionServer.check();

    // get the source Vishnu machine
    UMS_Data::Machine_ptr machine = new UMS_Data::Machine();
    machine->setMachineId(srcHost);
    MachineServer srcMachineServer(machine);

    // check the source machine
    if (isNotIP(srcHost)){
      srcMachineServer.checkMachine();
    }

    // get the source machineName
    if (isNotIP(srcHost)){
      srcMachineName = srcMachineServer.getMachineName();
    } else {
      srcMachineName = srcHost;
    }

    delete machine;

    // get the source machine user login
    if (isNotIP(srcHost)){
      srcUserLogin = UserServer(sessionServer).getUserAccountLogin(srcHost);
    } else {
      srcUserLogin = destUser;
    }


    if (destUser.compare("") == 0) {
      // get the destination Vishnu machine
      machine = new UMS_Data::Machine();
      machine->setMachineId(destHost);
      MachineServer destMachineServer(machine);

      // check the destination machine
      if (isNotIP(destHost)){
        destMachineServer.checkMachine();
      }

      // get the destination machineName
      destMachineName = destMachineServer.getMachineName();
      delete machine;

      // get the destination  machine user login
      if (isNotIP(destHost)){
        destUserLogin = UserServer(sessionServer).getUserAccountLogin(destHost);
      } else {
        destUserLogin = destUser;
      }
    }


    CpFileOptions_ptr options_ptr= NULL;
    if (!vishnu::parseEmfObject(optionsSerialized, options_ptr) ) {
      throw SystemException(ERRCODE_INVDATA, "solve_Copy: CpFileOptions object is not well built");
    }

    int vishnuId=ServerFMS::getInstance()->getVishnuId();

    boost::shared_ptr<FileTransferServer> fileTransferServer(new FileTransferServer(sessionServer, srcHost, destHost, srcPath, destPath,vishnuId));

    // Perfor the transfer now

    if (transferMode==File::sync){

      if(transferType==File::copy){
        fileTransferServer->addCpThread(srcUserLogin,srcMachineName,srcUserKey,destUserLogin,destMachineName,*options_ptr);
      }

      if (transferType==File::move){

        fileTransferServer->addMvThread(srcUserLogin,srcMachineName,srcUserKey,destUserLogin,destMachineName,*options_ptr);
      }

    }else{

      if(transferType==File::copy){
        fileTransferServer->addCpAsyncThread(srcUserLogin,srcMachineName,srcUserKey,destUserLogin,destMachineName,*options_ptr);
      }

      if (transferType==File::move){

        fileTransferServer->addMvAsyncThread(srcUserLogin,srcMachineName,srcUserKey,destUserLogin,destMachineName,*options_ptr);
      }

      FMS_Data::FMS_DataFactory_ptr ecoreFactory = FMS_Data::FMS_DataFactory::_instance();

      FMS_Data::FileTransfer_ptr fileTransfer=ecoreFactory->createFileTransfer();

      *fileTransfer= fileTransferServer->getFileTransfer();


      ::ecorecpp::serializer::serializer _ser;

      fileTransferSerialized =  _ser.serialize_str(const_cast<FMS_Data::FileTransfer_ptr>(fileTransfer));


      delete fileTransfer;
    }

    //To register the command
    sessionServer.finish(cmd, FMS, vishnu::CMDSUCCESS);

  } catch (VishnuException& err) {
    try {
      sessionServer.finish(cmd, FMS, vishnu::CMDFAILED);
    } catch (VishnuException& fe) {
      finishError =  fe.what();
      finishError +="\n";
    }
    err.appendMsgComp(finishError);

    errMsg = err.buildExceptionString().c_str();
  }

  if (transferMode==File::sync){

    diet_string_set(profile, 7, errMsg.c_str());

  }
  else{
    diet_string_set(profile, 7, fileTransferSerialized.c_str());
    diet_string_set(profile, 8, errMsg.c_str());

  }
  return 0;


}




/**
 * \brief Function to solve the generic query service
 * \param pb is a structure which corresponds to the descriptor of a profile
 * \return 0 if the service succeeds or an error code otherwise
 */
template <class QueryParameters, class List, class QueryType>
int
solveGenerique(diet_profile_t* pb) {

  std::string sessionKey = "";
  std::string optionValueSerialized = "";
  std::string listSerialized = "";
  std::string errorInfo;
  int mapperkey;
  std::string cmd;
  std::string finishError ="";

  //IN Parameters
  diet_string_get(pb,0, sessionKey);
  diet_string_get(pb,1, optionValueSerialized);

  SessionServer sessionServer  = SessionServer(sessionKey);

  QueryParameters* options = NULL;
  List* list = NULL;


  try {
    //To parse the object serialized
    if(!parseEmfObject(optionValueSerialized, options)) {
      throw UMSVishnuException(ERRCODE_INVALID_PARAM);
    }


  QueryType query(options, sessionServer);

    //MAPPER CREATION
    Mapper *mapper = MapperRegistry::getInstance()->getMapper(FMSMAPPERNAME);
    mapperkey = mapper->code(query.getCommandName());
    mapper->code(optionValueSerialized, mapperkey);
    cmd = mapper->finalize(mapperkey);

    //  perform the query

    list = query.list();

    ::ecorecpp::serializer::serializer _ser;

    listSerialized =  _ser.serialize_str(const_cast<List*>(list));

    //OUT Parameter
    diet_string_set(pb,2, listSerialized.c_str());
    diet_string_set(pb,3);
    sessionServer.finish(cmd, FMS, vishnu::CMDSUCCESS);
  } catch (VishnuException& e) {
    try {
      sessionServer.finish(cmd, FMS, vishnu::CMDFAILED);
    } catch (VishnuException& fe) {
      finishError =  fe.what();
      finishError +="\n";
    }
    e.appendMsgComp(finishError);
    errorInfo =  e.buildExceptionString();
    //OUT Parameter
    diet_string_set(pb,2, listSerialized.c_str());
    diet_string_set(pb,3, errorInfo.c_str());
  }
  delete options;
  delete list;
  return 0;
}



#endif
