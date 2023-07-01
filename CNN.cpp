#include "CNN.h"

double sigmoid(double x){
    double ret;
    ret=1/(1+exp(-x));
    return ret;
}

double sigmoid_derivative(double x){
    double n=sigmoid(x);
    return n*(1.0-n);
}

layer::layer(int num,int siz,int next){
    n=num;
    size=siz;
    neurons.resize(size);
    for(int i=0;i<size;i++){
        neurons[i]=neuron(next);
    }
}

neuron::neuron(){}

neuron::neuron(int l){
    l_size=l;
    weights=vector<double>(l_size);
    for(int i=0;i<weights.size();i++){
        weights[i]=0;
    }
    value=0;
}