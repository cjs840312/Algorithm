#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../util/help_function.h"
#include "RtMgr.h"

using namespace std;
enum STATE
{
  VERSION,
  NAMESCASESENSITIVE,
  UNITS,
  MANUFACTURINGGRID,
  USEMINSPACING,
  LAYER,
  VIA,
  END,
  ERO
};

static STATE parse_state(string&);
static void check_comment(string&);
static bool parse_layer(ifstream&, vector<string>&, Field& field);
static bool parse_via(ifstream&);


bool
RtMgr::parse_tech(ifstream& fin)
{
	string s, version,  use_min_spacing;
	int unit, grid;
	STATE state;
	while(getline(fin,s))
	{	
		check_comment(s);
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) continue;
		switch ( tokens[0] )
		{
			case VERSION
				version = tokens[1];
				break;
  			case NAMESCASESENSITIVE
  				break;
  			case UNITS
  				getline(fin,s);
  				myStr2Tok(s,tokens);
  				myStr2Int(tokens[2], unit);
  				getline(fin,s);
  				break;
  			case MANUFACTURINGGRID
  				myStr2Int(tokens[1], grid);
  			case USEMINSPACING
  				use_min_spacing = tokens[2];
  			case LAYER
  				parse_layer(fin, tokens, field);
  			case VIA
  				parse_via(fin);
  			case END	
  				return true;
			default :
				cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
				return false;
		}
	}
	return false;
}

static STATE parse_state(string& s)
{
	if (s == "VERSION")
		return VERSION;
	else if ( s == "NAMESCASESENSITIVE")
		return NAMESCASESENSITIVE;
	else if ( s == "UNITS")
		return UNITS;
	else if ( s == "MANUFACTURINGGRID")
		return MANUFACTURINGGRID;
	else if ( s == "USEMINSPACING")
		return USEMINSPACING;
	else if ( s == "LAYER")
		return LAYER;
	else if ( s == "VIA")
		return VIA;
	else if ( s == "END")
		return END;
	else 
		return ERO;
}
static bool parse_layer(ifstream&, vector<string>& v, Field& field)
{
	string s;	

	while(getline(fin,s))
	{
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) continue;
	}

}
static bool parse_via(ifstream&)
{
	string s;	

	while(getline(fin,s))
	{
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) continue;
	}
}
static void check_comment(string& s)
{
  int size=s.size();
  for(int i=0;i<size;i++)
  {
    if(s[i]=='#')
    {
      s.resize(i);
      break;
    }    
  }
}