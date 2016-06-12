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
  ERO,
  TYPE,
  WIDTH,
  MAXWIDTH,
  SPACING,
  PITCH,
  OFFSET,
  DIRECTION,
  RESISTANCE,
};

static STATE parse_state(string&);
static void check_comment(string&);
static bool parse_layer(ifstream&, vector<string>&, Field& field);
static bool parse_via(ifstream&, vector<string>&, Field& field);


bool
RtMgr::parse_tech(ifstream& fin)
{
	string s, version,  use_min_spacing;
	int unit;
	float grid;
	STATE state;
	while(getline(fin,s))
	{	
		check_comment(s);
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) continue;
		switch ( parse_state(tokens[0]) )
		{
			case VERSION:
				version = tokens[1];
				break;
  			case NAMESCASESENSITIVE:
  				break;
  			case UNITS:
  				getline(fin,s);
  				myStr2Tok(s,tokens);
  				myStr2Int(tokens[2], unit);
  				getline(fin,s); //read out END UNITS
  				break;
  			case MANUFACTURINGGRID:
  				myStr2float(tokens[1], grid);
  				break;
  			case USEMINSPACING:
  				use_min_spacing = tokens[2];
  				break;
  			case LAYER:
  				parse_layer(fin, tokens, field);
  				break;
  			case VIA:
  				parse_via(fin, tokens, field);
  				break;
  			case END:	
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
	else if ( s == "TYPE" )
		return TYPE;
	else if ( s == "WIDTH" )
		return WIDTH;
	else if ( s == "MAXWIDTH" )
		return MAXWIDTH;
	else if ( s == "SPACING" )
		return SPACING;
	else if ( s == "PITCH" )
		return PITCH;
	else if ( s == "OFFSET" )
		return OFFSET;
	else if ( s == "DIRECTION" )
		return DIRECTION;
	else if ( s == "RESISTANCE" )
		return RESISTANCE;

	else 
		return ERO;
}
static bool parse_layer(ifstream& fin, vector<string>& v, Field& field)
{
	string s;	
	Layer temp_layer;
	//if( !myStrNCmp("METAL", v[1], 5 ) ) 
	if ( v[1][0] != 'M' ) {
		getline(fin, s);
		getline(fin, s);
		return false;
	}
	temp_layer.name = v[1];
	string id_string = v[1].substr(5);
	myStr2Int( id_string, temp_layer.id );
	while(getline(fin,s))
	{
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) continue;
		switch(parse_state(tokens[0]))
		{
			case TYPE:
				temp_layer.type = tokens[1];
				break;
			case WIDTH:
				myStr2Int(tokens[1], temp_layer.min_width);
				break;
    		case MAXWIDTH:
    			myStr2Int(tokens[1], temp_layer.max_width);
				break;
    		case SPACING:
    			myStr2Int(tokens[1], temp_layer.spacing);
    			break;
    		case PITCH:
    			myStr2Int(tokens[1], temp_layer.pitch);
    			break;
    		case OFFSET:
    			myStr2Int(tokens[1], temp_layer.offset);
    			break;
    		case DIRECTION:
    			temp_layer.direction = tokens[1];
    			break;
    		case RESISTANCE:
    			mySci2float(tokens[2], temp_layer.Re_per_Sqrt);
    			break;
    		case END:
    			if( tokens[1] == temp_layer.name && tokens.size() == 2) {
    				(field.layers_map).insert( pair<string, Layer> (v[1],temp_layer) ); 
    				return true;
    			}
    			cerr<<"Illigal header \""<<tokens[1]<<"\" !!";
          		return false;
    		default:
    			cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
            	return false;
		}
	}
}
static bool parse_via(ifstream& fin, vector<string>& v, Field& field)
{
	string s;
	Via temp_via;
	temp_via.name = v[1];
	string buff = v[1].substr(3);
	int n = buff.find_first_of("_");
	myStr2Int( buff.substr(0,n), temp_via.cross_layer[0] );
	temp_via.cross_layer[1] = temp_via.cross_layer[0] + 1; 
	temp_via.type = buff.substr(n+1);

	while(getline(fin,s))
	{
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) continue;
		switch (parse_state(tokens[0]) )
		{
			case RESISTANCE:
			{
				mySci2float( tokens[1], temp_via.Re);
				break;
			}
			case LAYER:
			{
				//if ( !myStrNCmp("METAL", tokens[1], 5 ) )
				if( tokens[1][0] != 'M' ) {
					getline(fin, s);
					break;
				}
				int layer_num;
				myStr2Int(tokens[1].substr(5), layer_num);

				tokens.clear();
				getline(fin,s);
				myStr2Tok(s,tokens);
				//Rect temp_rect = {0.0, 0.0, 0.0, 0.0};
				vector<float> temp_rect;
				for(int i =1; i<5; ++i) {
					float tmp;
					myStr2float( tokens[ i ], tmp); //temp_rect.rect[ i -1 ] );
					temp_rect.push_back(tmp);
				}
				(temp_via.rect_map).insert( std::pair<int, vector<float> > (layer_num, temp_rect) );
				break;
			}
			case END:
			{
				if( tokens[1] == temp_via.name && tokens.size() == 2) {
					if( field.Vias_matrix.empty() ) {
						vector<Via> tmp_list;
						tmp_list.push_back( temp_via );
						field.Vias_matrix.push_back( tmp_list );
					}
    				else if( field.Vias_matrix.back().back().cross_layer[0] == temp_via.cross_layer[0] ) {
    					field.Vias_matrix.back().push_back( temp_via );
    				}
    				else {
    					vector<Via> tmp_list;
    					tmp_list.push_back(temp_via);
    					field.Vias_matrix.push_back ( tmp_list );
    				}
    				return true;
    			}
    			cerr<<"Illigal header \""<<tokens[1]<<"\" !!";
          		return false;
          	}
    		default:
    		{
    			cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
            	return false;
            }
		}

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