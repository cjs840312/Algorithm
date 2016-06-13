#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using namespace std;

class GraphNode
{
   friend class Graph;
public:
   GraphNode():idx(0),flag(false),parent(NULL){}

   int& operator = (const int& n) { idx=n; return idx;}
   bool operator == (const int x) const {return x==idx;}
   bool operator !=(const int x) const {return x!=idx;}
   void set_pos   (int x,int y)  {pos[0]=x;pos[1]=y;}   
   void set_parent(GraphNode* n) { parent=n;}
   void set_idx   (int n)        {idx=n;}   
   void set_flag  (bool b)       { flag=b;}
   void add_nghbr(GraphNode* n){ neighbor.push_back(n);}
   bool get_flag(){ return flag;}
   int rank_calc(int x,int y)
   {
      rank=0;
      rank+=(x>pos[0]? x-pos[0]:pos[0]-x);
      rank+=(y>pos[1]? y-pos[1]:pos[1]-y);
      return rank;
   }

private:
   int idx;
   int pos[2];
   vector<GraphNode*> neighbor;
   bool flag;   
   GraphNode* parent;
   int rank;

};



class Graph
{
public: 
   Graph();
   ~Graph();
   void init(int ,int);

   void print() const;
   void set_obs(int,int,int,int);
   void init_state();
   void set_path(int,int,int,int,bool=true,bool=false);
   bool A_star();
   bool trace();
   void on_color();
   unsigned int** get_array(){return color_array;}

   int size[2];

private:
   char print_char(int) const;   
   void init_flag();
   void init_parent();

   int idx_num;
   int line_size;

   vector<int> colors;

   GraphNode **nodes;
   GraphNode *start,*end;
   unsigned int** color_array; 
   bool l_r;


};
#endif