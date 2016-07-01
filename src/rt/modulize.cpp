#include "RtMgr.h"
#include "../bmp/bmp_file.h"
using namespace std;


#ifndef BASE
#define BASE 10
#endif

static int divByBase(int num) {return( num%10 >= 5) ? num/BASE + 1 : num/BASE ; }

bool
RtMgr::modulize()
{
  graphs = new Graph[1] ;
  int unit = field.unit;
  graphs[0].init (  
    divByBase(field.diearea[2] / unit),  
    divByBase(field.diearea[3] / unit)  
  );

  map<string,block>::iterator it=field.blocks.begin();

  while ( it!=field.blocks.end() && it->second.num>0 )
  {
    block& b = it->second;
    graphs[0].set_obs (
      divByBase( b.position[0] / unit),
      divByBase( b.position[1] / unit),
      divByBase( b.position[0] / unit + b.size[0] ),
      divByBase( b.position[1] / unit + b.size[1] )
    );

    ++it;
  }
  /*
  graphs[0].set_obs(39,25,89,75);
  graphs[0].set_obs(170,32,270,82);
  graphs[0].set_obs(154,177,224,237);
  */


  /*
  vector<int> temp_path;
  vector< vector<int> > tmp_pathes;
  it=field.blocks.begin();
  while ( it!=field.blocks.end() && it->second.num != 0 )
  {
    block& b = it->second;
    int count = b.num;
    cout<<b.name<<endl;
    map<string, pin>::iterator it2=b.pins.begin();
    while ( it2 != b.pins.end() ) {
      pin& p = it2->second;
      p.destination[0];
      cout<<p.name<<endl;
      cout<<p.destination[0]<<endl;

      map<string, Input>::iterator it3 = field.inputs_map.find( p.destination[0] );
      Input& input = it3->second;
      cout<<input.position[0]<<" "<<input.position[1]<<endl;
      it2++;
    }


    it++;
  }
  */

  
  vector<int> temp_path;
  //vector< vector<int> > tmp_pathes;
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