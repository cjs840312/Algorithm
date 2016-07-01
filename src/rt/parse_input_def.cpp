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
  DIVIDERCHAR,
  BUSBITCHARS,
  DESIGN,
  UNITS,
  PROPERTYDEFINITIONS,
  COMPONENTPIN ,
  DIEAREA,
  TRACKS,
  GCELLGRID,
  COMPONENTS,
  PINS,
  END,
  ERO,
};

static void check_comment(string& s);
static STATE parse_state(string&);
static void parse_property(ifstream&);
static void parse_component(ifstream&,int, Field&);
static void parse_pins(ifstream&, Field&);

bool
RtMgr::parse_input_def(ifstream& fin)
{
   string version, dividerchar, busbitchar,design;
   string s;
   STATE state;
   while(getline(fin,s))
   {
      check_comment(s);
      vector<string> tokens;
      myStr2Tok(s,tokens," ;()");
      if(tokens.empty()) continue;
      switch(parse_state(tokens[0]))
      {
          case VERSION :
            version=tokens[1];         //Not used
            break;
          case DIVIDERCHAR :
            dividerchar=tokens[1];     //Not used
            break;
          case BUSBITCHARS :
            busbitchar=tokens[1];      //Not used
            break;
          case DESIGN :
            design=tokens[1];          //Not used
            break;
          case UNITS :
            if(tokens[1]=="DISTANCE" && tokens[2]=="MICRONS")
               myStr2Int(tokens[3],field.unit);
            break;
          case PROPERTYDEFINITIONS :
            parse_property(fin);
            break;
          case DIEAREA :
          {
            for(int i=0;i<4;i++) {
              myStr2Int(tokens[i+1],field.diearea[i]);   
            }
            break;
          }
         case TRACKS :
          {
            //TODO..
            break;
          }
          case GCELLGRID :
          {
            //TODO..
                
            break;
          }
          case COMPONENTS :
          {  
            int n;myStr2Int(tokens[1],n);
            parse_component(fin,n,field); //TODO
            break;
          }
          case PINS :
            parse_pins(fin, field); //TODO
            break;
          case END :
            return true;
          case ERO :
          default :
            cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
            return false;
      }
   }
   return false;
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

static STATE parse_state(string& s)
{

  if(s == "VERSION")
    return VERSION;
  else if(s == "DIVIDERCHAR")
    return DIVIDERCHAR;
  else if(s == "BUSBITCHARS")
    return BUSBITCHARS;
  else if(s== "DESIGN")
    return DESIGN;
  else if(s=="UNITS")
    return UNITS;
  else if(s=="PROPERTYDEFINITIONS")
    return PROPERTYDEFINITIONS;
  else if(s=="DIEAREA")
    return DIEAREA;
  else if(s=="TRACKS")
    return TRACKS;
  else if(s == "GCELLGRID")
    return GCELLGRID;
  else if(s == "PINS")
    return PINS;
  else if(s == "COMPONENTS")
    return COMPONENTS;
  else if(s == "END")
    return END;
  else if (s == "COMPONENTPIN")
    return COMPONENTPIN;
  else
    return ERO;
}

static void parse_property(ifstream& fin)
{
  //TODO...
  string s;
  while(getline(fin,s))
  {
    check_comment(s);
    vector<string> tokens;
    myStr2Tok(s,tokens);    
    if(tokens.empty()) continue;
    switch(parse_state(tokens[0]))
    {
      case COMPONENTPIN :
        //Skip
        break;
      case DESIGN :
        //Skip
        break;
      case END :
        return ;
      default:
        cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
        return;
    }
  }
}

static void parse_component(ifstream& fin,int n, Field& field)
{
  string s,block_type,block_name,dirc;

  for(int i=0;i<n;i++)
  {
    getline(fin,s,';');
    check_comment(s);
    vector<string> tokens;
    myStr2Tok(s,tokens,"\n ()+-;"); 
    if(tokens.empty()) continue;
    else if(tokens[0]=="END") return;
    // TODO

    block_name=tokens[0];
    block_type=tokens[1];
    map<string,block>::iterator it=field.blocks.find( block_type );
    block& b = it->second;

    myStr2Int(tokens[3], b.position[0] );
    myStr2Int(tokens[4], b.position[1] );
    dirc=tokens[5];

  }
}

static void parse_pins(ifstream& fin, Field& field)
{
  string all="",s,temp;
  while(getline(fin,s))
  {
    check_comment(s);
    myStrGetTok(s,temp,0," ");
    if(temp=="END") break;
    all+=s;
  }
  
  vector<string> lines;
  myStr2Tok(all,lines,";");
  for(int i=0,size=lines.size();i<size;i++)
  {
    vector<string> tokens;
    myStr2Tok(lines[i],tokens,"\n +()");
    //string name=tokens[1];
    map<string, Input>::iterator it = field.inputs_map.find( tokens[1] );
    Input& input = it->second;
    for(int j=2,sizet=tokens.size();j<size;j++)
    {
      if(tokens[j]=="LAYER")
      {
        input.metal_layer=tokens[++j];
        //int place[4];
        myStr2Int(tokens[++j],input.metal_layer_rect[0]);
        myStr2Int(tokens[++j],input.metal_layer_rect[1]);
        myStr2Int(tokens[++j],input.metal_layer_rect[2]);
        myStr2Int(tokens[++j],input.metal_layer_rect[3]);
      }
      if(tokens[j]=="FIXED")
      {
        //int place[2];
        myStr2Int(tokens[++j],input.position[0]);
        myStr2Int(tokens[++j],input.position[1]);
        string dir=tokens[++j];
      }
    }
  }

}