#ifndef BMP_FILE_H
#define BMP_FILE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

union INT_CHAR
{
 unsigned char c[4];
 unsigned int n;
};

class pixel
{
public:
  
  pixel();
 ~pixel(){ delete [] pixel_data ; }
 
  void initial(unsigned int );
  void set(unsigned int , unsigned char);
  unsigned char* get(){ return pixel_data;}
  
  void print(unsigned int );

private:

   unsigned char* pixel_data;
};

class bmp_file
{
public:
  
  bmp_file();

  void init();
  void read( fstream& );
  void read( int,int,unsigned int**);
  void print_index();
  void output(fstream&);


private:
  char            ID[2]            ;
  unsigned int    file_size        ;
  unsigned int    offset           ;
  unsigned int    info_size        ;  
  unsigned int    width            ;
  unsigned int    heigth           ;
  short           planes           ;
  unsigned int    BPP              ;
  unsigned int    compression      ;
  unsigned int    data_size        ;
  unsigned int    H_Resolution     ;
  unsigned int    V_Resolution     ;
  unsigned int    used_colors      ;
  unsigned int    important_colors ;
  pixel*          palette          ;
  pixel**         data             ;  

  INT_CHAR ic;
};
#endif 
