/**
 * \file utilVishnu.cpp
 * \brief This file implements the utils functions of the vishnu system
 * \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com) and
 * Daouda Traoré (daouda.traore@sysfera.com and Ibrahima Cissé (ibrahima.cisse@sysfera.com)
 * \date 15/02/2011
 */

#include "utilVishnu.hpp"
#include <stdexcept>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/system/error_code.hpp>
#include <boost/regex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <time.h>
#include <ctype.h>

#include <sys/stat.h>
// Headers for getaddrinfo function
#include <netdb.h>
#include <sys/param.h>
#include<iostream>
#include<string>
#include<cstring>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <net/if.h>


#include "UserException.hpp"
#include "SystemException.hpp"
#include "TMS_Data.hpp"
#include "cliError.hpp"

namespace bfs=boost::filesystem; // an alias for boost filesystem namespace
namespace bs=boost::system;

/**
 * \brief Function to convert a given date into correspondant long value
 * \fn long long convertToTimeType(std::string date)
 * \param date The date to convert
 * \return The converted value
 */
long long
vishnu::convertToTimeType(const std::string& date) {
  /* For mysql, the empty date is 0000-00-00, not empty,
     need this test to avoid problem in ptime */
  if ((date.size() == 0) ||
      date.find("0000-00-00") != std::string::npos) {
    return 0;
  }

  try{
    boost::posix_time::ptime pt(time_from_string(date));
    boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));
    time_duration::sec_type time = (pt - epoch).total_seconds();
  } catch (std::exception& e){
    throw UserException(ERRCODE_INVALID_PARAM, "Error converting date :"+date+" to time, error is :" +e.what());
  }
  return (long long) time_t(time);
}

/**
 * \brief Function to convert a string to int
 * \param  val a value to convert to int
 * \return int value of the corresponding string
 */
int
vishnu::convertToInt(const std::string& sval) {
  int value = -1;
  try{
    value = boost::lexical_cast<int>(sval);
  }catch(...){}

  return value;
}


/**
 * \brief Function to convert a string to long int
 * \param  val a value to convert to int
 * \return int value of the corresponding string
 */
long
vishnu::convertToLong(const std::string& sval) {
  long value = -1;
  try{
    value = boost::lexical_cast<long>(sval);
  }catch(...){}

  return value;
}

/**
 * \brief To crypt a password
 * \fn std::string cryptPassword(const std::string& salt, const std::string password)
 * \param salt The salt to use to crypt
 * \param password The password to crypt
 * \param encrypted The flag for password encryption
 * \return The crypted password
 */

std::string
vishnu::cryptPassword(const std::string& salt, const std::string& password, bool encrypted) {
  if (!encrypted) {
    return password;
  } else {
    std::string saltTmp = "$6$" + salt + "$";
    std::string encryptedPassword = crypt(password.c_str(), saltTmp.c_str());
    return encryptedPassword.substr(saltTmp.size());
  }
}

/**
 * \brief Function to get a random number
 * \fn    int generate_numbers()
 * \return the number generated
 */
int
vishnu::generateNumbers() {
  boost::mt19937 gen;
  gen.seed(static_cast<boost::uint32_t>(std::time(0)));
  boost::uniform_int<> dist(1, 100000);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
  return die();
}

/**
 * \brief To retrieve the password
 * \param prompt: The message inviting the user to enter his/her password
 * \return The password entered.
 */
std::string
vishnu::takePassword(const std::string& prompt) {
  std::string password = getpass(prompt.c_str());
  return password;
}

/**
 * \brief Simple function to convert time
 * from string format (YYYY-MM-DD H:M:S) to
 * long integer format in seconds
 * \param ts: the time in string format
 * \return the time in long integer format in seconds
 */
std::time_t
vishnu::string_to_time_t(const std::string& ts) {
  // two aliases for convenience
  namespace bps= boost::posix_time;
  namespace bg=boost::gregorian;

  bps::ptime t;

  if (std::string::npos == ts.find(":")) {
    t = bps::ptime(bg::from_string(ts));
  } else {
    t = bps::ptime (bps::time_from_string(ts));
  }

  bps::ptime epoch(bg::date(1970,1,1));
  bps::time_duration::sec_type x = (t - epoch).total_seconds();
  return std::time_t(x);
}

/**
 * \brief Simple function to convert time
 * from string format (YYYY-MM-DD H:M:S) to
 * long integer format in seconds in utc
 * \param ts: the time in string format
 * \param utcOffset: time zone in string format
 * \return the time in long integer format in seconds
 */
std::time_t
vishnu::string_lc_to_utc_time_t(const std::string& ts,
                                const std::string& utcOffset) {
  // two aliases for convenience
  namespace bps= boost::posix_time;
  namespace bg=boost::gregorian;
  namespace blt=boost::local_time;

  std::cout << " convert " << ts << " " << utcOffset << " in utc time\n";

  boost::local_time::time_zone_ptr tz(new boost::local_time::posix_time_zone(utcOffset));

  bps::ptime t;

  if (std::string::npos == ts.find(":")) {
    t = bps::ptime(bg::from_string(ts));
  } else {
    t = bps::ptime (bps::time_from_string(ts));
  }

  bps::ptime epoch(bg::date(1970,1,1));
  blt::local_date_time ldt(t.date(), t.time_of_day(), tz,
                           blt::local_date_time::NOT_DATE_TIME_ON_ERROR);
  bps::time_duration::sec_type x = (ldt.utc_time() - epoch).total_seconds();
  return std::time_t(x);
}

/**
 * \brief Simple function to read the content of the regular file
 * \param filePath: the path to the file
 * \param rejectEmptyFile: tell whether empty file will be rejected
 * \return The content of the file
 */
std::string
vishnu::get_file_content(const std::string& filePath,
                         const bool& rejectEmptyFile) {
  bfs::path file (filePath);

  // Check the existence of file
  if (! bfs::exists(file) ||
      ! bfs::is_regular_file(file) ||
      ( bfs::is_empty(file) && rejectEmptyFile) ) {
    throw UserException(ERRCODE_INVALID_PARAM, "can not read the file: " + filePath);
  }

  bfs::ifstream ifs(file);
  // Read the whole file into string
  std::stringstream ss;
  ss << ifs.rdbuf();
  ifs.close();
  return ss.str();
}

/**
 * \brief Function to move file
 * \param src: the path of the file to move
 * \param dest: the destination where the file will be moved
 * \param file: the name of the file in dest
 * \return raises an exception on error
 */
int
vishnu::boostMoveFile(const std::string& src, const std::string& dest,
                      const std::string& filename) {
  bfs::path filePath(src);
  bfs::path fileDestPath(dest);
  bfs::path fileNewPath(src);
  if(filename.size()!=0) {
    fileNewPath = bfs::path(filename);
  }

  try {
    //If the destination does not exist, the file is created in the current directory
    if(!bfs::exists(fileDestPath)) {
      bfs::path completePath(bfs::current_path().string() / fileNewPath.filename());
      if(bfs::exists(completePath)) {
        bfs::remove(completePath);
      }
      bfs::copy_file(filePath, completePath);
      bfs::remove(filePath);
    } else {
      bfs::path completePath(fileDestPath / fileNewPath.filename());
      if(bfs::exists(completePath)){
        bfs::remove(completePath);
      }
      bfs::copy_file(filePath, completePath);
      bfs::remove(filePath);
    }
  } catch (std::exception& e) {
    throw UserException(ERRCODE_INVALID_PARAM, e.what());
  }
  return 0;
}

/**
 * \brief Function to check a numerical value
 * \param value The value to check
 * \return raises an exception on error
 */
bool
vishnu::isNumericalValue(const std::string& value) {
  bool ret;
  if (0 == value.size()) {
    throw UserException(ERRCODE_INVALID_PARAM,
                        ("Invalid numerical value: The given value is empty"));
  }
  try{
    ret = value.find_first_not_of("0123456789") == std::string::npos;
  } catch (std::exception& e){
    throw UserException(ERRCODE_INVALID_PARAM,
                        ("std exception caught for: " + value+ " with error: "+e.what()));
  }
  if (!ret) {
    throw UserException(ERRCODE_INVALID_PARAM,
                        ("Invalid numerical value: " + value));
  }
  return ret;
}


/**
 * \brief Function a given walltime into string
 * \param walltime The walltime to convert
 * \return the walltime converted to string
 */
std::string
vishnu::convertWallTimeToString(const long& walltime) {
  long totalTime = walltime;
  long j = totalTime/86400;
  totalTime = walltime-j*86400;
  long h =  totalTime/3600;
  totalTime =  totalTime-h*3600;
  long m =  totalTime/60;
  long s =  totalTime-m*60;

  std::ostringstream StrWallTime;
  if (j > 0) {
    if (j < 10) {
      StrWallTime << "0" << j << ":";
    } else {
      StrWallTime <<  j << ":";
    }
  }

  if (h < 10) {
    StrWallTime << "0" << h << ":";
  } else {
    StrWallTime <<  h << ":";
  }

  if (m < 10) {
    StrWallTime << "0" << m << ":";
  } else {
    StrWallTime << m << ":";
  }

  if(s < 10) {
    StrWallTime << "0" << s;
  } else {
    StrWallTime << s;
  }

  return StrWallTime.str();
}

/**
 * \brief Function a given walltime into seconds
 *
 * walltime can be of the following format:
 * - it can start and/or end by '"'
 * - each value is separated by ':'
 * - possible values represent:
 *   - days
 *   - hours
 *   - minutes
 *   - seconds
 * in the form [days:][hours:][minutes:]seconds
 *  (element between square brackets are optional)
 *
 * \param walltime The walltime to convert
 * \return the walltime converted to seconds
 */
long
vishnu::convertStringToWallTime(const std::string& walltime) {
  boost::regex reg("^\"?(\\d+)(?::(\\d+))?(?::(\\d+))?(?::(\\d+))?\"?$");
  boost::smatch groups;

  long time = 0;

  if (boost::regex_match(walltime, groups, reg)) {
    boost::smatch::const_iterator it;
    unsigned int start = 1;  // skip first value which is the full string

    it = groups.begin();
    ++it;  // skip first value which is the full string
    /* Count the number of not empty groups (-1, as the first element
     * in the group is the full string)
     */
    unsigned int nbFound =
      groups.size() - 1 - std::count(it, groups.end(), "");

    if (nbFound == 4) {  // days:hours:minutes:seconds
      time += 86400 * boost::lexical_cast<long>(groups[1]);
      start = 2;
    }

    for (unsigned int i = start; i <= nbFound; i++) {
      time += boost::lexical_cast<long>(
        std::pow(60.,
                 boost::lexical_cast<int>(nbFound - i))) * boost::lexical_cast<long>(groups[i]);
    }
  } else {
    throw UserException(ERRCODE_INVALID_PARAM,
                        "Invalid walltime value: '" + walltime + "'");
  }

  return time;
}

/**
 * \brief Function to check the job status
 * \param status the status of the job
 * \return raises an exception on error
 */
void
vishnu::checkJobStatus(const int& status) {
  if ((status < -1) || (status > 8)) {
    throw UserException(ERRCODE_INVALID_PARAM, "The status value is incorrect");
  }
}

/**
 * \brief Function to check the job priority
 * \param priority the priority of the job
 * \return raises an exception on error
 */
void
vishnu::checkJobPriority(const int& priority) {
  if ((priority < -1) || (priority > 5)) {
    throw UserException(ERRCODE_INVALID_PARAM,
                        "The priority value is incorrect");
  }
}

/**
 * \brief Function to check the job nbNodesAndCpuPerNode
 * \param nbNodesAndNbCpuPerNode the number of nodes and cpu per node
 * \return raises an exception on error
 */
void
vishnu::checkJobNbNodesAndNbCpuPerNode(const std::string& nbNodesAndCpuPerNode) {
  if(nbNodesAndCpuPerNode.size()) {
    size_t posNbNodes;
    try {
      posNbNodes = nbNodesAndCpuPerNode.find(":");
      if(posNbNodes!=std::string::npos) {

        std::string nbNodes = nbNodesAndCpuPerNode.substr(0, posNbNodes);
        isNumericalValue(nbNodes);

        std::string cpuPerNode = nbNodesAndCpuPerNode.substr(posNbNodes+1);
        isNumericalValue(cpuPerNode);
      } else {
        throw UserException(ERRCODE_INVALID_PARAM,
                            ("Invalid NbNodesAndNbCpuPerNode value: "+nbNodesAndCpuPerNode));
      }
    } catch(UserException& ue) {
      throw UserException(ERRCODE_INVALID_PARAM,
                          ("Invalid NbNodesAndNbCpuPerNode value: "+nbNodesAndCpuPerNode));
    }
  }
}

/**
 * \brief Function to get current time in seconds (UTC)
 * \return the time as the number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)
 */
time_t vishnu::getCurrentTimeInUTC() {

  return std::time(0);
}

/**
 * \brief Function to convert UTC time into localtime (seconds)
 * \return the correspondant localtime (seconds)
 */
time_t
vishnu::convertUTCtimeINLocaltime(const time_t& utctime) {
  //the current time
  boost::posix_time::ptime now =
      boost::posix_time::microsec_clock::local_time();

  time_t currentTime = string_to_time_t(to_simple_string(now));

  long diff = currentTime-std::time(0);
  return (utctime+diff);
}

/**
 * \brief Function to localtime into UTC (seconds)
 * \return the diffence time (seconds)
 */
time_t
vishnu::convertLocaltimeINUTCtime(const time_t& localtime) {
  //the current time
  boost::posix_time::ptime now =
      boost::posix_time::microsec_clock::local_time();

  time_t currentTime = string_to_time_t(to_simple_string(now));

  long diff = currentTime - std::time(0);
  return (localtime - diff);
}

/**
 * \brief Function to return the difference between localtime and UTC time (seconds)
 * \return the difference time (seconds)
 */
long
vishnu::diffLocaltimeUTCtime() {
  //the current time
  boost::posix_time::ptime now =
      boost::posix_time::microsec_clock::local_time();

  time_t currentTime = string_to_time_t(to_simple_string(now));

  long diff = currentTime - std::time(0);
  return diff;
}

/**
 * \brief Function to create temporary file
 * \param fileName The name of the file to create
 * \param file_content The content of the file
 */
void
vishnu::createTmpFile(char* fileName, const std::string& file_content) {
  int file_descriptor = mkstemp( fileName );
  ssize_t file_size = file_content.size();
  if (file_descriptor == -1) {
    throw
    SystemException(ERRCODE_SYSTEM, "vishnu::createTmpFile: Cannot create the file "+ std::string(fileName));
  }

  if (fchmod(file_descriptor, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH)) {
    close(file_descriptor);
    throw SystemException(ERRCODE_SYSTEM, "vishnu::createTmpFile: reading or writing rights have"
                          " not been change on the path. This can lead to an error");
  }

  if (write(file_descriptor, file_content.c_str(), file_size) != file_size ) {
    close(file_descriptor);
    throw SystemException(ERRCODE_SYSTEM,
                          "vishnu::createTmpFile: Cannot write the content int "
                          "to new created file");
  }

  close(file_descriptor);
}

/**
 * \brief Function to create temporary file
 * \param fileName The name of the file to create
 * \param content The content of the file
 */
void
vishnu::saveInFile(const std::string & fileName,
                   const std::string& content) {

  bfs::ofstream file(fileName);
  if (!file.good()) {
    throw SystemException(ERRCODE_INVDATA,
                          "vishnu::saveInFile: Cannot create the file "+fileName);
  }
  file << content;
  file.close();
}

/**
 * \brief Function to create temporary file
 * \param fileName The name of the file to create
 * \param missingDesc The content of the file
 */
void
vishnu::recordMissingFiles(const std::string & fileName,
                           const std::string& missingDesc) {

  bfs::ofstream file(fileName);

  ListStrings missingFiles;
  boost::split(missingFiles, missingDesc, boost::is_space());
  int count = missingFiles.size();
  for(int i = 1; i < count; i++) {
    file << missingFiles[i] << "\n";
    //std::cout << missingFiles[i] << "\n";
  }

  file.close();
}

/**
 * \brief Function to create temporary file
 * \param fileName The name of the file to create
 */
void
vishnu::createTmpFile(char* fileName) {
  int  file_descriptor = mkstemp(fileName);
  if( file_descriptor == -1 ) {
    throw SystemException(ERRCODE_SYSTEM,
                          "vishnu::createTmpFile: Cannot create new tmp file");
  }

  if(fchmod(file_descriptor, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH )) {
    close(file_descriptor);
    throw SystemException(ERRCODE_SYSTEM, "vishnu::createTmpFile: reading or "
                          "writing rights have not been on the path. "
                          "This can lead to an error");
  }

  close(file_descriptor);
}

/**
 * \brief Function to delete file
 * \param fileName The name of the file to create
 */
int
vishnu::deleteFile(const char* fileName) {
  return unlink(fileName);
}

/**
 * \brief Function to check the metric value
 * \param value the metric value
 * \return raises an exception on error
 */
void
vishnu::checkMetricHistoryValue(const int& metric) {
  if ((metric < -1) || (metric > 6)) {
    throw UserException(ERRCODE_INVALID_PARAM, "The metric value is incorrect");
  }
}

/**
 * \brief Function to check the remote file path
 * \param path the remote file path
 * \return raises an exception on error
 */
void
vishnu::checkRemotePath(const std::string& path){
  if (path.find(":") == std::string::npos){
    throw FMSVishnuException(ERRCODE_INVALID_PATH, "The path must be a remote file and in the form machineId:path");
  }
}

/**
 * \brief Check if the pid exists
 * \param pid The given pid
 * \param proc_dir The given process info directory
 * \return True if the pid exists
 */


bool
vishnu::process_exists(const std::string& pid, const bfs::path& proc_dir) {
  // FIXME : procdir is not portable, kill 0 might be better, but right problems ?
  bfs::path token(proc_dir);
  token /= pid;
  return bfs::exists(token);
}


/**
 * \brief Get the fully qualified name for the current system
 * \param port the port
 * \return the fully qualified name for the current system
 */
std::string
vishnu::getLocalMachineName(const std::string& port ) {
  char hostname[MAXHOSTNAMELEN];
  gethostname(hostname, MAXHOSTNAMELEN);
  struct addrinfo hints, *servinfo;
  int rv;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // ither IPV4 or IPV6  use AF_INET6 to force IPv6
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;

  if ((rv = getaddrinfo(hostname,port.c_str(), &hints, &servinfo))) {
    SystemException(ERRCODE_SYSTEM, gai_strerror(rv));
  }
  if(!servinfo->ai_canonname) {
    throw SystemException(ERRCODE_SYSTEM, "can not resolve the machine name");
  }

  return servinfo->ai_canonname;
}

/**
 * \brief Function to check if a string is empty
 * \param str The string to check
 * \param compMsg The complementary message to print
 * \return raises an exception on error
 */
void
vishnu::checkEmptyString(const std::string& str,
                         const std::string& compMsg) {
  if(str.empty()) {
    throw UserException(ERRCODE_INVALID_PARAM, compMsg + " must not be empty");
  }
}

/**
 * \brief Function to parse textual or file parameters
 * \param IN opt A structure containing the set of submitted options
 * \param OUT paramsStr a string containing all of parameters
 * \param IN paramOptName the name of the option for a single parameter
 * \param IN paramsVector a vector of parameters
 * \return true if all parameters are syntaxicaly valid
 */
int
vishnu::validateParameters(const boost::shared_ptr<Options> & opt,
                           std::string & paramsStr,
                           const std::string & paramOptName,
                           const ListStrings & paramsVector) {

  if (opt->count(paramOptName)) {
    paramsStr = opt->get<std::string>(paramOptName);
  }

  // Append other parameters in paramStr
  for(ListStrings::const_iterator it = paramsVector.begin();
      it != paramsVector.end(); ++it) {
    paramsStr += " " + *it;
  }

  //Now check the syntax of parameters and set them suitable for VISHNU
  ListStrings paramsVecBuffer;
  boost::trim(paramsStr);
  boost::split(paramsVecBuffer, paramsStr, boost::is_space(), boost::token_compress_on);

  paramsStr = ""; // Reinitialization for outpout
  for(ListStrings::iterator it = paramsVecBuffer.begin();
      it != paramsVecBuffer.end(); ++it) {
    size_t pos = (*it).find("=");
    if (pos == 0 || pos == std::string::npos || pos == (*it).size() - 1) {
      std::cerr << "Uncompleted definition for the parameter : '" << *it << "'\n";
      return CLI_ERROR_INVALID_PARAMETER;
    }

    std::string paramName = (*it).substr(0, pos); // Keep the parameter name in upper case
    std::string paramValue = (*it).substr(pos+1, std::string::npos);

    // Check whether the parameter is duplicate
    if (paramsStr.size()) {
      size_t start(0);
      while (pos = paramsStr.find(paramName + "=", start),
             pos != std::string::npos) {
        if (pos == 0 || paramsStr[pos-1] == char(' ')) {
          std::cerr << "Duplicate parameter : '" << paramName << "'\n";
          return CLI_ERROR_INVALID_PARAMETER;
        }
        start = pos + paramName.size();
      }
      paramsStr += " ";
    }
    // Append the parameter
    paramsStr += paramName + "=" + paramValue;
  }
  return 0;
}


/**
 * \brief Function to list file containing in a directory. Recursivity is not taken into account
 * \param fileNames the names of files containing in the directory
 * \param dirPath The path of the directory
 * \return true on success and false if not
 * */
bool
vishnu::appendFilesFromDir(std::ostringstream& fileNames,
                           const std::string & dirPath) {
  if (! bfs::exists(dirPath)) {
    return false;
  }

  for (bfs::directory_iterator it(dirPath);
       it != bfs::directory_iterator(); ++it) {
    if ( bfs::is_directory( *it )) {
      continue;
    }

    //TODO Check if it's a absolute or a relative path
    fileNames << ((fileNames.str().size())? " " : "") + it->path().string();
  }

  return true;
}

/**
 * \brief Function to get the list of output files related to a job
 * \param result : The Job Result
 * \param appendJobId : Determine whether or not append the job id before the files lists
 * \return The list of files
 * Throw exception on error
 * */
//FIXME: do it with ssh and add try catch
std::string
vishnu::getResultFiles(const TMS_Data::JobResult & result,
                       const bool & appendJobId) {

  std::ostringstream existingFiles;
  if(appendJobId) {
    existingFiles << result.getJobId();
  }
  existingFiles << (existingFiles.str().size()? " " : "") << result.getOutputPath()
                << " " << result.getErrorPath()
                << " " << result.getOutputDir()
                << "\n";
  return existingFiles.str();
}

/**
 * \brief Function to create a directory
 * \param dirPath The path of the directory
 * Throw exception on error
 * */
void
vishnu::createOutputDir(std::string& dirPath) {

  if (bfs::exists(dirPath) && bfs::is_directory(dirPath)) {
    return ;
  }
  try{
    if (! bfs::create_directory(bfs::path(dirPath))) {
      throw SystemException(ERRCODE_SYSTEM, "vishnu::createDir: Cannot create the directory: " + dirPath) ;
    }
  } catch(...) {
    throw SystemException(ERRCODE_SYSTEM, "Directory creation failed") ;
  }
}

/**
 * \brief Function to create a unique file suffix with the current time
 * \return the suffix created
 * */
std::string
vishnu::createSuffixFromCurTime() {
  std::ostringstream ossBuf;
  time_t rawtime;
  time(&rawtime);
  struct tm * tinfo;
  tinfo = localtime(&rawtime);
  ossBuf << "_" << (1900 + tinfo->tm_year)
         << ( tinfo->tm_mon < 9? "0": "")<< tinfo->tm_mon + 1
         << ( tinfo->tm_mday < 10? "0": "" )<< tinfo->tm_mday
         << ( tinfo->tm_hour < 10? "0": "" )<< tinfo->tm_hour
         << ( tinfo->tm_min < 10? "0": "" )<< tinfo->tm_min
         << ( tinfo->tm_sec < 10? "0": "" )<< tinfo->tm_sec;
  return ossBuf.str();
}

/**
 * \brief Function to make a link from a given
 * \param src : the source file
 * \return the path of the link
 * Throw exception on error
 */
std::string
vishnu::mklink(const std::string& src) {
  if (! bfs::exists(src)) {
    throw UserException(ERRCODE_FILENOTFOUND, "SSHJobExec::mklink : "
                        "the file "+ src + " doesnot exist.");
  }
  bfs::path dest;
  try {
    dest = bfs::unique_path("/tmp/vishnulink%%%%%%");
    bfs::create_symlink(src, dest);
  } catch (...) {
    throw SystemException(ERRCODE_SYSTEM, "SSHJobExec::mklink : "
                          "error while making a link on the file " + src + " from " + dest.string());
  }
  return dest.string();
}

// Cela fait une copie de la liste en retour, à modifier si cela gène
std::vector<std::string>
vishnu::getIPList(){
  std::vector<std::string> addresses;

  struct ifaddrs *ifa = NULL, *ifEntry = NULL;
  int rc = 0;

  // Recuperation of the interfaces
  rc = getifaddrs(&ifa);
  // If interfaces gotten without error
  if (rc == 0) {
    void *addPtr = NULL;
    char addressBuffer[INET6_ADDRSTRLEN]; // Max size for ipv6 in case

    // Browing the list of interface
    for(ifEntry=ifa; ifEntry!=NULL; ifEntry=ifEntry->ifa_next) {
      // If not address continue
      if(ifEntry->ifa_addr->sa_data == NULL) {
        continue;
      }
      // If IPV4
      if(ifEntry->ifa_addr->sa_family==AF_INET) {
        addPtr = &((struct sockaddr_in *)ifEntry->ifa_addr)->sin_addr;
      } else {
        //It isn't IPv4
        continue;
      }
      // Converting address
      const char *a = inet_ntop(ifEntry->ifa_addr->sa_family,
                                addPtr,
                                addressBuffer,
                                sizeof(addressBuffer));
      std::string localhost = "127.0.0.1";
      // Adding the found adress
      if(a != NULL && localhost.compare(std::string(a)) != 0) {
        addresses.push_back(std::string(a));
      }
    }
  }
  // Freeing memory
  freeifaddrs(ifa);

  return addresses;
}

void
vishnu::setIP(std::string& name, std::string IP){
  std::string tmp = std::string("localhost");
  name.replace(name.find(tmp), tmp.length(), IP);
}

bool
vishnu::isNotIP(std::string name) {
  boost::asio::ip::address ad;

  try {
    /* We use boost asio to check whether "name" is an IP address
     * It will throw an exception if "name" is not an IP"
     */
    ad.from_string(name);
  } catch (boost::exception & e) {
    return true;
  }

  return false;
}

/**
 * \brief Function to parse the string representing the version
 * \param version the string representing the version
 * \return  The version object
 */
UMS_Data::Version_ptr
vishnu::parseVersion(const std::string& version) {
  UMS_Data::Version_ptr vers = NULL;
  std::string major;
  std::string minor;
  std::string patch;

  size_t found = version.find_first_of(".");
  if (found != std::string::npos) {
    major = version.substr(0, found) ;
    std::string rest = version.substr(found+1, version.size()) ;
    found = rest.find_first_of(".");
    if (found != std::string::npos) {
      minor = rest.substr(0, found);
      patch = rest.substr(found+1, rest.size());
    }
    //if the string major, minor, patch are not empty
    if ((major.size() != 0) && (minor.size() != 0)
        && (patch.size() != 0)) {
      //if the values major, minor, patch are positives and major value higher than zero
      if ((convertToInt(major) > 0) && (convertToInt(minor) >= 0)
          && (convertToInt(patch) >= 0)) {
        UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
        vers = ecoreFactory->createVersion();
        vers->setMajor(convertToInt(major));
        vers->setMinor(convertToInt(minor));
        vers->setPatch(convertToInt(patch));
        vers->setStringformat(version);
      }
    }
  }

  return vers;
}

/**
 * \brief Source an configuration file
 * \param filePath: the path to the file
 */
void
vishnu::sourceFile(const std::string& filePath) {

  std::istringstream fstream (vishnu::get_file_content(filePath, false));
  std::string line;
  if( fstream.good()) {
    while(getline(fstream, line)) {

      if(line.size() == 0 ||
         ! ::isalpha(line[0])) {
        continue;
      }

      size_t pos = line.find("=");
      std::string variable = line.substr(0, pos);
      std::string value = line.substr(pos+1, std::string::npos);
      setenv(variable.c_str(), value.c_str(), 0);
    }
  }
}


/**
 * \brief Function to convert a string to a batch type
 * \param  batchName the name of the batch type
 * \return BatchType value of the corresponding string.
 */
BatchType
vishnu::convertToBatchType(const std::string& batchName) {

  BatchType batchType = UNDEFINED;
  if (batchName == "TORQUE") {
    batchType = TORQUE;
  } else if (batchName == "LOADLEVELER") {
    batchType = LOADLEVELER;
  } else if (batchName == "SLURM") {
    batchType = SLURM;
  } else if (batchName == "LSF") {
    batchType = LSF;
  } else if (batchName == "SGE") {
    batchType = SGE;
  } else if (batchName == "DELTACLOUD") {
    batchType = DELTACLOUD;
  } else if (batchName == "PBS") {
    batchType = PBSPRO;
  } else if (batchName == "POSIX") {
    batchType = POSIX;
  }

  return batchType;
}
