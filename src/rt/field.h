#ifndef FIELD
#define FIELD

#include <vector>
#include <map>
#include "block.h"
using namespace std;


class Field
{
public :
	
	Field(){}



	vector<string> inputs;
	map<string,block> blocks;

};

#endif