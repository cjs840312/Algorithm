#ifndef FIELD
#define FIELD

#include <vector>
#include <map>
#include "block.h"
#include "layer.h"
using namespace std;


class Input
{
public :   
	Input(){}
	~Input(){}

	string name;
	string metal_layer;
	int metal_layer_rect[4];
	int position[2];


};

class Field
{
public :
	
	Field(){}

	int unit, diearea[4];
	map<string, Input> inputs_map;
	map<string, block> blocks;
	map<string, Layer> layers_map;
	vector<  vector< Via > > Vias_matrix;

};


#endif