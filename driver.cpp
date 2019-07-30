// Steven Mare - MRXSTE008
// 10 May 2018
// for CSC3022H Assignment 5

#include "audio.h"
#include <string>
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace MRXSTE008;

void clear(void) { system("clear"); }//clears screen

template <typename T> bool performOp(string ops,T & a,T & b, T & c,
string sf1, string sf2, string f, 
int r1b, int r1e, int r2b, int r2e, float fl, float fr)//template operation used to take in Audio template objects
//Arguments: operation, Audio a, Audio b, Audio c(output Audio), 
//soundfile 1, sound file 2, outputfile
//range 1 beginning, range 1 end, range 2 beginning, range 2 end, floating left, floating right (floats are reused depending on function)
{
  if(ops.compare("-add")==0)
  {
    cout << "Adding..." << endl;
    a.load(sf1);
    b.load(sf2);
    c = a+b;
    c.save(f);
    return true;
  }
  else if(ops.compare("-cut")==0)
  {
    cout << "Cutting..." << endl;
    pair<int,int> slice(r1b,r1e);
    a.load(sf1);
    c = a^slice;
    c.save(f);
    return true;
  }
  else if(ops.compare("-radd")==0)
  {
    cout << "Adding ranges..." << endl;
    pair<int,int> slice1(r1b,r1e);
    pair<int,int> slice2(r2b,r2e);
    a.load(sf1);
    b.load(sf2);
    c = (a/slice1) + (b/slice2);
    c.save(f);
    return true;
  }
  else if(ops.compare("-cat")==0)
  {
    cout << "Concatenating..." << endl;
    a.load(sf1);
    b.load(sf2);
    c = a|b;
    c.save(f);
    return true;
  }
  else if(ops.compare("-v")==0)
  {
    cout << "Adjusting Volume..." << endl;
    pair<float,float> slice(fl,fr);
    a.load(sf1);
    c = a*slice;
    c.save(f);
    return true;
  }
  else if(ops.compare("-rev")==0)
  {
    cout << "Reversing..." << endl;
    a.load(sf1);
    c = !a;
    c.save(f);
    return true;
  }
  else if(ops.compare("-rms")==0)
  {
    cout << "Calculating RMS..." << endl;
    a.load(sf1);
    a.RMS();
    
    return true;
  }
  else if(ops.compare("-norm")==0)
  {
    cout << "Normalizing..." << endl;
    a.load(sf1);
    a.normalize(pair<float,float> (fl,fr));
    a.save(f);
    return true;
  }
  else if(ops.compare("-fadein")==0)
  {
    cout << "Adding fade in..." << endl;
    int samples = fl*fr;
    //f1 = fade time, fr = sampling rate
    a.load(sf1);
    a.fadeIn(samples);
    a.save(f);
    return true;
    
  }
  else if(ops.compare("-fadeout")==0)
  {
    cout << "Adding fade out..." << endl;
    int samples = fl*fr;
    //f1 = fade time, fr = sampling rate
    a.load(sf1);
    a.fadeOut(samples);
    a.save(f);
    return true;
  }
  return false;
}


int main (int argc, char** argv){
  clear();

  cout << "Running" << endl;

  //variables used by all functions
  int i=0; //index for going through arguments
  string arg; 
  ifstream is;
  int filelength=0;
  int samplesize=0;
  int sampleRate = 0;
  int bitCount = 0;
  int channelCount = 0;
  string channelName = "mono";
  string filename = "out";
  string soundFile1 = "none";
  string soundFile2 = "none";
  string ops = "none";

  //variables for functions that have range
  int range1beg = 0;
  int range1end = 0;
  int range2beg = 0;
  int range2end = 0;

  //used for volume factor or normalizing
  float floatLeft = 0;
  float floatRight = 0;


  if(argc<9)
  {
    cout << "Not enough input arguments" << endl;
    return 0;
  }


  for(i=1; i<argc; i++){//loops through arguments, sets values where appropriate
    arg = argv[i];
    if(arg.compare("-r")==0){
      sampleRate = atoi(argv[++i]);
    }
    else if(arg.compare("-b")==0){
      bitCount = atoi(argv[++i]);
      if(bitCount != 8 && bitCount != 16)
      {
        cout << "Invalid bit count" << endl;
        return 0;
      }
    }
    else if(arg.compare("-c")==0){
      channelCount = atoi(argv[++i]);
      if(channelCount == 2)
      {
        channelName = "stereo";
      }
      else if(channelCount != 1)
      {
        cout << "Invalid channel count" << endl;
        return 0;
      }
    }
    else if(arg.compare("-o")==0){
      filename = argv[++i];
      cout << filename << endl;
    }
    else if(arg.compare("-add")==0)
    {
      ops = "-add";
      soundFile1 = argv[++i];
      soundFile2 = argv[++i];
    }
    else if(arg.compare("-cut")==0)
    {
      ops = "-cut";
      range1beg = atoi(argv[++i]);
      range1end = atoi(argv[++i]);
      soundFile1 = argv[++i];
    }
    else if(arg.compare("-radd")==0)
    {
      ops = "-radd";
      range1beg = atoi(argv[++i]);
      range1end = atoi(argv[++i]);
      range2beg = atoi(argv[++i]);
      range2end = atoi(argv[++i]); 
      soundFile1 = argv[++i];
      soundFile2 = argv[++i];   
    }
    else if(arg.compare("-cat")==0)
    {
      ops = "-cat";
      soundFile1 = argv[++i];
      soundFile2 = argv[++i];
    }
    else if(arg.compare("-v")==0)
    {
      ops = "-v";
      floatLeft = atof(argv[++i]);
      floatRight = atof(argv[++i]);
      soundFile1 = argv[++i];
    }
    else if(arg.compare("-rev")==0)
    {
      ops = "-rev";
      soundFile1 = argv[++i];
    }
    else if(arg.compare("-rms")==0)
    {
      ops = "-rms";
      soundFile1 = argv[++i];
    }
    else if(arg.compare("-norm")==0)
    {
      ops = "-norm";
      floatLeft = atof(argv[++i]);
      floatRight = atof(argv[++i]);
      soundFile1 = argv[++i];
    }
    else if(arg.compare("-fadein")==0)
    {
      ops = "-fadein";
      floatLeft = atof(argv[++i]);
      floatRight = sampleRate;
      soundFile1 = argv[++i];
    }
    else if(arg.compare("-fadeout")==0)
    {
      ops = "-fadeout";
      floatLeft = atof(argv[++i]);
      floatRight = sampleRate;
      soundFile1 = argv[++i];
    }
  }

  is.open(soundFile1,ios::binary);//opens file to determine vector size
  if(!is)
  {
    cout << "Could not open file " << soundFile1 << endl;
    return 0;
  }
  is.seekg (0, is.end);
  filelength = is.tellg();
  is.close();

  filename += "_"+to_string(sampleRate)+"_signed_"+to_string(bitCount)+"bit_"+channelName+".raw";

  if(bitCount==8)//if 8 bit sound
  {
    if(channelCount==1)//if 8 bit mono
    {
      samplesize = filelength / (sizeof(int8_t) * 1);

      Audio<int8_t> a (samplesize);
      Audio<int8_t> b (samplesize);
      Audio<int8_t> c (samplesize);
      if(performOp(ops, a, b, c, soundFile1, soundFile2, filename,
        range1beg, range1end, range2beg, range2end, floatLeft, floatRight))
      {
        cout << "Function Complete" << endl;
      }
      else
      {
        cout << "No Function Found" << endl;
      }
    }
    else//if 8 bit stereo
    {
      samplesize = filelength / (sizeof(int8_t) * 2);

      Audio<pair<int8_t,int8_t> > a (samplesize);
      Audio<pair<int8_t,int8_t> > b (samplesize);
      Audio<pair<int8_t,int8_t> > c (samplesize);
      if(performOp(ops, a, b, c, soundFile1, soundFile2, filename,
        range1beg, range1end, range2beg, range2end, floatLeft, floatRight))
      {
        cout << "Function Complete" << endl;
      }
      else
      {
        cout << "No Function Found" << endl;
      }
    }

  }
  else//if 16 bit sound
  {
    if(channelCount==1)//if 16 bit mono
    {
      samplesize = filelength / (sizeof(int16_t) * 1);
      Audio<int16_t> a (samplesize);
      Audio<int16_t> b (samplesize);
      Audio<int16_t> c (samplesize);

      if(performOp(ops, a, b, c, soundFile1, soundFile2, filename,
        range1beg, range1end, range2beg, range2end, floatLeft, floatRight))
      {
        cout << "Function Complete" << endl;
      }
      else
      {
        cout << "No Function Found" << endl;
      }
    }
    else//if 16 bit stereo
    {
      samplesize = filelength / (sizeof(int16_t) * 2);
      Audio<pair<int16_t,int16_t> > a (samplesize);
      Audio<pair<int16_t,int16_t> > b (samplesize);
      Audio<pair<int16_t,int16_t> > c (samplesize);

      if(performOp(ops, a, b, c, soundFile1, soundFile2, filename,
        range1beg, range1end, range2beg, range2end, floatLeft, floatRight))
      {
        cout << "Function Complete" << endl;
      }
      else
      {
        cout << "No Function Found" << endl;
      }
    }

  }





/*



  
  }
*/
  return 0;
}
