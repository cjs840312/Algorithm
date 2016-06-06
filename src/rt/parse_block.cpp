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
  SITE,
  MACRO,
  CLASS,
  SYMMETRY,
  SIZE,
  ORIGIN,
  PIN,
  OBS,
  DIRECTION,
  USE,
  PORT,
  LAYER,
  END,
  ERO
};

static STATE parse_state(string&);
static void check_comment(string&);
static bool parse_site(ifstream& , vector<string>&);
static bool parse_macro(ifstream& , vector<string>&, Field& field);
static bool parse_pin(ifstream& , vector<string>&,block&);
static bool parse_layer(ifstream& , vector<string>&,vector<vector<string> >& );

bool
RtMgr::parse_block(ifstream& fin)
{
   string version, namescasesensitive;

   string s;
   STATE state;
   while(getline(fin,s))
   {
      check_comment(s);
      vector<string> tokens;
      myStr2Tok(s,tokens);
      if(tokens.empty()) continue;
      switch(parse_state(tokens[0]))
      {
          case VERSION :
            version=tokens[1];  // Not used yet
            break;
          case NAMESCASESENSITIVE :
            namescasesensitive=tokens[1];  // Not used yet
            break;
          case SITE :
            parse_site(fin,tokens);  // Not used yet
            break;
          case MACRO :
            parse_macro(fin,tokens,field); 
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
  else if(s == "NAMESCASESENSITIVE")
    return NAMESCASESENSITIVE;
  else if(s == "SITE")
    return SITE;
  else if(s== "MACRO")
    return MACRO;
  else if(s=="CLASS")
    return CLASS;
  else if(s=="SYMMETRY")
    return SYMMETRY;
  else if(s=="SIZE")
    return SIZE;
  else if(s=="ORIGIN")
    return ORIGIN;
  else if(s=="PIN")
    return PIN;
  else if(s=="OBS")
    return OBS;
  else if(s == "DIRECTION")
    return DIRECTION;
  else if(s == "USE")
    return USE;
  else if(s == "PORT")
    return PORT;
  else if(s == "LAYER")
    return LAYER;
  else if(s == "END")
    return END;
  else
    return ERO;
}


static bool parse_site(ifstream& fin,vector<string>& v)
{
  string s,name=v[1],c , size[2];
  vector<string> symmetry;
  
  while(getline(fin,s))
   {  
      check_comment(s);
      vector<string> tokens;
      myStr2Tok(s,tokens);
      if(tokens.empty()) continue;
      switch(parse_state(tokens[0]))
      {
          case CLASS :
            c=tokens[1];
            break;
          case SYMMETRY :
            for(int i=1,sizet=tokens.size();i<sizet;i++)
              symmetry.push_back(tokens[i]);
            break;
          case SIZE :
            size[0]=tokens[1];
            size[1]=tokens[3];
            break;
          case END :
            if(tokens[1]==name && tokens.size()==2)
              return true;
            cerr<<"Illigal header \""<<tokens[1]<<"\" !!";
            return false;
          case ERO :
          default :
            cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
            return false;
      }
   }

}
static bool parse_macro(ifstream& fin,vector<string>& v,Field& field)
{
  block temp_block;
  string s;
  temp_block.name=v[1];

  while(getline(fin,s))
   {  
      check_comment(s);
      vector<string> tokens;
      myStr2Tok(s,tokens);
      if(tokens.empty()) continue;
      switch(parse_state(tokens[0]))
      {
          case CLASS :
            temp_block.CLASS=tokens[1];
            break;
          case SYMMETRY :
            for(int i=1,sizet=tokens.size();i<sizet;i++)
              temp_block.SYMMETRY.push_back(tokens[i]);
            break;
          case SIZE :
            myStr2Int(tokens[1], temp_block.size[0]);
            myStr2Int(tokens[3], temp_block.size[1]);
            break;
          case ORIGIN :
            myStr2Int(tokens[1], temp_block.ORIGIN[0]);
            myStr2Int(tokens[2], temp_block.ORIGIN[1]);
            break;
          case PIN :
            parse_pin(fin,tokens,temp_block);
            break;
          case OBS :
            parse_layer(fin,tokens,temp_block.OBS);
            break;
          case END :
            if(tokens[1]==temp_block.name && tokens.size()==2)
              return true;
            cerr<<"Illigal header \""<<tokens[1]<<"\" !!";
            return false;
          case ERO :
          default :
            cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
            return false;
      }
   }
   field.blocks.push_back(temp_block);
}
static bool parse_pin(ifstream& fin,vector<string>& v,block& temp_block)
{
  pin temp_pin;
  temp_pin.name=v[1];
  string s;
  vector<string> symmetry;

  while(getline(fin,s))
  {  
    check_comment(s);
    vector<string> tokens;
    myStr2Tok(s,tokens);
    if(tokens.empty()) continue;
    switch(parse_state(tokens[0]))
    {         
        case DIRECTION:
          temp_pin.DIRECTION=tokens[1];
          break;
        case USE :
          temp_pin.USE=tokens[1];
          break;
        case PORT :
          parse_layer(fin,tokens,temp_pin.PORT);
          break;
        case END :
          if(tokens[1]==temp_pin.name && tokens.size()==2)
            return true;
          cerr<<"Illigal header \""<<tokens[1]<<"\" !!";
          return false;
        case ERO :
        default :
          cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
          return false;
    }
  }
  temp_block.pins.push_back(temp_pin);

}

static bool parse_layer(ifstream& fin,vector<string>& v,vector<vector<string> >& layers)
{
  string s;
  vector<string> x;

  while(getline(fin,s))
  {  
    check_comment(s);
    vector<string> tokens;
    myStr2Tok(s,tokens);
    if(tokens.empty()) continue;
    switch(parse_state(tokens[0]))
    {
        case LAYER:
          x.push_back(tokens[1]);
          getline(fin,s);
          check_comment(s);
          tokens.clear();
          myStr2Tok(s,tokens);
          for(int i=0,size=tokens.size();i<size;i++)
            x.push_back(tokens[i]);
          break;
        case END :
          if(tokens.size()==1)
            return true;
          cerr<<"Illigal header \""<<tokens[1]<<"\" !!";
          return false;
        case ERO :
        default :
          cerr<<"Illigal header \""<<tokens[0]<<"\" !!";
          return false;
    }
  }
  layers.push_back(x);

}