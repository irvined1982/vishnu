

#include "update_local_account.hpp"
#include "utils.hpp"
#include "localAccountUtils.hpp"
#include "sessionUtils.hpp"
#include <boost/bind.hpp>

namespace po = boost::program_options;

using namespace std;

int main (int ac, char* av[]){



  /******* Parsed value containers ****************/

  string dietConfig;

  std::string sshKeyPath;

  std::string sessionKey;


  /********** EMF data ************/

  UMS_Data::LocalAccount upAcLogin;
  /******** Callback functions ******************/

  boost::function1<void,string> fUserId( boost::bind(&UMS_Data::LocalAccount::setUserId,boost::ref(upAcLogin),_1));
  boost::function1<void,string> fMachineId( boost::bind(&UMS_Data::LocalAccount::setMachineId,boost::ref(upAcLogin),_1));
  boost::function1<void,string> fAcLogin( boost::bind(&UMS_Data::LocalAccount::setAcLogin,boost::ref(upAcLogin),_1));
  boost::function1<void,string> fSshKeyPath( boost::bind(&UMS_Data::LocalAccount::setSshKeyPath,boost::ref(upAcLogin),_1));
  boost::function1<void,string> fHomeDirectory( boost::bind(&UMS_Data::LocalAccount::setHomeDirectory,boost::ref(upAcLogin),_1));

  /**************** Describe options *************/

  boost::shared_ptr<Options> opt=makeLocalAccountOptions(av[0], fUserId,dietConfig,fMachineId,
                                                         fAcLogin,fSshKeyPath,fHomeDirectory);

  try {
    /**************  Parse to retrieve option values  ********************/

    opt->parse_cli(ac,av);

    opt->parse_env(env_name_mapper());

    opt->notify();


    /********  Process **************************/


    checkVishnuConfig(*opt);


    /************** Call UMS connect service *******************************/

    // initializing DIET

    if (vishnuInitialize(const_cast<char*>(dietConfig.c_str()), ac, av)) {
      cerr << "DIET initialization failed !" << endl;
      return 1;
    }


    //get the sessionKey

    sessionKey=getLastSessionKey(getppid());

    if(false==sessionKey.empty()){

      cout <<"the current sessionkey is: " << sessionKey <<endl;

      updateLocalAccount(sessionKey,upAcLogin);


    }






  }// End of try bloc

  catch(po::required_option& e){// a required parameter is missing


    usage(*opt," userId machineId","required parameter is missing");
  }

  catch(VishnuException& e){// catch all Vishnu runtime error

    errorUsage(av[0], e.getMsg(),EXECERROR);

    return e.getMsgI() ;
  }

  catch(std::exception& e){

    errorUsage(av[0],e.what());

    return 1;
  }

  return 0;

}// end of main


