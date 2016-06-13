#include <iostream>
#include <cassert>
#include <iomanip>
#include "graph.h"
#include "../util/min_heap.h"
using namespace std;

extern unsigned int color_gen(int, int, int);

Graph::Graph()
:idx_num(0),line_size(0),color_array(0),l_r(false)
{
   colors.push_back( color_gen(  0,  0,  0) );
   colors.push_back( color_gen(255,255,255) );
   colors.push_back( color_gen(  0,  0,255) );
   colors.push_back( color_gen(  0,255,  0) );
   colors.push_back( color_gen(255,  0,  0) );
   colors.push_back( color_gen(255,255,  0) );
   colors.push_back( color_gen(  0,255,255) );
   colors.push_back( color_gen(255,  0,255) );
};

void
Graph::init(int x,int y)
{
   size[0]=x;size[1]=y;
   nodes = new GraphNode*[x];
   for(int i=0;i<x;i++)
      nodes[i] = new GraphNode[y];
   for(int i=0;i<x;i++)
   {
      for(int j=0;j<y;j++)
      {
         nodes[i][j].set_pos(i,j);
         if(i==0 || j==0 || i==x-1 || j==y-1)
            nodes[i][j]=-1;
         if(i!=0)
            nodes[i][j].add_nghbr(&nodes[i-1][j]);
         if(i!=x-1)
            nodes[i][j].add_nghbr(&nodes[i+1][j]);
         if(j!=0)
            nodes[i][j].add_nghbr(&nodes[i][j-1]);
         if(j!=y-1)
            nodes[i][j].add_nghbr(&nodes[i][j+1]);
      }
   }
}

Graph::~Graph()
{
   if(nodes!=0)
   {
      for(int i=0;i<size[0];i++)
         delete [] nodes[i];
      delete [] nodes;
   }

   if(color_array!=0)
   {
      for(int i=0;i<size[0];i++)
         delete [] color_array[i];
      delete [] color_array;
   }

}

void
Graph::print() const
{
   for(int j=size[1]-1;j>=0;j--)
   {
      for(int i=0;i<size[0];i++)
         cout<<setfill(' ')<<setw(2)<<print_char(nodes[i][j].idx);
      cout<<endl;
   }
}

char
Graph::print_char(int x) const
{
   if(x==-1)
      return '#';
   if(x==0)
      return ' ';
   return (char)(x+35);
}

void
Graph::set_obs(int x1,int y1,int x2,int y2)
{
   assert(x2>x1 && y2>y1);
   for(int i=x1;i<=x2;i++)
   {
      for(int j=y1;j<=y2;j++)
         nodes[i][j]=-1;
   }
}

void
Graph::init_state()
{
   init_flag();
   init_parent();
}

void
Graph::init_flag()
{
   for(int i=0;i<size[0];i++)
   {
      for(int j=0;j<size[1];j++)
      {
         if(nodes[i][j]==0 || nodes[i][j]==line_size)
            nodes[i][j].set_flag(false);
         else
            nodes[i][j].set_flag(true);
      }
   }
}

void
Graph::init_parent()
{
   for(int i=0;i<size[0];i++)
   {
      for(int j=0;j<size[1];j++)
         nodes[i][j].parent=0;
   }

}


void
Graph::set_path(int x1,int y1,int x2,int y2,bool change,bool multi )
{
   if(change==true)
      line_size++;


   if(!multi || end==0)
      l_r = ( x1 > x2 ? x1-x2 : x2-x1 ) > ( y1 > y2 ? y1-y2 : y2-y1 );
   else
   {
      if(end->pos[0]==0 || end->pos[0]==size[1]-1)
         l_r=false;
      else 
         l_r=true;
   }

   start = &nodes[x1][y1];
   end = &nodes[x2][y2];

   start->set_idx(line_size);
   end->set_idx(line_size);

}

bool
Graph::A_star()
{
   MinHeap<int,GraphNode*> que;
   GraphNode *current,*nghbr;
   init_state();
   end->set_flag(false);

   int sizen;
   int ex = end->pos[0] ;
   int ey = end->pos[1];

   que.push(start->rank_calc(ex,ey),start);

   if(l_r)
   {   
      while(!que.empty())
      {
         current=que.pop();
         if(current->idx==line_size && current != start)
         {
            end=current;
            return true;
         }
         sizen=current->neighbor.size();
         for(int i=0;i<sizen;i++)
         {
            nghbr=current->neighbor[i];
            if(!nghbr->get_flag())
            {
               nghbr->set_flag(true);
               nghbr->set_parent(current);
               que.push(nghbr->rank_calc(ex,ey),nghbr);
            }
         }
      }
   }
   else
   {
      while(!que.empty())
      {
         current=que.pop();
         if(current->idx==line_size && current != start)
         {
            end=current;
            return true;
         }
         sizen=current->neighbor.size();
         for(int i=sizen-1;i>=0;i--)
         {
            nghbr=current->neighbor[i];
            if(!nghbr->get_flag())
            {
               nghbr->set_flag(true);
               nghbr->set_parent(current);
               que.push(nghbr->rank_calc(ex,ey),nghbr);
            }
         }
      }
   }

   return false;
}

bool
Graph::trace()
{
   GraphNode* current = end;

   if(end->parent==0)
      return false;

   while(current!=start)
   {
      current->set_idx(line_size);
      current = current->parent;
   }
   return start;
}

void
Graph::on_color()
{
   if(color_array==0)
   {
      color_array=new unsigned int*[size[0]];
      for(int i=0;i<size[0];i++)
         color_array[i]=new unsigned int[size[1]];
   }

   for(int i=0;i<size[0];i++)
   {
      for(int j=0;j<size[1];j++)
         color_array[i][j] = colors[ nodes[i][j].idx+1 ];
   }
}