#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <map>
using namespace std;


class Layer
{
public :
	
	Layer(){}
	~Layer(){}

	int id;
	string name;
	string type;
	int min_width;
	int max_width;
	int spacing;
	int pitch;
	int offset;
	string direction;
	float Re_per_Sqrt;

};

class Via
{
public:
	Via(){}
	~Via(){}

	string name;
	int cross_layer[2];
	char type;
	float Re;
	map<int, float[4] >  rect_map;
};

#endif