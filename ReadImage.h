#ifndef PROYECTO_V0_READIMAGE_H
#define PROYECTO_V0_READIMAGE_H

#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

class Image{
protected:
    vector<unsigned char> img_data;
    int label;
    Image(){}
public:
    void print(){
        for (int i=0;i<28;i++) {
            for (int j=0;j<28;j++) {
                unsigned char pixel=img_data[i*28+j];
                if(pixel > 128) cout<<"X";
                else cout<< " ";
                cout<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
    auto data(){
        return img_data.data();
    }
    void set_label(unsigned char c){
        label=static_cast<int>(c);
    }
    int get_label(){return label;}
};

class TrainImage:public Image{
public:
    TrainImage(vector<unsigned char> v){
        img_data=v;
    }
    friend class CNN;
};

class TestImage:public Image{
public:
    TestImage(vector<unsigned char> v){
        img_data=v;
    }
    friend class CNN;
};

void trainingImages(vector<TrainImage> &trainData,string directory);

void testingImages(vector<TestImage> &testData);

#endif //PROYECTO_V0_READIMAGE_H
