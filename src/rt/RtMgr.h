#ifndef RTMGR
#define RTMGR

#include <string>
#include <map>
#include <fstream>
#include "field.h"
using namespace std;

class RtMgr
{   
public:
   RtMgr(){}
   bool parse( ifstream& fin, int n)
   {
   	if(n==3)
   		parse_block(fin);
   }

private:
	
	bool parse_block(ifstream&);
	Field field;

};

#endif
