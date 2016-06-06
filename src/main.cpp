#include <iostream>
#include <stdlib.h>
#include "cmd/cmd.h"
#include "util/help_function.h"
#include "util/myUsage.h"
#include "rt/RtMgr.h"
using namespace std;

extern bool initCommonCmd();
extern bool initPlnCmd();

CmdParser* cmdMgr = new CmdParser("cmd> ");
MyUsage* myusage;
RtMgr* rtMgr = new RtMgr();

int main(int argc, char** argv)
{
   ifstream dof;

   if(argc == 6)  //cmd <case.v> <case_input.def> <tech.lef> <blocks.lef> <initial_files>
   {
   	 //  TODO...







		return 0;
   }
   else if (argc == 3)   // -File <doFile>
   {
      if (myStrNCmp("-File", argv[1], 2))
      {
         if (!cmdMgr->openDofile(argv[2]))
         {
            cerr << "Error: cannot open file \"" << argv[2] << "\"!!\n";
            exit(-1);
         }
      }
      else {
         cerr << "Error: unknown argument \"" << argv[1] << "\"!!\n";
         exit(-1);
      }
   }
   else if (argc != 1)
   {
      cerr << "Error: illegal number of argument (" << argc << ")!!\n"<<endl
           << "ussage : cmd <case.v> <case_input.def> <tech.lef> <blocks.lef> <initial_files>"<<endl;
      exit(-1);
   }
   
   if (!initCommonCmd() || !initPlnCmd())
   {
      cerr << "Registering \"init\" commands fails... exiting" << endl;
      return 1;
   }

   system("clear");
   cout<<"********************************************************************************"<<endl
       <<"* Program       : CAD contest - Multiple Power Distribution Network Planning   *"<<endl
       <<"* Group         : NTUEE_JTCC                                                   *"<<endl
       <<"* Author        : Chen, Jia-Shiuan  Tsai, Cheng-Wei                            *"<<endl
       <<"* Version       : Alpha                                                        *"<<endl
       <<"* Last modified : 2016.06.05                                                   *"<<endl
       <<"* Description   :                                                              *"<<endl
       <<"********************************************************************************"<<endl;

   myusage = new MyUsage();
   
   CmdExecStatus status = CMD_EXEC_DONE;
   while (status != CMD_EXEC_QUIT) 
   {
      myusage->start();
      status = cmdMgr->execOneCmd();
      cout << endl;
      myusage->stop();
   }

   return 0;
}