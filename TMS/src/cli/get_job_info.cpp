/**
 * \file get_job_info.cpp
 * This file defines the VISHNU get job info command 
 * \author Coulomb Kevin (kevin.coulomb@sysfera.com) and Daouda Traore (daouda.traore@sysfera.com)
 */


#include "CLICmd.hpp"
#include "utilVishnu.hpp"
#include "cliError.hpp"
#include "cliUtil.hpp"
#include "api_ums.hpp"
#include "api_tms.hpp"
#include "sessionUtils.hpp"
#include "displayer.hpp"

#include "GenericCli.hpp"

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;

struct InfoJobFunc {

  std::string mmachineId;
  std::string mjobId;

  InfoJobFunc(const std::string& machineId, const std::string& jobId):
    mmachineId(machineId), mjobId(jobId)
  {};

  int operator()(std::string sessionKey) {
     TMS_Data::Job job;
     int res = getJobInfo(sessionKey, mmachineId, mjobId, job);
     displayJob(job); 
     return res;
  }
};


int 
main (int argc, char* argv[]){
  
  /******* Parsed value containers ****************/
  string configFile;
  string machineId;
  string jobId;

  /**************** Describe options *************/
  boost::shared_ptr<Options> opt(new Options(argv[0]));

  // Environement option
  opt->add("configFile,c",
           "VISHNU configuration file",
           ENV,
           configFile);

  // All cli obligatory parameters
  opt->add("machineId,m",
	   "represents the id of the machine where the job has been submitted",
	   HIDDEN,
	   machineId,1);
  opt->setPosition("machineId",1);

  opt->add("jobId,j",
	   "represents the id of the job",
	   HIDDEN,
	   jobId,1);
  opt->setPosition("jobId",1);
 
  bool isEmpty;
  //To process list options
  GenericCli().processListOpt(opt, isEmpty, argc, argv, "machineId jobId");

  //call of the api function
  InfoJobFunc infoJobFunc(machineId, jobId);
  return GenericCli().run(infoJobFunc, configFile, argc, argv);
 
}
