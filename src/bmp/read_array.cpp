#include <iostream>
#include "bmp_file.h"
using namespace std;

void
bmp_file::read(int x,int y,unsigned int** array)
{

   if(palette!=0)
    delete [] palette;

   if(data!=0)
   {
      for(int i=0;i<heigth;i++)
         delete [] data[i];
      delete [] data;

   }

   init();

   data_size = y*((x*3-1)/4+1)*4  ;
   file_size = 54 + data_size ;

   width     = y  ;
   heigth    = x  ;

   data = new pixel*[y];
   for(int i=0 ; i< y; i++)
      data[i]= new pixel[x]; 

   for(int i=0;i<x;i++)
   {
      for(int j=0;j<y;j++)
      {
         data[i][j].initial(3);
         ic.n=array[i][j];
         for(int k=0;k<3;k++)
         {
            data[i][j].set(2-k, ic.c[k] );
         }
      }
   }
}

void
bmp_file::output(fstream& fout)
{
   fout.write(ID,2);

   ic.n=file_size;
   fout.write((char*)ic.c,4);


   ic.n=0;
   fout.write((char*)ic.c,4);

   ic.n=offset;
   fout.write((char*)ic.c,4);

   ic.n=info_size;
   fout.write((char*)ic.c,4);

   ic.n=width;
   fout.write((char*)ic.c,4);

   ic.n=heigth;
   fout.write((char*)ic.c,4);

   ic.n=planes;
   fout.write((char*)ic.c,2);

   ic.n=BPP;
   fout.write((char*)ic.c,2);

   ic.n=compression;
   fout.write((char*)ic.c,4);

   ic.n=data_size;
   fout.write((char*)ic.c,4);

   ic.n=H_Resolution;
   fout.write((char*)ic.c,4);

   ic.n=V_Resolution;
   fout.write((char*)ic.c,4);

   ic.n=used_colors;
   fout.write((char*)ic.c,4);

   ic.n=important_colors;
   fout.write((char*)ic.c,4);


   int dummy_byte = ((32-(width*24)%32)%32)/8 ;

   for(int j=0;j<heigth;j++)
   {
      for(int i=0;i<width;i++)
      {
         fout.write((char*)data[i][j].get(),3);
      }
      ic.n=0;
      fout.write((char*)ic.c,dummy_byte);
   }
}