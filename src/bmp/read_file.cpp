#include "bmp_file.h"
using namespace std;

void bmp_file::read( fstream& fin)
{
  if(palette!=0)
    delete [] palette;

  if(data!=0)
  {
    for(int i=0;i<heigth;i++)
      delete [] data[i];
    delete [] data;

  }

  unsigned char byte;
  
  fin.read( (char*)&byte,1);  ID[0] = (char)byte ;
  fin.read( (char*)&byte,1);  ID[1] = (char)byte ;


  fin.read( (char*)ic.c,4);
  file_size = ic.n;
  
  fin.read( (char*)ic.c,4);
  
  fin.read( (char*)ic.c,4);
  offset = ic.n;
  
  fin.read( (char*)ic.c,4);
  info_size = ic.n; 
  
  fin.read( (char*)ic.c,4);
  width = ic.n; 
  
  fin.read( (char*)ic.c,4);
  heigth = ic.n;
  
  ic.n=0;
  fin.read( (char*)ic.c,2);
  planes = ic.n;  
  
  ic.n=0;
  fin.read( (char*)ic.c,2);
  BPP = ic.n;
  
  fin.read( (char*)ic.c,4);
  compression = ic.n;
  
  fin.read( (char*)ic.c,4);
  data_size = ic.n;
  
  fin.read( (char*)ic.c,4);
  H_Resolution = ic.n;

  fin.read( (char*)ic.c,4);
  V_Resolution = ic.n;

  fin.read( (char*)ic.c,4);
  used_colors = ic.n;
  
  fin.read( (char*)ic.c,4);
  important_colors = ic.n;
  
  palette = new pixel[(offset-54)/4];  
  

  for(int n=0 ; n<(offset-54)/4 ; n++)
  {
    palette[n].initial(4);
    for(int m=0; m<4;m++)
    {
      fin.read( (char*)&byte,1);    
      palette[n].set( m,byte );
    }    
  } 


  data = new pixel*[heigth];
  for(int i=0 ; i< heigth; i++)
    data[i]= new pixel[width];  
  
  int dummy_byte = ((32-(width*BPP)%32)%32)/8 ;
  unsigned int byte_num=(BPP+7)/8;
  if(BPP >= 8)
  {
    for(int i=0 ; i<heigth ; i++)
    {
      for(int j=0 ; j < width ; j++)
      {
        data[i][j].initial( byte_num );
        for(unsigned int k=0 ; k<byte_num ; k++)
        {
          fin.read( (char*)&byte,1);          
          data[i][j].set( k, byte );        
        }
      }    
      for(int j=0 ; j<dummy_byte ; j++)
        fin.read( (char*)&byte,1);    
    }
  }
  else
  {
    for(int i=0 ; i<heigth ; i++)
    { 
      int p=0;
      for(int j=0 ; j < (width*BPP+7)/8 ; j++)
      {
        fin.read( (char*)&byte,1);
         
        for(unsigned int k=1 ; k <= 8/BPP && p<width ; k++)
        {
          data[i][p].initial(1);
          data[i][p].set(0, (unsigned char)(((unsigned int)byte>>(8-BPP*k)) % (1<<BPP)) );
          p++;
        }  
      }
     
      for(int j=0 ; j<dummy_byte ; j++)
        fin.read( (char*)&byte,1);  
    }
  }
}
