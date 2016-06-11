#ifndef HELP_H
#define HELP_H

#include <string>
#include <vector>
using namespace std;

int myStrNCmp(const string&, const string&, unsigned);


size_t myStrGetTok(const string&, string&, size_t=0,string=" ");
int myStr2Tok(const string&, vector<string>&,string =" ");
bool myStr2Int(const string&, int& );
bool myStr2float(const string&, float& );
bool mySci2float(const string&, float& );
char dec_to_hex(unsigned int );
unsigned int color_gen(int ,int ,int ) ;
#endif