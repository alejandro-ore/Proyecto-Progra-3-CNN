#ifndef PROYECTO_V0_CNN_H
#define PROYECTO_V0_CNN_H

#include "ReadImage.h"
using namespace std;

double sigmoid(double x);

double sigmoid_derivative(double x);

class layer;

class neuron{
private:
    double value;
    vector<double> weights;
    double error;
    int l_size;
public:
    neuron();
    neuron(int l);
    friend class layer;
    friend class CNN;
};

class layer{
private:
    int n;
    int size;
    vector<neuron> neurons;
    double bias;
public:
    layer(int num,int siz,int next);
    friend class neuron;
    friend class CNN;
};

class CNN{
private:
    vector<layer> layers;
    void forward_propagation(){
        for(int i=1;i<layers.size();i++){
            for(int j=0;j<layers[i].neurons.size();j++){
                double sum=0;
                for(int k=0;k<layers[i-1].neurons.size();k++){
                    sum+=layers[i-1].neurons[k].weights[j]*layers[i-1].neurons[k].value;
                }
                layers[i].neurons[j].value=sigmoid(sum);
            }
        }
    }
    void backward_propagation(int label){
        for(int i=0;i<10;i++){
            layers[layers.size()-1].neurons[i].error=
                    (i==label)-layers[layers.size()-1].neurons[i].value;
        }
        for(int i=layers.size()-2;i>=1;i--){
            for(int j=0;j<layers[i].neurons.size();j++){
                double sum=0;
                for(int k=0;k<layers[i+1].neurons.size();k++){
                    sum+=layers[i].neurons[j].weights[k]*layers[i+1].neurons[k].error;
                }
                layers[i].neurons[j].error=sum;
            }
        }
    }
    void gradient_descent(double rate){
        for(int i=1;i<layers.size();i++){
            for(int j=0;j<layers[i].neurons.size();j++){
                for(int k=0;k<layers[i-1].neurons.size();k++){
                    double gradient=layers[i].neurons[j].error*sigmoid_derivative(layers[i].neurons[j].value);
                    double update=rate*gradient*layers[i-1].neurons[k].value;
                    layers[i-1].neurons[k].weights[j]+=update;
                }
            }
        }
    }
    int result(){
        int n=0;
        int last=layers.size()-1;
        for(int i=0;i<10;i++){
            if(layers[last].neurons[i].value>layers[last].neurons[n].value){
                n=i;
            }
        }
        return n;
    }
public:
    CNN(int l,int n){
        layers.push_back(layer(1,28*28,n));
        for(int i=1;i<l;i++){
            layers.push_back(layer(i+1,n,n));
        }
        layers.push_back(layer(l+1,n,10));
        layers.push_back(layer(l,10,0));
    }
    void train(vector<TrainImage> training,double rate){
        random_device rd;
        mt19937 generator(rd());
        uniform_real_distribution<double> distribution(-1.0,1.0);
        double scale=sqrt(1.0/(28*28+10));
        for(int i=0;i<layers.size();i++){
            for(int j=0;j<layers[i].neurons.size();j++){
                for(int k=0;k<layers[i].neurons[j].weights.size();k++){
                    layers[i].neurons[j].weights[k]=distribution(generator)*scale;
                }
            }
        }
        cout<<"Starting training...\n";
        for(TrainImage image:training){
            for(int i=0;i<layers[0].neurons.size();i++){
                layers[0].neurons[i].value=static_cast<double>(image.img_data[i])/static_cast<double>(255);
            }
            forward_propagation();
            backward_propagation(image.get_label());
            gradient_descent(rate);
        }/*
        cout<<"label: "<<training[training.size()-1].get_label()<<"\n";
        training[training.size()-1].print();
        print();*/
        cout<<"Training complete!\n\n";
    }
    void test(TestImage image){
        for(int i=0;i<layers[0].neurons.size();i++){
            layers[0].neurons[i].value=static_cast<double>(image.img_data[i])/static_cast<double>(255);
        }
        forward_propagation();
        cout<<"Expected result: "<<image.get_label()<<"\n";
        image.print();
        cout<<"Obtained result: "<<result()<<"\n";
        cout<<"Accuracy: "<<layers[layers.size()-1].neurons[result()].value<<"\n";
    }
    void print(){
        for(auto i:layers){
            for(auto j:i.neurons){
                cout<<j.value<<" ";
            }
            cout<<"\n";
        }
    }
};

#endif //PROYECTO_V0_CNN_H
