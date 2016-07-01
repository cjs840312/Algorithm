#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../util/help_function.h"
#include "RtMgr.h" 

using namespace std;

enum STATE
{
	MODULE,
	INPUT,
	BLOCK,
	END
};

static void check_comment(ifstream&, string&);
static STATE state_parse(string&);

bool
RtMgr::parse_v(ifstream& fin)
{

	string s;
	while(getline(fin,s,';'))
	{
		check_comment(fin,s);
		vector<string> tokens;
		myStr2Tok(s,tokens,",.() \n\t");
		if(tokens.empty()) continue;
		switch(state_parse(tokens[0]))
		{
			case MODULE: /* skip error handling */	break;			
			case INPUT:
				for(int i=1,size=tokens.size();i<size;i++) {
					Input tmp_input;
					tmp_input.name = tokens[i];
					(field.inputs_map).insert( pair< string,Input > (tmp_input.name, tmp_input) );
				}
				break;
			case BLOCK:
			{	
				map<string,block>::iterator it=field.blocks.find( tokens[0]);
			    if(it!=field.blocks.end())
			    {
			    	block& b = it->second;
			    	b.num++;
			    	b.member.push_back(tokens[1]); //initial B1, B2,etc member
					for(int i=2,size=tokens.size();i<size;i+=2)
					{
						map<string,pin>::iterator it1=b.pins.find( tokens[i]);
						if(it1!=b.pins.end())
					    {
					    	pin& p = it1->second;
					    	p.destination.push_back(tokens[i+1]);
					    	//cout<<p.destination[0]<<endl;
		    			}
		    			else 
		    			{
		    				cerr<<"Illegal pin \""<<tokens[i]<<"\" !!"<<endl;
		    				return false;
		    			}
					}

    			}
    			else 
    			{
    				cerr<<"Illegal block \""<<tokens[0]<<"\" !!"<<endl;
    				return false;
    			}
    			break;
			}
			case END: /*skip*/ return true;
		}
	}

	return false;
}

static void check_comment(ifstream& fin, string& s)
{
   int size=s.size(),start=0;
   string temp="";
   for(int i=0;i<size-1; i++)
   {
      if(s[i]=='/' && s[i+1]=='/')
      {
         temp += s.substr(start,i-start);
         i+=2;
         while( s[i] !='\n' && s[i] !='\0')  i++;
         start = i+1 ;
      }
      else if(s[i]=='/' && s[i+1]=='*')
      {
         temp += s.substr(start,i-start);
         i+=2;
         while(true)
         {
         	if(s[i] !='\0')
         	{
         		if(s[i]=='*' && s[i+1]=='/'){ i++; break; }
            	i++;     
         	}
         	else
    		{
    			if(!getline(fin,s,';')) break;
    			size=s.size();
    			start=0;
    			i=0;
    		}
         }

         start = i+1 ;
      }
   }
   if(start<size)
      temp += s.substr(start,size-start);
   s=temp;
}

static STATE state_parse(string& state)
{
	if( state=="module")
		return MODULE;
	else if( state == "input")
		return INPUT;
	else if( state == "endmodule" )
		return END;
	else
		return BLOCK;
}