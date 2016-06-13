#include "RtMgr.h"
#include "../bmp/bmp_file.h"
using namespace std;

bool
RtMgr::modulize()
{
  graphs = new Graph[1] ;
  graphs[0].init(300,300);

  graphs[0].set_obs(39,25,89,75);
  graphs[0].set_obs(170,32,270,82);
  graphs[0].set_obs(154,177,224,237);

  vector<int> temp_path;



  temp_path.clear();
  temp_path.push_back(0);
  temp_path.push_back(50);
  temp_path.push_back(169);
  temp_path.push_back(55);
  temp_path.push_back(3);
  temp_path.push_back(0);
  pathes.push(temp_path);

  temp_path.clear();
  temp_path.push_back(20);
  temp_path.push_back(0);
  temp_path.push_back(169);
  temp_path.push_back(36);
  temp_path.push_back(2);
  temp_path.push_back(0);
  pathes.push(temp_path);


  temp_path.clear();
  temp_path.push_back(153);
  temp_path.push_back(190);
  temp_path.push_back(0);
  temp_path.push_back(100);
  temp_path.push_back(1);
  temp_path.push_back(1);
  pathes.push(temp_path);

  temp_path.clear();
  temp_path.push_back(38);
  temp_path.push_back(33);
  temp_path.push_back(0);
  temp_path.push_back(100);
  temp_path.push_back(1);
  temp_path.push_back(1);
  pathes.push(temp_path);


  cout<<"Modulize successfully !!"<<endl;
  return true;
}

void
RtMgr::print(int n,string file_name)
{
  bmp_file bmp;
  bmp.read(graphs[n].size[0],graphs[n].size[1],graphs[n].get_array());

  fstream fout;
  fout.open(file_name.c_str(),ios::out|ios::binary);
  bmp.output(fout);
  fout.close();
}