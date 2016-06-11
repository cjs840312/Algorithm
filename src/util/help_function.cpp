#include <string>
#include <vector>
#include <cassert>
using namespace std;
 
bool myStrNCmp(const string& s1, const string& s2, unsigned n)
{
   assert(n > 0);
   unsigned n2 = s2.size();
   unsigned n1 = s1.size();

   if (n2 == 0 || n2>n1 )
      return false;

   assert(n1 >= n);

   for (unsigned i = 0; i < n1; ++i)
   {
      if (i == n2)
         return i >= n ;
      char ch1 = (isupper(s1[i]))? tolower(s1[i]) : s1[i];
      char ch2 = (isupper(s2[i]))? tolower(s2[i]) : s2[i];
      if (ch1 != ch2)
         return false;
   }
   return true;
}

size_t myStrGetTok(const string& str, string& tok, size_t pos,string del)
{
   size_t begin = str.find_first_not_of(del, pos);
   if (begin == string::npos) { tok = ""; return begin; }
   size_t end = str.find_first_of(del, begin);
   tok = str.substr(begin, end - begin);
   return end;
}

int myStr2Tok(const string& s, vector<string>& tokens,string del)
{
   string token;
   size_t pos = myStrGetTok(s, token,0,del);
   while (token.size())
   {
      tokens.push_back(token);
      pos = myStrGetTok(s, token, pos,del);
   }
   
   return tokens.size();
}

// Convert string "str" to integer "num". Return false if str does not appear
// to be a number
bool myStr2Int(const string& str, int& num)
{
   num = 0;
   size_t i = 0;
   int sign = 1;
   if (str[0] == '-') { sign = -1; i = 1; }
   bool valid = false;
   for (; i < str.size(); ++i) 
   {
      if (isdigit(str[i])) 
      {
         num *= 10;
         num += int(str[i] - '0');
         valid = true;
      }
      else return false;
   }
   num *= sign;
   return valid;
}
// Convert string "str" to float "num". Return false if str does not appear
// to be a number
bool myStr2float(const string& str, float& num)
{
  size_t n =str.find_first_of(".");
  string str_int,str_float="";
  if( n!=string::npos )
  {
    str_int=str.substr(0,n);
    str_float=str.substr(n+1);
  }
  else 
    str_int=str;
  int int_part=0,float_part=0;
  myStr2Int(str_int,int_part);
  myStr2Int(str_float,float_part);
  float temp_float=float_part;
  for(int i=0;i<str_float.size();i++)
      temp_float/=10;
  num=int_part+temp_float;
return true;
}
// Convert scientific notation string "str" to float "num". Return false if str does not appear
// to be a number
bool mySci2float(const string& str, float& num)
{
  size_t n = str.find_first_of('e');
  string str_float,str_exp;
  str_float=str.substr(0,n);
  str_exp=str.substr(n+1);
  int int_exp;
  myStr2Int(str_exp,int_exp);
  myStr2float(str_float,num);
  if(int_exp>=0)
  {
    for(int i=0;i<int_exp;i++)
      num*=10;
  }
  else
  {
    for(int i=0;i<int_exp*(-1);i++)
      num/=10;
  }
}
