#include "ReadImage.h"
#include "CNN.h"
using namespace std;

int main(){
    srand(time(0));

    string directory="/home/d4rkmn/Desktop/UTEC/Ciclo III/Programación III/Proyecto-v0/dataset/";
    //directory es donde se encuentra ubicado la carpeta con el dataset

    vector<TrainImage> trainImages;
    vector<TestImage> testImages;

    trainingImages(trainImages,directory);
    testingImages(testImages,directory);

    int layers=2;
    int neurons=64;
    double learning_rate=0.675;

    CNN MNIST(layers,neurons); //2 capas ocultas, de 64 neuronas cada una
    MNIST.train(trainImages,learning_rate);
    //entrenando a la red neuronal convolucional

    for(int i=0;i<testImages.size();i++){
        MNIST.test(testImages[i]);
        do{}while(cin.get()!='\n');
        //presiona enter en la terminal para pasar a la siguiente imagen
    }

    return 0;
}

