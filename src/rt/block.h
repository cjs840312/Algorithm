#ifndef BLOCK
#define BLOCK

#include <string>
using namespace std;

class pin
{
public:
	pin(){}

	string name;
    string DIRECTION;
    string USE;

    vector<vector<string> > PORT; // need to be tarsform to int
};


class block
{
public :
	block(){};

	string name;
	string CLASS;
  	int ORIGIN[2];
  	int size[2];
  	vector<string> SYMMETRY ;  	
  	vector< vector<string> > OBS ; // need to be tarsform to int
  	vector<pin> pins;

  	vector<vector<int > > destination ;



};
#endif