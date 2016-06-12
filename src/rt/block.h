#ifndef BLOCK_H
#define BLOCK_H

#include <string>
using namespace std;

class pin
{
public:
	pin(){}

  string name;
  string DIRECTION;
  string USE;
  float current;
  float IR_drop;

  vector<vector<string> > PORT; // need to be tarsform to int

  vector<string > destination ;
};


class block
{
public :
	block():num(0){};

    int num;
	string name;
	string CLASS;
	int ORIGIN[2];
	int size[2];
	vector<string> SYMMETRY ;  	
	vector< vector<string> > OBS ; // need to be tarsform to int

	map<string, pin> pins;

  vector<string> member;

};
#endif