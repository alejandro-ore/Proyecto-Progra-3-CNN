#include "ReadImage.h"

void trainingImages(vector<TrainImage> &trainData,string directory=""){
    string images_name=directory+"train-images-idx3-ubyte";
    string labels_name=directory+"train-labels-idx1-ubyte";

    vector<unsigned char> labels;

    ifstream file1(images_name, std::ios::binary);
    ifstream file2(labels_name, std::ios::binary);

    if (!file1||!file2){
        cerr<<"Error on loading image\n";
        return;
    }

    int magic1=0,magic2=0;
    file1.read(reinterpret_cast<char*>(&magic1),sizeof(magic1));
    file2.read(reinterpret_cast<char*>(&magic2),sizeof(magic2));
    magic1=__builtin_bswap32(magic1);
    magic2=__builtin_bswap32(magic2);

    int num1=0,num2=0;
    file1.read(reinterpret_cast<char*>(&num1),sizeof(num1));
    file2.read(reinterpret_cast<char*>(&num2),sizeof(num2));
    num1=__builtin_bswap32(num1);
    num2=__builtin_bswap32(num2);

    int rows = 0, cols = 0;
    file1.read(reinterpret_cast<char*>(&rows),sizeof(rows));
    rows=__builtin_bswap32(rows);
    file1.read(reinterpret_cast<char*>(&cols),sizeof(cols));
    cols=__builtin_bswap32(cols);

    labels.resize(num2);
    file2.read(reinterpret_cast<char*>(labels.data()), num2);
    trainData.resize(num1,vector<unsigned char>(rows*cols));
    for (int i=0;i<num1;i++){
        file1.read(reinterpret_cast<char*>(trainData[i].data()),rows * cols);
        trainData[i].set_label(labels[i]);
    }

    file1.close();
    file2.close();
}

void testingImages(vector<TestImage> &testData){
    string directory="/home/d4rkmn/Desktop/UTEC/Ciclo III/Programación III/Proyecto-v0/dataset/";
    string images_name=directory+"t10k-images-idx3-ubyte";
    string labels_name=directory+"t10k-labels-idx1-ubyte";

    vector<unsigned char> labels;

    ifstream file1(images_name, std::ios::binary);
    ifstream file2(labels_name, std::ios::binary);

    if (!file1||!file2){
        cerr<<"Error on loading image\n";
        return;
    }

    int magic1=0,magic2=0;
    file1.read(reinterpret_cast<char*>(&magic1),sizeof(magic1));
    file2.read(reinterpret_cast<char*>(&magic2),sizeof(magic2));
    magic1=__builtin_bswap32(magic1);
    magic2=__builtin_bswap32(magic2);

    int num1=0,num2=0;
    file1.read(reinterpret_cast<char*>(&num1),sizeof(num1));
    file2.read(reinterpret_cast<char*>(&num2),sizeof(num2));
    num1=__builtin_bswap32(num1);
    num2=__builtin_bswap32(num2);

    int rows = 0, cols = 0;
    file1.read(reinterpret_cast<char*>(&rows),sizeof(rows));
    rows=__builtin_bswap32(rows);
    file1.read(reinterpret_cast<char*>(&cols),sizeof(cols));
    cols=__builtin_bswap32(cols);

    labels.resize(num2);
    file2.read(reinterpret_cast<char*>(labels.data()), num2);
    testData.resize(num1,vector<unsigned char>(rows*cols));
    for (int i=0;i<num1;i++){
        file1.read(reinterpret_cast<char*>(testData[i].data()),rows * cols);
        testData[i].set_label(labels[i]);
    }

    file1.close();
    file2.close();
}