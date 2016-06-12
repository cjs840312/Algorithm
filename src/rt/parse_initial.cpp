#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../util/help_function.h"
#include "RtMgr.h"

using namespace std;


static void parse_current( ifstream& );
static void parse_voltage( ifstream& );
static void parse_IRdrop( ifstream& );
static void parse_weight( ifstream&,  Field& );


bool
RtMgr::parse_initial(ifstream& fin)
{
	string s;
	int c = 0;
	while ( getline(fin,s) )
	{
		if( s[0] == '#') c += 1;
		switch (c)
		{
			case 1:	/* The current drawn by each power pin (mA) */
				parse_current(fin);
				break;
			case 2:	/* The voltage of each power source (V) */
				parse_voltage(fin);
				break;
			case 3: /* The IR-drop constraint of each power pin (%) */
				parse_IRdrop(fin);
				break;
			case 4: /* The weights on metal layers */
				parse_weight(fin, field );
				break;
		}
	}
	return true;
}

static void parse_current( ifstream& fin)
{
	string s;
	while(getline(fin,s))
	{
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) return;
		float tmp_float;
		myStr2float( tokens[2], tmp_float);
		//tmp_float save to block's pin current;
	}
}
static void parse_voltage( ifstream& fin)
{
	string s;
	while(getline(fin,s))
	{
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) return;
		float tmp_float;
		myStr2float( tokens[1], tmp_float);
		
		//tmp_float save to each VDD
	}
}
static void parse_IRdrop( ifstream& fin)
{
	string s;
	while(getline(fin,s))
	{
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) return;
		float tmp_float;
		myStr2float( tokens[2], tmp_float);
		//tmp_float save to block's pin IR_drop;
	}
}
static void parse_weight( ifstream& fin,  Field& field)
{
	string s;
	while(getline(fin,s))
	{
		vector<string> tokens;
		myStr2Tok(s,tokens);
		if(tokens.empty()) continue;
		float tmp_float;
		myStr2float( tokens[1], tmp_float);
		field.layers_map.find( tokens[0] )->second.metal_weight = tmp_float;

	}
}
