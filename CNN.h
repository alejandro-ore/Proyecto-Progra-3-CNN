#ifndef PROYECTO_V0_CNN_H
#define PROYECTO_V0_CNN_H

#include "ReadImage.h"
#include <random>
#include <thread>
#include <queue>
using namespace std;

double sigmoid(double x);

double sigmoid_derivative(double x);

class layer;

class neuron{
private:
    double value;
    vector<double> weights;
    double error;
    double bias;
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
public:
    layer(int num,int siz,int next);
    friend class neuron;
    friend class CNN;
};

class CNN{
private:
    vector<layer> layers;
    template<typename func,typename ...Args>
    void callable_layer(layer &l,func call,Args... args){
        queue<thread> threads;
        int n_threads=min(l.size,16);
        int n_size=l.neurons.size()/n_threads;
        int rest=0;
        for(int j=0;j<l.neurons.size();j+=n_size){
            if(j+n_size+l.neurons.size()%n_threads>=l.neurons.size()) rest=l.neurons.size()%n_threads;
            threads.emplace(call,l.neurons.begin()+j,l.neurons.begin()+j+n_size+rest,args...);
            if(rest!=0) break;
        }
        while(!threads.empty()){
            threads.front().join();
            threads.pop();
        }
    }
    void forward_propagation(Image *img){
        auto setup=[](vector<neuron>::iterator it1,vector<neuron>::iterator it2,Image *im,vector<neuron> *v){
            for(auto it=it1;it!=it2;it++){
                it->value=static_cast<double>(im->img_data[distance(v->begin(),it)])/static_cast<double>(255);
            }
        };
        callable_layer(layers[0],setup,img,&layers[0].neurons);
        auto forward=[this](vector<neuron>::iterator it1,vector<neuron>::iterator it2,int prev,vector<neuron> *v){
            int j=distance(v->begin(),it1);
            for(auto it=it1;it!=it2;it++){
                double sum=0;
                for(int i=0;i<layers[prev].neurons.size();i++){
                    sum+=layers[prev].neurons[i].weights[j]*layers[prev].neurons[i].value;
                }
                j++;
                sum+=it->bias;
                it->value=sigmoid(sum);
            }
        };
        for(int i=1;i<layers.size();i++){
            callable_layer(layers[i],forward,i-1,&layers[i].neurons);
        }
    }
    void backward_propagation(int label){
        for(int i=0;i<10;i++){
            layers[layers.size()-1].neurons[i].error=
                    (i==label)-layers[layers.size()-1].neurons[i].value;
        }
        auto back=[this](vector<neuron>::iterator it1,vector<neuron>::iterator it2,int next){
            for(auto it=it1;it!=it2;it++){
                double sum=0;
                for(int i=0;i<layers[next].neurons.size();i++){
                    sum+=it->weights[i]*layers[next].neurons[i].error;
                }
                it->error=sum;
            }
        };
        for(int i=layers.size()-2;i>=1;i--){
            callable_layer(layers[i],back,i+1);
        }
    }
    void gradient_descent(double rate){
        auto gd=[this,rate](vector<neuron>::iterator it1,vector<neuron>::iterator it2,int prev,vector<neuron> *v){
            int j=distance(v->begin(),it1);
            for(auto it=it1;it!=it2;it++){
                for(int i=0;i<layers[prev].neurons.size();i++){
                    double gradient=it->error*sigmoid_derivative(it->value);
                    double update=rate*gradient*layers[prev].neurons[i].value;
                    layers[prev].neurons[i].weights[j]+=update;
                }
                it->bias+=rate*it->error;
                j++;
            }
        };
        for(int i=1;i<layers.size();i++){
            callable_layer(layers[i],gd,i-1,&layers[i].neurons);
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
        layers.emplace_back(1,28*28,n);
        for(int i=1;i<l;i++){
            layers.emplace_back(i+1,n,n);
        }
        layers.emplace_back(l+1,n,10);
        layers.emplace_back(l,10,0);
    }
    void train(vector<TrainImage> &training,double rate){
        random_device rd;
        mt19937 generator(rd());
        uniform_real_distribution<double> weight_distribution(-1.0,1.0);
        uniform_real_distribution<double> bias_distribution(-0.1,0.1);
        double scale=sqrt(1.0/(28*28+10));
        auto setup=[&scale,&generator,&weight_distribution,&bias_distribution](vector<neuron>::iterator it1,vector<neuron>::iterator it2){
            for(auto it=it1;it!=it2;it++){
                it->bias=bias_distribution(generator);
                for(int i=0;i<it->weights.size();i++){
                    it->weights[i]=weight_distribution(generator)*scale;
                }
            }
        };
        for(int i=0;i<layers.size();i++){
            callable_layer(layers[i],setup);
        }
        cout<<"Starting training...\n";
        for(TrainImage &image:training){
            forward_propagation(&image);
            backward_propagation(image.get_label());
            gradient_descent(rate);
        }
        cout<<"Training complete!\n\n";
    }
    bool test(TestImage &image){
        forward_propagation(&image);
        if(image.get_label()==result()) return true;
        else return false;
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
