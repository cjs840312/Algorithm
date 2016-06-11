#ifndef RTMGR
#define RTMGR

#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include "graph.h"
#include "field.h"
using namespace std;

class RtMgr
{   
public:
   RtMgr(){}
   ~RtMgr(){if(graphs!=0) delete [] graphs;}
  	bool parse_block(ifstream&);
	bool parse_v(ifstream&);
	bool parse_tech(ifstream&);


   bool modulize();
   bool routing();
   void print(int,string);

private:
	Field field;
   Graph* graphs;
   stack< vector<int> > pathes;
};

#endif
