#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <map>
using namespace std;


class Layer
{
public :
	
	Layer(){}

	int id;
	string name;
	int min_width;
	int max_width;
	int spacing;
	int pitch;
	int offset;
	float Re_per_Sqrt;

};

class Via
{
public:
	Via(){}
	string name;
	float Re;
	map<string, vector<float> >  jump_map;
};

#endif