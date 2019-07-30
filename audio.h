// Steven Mare - MRXSTE008
// 11 May 2018
// for CSC3022H Assignment 5


#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <cstdint>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <functional>
#include <cmath>
#include <numeric>


namespace MRXSTE008
{
    template <typename T> class Audio
    {
      private: // private members
        std::vector<T> sample;
      public: // public members
        Audio(size_t N): sample(std::vector<T>(N)){}
        ~Audio(){}

        Audio(const Audio & rhs) // Copy Constructor
        {
            sample = std::vector<T>(rhs.sample.size());
            for(int i=0; i<sample.size(); i++)
            {
                sample[i]=rhs.sample[i];
            }
            
        }
        Audio(Audio && rhs)// Move Constructor
        {
            sample = move(rhs.sample);
        }
        // Copy and Move Assignment Operators
        Audio & operator=(const Audio & rhs)
        {
            sample = std::vector<T>(rhs.sample.size());
            for(int i=0; i<sample.size(); i++){
                sample[i]=rhs.sample[i];
            }
            return *this;
        }

        Audio & operator=(Audio && rhs)
        {
            sample = move(rhs.sample);
            return *this;
        }

        //Operator Overloads
        Audio operator|(const Audio & rhs)//concatenating two files
        {
            Audio<T> temp(sample.size()+rhs.sample.size());
            for(int i = 0; i<sample.size(); i++){
                temp.sample[i] = sample[i];
            }
            for(int i = 0; i<rhs.sample.size(); i++){
                temp.sample[i+sample.size()] = rhs.sample[i];
            }
            return temp;
        }

        Audio operator*(const std::pair<float,float> rhs)//adjust volume by float, only uses first float for mono
        {
            Audio<T> temp (sample.size());
            for(int i = 0; i<sample.size(); i++)
            {
                temp.sample[i] = sample[i]*rhs.first;
            }
            return temp;
        }

        Audio operator+(const Audio & rhs)//overlays two audio on top of each other, clips sound that is too high or low
        {

            Audio<T> temp (sample.size());
            int  max = std::numeric_limits<T>::max();
            int  min = std::numeric_limits<T>::min();

            for(int i = 0; i<sample.size(); i++)
            {
                temp.sample[i] = std::max(std::min(sample[i]+rhs.sample[i],max),min);
            }
            return temp;
        }
        
        Audio operator^(const std::pair<int,int> rhs)//returns file with piece clipped out
        {
            Audio<T> temp (sample.size()-(rhs.second-rhs.first+1));

            for(int i = 0; i<rhs.first; i++)
            {
                temp.sample[i] = sample[i];
            }
            for(int i = rhs.second+1; i<sample.size(); i++)
            {
                temp.sample[rhs.first+i-rhs.second-1] = sample[i];
            }
            return temp;


        }

        Audio operator/(const std::pair<int,int> rhs)//returns clipped piece only
        {
            Audio<T> temp (rhs.second-rhs.first+1);
            std::copy(sample.begin()+rhs.first,sample.begin()+rhs.second+1,temp.sample.begin());
            return temp;
        }

        Audio operator!(void)//for reversal
        {
            Audio<T> temp (sample.size());
            temp.sample = sample;
            std::reverse(temp.sample.begin(),temp.sample.end());
            return temp;
        }
        
        
        void load(std::string f)//for reading Audio into Audio object
        {
            std::ifstream infile(f, std::ios::binary);
            std::cout << "Reading " << f << std::endl;
            infile.read((char*)&sample[0],sample.size()*sizeof(T));
            infile.close();
        }
        
        void save(std::string f)//for output data in Audio object to output file
        {
            std::ofstream outfile;
            outfile.open(f, std::ios::binary);
            outfile.write((char*)&sample[0],sample.size()*sizeof(T));
            outfile.close();
            std::cout << "Written to " << f << std::endl;
        }

        float rmsOperation()//used in calculation of rms for mono
        {         
            auto lambda =  [&](float x,T y){return (float)(x+y*y);};
            float temp = std::accumulate(sample.begin(),sample.end(),0.0f,lambda);
            temp = std::sqrt(temp/sample.size());
            return temp;
        }

        void RMS()//prints RMS value to screen
        {
            float temp = rmsOperation();
            std::cout << "RMS is " << temp << std::endl;
        }

        static T normOperation(T x,float y)//normalizing operation used for STL transform
        {
            T max = std::numeric_limits<T>::max();
            T min = std::numeric_limits<T>::min();
            T temp = std::max(std::min((T)(x*y),max),min);
            return temp;
        }

        void normalize(const std::pair<float,float> rhs)//normalize sound
        {
            float rms = rmsOperation();
            std::vector<float> norm (sample.size(),rhs.first/rms);
            std::transform(sample.begin(), sample.end(), norm.begin(), sample.begin(), normOperation);
        }

        void fadeIn(int n)//give sound a fade in over n samples
        {
            for(int i=0; i<=n; i++)
            {
                sample[i]*=(float)i/n;
            }
        }

        void fadeOut(int n)//give sound a fade out over n samples
        {
            for(int i=sample.size()-n; i<sample.size(); i++)
            {
                sample[i]*=(float)(sample.size()-i)/n;
            }
        }

        std::vector<T> & getSample()//for unit testing
        {
            return sample;
        }


    };



    template <typename T> class Audio <std::pair<T,T> >//specialized template for stereo sound
    {
      private: // private members
        std::vector<std::pair<T,T> > sample;
      public: // public members
        Audio(size_t N): sample(std::vector<std::pair<T,T> >(N))
        {
            for(int i=0; i<sample.size(); i++)
            {
                sample[i].first=0;
                sample[i].second=0;

            }
        }
        ~Audio(){}

        Audio(const Audio & rhs) // Copy Constructor
        {
            sample = std::vector<std::pair<T,T> >(rhs.sample.size());
            for(int i=0; i<sample.size(); i++)
            {
                sample[i].first=rhs.sample[i].first;
                sample[i].second=rhs.sample[i].second;

            }
            
        }
        Audio(Audio && rhs)// Move Constructor
        {
            sample = move(rhs.sample);
        }
        // Copy and Move Assignment Operators
        Audio & operator=(const Audio & rhs)
        {
            sample = std::vector<std::pair<T,T> >(rhs.sample.size());
            for(int i=0; i<sample.size(); i++){
                sample[i].first=rhs.sample[i].first;
                sample[i].second=rhs.sample[i].second;
            }
            return *this;
        }

        Audio & operator=(Audio && rhs)
        {
            sample = move(rhs.sample);
            return *this;
        }

        //Operator Overloads
        Audio operator|(const Audio & rhs)//concatenate two sound files
        {
            Audio<std::pair<T,T> > temp(sample.size()+rhs.sample.size());
            for(int i = 0; i<sample.size(); i++){
                temp.sample[i].first = sample[i].first;
                temp.sample[i].second = sample[i].second;
            }
            for(int i = 0; i<rhs.sample.size(); i++){
                temp.sample[i+sample.size()].first = rhs.sample[i].first;
                temp.sample[i+sample.size()].second = rhs.sample[i].second;
            }
            return temp;
        }

        Audio operator*(const std::pair<float,float> rhs)//adjust sound file, left and right sound can have different adjustments
        {
            Audio<std::pair<T,T> > temp (sample.size());
            for(int i = 0; i<sample.size(); i++)
            {
                temp.sample[i].first = sample[i].first*rhs.first;
                temp.sample[i].second = sample[i].second*rhs.second;
            }
            return temp;
        }

        Audio operator+(const Audio & rhs)//overlay two sound samples, clips too high and too low sound
        {
            Audio<std::pair<T,T> > temp (sample.size());
            int  max = std::numeric_limits<T>::max();
            int  min = std::numeric_limits<T>::min();


            for(int i = 0; i<sample.size(); i++)
            {
                temp.sample[i].first = std::max(std::min(sample[i].first+rhs.sample[i].first,max),min);
                temp.sample[i].second = std::max(std::min(sample[i].second+rhs.sample[i].second,max),min);
            }
            return temp;
        }
        
        Audio operator^(const std::pair<int,int> rhs)//returns file with piece clipped out
        {
            Audio<std::pair<T,T> > temp (sample.size()-(rhs.second-rhs.first+1));
            for(int i = 0; i<rhs.first; i++)
            {
                temp.sample[i].first = sample[i].first;
                temp.sample[i].second = sample[i].second;
            }
            for(int i = rhs.second+1; i<sample.size(); i++)
            {
                temp.sample[rhs.first+i-rhs.second-1].first = sample[i].first;
                temp.sample[rhs.first+i-rhs.second-1].second = sample[i].second;
            }
            return temp;


        }

        Audio operator/(const std::pair<int,int> rhs)//returns clipped piece only
        {
            Audio<std::pair<T,T> > temp (rhs.second-rhs.first+1);
            std::copy(sample.begin()+rhs.first,sample.begin()+rhs.second+1,temp.sample.begin());
            return temp;
        }

        Audio operator!(void)//for reversal
        {
            Audio<std::pair<T,T> > temp (sample.size());
            temp.sample = sample;
            std::reverse(temp.sample.begin(),temp.sample.end());
            return temp;
        }
        
        
        void load(std::string f)//for reading Audio into Audio object
        {
            std::ifstream infile(f, std::ios::binary);
            std::cout << "Reading " << f << std::endl;
            infile.read((char*)&sample[0],sample.size()*sizeof(T)*2);
            infile.close();
        }
        
        void save(std::string f)//for output data in Audio object to output file
        {
            std::ofstream outfile;
            //writes header file
            outfile.open(f, std::ios::binary);
            outfile.write((char*)&sample[0],sample.size()*sizeof(T)*2);
            outfile.close();
            std::cout << "Written to " << f << std::endl;
        }

        std::pair<float,float> rmsOperation()//used in RMS calulation
        {
            auto lambda =  [&](std::pair<float,float> x,std::pair<T,T> y){return std::pair<float,float>(x.first+y.first*y.first,x.second+y.second*y.second);};
            std::pair<float,float> temp = std::accumulate(sample.begin(),sample.end(),std::pair<float,float>(0.0f,0.0f),lambda);
            
            temp.first = std::sqrt(temp.first/sample.size());
            temp.second = std::sqrt(temp.second/sample.size());
            return temp;
        }

        void RMS()//prints out left and right RMS
        {
            std::pair<float,float> temp = rmsOperation();
            std::cout << "Left RMS is " << temp.first << " Right RMS is " << temp.second << std::endl;
        }

        static std::pair<T,T> normOperation(std::pair<T,T> x,std::pair<float,float> y){
            T max = std::numeric_limits<T>::max();
            T min = std::numeric_limits<T>::min();
            std::pair<T,T> temp (std::max(std::min((T)(x.first*y.first),max),min),std::max(std::min((T)(x.second*y.second),max),min));
            return temp;
        }

        void normalize(const std::pair<float,float> rhs)//normalizes sound, left and right can have different values
        {
            std::pair<float,float> rms = rmsOperation();
            std::vector<std::pair<float,float>> norm (sample.size(),std::pair<float,float> (rhs.first/rms.first,rhs.second/rms.second));
            std::transform(sample.begin(), sample.end(), norm.begin(), sample.begin(), normOperation);
        }

        void fadeIn(int n)//fade in over n samples
        {
            for(int i=0; i<=n; i++)
            {
                sample[i].first *=(float)i/n;
                sample[i].second *=(float)i/n;
            }
        }

        void fadeOut(int n)//fade out over n samples
        {
            for(int i=sample.size()-n; i<sample.size(); i++)
            {
                sample[i].first*=(float)(sample.size()-i)/n;
                sample[i].second*=(float)(sample.size()-i)/n;
            }
        }

        std::vector<std::pair<T,T> > & getSample()//for unit testing
        {
            return sample;
        }


    };

}

#endif
