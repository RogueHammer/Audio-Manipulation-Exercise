//MRXSTE008 - Steven Mare
//For CSC3022H Assignment 4
//22 April 2018

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "audio.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace MRXSTE008;
using namespace std;

TEST_CASE("Construct empty Audio Object","[Audio]") {
    Audio<int8_t> a(1);
    Audio<int16_t> b(1);
    Audio<pair<int8_t,int8_t> > c(1);
    Audio<pair<int16_t,int16_t> > d(1);
    REQUIRE( a.getSample().size() == 1 );
    REQUIRE( typeid(a.getSample()[0]) == typeid(int8_t) );
    REQUIRE( b.getSample().size() == 1 );
    REQUIRE( typeid(b.getSample()[0]) == typeid(int16_t) );
    REQUIRE( c.getSample().size() == 1 );
    REQUIRE( typeid(c.getSample()[0].first) == typeid(int8_t) );
    REQUIRE( typeid(c.getSample()[0].second) == typeid(int8_t) );
    REQUIRE( d.getSample().size() == 1 );
    REQUIRE( typeid(d.getSample()[0].first) == typeid(int16_t) );
    REQUIRE( typeid(d.getSample()[0].second) == typeid(int16_t) );
}


TEST_CASE("Test Copy constructor","[Audio]") {

    Audio<int8_t> a(1);
    Audio<int16_t> b(1);
    Audio<pair<int8_t,int8_t> > c(1);
    Audio<pair<int16_t,int16_t> > d(1);
    Audio<int8_t> e=a;
    Audio<int16_t> f=b;
    Audio<pair<int8_t,int8_t> > g=c;
    Audio<pair<int16_t,int16_t> > h=d;
    REQUIRE( e.getSample().size() == 1 );
    REQUIRE( typeid(e.getSample()[0]) == typeid(int8_t) );
    REQUIRE( f.getSample().size() == 1 );
    REQUIRE( typeid(f.getSample()[0]) == typeid(int16_t) );
    REQUIRE( g.getSample().size() == 1 );
    REQUIRE( typeid(g.getSample()[0].first) == typeid(int8_t) );
    REQUIRE( typeid(g.getSample()[0].second) == typeid(int8_t) );
    REQUIRE( h.getSample().size() == 1 );
    REQUIRE( typeid(h.getSample()[0].first) == typeid(int16_t) );
    REQUIRE( typeid(h.getSample()[0].second) == typeid(int16_t) );
}

TEST_CASE("Test Move constructor","[Audio]") {
    Audio<int8_t> a(1);
    Audio<int16_t> b(1);
    Audio<pair<int8_t,int8_t> > c(1);
    Audio<pair<int16_t,int16_t> > d(1);
    Audio<int8_t> e=move(a);
    Audio<int16_t> f=move(b);
    Audio<pair<int8_t,int8_t> > g=move(c);
    Audio<pair<int16_t,int16_t> > h=move(d);
    REQUIRE( e.getSample().size() == 1 );
    REQUIRE( typeid(e.getSample()[0]) == typeid(int8_t) );
    REQUIRE( f.getSample().size() == 1 );
    REQUIRE( typeid(f.getSample()[0]) == typeid(int16_t) );
    REQUIRE( g.getSample().size() == 1 );
    REQUIRE( typeid(g.getSample()[0].first) == typeid(int8_t) );
    REQUIRE( typeid(g.getSample()[0].second) == typeid(int8_t) );
    REQUIRE( h.getSample().size() == 1 );
    REQUIRE( typeid(h.getSample()[0].first) == typeid(int16_t) );
    REQUIRE( typeid(h.getSample()[0].second) == typeid(int16_t) );
}



TEST_CASE("Test Copy assignment","[Audio]") {
    Audio<int8_t> a(1);
    Audio<int16_t> b(1);
    Audio<pair<int8_t,int8_t> > c(1);
    Audio<pair<int16_t,int16_t> > d(1);
    Audio<int8_t> e(0);
    Audio<int16_t> f(0);
    Audio<pair<int8_t,int8_t> > g(0);
    Audio<pair<int16_t,int16_t> > h(0);
    e=a;
    f=b;
    g=c;
    h=d;
    REQUIRE( e.getSample().size() == 1 );
    REQUIRE( typeid(e.getSample()[0]) == typeid(int8_t) );
    REQUIRE( f.getSample().size() == 1 );
    REQUIRE( typeid(f.getSample()[0]) == typeid(int16_t) );
    REQUIRE( g.getSample().size() == 1 );
    REQUIRE( typeid(g.getSample()[0].first) == typeid(int8_t) );
    REQUIRE( typeid(g.getSample()[0].second) == typeid(int8_t) );
    REQUIRE( h.getSample().size() == 1 );
    REQUIRE( typeid(h.getSample()[0].first) == typeid(int16_t) );
    REQUIRE( typeid(h.getSample()[0].second) == typeid(int16_t) );
}

TEST_CASE("Test Move assignment","[Audio]") {
    Audio<int8_t> a(1);
    Audio<int16_t> b(1);
    Audio<pair<int8_t,int8_t> > c(1);
    Audio<pair<int16_t,int16_t> > d(1);
    Audio<int8_t> e(0);
    Audio<int16_t> f(0);
    Audio<pair<int8_t,int8_t> > g(0);
    Audio<pair<int16_t,int16_t> > h(0);
    e=move(a);
    f=move(b);
    g=move(c);
    h=move(d);
    REQUIRE( e.getSample().size() == 1 );
    REQUIRE( typeid(e.getSample()[0]) == typeid(int8_t) );
    REQUIRE( f.getSample().size() == 1 );
    REQUIRE( typeid(f.getSample()[0]) == typeid(int16_t) );
    REQUIRE( g.getSample().size() == 1 );
    REQUIRE( typeid(g.getSample()[0].first) == typeid(int8_t) );
    REQUIRE( typeid(g.getSample()[0].second) == typeid(int8_t) );
    REQUIRE( h.getSample().size() == 1 );
    REQUIRE( typeid(h.getSample()[0].first) == typeid(int16_t) );
    REQUIRE( typeid(h.getSample()[0].second) == typeid(int16_t) );
}


TEST_CASE("Test Load Operation","[Audio]") {

  ofstream outfile;

  int8_t arr1[] = {1,2,1,2,0,7};
  outfile.open("test.raw", std::ios::binary);
  outfile.write((char*)&arr1[0],6*sizeof(int8_t));
  outfile.close();
  Audio<int8_t> a(6);
  a.load("test.raw");

  int16_t arr2[] = {2,4,5,2,213,677};
  outfile.open("test.raw", std::ios::binary);
  outfile.write((char*)&arr2[0],6*sizeof(int16_t));
  outfile.close();
  Audio<int16_t> b(6);
  b.load("test.raw");

  int8_t arr3[] = {1,2,1,2,0,7,4,3,2,1};
  outfile.open("test.raw", std::ios::binary);
  outfile.write((char*)&arr3[0],12*sizeof(int8_t));
  outfile.close();
  Audio<pair<int8_t,int8_t> > c(6);
  c.load("test.raw");

  int16_t arr4[] = {2,4,5,2,213,677,213,324,2,1};
  outfile.open("test.raw", std::ios::binary);
  outfile.write((char*)&arr4[0],12*sizeof(int16_t));
  outfile.close();
  Audio<pair<int16_t,int16_t> > d(6);
  d.load("test.raw");

  for(int i=0;i<6;i++)
  {
    REQUIRE(a.getSample()[i]==arr1[i]);
    REQUIRE(b.getSample()[i]==arr2[i]);
    REQUIRE(c.getSample()[i].first==arr3[i*2]);
    REQUIRE(c.getSample()[i].second==arr3[i*2+1]);
    REQUIRE(d.getSample()[i].first==arr4[i*2]);
    REQUIRE(d.getSample()[i].second==arr4[i*2+1]);
  }
  
}

TEST_CASE("Test Save Operation","[Audio]") {

  ifstream infile;

  int8_t arr1[] = {1,2,1,2,0,7};
  Audio<int8_t> a(6);

  int16_t arr2[] = {2,4,5,2,213,677};
  Audio<int16_t> b(6);

  int8_t arr3[] = {1,2,1,2,0,7,4,3,2,1};
  Audio<pair<int8_t,int8_t> > c(6);

  int16_t arr4[] = {2,4,5,2,213,677,213,324,2,1};
  Audio<pair<int16_t,int16_t> > d(6);

  for(int i=0;i<6;i++)
  {
    a.getSample()[i]=arr1[i];
    b.getSample()[i]=arr2[i];
    c.getSample()[i].first=arr3[i*2];
    c.getSample()[i].second=arr3[i*2+1];
    d.getSample()[i].first=arr4[i*2];
    d.getSample()[i].second=arr4[i*2+1];
  }

  int8_t res1[6];
  int16_t res2[6];
  int8_t res3[12];
  int16_t res4[12];

  a.save("test.raw");
  infile.open("test.raw", std::ios::binary);
  infile.read((char*)res1,6*sizeof(int8_t));
  infile.close();

  b.save("test.raw");
  infile.open("test.raw", std::ios::binary);
  infile.read((char*)res2,6*sizeof(int16_t));
  infile.close();

  c.save("test.raw");
  infile.open("test.raw", std::ios::binary);
  infile.read((char*)res3,12*sizeof(int8_t));
  infile.close();

  d.save("test.raw");
  infile.open("test.raw", std::ios::binary);
  infile.read((char*)res4,12*sizeof(int16_t));
  infile.close();

  for(int i=0;i<6;i++)
  {
    REQUIRE(arr1[i]==res1[i]);
    REQUIRE(arr2[i]==res2[i]);
    REQUIRE(arr3[i]==res3[i]);
    REQUIRE(arr4[i]==res4[i]);
  }
  
}


TEST_CASE("Test | opperator","[Audio]") {
  int8_t arr8mono1[] = {1,2,1};
  Audio<int8_t> m81(3);
  int8_t arr8mono2[] = {1,4,2};
  Audio<int8_t> m82(3);
  int8_t arr8mono3[] = {1,2,1,1,4,2};
  Audio<int8_t> m83(6);


  int16_t arr16mono1[] = {23,1,56};
  Audio<int16_t> m161(3);
  int16_t arr16mono2[] = {7,13,67};
  Audio<int16_t> m162(3);
  int16_t arr16mono3[] = {23,1,56,7,13,67};
  Audio<int16_t> m163(6);

  int8_t arr8stereo1[] = {1,2,1,2,0,7};
  Audio<pair<int8_t,int8_t> > s81(3);
  int8_t arr8stereo2[] = {1,4,2,1,1,1};
  Audio<pair<int8_t,int8_t> > s82(3);
  int8_t arr8stereo3[] = {1,2,1,2,0,7,1,4,2,1,1,1};
  Audio<pair<int8_t,int8_t> > s83(6);


  int16_t arr16stereo1[] = {27,456,12,3,241,2};
  Audio<pair<int16_t,int16_t> > s161(3);
  int16_t arr16stereo2[] = {543,123,1,7,345,1};
  Audio<pair<int16_t,int16_t> > s162(3);
  int16_t arr16stereo3[] = {27,456,12,3,241,2,543,123,1,7,345,1};
  Audio<pair<int16_t,int16_t> > s163(6);

  for(int i=0;i<3;i++)
  {
    m81.getSample()[i]=arr8mono1[i];
    m82.getSample()[i]=arr8mono2[i];
    m161.getSample()[i]=arr16mono1[i];
    m162.getSample()[i]=arr16mono2[i];

    s81.getSample()[i].first=arr8stereo1[i*2];
    s81.getSample()[i].second=arr8stereo1[i*2+1];
    s82.getSample()[i].first=arr8stereo2[i*2];
    s82.getSample()[i].second=arr8stereo2[i*2+1];
    s161.getSample()[i].first=arr16stereo1[i*2];
    s161.getSample()[i].second=arr16stereo1[i*2+1];
    s162.getSample()[i].first=arr16stereo2[i*2];
    s162.getSample()[i].second=arr16stereo2[i*2+1];
  }
  m83 = m81|m82;
  m163 = m161|m162;
  s83 = s81|s82;
  s163 = s161|s162;

  for(int i=0;i<3;i++)//check originals have not been editied
  {
    REQUIRE(m81.getSample()[i]==arr8mono1[i]);
    REQUIRE(m82.getSample()[i]==arr8mono2[i]);
    REQUIRE(m161.getSample()[i]==arr16mono1[i]);
    REQUIRE(m162.getSample()[i]==arr16mono2[i]);

    REQUIRE(s81.getSample()[i].first==arr8stereo1[i*2]);
    REQUIRE(s81.getSample()[i].second==arr8stereo1[i*2+1]);
    REQUIRE(s82.getSample()[i].first==arr8stereo2[i*2]);
    REQUIRE(s82.getSample()[i].second==arr8stereo2[i*2+1]);
    REQUIRE(s161.getSample()[i].first==arr16stereo1[i*2]);
    REQUIRE(s161.getSample()[i].second==arr16stereo1[i*2+1]);
    REQUIRE(s162.getSample()[i].first==arr16stereo2[i*2]);
    REQUIRE(s162.getSample()[i].second==arr16stereo2[i*2+1]);
  }
  for(int i=0;i<6;i++)//check concatenation
  {
    REQUIRE(m83.getSample()[i]==arr8mono3[i]);
    REQUIRE(m163.getSample()[i]==arr16mono3[i]);
    REQUIRE(s83.getSample()[i].first==arr8stereo3[i*2]);
    REQUIRE(s83.getSample()[i].second==arr8stereo3[i*2+1]);
    REQUIRE(s163.getSample()[i].first==arr16stereo3[i*2]);
    REQUIRE(s163.getSample()[i].second==arr16stereo3[i*2+1]);
  }
}

TEST_CASE("Test * opperator","[Audio]") {
  int8_t arr8mono1[] = {1,2,1};
  Audio<int8_t> m81(3);
  int8_t arr8mono2[3];
  Audio<int8_t> m82(3);

  int16_t arr16mono1[] = {23,1,56};
  Audio<int16_t> m161(3);
  int16_t arr16mono2[3];
  Audio<int16_t> m162(3);

  int8_t arr8stereo1[] = {1,2,1,2,0,7};
  Audio<pair<int8_t,int8_t> > s81(3);
  int8_t arr8stereo2[6];
  Audio<pair<int8_t,int8_t> > s82(3);

  int16_t arr16stereo1[] = {71,45,234,456,675,234};
  Audio<pair<int16_t,int16_t> > s161(3);
  int16_t arr16stereo2[6];
  Audio<pair<int16_t,int16_t> > s162(3);

  pair<float,float> vol (0.1,0.4);
  for(int i=0;i<3;i++)
  {
    m81.getSample()[i]=arr8mono1[i];
    m161.getSample()[i]=arr16mono1[i];

    s81.getSample()[i].first=arr8stereo1[i*2];
    s81.getSample()[i].second=arr8stereo1[i*2+1];
    s161.getSample()[i].first=arr16stereo1[i*2];
    s161.getSample()[i].second=arr16stereo1[i*2+1];

    arr8mono2[i] = arr8mono1[i]*vol.first;
    arr16mono2[i] = arr16mono1[i]*vol.first;
    arr8stereo2[i*2] = arr8stereo1[i*2]*vol.first;
    arr8stereo2[i*2+1] = arr8stereo1[i*2+1]*vol.second;
    arr16stereo2[i*2] = arr16stereo1[i*2]*vol.first;
    arr16stereo2[i*2+1] = arr16stereo1[i*2+1]*vol.second;

  }
  m82 = m81*vol;
  m162 = m161*vol;
  s82 = s81*vol;
  s162 = s161*vol;

  for(int i=0;i<3;i++)
  {
    REQUIRE(m81.getSample()[i]==arr8mono1[i]);
    REQUIRE(m82.getSample()[i]==arr8mono2[i]);
    REQUIRE(m161.getSample()[i]==arr16mono1[i]);
    REQUIRE(m162.getSample()[i]==arr16mono2[i]);

    REQUIRE(s81.getSample()[i].first==arr8stereo1[i*2]);
    REQUIRE(s81.getSample()[i].second==arr8stereo1[i*2+1]);
    REQUIRE(s82.getSample()[i].first==arr8stereo2[i*2]);
    REQUIRE(s82.getSample()[i].second==arr8stereo2[i*2+1]);
    REQUIRE(s161.getSample()[i].first==arr16stereo1[i*2]);
    REQUIRE(s161.getSample()[i].second==arr16stereo1[i*2+1]);
    REQUIRE(s162.getSample()[i].first==arr16stereo2[i*2]);
    REQUIRE(s162.getSample()[i].second==arr16stereo2[i*2+1]);
  }
}

TEST_CASE("Test + opperator","[Audio]") {// tests addition operation including edge case
  int8_t arr8mono1[] = {1,-111,123};
  Audio<int8_t> m81(3);
  int8_t arr8mono2[] = {1,-34,100};
  Audio<int8_t> m82(3);
  int8_t arr8mono3[] = {2,-128,127};
  Audio<int8_t> m83(3);


  int16_t arr16mono1[] = {23,-31000,31345};
  Audio<int16_t> m161(3);
  int16_t arr16mono2[] = {7,-13000,12000};
  Audio<int16_t> m162(3);
  int16_t arr16mono3[] = {30,-32768,32767};
  Audio<int16_t> m163(6);

  int8_t arr8stereo1[] = {1,-123,-111,100,97,7};
  Audio<pair<int8_t,int8_t> > s81(3);
  int8_t arr8stereo2[] = {1,-35,-67,89,44,1};
  Audio<pair<int8_t,int8_t> > s82(3);
  int8_t arr8stereo3[] = {2,-128,-128,127,127,8};
  Audio<pair<int8_t,int8_t> > s83(3);


  int16_t arr16stereo1[] = {27,-31234,-23567,31234,23123,2};
  Audio<pair<int16_t,int16_t> > s161(3);
  int16_t arr16stereo2[] = {543,-12345,-21123,11323,18111,1};
  Audio<pair<int16_t,int16_t> > s162(3);
  int16_t arr16stereo3[] = {570,-32768,-32768,32767,32767,3};
  Audio<pair<int16_t,int16_t> > s163(3);

  for(int i=0;i<3;i++)
  {
    m81.getSample()[i]=arr8mono1[i];
    m82.getSample()[i]=arr8mono2[i];
    m161.getSample()[i]=arr16mono1[i];
    m162.getSample()[i]=arr16mono2[i];

    s81.getSample()[i].first=arr8stereo1[i*2];
    s81.getSample()[i].second=arr8stereo1[i*2+1];
    s82.getSample()[i].first=arr8stereo2[i*2];
    s82.getSample()[i].second=arr8stereo2[i*2+1];
    s161.getSample()[i].first=arr16stereo1[i*2];
    s161.getSample()[i].second=arr16stereo1[i*2+1];
    s162.getSample()[i].first=arr16stereo2[i*2];
    s162.getSample()[i].second=arr16stereo2[i*2+1];
  }
  m83 = m81+m82;
  m163 = m161+m162;
  s83 = s81+s82;
  s163 = s161+s162;

  for(int i=0;i<3;i++)//check originals have not been editied
  {
    REQUIRE(m81.getSample()[i]==arr8mono1[i]);
    REQUIRE(m82.getSample()[i]==arr8mono2[i]);
    REQUIRE(m161.getSample()[i]==arr16mono1[i]);
    REQUIRE(m162.getSample()[i]==arr16mono2[i]);

    REQUIRE(s81.getSample()[i].first==arr8stereo1[i*2]);
    REQUIRE(s81.getSample()[i].second==arr8stereo1[i*2+1]);
    REQUIRE(s82.getSample()[i].first==arr8stereo2[i*2]);
    REQUIRE(s82.getSample()[i].second==arr8stereo2[i*2+1]);
    REQUIRE(s161.getSample()[i].first==arr16stereo1[i*2]);
    REQUIRE(s161.getSample()[i].second==arr16stereo1[i*2+1]);
    REQUIRE(s162.getSample()[i].first==arr16stereo2[i*2]);
    REQUIRE(s162.getSample()[i].second==arr16stereo2[i*2+1]);

    REQUIRE(m83.getSample()[i]==arr8mono3[i]);
    REQUIRE(m163.getSample()[i]==arr16mono3[i]);
    REQUIRE(s83.getSample()[i].first==arr8stereo3[i*2]);
    REQUIRE(s83.getSample()[i].second==arr8stereo3[i*2+1]);
    REQUIRE(s163.getSample()[i].first==arr16stereo3[i*2]);
    REQUIRE(s163.getSample()[i].second==arr16stereo3[i*2+1]);
  }
}

TEST_CASE("Test ^ opperator","[Audio]") {
  int8_t arr8mono1[] = {1,2,1,56,2,123};
  Audio<int8_t> m81(6);
  int8_t arr8mono2[]= {1,2,123};
  Audio<int8_t> m82(3);

  int16_t arr16mono1[] = {23,1,56,456,3245,123};
  Audio<int16_t> m161(6);
  int16_t arr16mono2[] = {23,3245,123};
  Audio<int16_t> m162(3);

  int8_t arr8stereo1[] = {1,2,1,2,0,7,67,34,21,1,3,123};
  Audio<pair<int8_t,int8_t> > s81(6);
  int8_t arr8stereo2[] = {1,2,21,1,3,123};
  Audio<pair<int8_t,int8_t> > s82(3);

  int16_t arr16stereo1[] = {71,45,234,456,675,234,45,1234,435,3123,43,5678};
  Audio<pair<int16_t,int16_t> > s161(6);
  int16_t arr16stereo2[] = {71,45,435,3123,43,5678};
  Audio<pair<int16_t,int16_t> > s162(3);

  pair<int,int> clip (1,3);

  for(int i=0;i<6;i++)
  {
    m81.getSample()[i]=arr8mono1[i];
    m161.getSample()[i]=arr16mono1[i];

    s81.getSample()[i].first=arr8stereo1[i*2];
    s81.getSample()[i].second=arr8stereo1[i*2+1];
    s161.getSample()[i].first=arr16stereo1[i*2];
    s161.getSample()[i].second=arr16stereo1[i*2+1];
  }
  m82 = m81^clip;
  m162 = m161^clip;
  s82 = s81^clip;
  s162 = s161^clip;

  for(int i=0;i<3;i++)
  {
    REQUIRE(m81.getSample()[i]==arr8mono1[i]);
    REQUIRE(m82.getSample()[i]==arr8mono2[i]);
    REQUIRE(m161.getSample()[i]==arr16mono1[i]);
    REQUIRE(m162.getSample()[i]==arr16mono2[i]);

    REQUIRE(s81.getSample()[i].first==arr8stereo1[i*2]);
    REQUIRE(s81.getSample()[i].second==arr8stereo1[i*2+1]);
    REQUIRE(s82.getSample()[i].first==arr8stereo2[i*2]);
    REQUIRE(s82.getSample()[i].second==arr8stereo2[i*2+1]);
    REQUIRE(s161.getSample()[i].first==arr16stereo1[i*2]);
    REQUIRE(s161.getSample()[i].second==arr16stereo1[i*2+1]);
    REQUIRE(s162.getSample()[i].first==arr16stereo2[i*2]);
    REQUIRE(s162.getSample()[i].second==arr16stereo2[i*2+1]);
  }
}

TEST_CASE("Test / opperator","[Audio]") {
  int8_t arr8mono1[] = {1,2,1,56,2,123};
  Audio<int8_t> m81(6);
  int8_t arr8mono2[]= {2,1,56};
  Audio<int8_t> m82(3);

  int16_t arr16mono1[] = {23,1,56,456,3245,123};
  Audio<int16_t> m161(6);
  int16_t arr16mono2[] = {1,56,456};
  Audio<int16_t> m162(3);

  int8_t arr8stereo1[] = {1,2,1,2,0,7,67,34,21,1,3,123};
  Audio<pair<int8_t,int8_t> > s81(6);
  int8_t arr8stereo2[] = {1,2,0,7,67,34};
  Audio<pair<int8_t,int8_t> > s82(3);

  int16_t arr16stereo1[] = {71,45,234,456,675,234,45,1234,435,3123,43,5678};
  Audio<pair<int16_t,int16_t> > s161(6);
  int16_t arr16stereo2[] = {234,456,675,234,45,1234};
  Audio<pair<int16_t,int16_t> > s162(3);

  pair<int,int> clip (1,3);

  for(int i=0;i<6;i++)
  {
    m81.getSample()[i]=arr8mono1[i];
    m161.getSample()[i]=arr16mono1[i];

    s81.getSample()[i].first=arr8stereo1[i*2];
    s81.getSample()[i].second=arr8stereo1[i*2+1];
    s161.getSample()[i].first=arr16stereo1[i*2];
    s161.getSample()[i].second=arr16stereo1[i*2+1];
  }
  m82 = m81/clip;
  m162 = m161/clip;
  s82 = s81/clip;
  s162 = s161/clip;

  for(int i=0;i<3;i++)
  {
    REQUIRE(m81.getSample()[i]==arr8mono1[i]);
    REQUIRE(m82.getSample()[i]==arr8mono2[i]);
    REQUIRE(m161.getSample()[i]==arr16mono1[i]);
    REQUIRE(m162.getSample()[i]==arr16mono2[i]);

    REQUIRE(s81.getSample()[i].first==arr8stereo1[i*2]);
    REQUIRE(s81.getSample()[i].second==arr8stereo1[i*2+1]);
    REQUIRE(s82.getSample()[i].first==arr8stereo2[i*2]);
    REQUIRE(s82.getSample()[i].second==arr8stereo2[i*2+1]);
    REQUIRE(s161.getSample()[i].first==arr16stereo1[i*2]);
    REQUIRE(s161.getSample()[i].second==arr16stereo1[i*2+1]);
    REQUIRE(s162.getSample()[i].first==arr16stereo2[i*2]);
    REQUIRE(s162.getSample()[i].second==arr16stereo2[i*2+1]);
  }
}

TEST_CASE("Test ! opperator","[Audio]") {
  int8_t arr8mono1[] = {1,2,24};
  Audio<int8_t> m81(3);
  int8_t arr8mono2[] = {24,2,1};
  Audio<int8_t> m82(3);

  int16_t arr16mono1[] = {23,1,56};
  Audio<int16_t> m161(3);
  int16_t arr16mono2[] = {56,1,23};
  Audio<int16_t> m162(3);

  int8_t arr8stereo1[] = {1,2,1,2,0,7};
  Audio<pair<int8_t,int8_t> > s81(3);
  int8_t arr8stereo2[] = {0,7,1,2,1,2};
  Audio<pair<int8_t,int8_t> > s82(3);

  int16_t arr16stereo1[] = {71,45,234,456,675,234};
  Audio<pair<int16_t,int16_t> > s161(3);
  int16_t arr16stereo2[] = {675,234,234,456,71,45};
  Audio<pair<int16_t,int16_t> > s162(3);

  for(int i=0;i<3;i++)
  {
    m81.getSample()[i]=arr8mono1[i];
    m161.getSample()[i]=arr16mono1[i];

    s81.getSample()[i].first=arr8stereo1[i*2];
    s81.getSample()[i].second=arr8stereo1[i*2+1];
    s161.getSample()[i].first=arr16stereo1[i*2];
    s161.getSample()[i].second=arr16stereo1[i*2+1];

  }
  m82 = !m81;
  m162 = !m161;
  s82 = !s81;
  s162 = !s161;

  for(int i=0;i<3;i++)
  {
    REQUIRE(m81.getSample()[i]==arr8mono1[i]);
    REQUIRE(m82.getSample()[i]==arr8mono2[i]);
    REQUIRE(m161.getSample()[i]==arr16mono1[i]);
    REQUIRE(m162.getSample()[i]==arr16mono2[i]);

    REQUIRE(s81.getSample()[i].first==arr8stereo1[i*2]);
    REQUIRE(s81.getSample()[i].second==arr8stereo1[i*2+1]);
    REQUIRE(s82.getSample()[i].first==arr8stereo2[i*2]);
    REQUIRE(s82.getSample()[i].second==arr8stereo2[i*2+1]);
    REQUIRE(s161.getSample()[i].first==arr16stereo1[i*2]);
    REQUIRE(s161.getSample()[i].second==arr16stereo1[i*2+1]);
    REQUIRE(s162.getSample()[i].first==arr16stereo2[i*2]);
    REQUIRE(s162.getSample()[i].second==arr16stereo2[i*2+1]);
  }
}

TEST_CASE("Test RMS calculation Operation","[Audio]") {

  int8_t arr1[] = {1,2,1,2,0,7};
  Audio<int8_t> a(6);

  int16_t arr2[] = {2,4,5,2,213,677};
  Audio<int16_t> b(6);

  int8_t arr3[] = {1,2,1,2,0,7,4,3,2,1};
  Audio<pair<int8_t,int8_t> > c(6);

  int16_t arr4[] = {2,4,5,2,213,677,213,324,2,1};
  Audio<pair<int16_t,int16_t> > d(6);

  float rmsA = 0;
  float rmsB = 0;
  float rmsCl = 0;
  float rmsCr = 0;
  float rmsDl = 0;
  float rmsDr = 0;


  for(int i=0;i<6;i++)
  {
    a.getSample()[i]=arr1[i];
    b.getSample()[i]=arr2[i];
    c.getSample()[i].first=arr3[i*2];
    c.getSample()[i].second=arr3[i*2+1];
    d.getSample()[i].first=arr4[i*2];
    d.getSample()[i].second=arr4[i*2+1];

    rmsA += arr1[i]*arr1[i];
    rmsB += arr2[i]*arr2[i];
    rmsCl += arr3[i*2]*arr3[i*2];
    rmsCr += arr3[i*2+1]*arr3[i*2+1];
    rmsDl += arr4[i*2]*arr4[i*2];
    rmsDr += arr4[i*2+1]*arr4[i*2+1];
  }

  rmsA = sqrt(rmsA/6);
  rmsB = sqrt(rmsB/6);
  rmsCl = sqrt(rmsCl/6);
  rmsCr = sqrt(rmsCr/6);
  rmsDl = sqrt(rmsDl/6);
  rmsDr = sqrt(rmsDr/6);

  float e = 0.001f;
  REQUIRE(a.rmsOperation()<rmsA+e);
  REQUIRE(a.rmsOperation()>rmsA-e);
  REQUIRE(b.rmsOperation()<rmsB+e);
  REQUIRE(b.rmsOperation()>rmsB-e);
  REQUIRE(c.rmsOperation().first<rmsCl+e);
  REQUIRE(c.rmsOperation().first>rmsCl-e);
  REQUIRE(c.rmsOperation().second<rmsCr+e);
  REQUIRE(c.rmsOperation().second>rmsCr-e);
  REQUIRE(d.rmsOperation().first<rmsDl+e);
  REQUIRE(d.rmsOperation().first>rmsDl-e);
  REQUIRE(d.rmsOperation().second<rmsDr+e);
  REQUIRE(d.rmsOperation().second>rmsDr-e);

}

TEST_CASE("Test Normalize Operation","[Audio]") {

  int8_t arr1[] = {1,2,1,2,0,7};
  int8_t res1[6];
  Audio<int8_t> a(6);

  int16_t arr2[] = {2,4,5,2,213,677};
  int16_t res2[6];
  Audio<int16_t> b(6);

  int8_t arr3[] = {1,2,1,2,0,7,4,3,2,1,45,34};
  int8_t res3[12];
  Audio<pair<int8_t,int8_t> > c(6);

  int16_t arr4[] = {2,4,5,2,213,677,213,324,2,1,32,11};
  int16_t res4[12];
  Audio<pair<int16_t,int16_t> > d(6);

  for(int i=0;i<6;i++)
  {
    a.getSample()[i]=arr1[i];
    b.getSample()[i]=arr2[i];
    c.getSample()[i].first=arr3[i*2];
    c.getSample()[i].second=arr3[i*2+1];
    d.getSample()[i].first=arr4[i*2];
    d.getSample()[i].second=arr4[i*2+1];
  }

  float rhsA = a.rmsOperation();
  float rhsB = b.rmsOperation();
  pair<float,float> rhsC = c.rmsOperation();
  pair<float,float> rhsD = d.rmsOperation();

  pair<float,float> norm (4.1f,1.2f);

  for(int i=0;i<6;i++)
  {
    res1[i] = arr1[i]*norm.first/rhsA;
    res2[i] = arr2[i]*norm.first/rhsB;
    res3[i*2] = arr3[i*2]*norm.first/rhsC.first;
    res3[i*2+1] = arr3[i*2+1]*norm.second/rhsC.second;
    res4[i*2] = arr4[i*2]*norm.first/rhsD.first;
    res4[i*2+1] = arr4[i*2+1]*norm.second/rhsD.second;
  }

  a.normalize(norm);
  b.normalize(norm);
  c.normalize(norm);
  d.normalize(norm);

  for(int i=0;i<6;i++)
  {
    REQUIRE(a.getSample()[i]==res1[i]);
    REQUIRE(b.getSample()[i]==res2[i]);
    REQUIRE(c.getSample()[i].first==res3[i*2]);
    REQUIRE(c.getSample()[i].second==res3[i*2+1]);
    REQUIRE(d.getSample()[i].first==res4[i*2]);
    REQUIRE(d.getSample()[i].second==res4[i*2+1]);
  }

}

TEST_CASE("Test Fade In Operation","[Audio]") {

  int8_t arr1[] = {56,67,67,34,67,56};
  Audio<int8_t> a(6);

  int16_t arr2[] = {567,865,1111,789,213,677};
  Audio<int16_t> b(6);

  int8_t arr3[] = {99,45,78,98,89,67,89,78,89,102,111,78};
  Audio<pair<int8_t,int8_t> > c(6);

  int16_t arr4[] = {3423,3422,4532,3422,3422,4332,1121,4532,5657,4454,4342,3342};
  Audio<pair<int16_t,int16_t> > d(6);


  for(int i=0;i<6;i++)
  {
    a.getSample()[i]=arr1[i];
    b.getSample()[i]=arr2[i];
    c.getSample()[i].first=arr3[i*2];
    c.getSample()[i].second=arr3[i*2+1];
    d.getSample()[i].first=arr4[i*2];
    d.getSample()[i].second=arr4[i*2+1];
  }

  a.fadeIn(3);
  b.fadeIn(3);
  c.fadeIn(3);
  d.fadeIn(3);

  for(int i=0;i<3;i++)
  {
    arr1[i] *= (float)i/3;
    arr2[i] *= (float)i/3;
    arr3[i*2] *= (float)i/3;
    arr3[i*2+1] *= (float)i/3;
    arr4[i*2] *= (float)i/3;
    arr4[i*2+1] *= (float)i/3;
  }

  for(int i=0;i<6;i++)
  {
    REQUIRE(a.getSample()[i]==arr1[i]);
    REQUIRE(b.getSample()[i]==arr2[i]);
    REQUIRE(c.getSample()[i].first==arr3[i*2]);
    REQUIRE(c.getSample()[i].second==arr3[i*2+1]);
    REQUIRE(d.getSample()[i].first==arr4[i*2]);
    REQUIRE(d.getSample()[i].second==arr4[i*2+1]);
  }

}
  
TEST_CASE("Test Fade Out Operation","[Audio]") {

  int8_t arr1[] = {56,67,67,34,67,56};
  Audio<int8_t> a(6);

  int16_t arr2[] = {567,865,1111,789,213,677};
  Audio<int16_t> b(6);

  int8_t arr3[] = {99,45,78,98,89,67,89,78,89,102,111,78};
  Audio<pair<int8_t,int8_t> > c(6);

  int16_t arr4[] = {3423,3422,4532,3422,3422,4332,1121,4532,5657,4454,4342,3342};
  Audio<pair<int16_t,int16_t> > d(6);

  for(int i=0;i<6;i++)
  {
    a.getSample()[i]=arr1[i];
    b.getSample()[i]=arr2[i];
    c.getSample()[i].first=arr3[i*2];
    c.getSample()[i].second=arr3[i*2+1];
    d.getSample()[i].first=arr4[i*2];
    d.getSample()[i].second=arr4[i*2+1];
  }

  a.fadeOut(3);
  b.fadeOut(3);
  c.fadeOut(3);
  d.fadeOut(3);

  for(int i=3;i<6;i++)
  {
    arr1[i] *= (float)(6-i)/3;
    arr2[i] *= (float)(6-i)/3;
    arr3[i*2] *= (float)(6-i)/3;
    arr3[i*2+1] *= (float)(6-i)/3;
    arr4[i*2] *= (float)(6-i)/3;
    arr4[i*2+1] *= (float)(6-i)/3;
  }

  for(int i=0;i<6;i++)
  {
    REQUIRE(a.getSample()[i]==arr1[i]);
    REQUIRE(b.getSample()[i]==arr2[i]);
    REQUIRE(c.getSample()[i].first==arr3[i*2]);
    REQUIRE(c.getSample()[i].second==arr3[i*2+1]);
    REQUIRE(d.getSample()[i].first==arr4[i*2]);
    REQUIRE(d.getSample()[i].second==arr4[i*2+1]);
  }

}
