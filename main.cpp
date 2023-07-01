#include "ReadImage.h"
#include "CNN.h"
using namespace std;

int main(){ // modificado para usar threads para optimizacion
    random_device rd;
    srand(rd());

    string directory="/home/d4rkmn/Desktop/UTEC/Ciclo III/Programación III/Proyecto-v0/dataset/";
    //directory es donde se encuentra ubicado la carpeta con el dataset
    // (modificar en relacion a tu directorio)

    vector<TrainImage> trainImages;
    vector<TestImage> testImages;

    trainingImages(trainImages,directory);
    testingImages(testImages,directory);

    int layers=2;
    int neurons=128;
    double learning_rate=0.01;

    // (por favor modificar estos valores hasta q la precision sea la mejor posible)


    CNN MNIST(layers,neurons); // 2 capas ocultas, de 64 neuronas cada una
    MNIST.train(trainImages,learning_rate);
    // entrenando a la red neuronal convolucional

    int count=0;
    for(int i=0;i<testImages.size();i++){
        if(MNIST.test(testImages[i])) count++;
    }
    // modificado para q ahora, si adivina correctamente count aumenta en 1
    // al final veremos cuantas respuestas correctas tuvo
    // lo q falta es modificar los valores de layers,neurons y learning rate
    // hasta q la cantidad de respuestas correctas sea maxima.
    // lo mejor que yo he encontrado es:
    // layers:2,neurons:128,learning_rate:0.01,correctas:8054
    // si consiguen mejor numero de correctas con otro setup avisen
    
    cout<<"correctas: "<<count<<"\n";
    cout<<"precision: "<<static_cast<double>(count)/10000.0<<"\n";

    return 0;
}

