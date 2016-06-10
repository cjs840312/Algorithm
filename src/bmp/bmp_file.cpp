#include <iostream>
#include <fstream> 
#include "bmp_file.h"
using namespace std;

extern char dec_to_hex(unsigned int);

pixel::pixel() { pixel_data = 0;}

void pixel::initial(unsigned int n) { pixel_data = new unsigned char[n];}

void pixel::set(unsigned int n , unsigned char byte)
{
  pixel_data[n]=byte;  
}

void pixel::print(unsigned int num)
{ 
  if(num >= 8)
  {
    for(int n=0;n<num/8;n++)
      cout<<dec_to_hex(((unsigned int)pixel_data[n])/16)
          <<dec_to_hex(((unsigned int)pixel_data[n])%16) <<' ';        
  }
  else
    cout<<dec_to_hex(((unsigned int)pixel_data[0])%16) <<' ';
}

bmp_file::bmp_file()
{
  init();
}

void
bmp_file::init()
{
  ID[0]='B';  ID[1]='M';
  file_size = 0  ;
  offset    = 54 ;
  info_size = 40 ;
  width     = 0  ;
  heigth    = 0  ;
  planes    = 1  ;
  BPP       = 24 ;
  
  compression = 0       ;
  data_size = 0         ;
  H_Resolution = 0      ;
  V_Resolution = 0      ;
  used_colors = 0       ;
  important_colors = 0  ;
  palette=0;
  data =0  ;
}

void bmp_file::print_index()
{
  cout<< "Identifier          : " << ID[0] <<ID[1]  << endl
      << "File size           : " << file_size      << " Bytes" << endl
      << "Bitmap Data Offset  : " << offset         << endl
      << "Bitmap Header Size  : " << info_size      << endl
      << "Width               : " << width          << endl
      << "Height              : " << heigth         << endl
      << "Planes              : " << planes         << endl      
      << "Bits Per Pixel      : " << BPP            << endl;
  cout<< "Compression         : " ;
                                if (compression == 0)
                                  cout<< "No";
                                else if (compression == 1)
                                  cout<< "RLE 8-bit/pixel";
                                else if (compression == 2)
                                  cout<< "RLE 4-bit/pixel";
                                else if (compression == 3)
                                  cout<< "Bitfields";
                                else 
                                  cout<<compression;
                                                            cout << endl;
      
  cout<< "Bitmap Data Size    : " << data_size              << endl
      << "H-Resolution        : " << H_Resolution           << endl
      << "V-Resolution        : " << V_Resolution           << endl
      << "Used Colors         : " << used_colors            << endl
      << "Important Colors    : " << important_colors       << endl
      << "Palette             : "                           << endl;
          for(unsigned int n=0; n < (offset-54)/4 ; n++ )
          {
            cout << '[' << dec_to_hex(n/16) << dec_to_hex(n%16) << "] ";
            palette[n].print(32);
            cout<<"  ";
            if(n%4==3)
              cout<< endl;
          }   cout<< endl;
  cout<< "Map                 : "<<endl;
          for(int m=0 ; m < heigth; m++ )
          {
            for(int n=0 ; n< width ; n++)
            {
              cout<<'[';
              if(m<100)    cout<<'0';
              if(m<10 )    cout<<'0';
              cout << m <<"][";
              if(n<100)    cout<<'0';
              if(n<10 )    cout<<'0';
              cout << n <<"] ";
               
              data[m][n].print(BPP);
              cout<<"  ";
              if(n%3==2)
                cout<< endl;
            }   cout<< endl;       
          }

}