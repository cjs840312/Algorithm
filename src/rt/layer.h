#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <map>
using namespace std;

struct Rect
{
	float rect[4];
};

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
	float metal_weight;
};

class Via
{
public:
	Via(){}
	~Via(){}

	string name;
	int cross_layer[2];
	string type;
	float Re;
	std::map<int, vector<float> >  rect_map;
};



#endif