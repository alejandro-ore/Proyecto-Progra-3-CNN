#include "ReadImage.h"
#include "CNN.h"
using namespace std;

int main(){
    random_device rd;
    srand(rd());

    string directory="/home/d4rkmn/Desktop/UTEC/Ciclo III/Programación III/Proyecto-v0/dataset/";
    //directory es donde se encuentra ubicado la carpeta con el dataset

    vector<TrainImage> trainImages;
    vector<TestImage> testImages;

    trainingImages(trainImages,directory);
    testingImages(testImages,directory);

    int layers=2;
    int neurons=128;
    double learning_rate=0.01;

    // 2 layers, 128 neurons each (3 min approx)
    // 0.2: 6901
    // 0.1: 7665
    // 0.05: 7344
    // 0.01: 8054
    // 0.0095: 7922
    // 0.009: 7986
    // 0.008: 7969
    // 0.005: 7469


    CNN MNIST(layers,neurons); //2 capas ocultas, de 64 neuronas cada una
    MNIST.train(trainImages,learning_rate);
    //entrenando a la red neuronal convolucional

    int count=0;

    for(int i=0;i<testImages.size();i++){
        if(MNIST.test(testImages[i])) count++;
        //MNIST.test(testImages[i]);
        //do{}while(cin.get()!='\n');
        //presiona enter en la terminal para pasar a la siguiente imagen
    }

    cout<<"correctas: "<<count<<"\n";
    cout<<"precision: "<<static_cast<double>(count)/10000.0<<"\n";

    return 0;
}

