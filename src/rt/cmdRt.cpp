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
   if ( !(cmdMgr->regCmd("REad"     , 2, new ReadCmd    )) || 
        !(cmdMgr->regCmd("Modulize" , 1, new ModulizeCmd)) ||
        !(cmdMgr->regCmd("ROuting"  , 2, new RoutingCmd )) ||
        !(cmdMgr->regCmd("Print"    , 1, new PrintCmd   ))     )
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

      ifstream fin0( target[0].c_str()),
               fin3( target[3].c_str()), 
               fin2( target[2].c_str()),
               fin4( target[4].c_str()), 
               fin1( target[1].c_str()) ;


      if( !fin3.is_open() || !rtMgr->parse_block(fin3))
      {
         cout<<"Read input file \""<<target[3]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }
      cout << "Read input file  \""<<target[3]<<"\" successfully" << endl;      


      if( !fin2.is_open() || !rtMgr->parse_tech(fin2))
      {
         cout<<"Read input file \""<<target[2]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }
      cout << "Read input file  \""<<target[2]<<"\" successfully" << endl;


      if( !fin0.is_open() || !rtMgr->parse_v(fin0))
      {
         cout<<"Read input file \""<<target[0]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }
      cout << "Read input file  \""<<target[0]<<"\" successfully" << endl;

      if( !fin1.is_open() || !rtMgr->parse_input_def(fin1))
      {
         cout<<"Read input file \""<<target[1]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }
      cout << "Read input file  \""<<target[1]<<"\" successfully" << endl;

      if( !fin4.is_open() || !rtMgr->parse_initial(fin4))
      {
         cout<<"Read input file \""<<target[4]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }
      cout << "Read input file  \""<<target[4]<<"\" successfully" << endl;


   }
   else
      return CMD_EXEC_ERROR;
   return CMD_EXEC_DONE;
}

void
ReadCmd::usage(ostream& os) const
{
   os << "Usage: REad < string File1 > < string File2 >" << endl;
}

void
ReadCmd::help() const
{
   cout << setw(10) << left << "REad"
        << ": read and parse input file " << endl;
}

//-----------------------------------------------------------------------------
//    Modulize
//-----------------------------------------------------------------------------

CmdExecStatus
ModulizeCmd::exec(const string& option)
{
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(!tokens.empty())
      return errorOption(CMD_OPT_EXTRA, tokens[0]);
   else if(!rtMgr->modulize())
   {
      cerr<<"Failed to Modulize..."<<endl;
      return CMD_EXEC_ERROR;
   }
   return CMD_EXEC_DONE;
}

void
ModulizeCmd::usage(ostream& os) const
{
   os << "Usage: Modulize" << endl;
}

void
ModulizeCmd::help() const
{
   cout << setw(10) << left << "Modulize"
        << ": transfer the input infomation to graph " << endl;
}

//-----------------------------------------------------------------------------
//    Routing
//-----------------------------------------------------------------------------

CmdExecStatus
RoutingCmd::exec(const string& option)
{
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(!tokens.empty())
      return errorOption(CMD_OPT_EXTRA, tokens[0]);
   else if(!rtMgr->routing())
   {
      cerr<<"Failed to Route..."<<endl;
      return CMD_EXEC_ERROR;
   }
   return CMD_EXEC_DONE;
}

void
RoutingCmd::usage(ostream& os) const
{
   os << "Usage: ROuting" << endl;
}

void
RoutingCmd::help() const
{
   cout << setw(10) << left << "ROuting"
        << ": main function in this program " << endl;
}

//-----------------------------------------------------------------------------
//    Print
//-----------------------------------------------------------------------------

CmdExecStatus
PrintCmd::exec(const string& option)
{
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(tokens.size()>2)
      return errorOption(CMD_OPT_EXTRA, tokens[2]);
   else if(getParameter(tokens, target, 2))
   {
      int p;
      if(!myStr2Int(target[0],p))
      {
         cerr<<"Illegal argument \""<<target[0]<<"\" !!"<<endl;
         return CMD_EXEC_ERROR;
      }
      
      rtMgr->print(p,target[1]);      
   }
   else
      return CMD_EXEC_ERROR;
   return CMD_EXEC_DONE;
}

void
PrintCmd::usage(ostream& os) const
{
   os << "Usage: Print <plane_#> <bmp_name>" << endl;
}

void
PrintCmd::help() const
{
   cout << setw(10) << left << "Print"
        << ": print the result graph to BMP file " << endl;
}