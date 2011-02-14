/**
* \file OptionValueServer.hpp
* \brief This file presents the Class which manipulates VISHNU options on server side.
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2011
*/

#ifndef OPTION_VALUE_SERVER_H
#define OPTION_VALUE_SERVER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <exception>
#include "SystemException.hh"
#include "UMS_Data.hpp"
#include "UMS_Data_forward.hpp"
#include "POSTGREDatabase.hh"
#include "DbFactory.hh"
#include "DatabaseResult.hh"
#include "UserServer.hh"

/**
* \class OptionValueServer
* \brief Implementation of the OptionValueServer class
*/
class OptionValueServer { 
  
public:
  /**
  * \brief Constructor
  * \fn OptionValueServer() 
  */
  OptionValueServer();
  /**
  * \brief Constructor
  * \fn OptionValueServer(UMS_Data::OptionValue optionvalue)
  * \param optionvalue the option data structure 
  */
  OptionValueServer(UMS_Data::OptionValue optionvalue);
  /**
  * \brief Function to configure options on the database
  * \fn    int configureOption()
  * \return  raises an exception on error
  */
  int 
  configureOption();
  /**
  * \brief Function to configure default options on the database
  * \fn    int configureDefaultOption()
  * \return  raises an exception on error
  */
  int 
  configureDefaultOption();
  /**
  * \brief Destructor
  * \fn  ~OptionValueServer()
  */
  ~OptionValueServer();
  /**
  * \brief Function to get option data structure
  * \fn UMS_Data::OptionValue getData()
  * \return  The user data structure
  */
  UMS_Data::OptionValue 
  getData();
  /**
  * \brief Function to get option information from the database vishnu
  * \fn getAttribut(std::string condition, std::string attrname, defaultOptions);
  * \param condition The condition of the select request
  * \param attrname the name of the attribut to get
  * \param defaultOptions the flag to get data from defauts options table
  * \return the value of the attribut or empty string if no results
  */
  std::string 
  getAttribut(std::string condition, std::string attrname="value", bool defaultOptions=false);
  /**
  * \brief Function to get closure information from the database vishnu
  * \fn getAttribut(std::string condition, std::string attrname, defaultOptions);
  * \param numuserId The database number id of the user who wants to get closure information
  * \param nameInfo the name of the closure information 
  */
  int 
  getClosureInfo(std::string numuserId, std::string nameInfo = "VISHNU_CLOSE_POLICY");
  //static UMS_Data::ListOptionsValues  list(SessionServer session, UMS_Data::ListOptOptions  options);
private:
  /**
  * \brief The option data structure
  */
  UMS_Data::OptionValue moptionValue;
  /**
  * \brief An instance of vishnu database
  */
  Database *mdatabaseVishnu;
};
#endif//OPTION_VALUE_SERVER_H
