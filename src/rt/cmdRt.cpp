#include <iomanip>
#include <cstring>
#include <vector>
#include "../util/help_function.h"
#include "cmdRt.h"
#include "RtMgr.h"

using namespace std;

extern RtMgr* rtMgr;

bool
initPlnCmd()
{
   if ( !(cmdMgr->regCmd("Read"     , 1, new ReadCmd))       )
      return false;
   return true;
}


//-----------------------------------------------------------------------------
//    Read <case.v> <case_input.def> <tech.lef> <blocks.lef> <initial_files>
//-----------------------------------------------------------------------------
CmdExecStatus
ReadCmd::exec(const string& option)
{
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(tokens.size()>5)
      return errorOption(CMD_OPT_EXTRA, tokens[5]);
   else if(getParameter(tokens, target, 5))
   {
      delete rtMgr;
      rtMgr= new RtMgr();

      ifstream fin0( target[0].c_str()), fin3( target[3].c_str());


      if( !fin3.is_open() || !rtMgr->parse_block(fin3))
      {
         cout<<"Read input file \""<<target[3]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }
      cout << "Read input file  \""<<target[3]<<"\" successfully" << endl;      



      if( !fin0.is_open() || !rtMgr->parse_v(fin0))
      {
         cout<<"Read input file \""<<target[0]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }
      cout << "Read input file  \""<<target[0]<<"\" successfully" << endl;




   }
   else
      return CMD_EXEC_ERROR;
   return CMD_EXEC_DONE;
}

void
ReadCmd::usage(ostream& os) const
{
   os << "Usage: Read < string File1 > < string File2 >" << endl;
}

void
ReadCmd::help() const
{
   cout << setw(10) << left << "Read"
        << ": read and parse input file " << endl;
}
