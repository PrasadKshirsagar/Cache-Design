#include <bits/stdc++.h>
#include <vector>

using namespace std;



class Block {

public:
  int tag;
  bool dirty;
  int lru;
  bool valid;

  Block()
  {
    tag = 0;
    dirty = false;
    lru = 0;
    valid = false;
  }
  

};

class CacheSet {

public:
  Block b1;
  Block arr[40];
  
//vector of blocks, size of vector is number of ways
};


class Cache {

 public: 
 CacheSet c1;
 CacheSet a[12500];
  
}; 



int main()

{

int hit=0;
int miss =0;
int writeback =0;
unsigned int csize;
unsigned int bsize;
unsigned int way;


cout << "Enter the cache size (in Bytes only):\n";
cin >> csize;
cout << "Enter the Block size (in Bytes only):\n";
cin >> bsize;
cout << "Enter the number of ways :";
cin >> way;
cout <<"\n\n\n";
Cache obj;

unsigned int no_of_sets = (csize/bsize)/way;
unsigned int no_of_blocks = no_of_sets * way;
unsigned int index_bits = 0;
unsigned int offset_bits = 0;
unsigned int t = no_of_sets;
unsigned int t1 = bsize ;
while(t != 0)
{
  index_bits++;
  t = t/2;
  
}

while(t1 != 0)
{
  t1 = t1/2;
  offset_bits++;
  
}
offset_bits--;

//cout << offset_bits << endl;
//cout << index_bits << endl;


unsigned int num = 32 - offset_bits - index_bits;
unsigned int num1 = 32 - offset_bits;
unsigned int count = 0;
string line;

fstream fin;
fin.open("input.txt");
while(!fin.eof())
 {
    getline(fin,line);
    count++;
 }
count--;
fin.close();
fin.open("trial");
for(int j=0;j<count;j++)
{

char ch;
unsigned int n;
fin >> ch;
fin >> hex >> n;

if(ch == 'R')
{
bool temp = false;
unsigned int index = n<<num;
index = index >>num1;
unsigned int tagg = n >> (offset_bits + index_bits);
int co=0,co1=-1;

for(int i=0;i<way;i++)
{
  if(tagg == obj.a[index].arr[i].tag)
  {
     hit++;
     obj.a[index].arr[i].lru = obj.a[index].arr[i].lru + 1;
     temp = true;
     break;
  }

}

if(temp == false)

{

for(int i=0;i<way;i++)
{
  
  if(tagg != obj.a[index].arr[i].tag)
  {
     co++;
  }
  
  if(0 == obj.a[index].arr[i].valid)
  {
     co1 = i;
  }

}

if(co1 != -1 && co == way)
{
   Block bk;
   bk.tag = tagg;
   bk.dirty = false;
   bk.lru = 0;
   bk.valid = true;
   obj.a[index].arr[co1] = bk;
   miss++;


}
else
{
   int minn = 0;
   miss++;
   for(int i=0;i<way;i++)
 {
    if(obj.a[index].arr[i].lru < obj.a[index].arr[minn].lru)   
       minn = i;

 }
   
   Block bk;
   bk.tag = tagg;
   bk.dirty = false;
   bk.lru = 0;
   bk.valid = true;
   if(obj.a[index].arr[minn].dirty == true)
       writeback++;
      
   obj.a[index].arr[minn] = bk;

}

}

}


else
{

bool temp = false;
unsigned int index = n<<num;
index = index >>num1;
//cout <<"ind =" <<index <<endl;
unsigned int tagg = n >> (offset_bits + index_bits);
int co=0,co1=-1;

for(int i=0;i<way;i++)
{
 // cout << tagg <<"  " <<obj.a[index].arr[i].tag <<endl;
  if(tagg == obj.a[index].arr[i].tag)
  {
     hit++;
    // cout << "hit at j :" << j <<endl;
     obj.a[index].arr[i].lru = obj.a[index].arr[i].lru + 1;
     temp = true;
     break;
  }

}
//cout << temp <<endl;
if(temp == false)

{

for(int i=0;i<way;i++)
{
  
  if(tagg != obj.a[index].arr[i].tag)
  {
     co++;
  }
}
 
for(int i=0;i<way;i++)
{

  if(0 == obj.a[index].arr[i].valid)
  {
     co1 = i;
     break;
  }

}
// cout << "co1 = "<<co1 <<"co= "<<co <<endl;
if(co1 != -1 && co == way)
{
   Block bk;
   bk.tag = tagg;
   bk.dirty = true;
   bk.lru = 0;
   bk.valid = true;
   obj.a[index].arr[co1] = bk;
   miss++;

}

else
{
   int minn = 0;
   miss++;
   for(int i=0;i<way;i++)
 {
    if(obj.a[index].arr[i].lru < obj.a[index].arr[minn].lru)   
       minn = i;

 }
   
   Block bk1;
   bk1.tag = tagg;
   bk1.dirty = true;
   bk1.lru = 0;
   bk1.valid = true;
 // cout << obj.a[index].arr[minn].dirty <<endl;
   if(obj.a[index].arr[minn].dirty == true)
       writeback++;
      
   obj.a[index].arr[minn] = bk1;

}


}

}

}

cout << "Data Statistics is as follows :\n";
cout << "1. number of hits : " <<hit <<endl;
cout << "2. number of misses : " << miss <<endl;
cout << "3. number of writebacks : " << writeback <<endl;






return 0;
}
