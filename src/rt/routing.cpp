#include <iostream>
#include "RtMgr.h"
using namespace std;

bool
RtMgr::routing()
{
   int current_line = 0;
   while(!pathes.empty())
   {

      vector<int> path = pathes.top();
      pathes.pop();
      if(path[4]==current_line)
      {
         graphs[0].set_path(path[0],path[1],path[2],path[3],false,(bool)path[5]);
      }
      else
      {
         current_line=path[4];
         graphs[0].set_path(path[0],path[1],path[2],path[3],true,(bool)path[5]);
      }
      
      if(graphs[0].A_star())
      {     
         graphs[0].trace();

         cout<<"success!!"<<endl;
      }
      else
         cout<<"failed"<<endl;
   }

   graphs[0].on_color();

   cout<<"Routing successfully !!"<<endl;
   return true;
}