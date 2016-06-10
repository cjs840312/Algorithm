#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <iostream>
using namespace std;

#define HEAPSIZE 10000000

template <class K, class E>
class Heap_Node
{
public:
   bool operator > (const Heap_Node n) const{ return key>n.key ;}

   K key;
   E element;
};

template <class K, class E>
class MinHeap 
{
public:
   MinHeap():size(0) { ary = new Heap_Node<K,E> [HEAPSIZE]; }

   ~MinHeap(){ delete[] ary;  }
  
   void push(K _key, E _element)
   {
      Heap_Node<K,E> root;
      root.key = _key;
      root.element = _element;
      ary[size] = root;
      up_heapify(size++);
   }

   E pop()
   {
      E min_element = ary[0].element;
      ary[0] = ary[--size];
      dn_heapify(0);
      return min_element;
   }

   void dn_heapify(int i)
   {
      int s = i;        //s = smallest
      int l = 2*i + 1;
      int r = 2*i + 2;  
      if(l < size && ary[i] > ary[l]) { s = l; }  
      if(r < size && ary[s] > ary[r]) { s = r; }
      if(s != i)
      {
         swap(i, s);
         dn_heapify(s);
      }
   }

   void up_heapify(int i)
   {
      int p = (i-1)/2;

      if( p>=0 && ary[p] > ary[i])
      {
         swap(i, p);
         up_heapify(p);
      }
   }

  // This function is for your convenience
  void swap(int i, int j)
  {
      Heap_Node<K,E> temp = ary[i];
      ary[i] = ary[j];
      ary[j] = temp;
  }

  bool empty(){ return size==0;}

protected:
  Heap_Node<K,E> *ary;
  int size;

};

#endif
