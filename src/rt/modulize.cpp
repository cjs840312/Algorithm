#include "RtMgr.h"
#include "../bmp/bmp_file.h"
using namespace std;

bool
RtMgr::modulize()
{
  graphs = new Graph[1] ;
  graphs[0].init(20,20);

  graphs[0].set_obs(3,3,5,5);
  graphs[0].set_obs(10,13,15,17);
  graphs[0].set_obs(9,4,12,8);
  graphs[0].set_obs(4,13,7,16);

  vector<int> temp_path;

  temp_path.clear();
  temp_path.push_back(16);
  temp_path.push_back(16);
  temp_path.push_back(10);
  temp_path.push_back(0);
  temp_path.push_back(2);
  pathes.push(temp_path);

  temp_path.clear();
  temp_path.push_back(8);
  temp_path.push_back(16);
  temp_path.push_back(1);
  temp_path.push_back(0);
  temp_path.push_back(1);
  pathes.push(temp_path);

  temp_path.clear();
  temp_path.push_back(13);
  temp_path.push_back(7);
  temp_path.push_back(1);
  temp_path.push_back(0);
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