#ifndef RTMGR
#define RTMGR

#include <string>
#include <fstream>
#include "field.h"
using namespace std;

class RtMgr
{   
public:
    RtMgr(){}
   	bool parse_block(ifstream&);
	bool parse_v(ifstream&);
	bool parse_tech(ifstream&);


private:
	Field field;

};

#endif
