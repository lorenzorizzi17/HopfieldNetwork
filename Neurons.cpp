#include "Neurons.hpp"
#include<random>
#include<iostream>

//overloading operator*. Implements the product matrix-vector
template <class T>
vector<double> operator*(Matrix const& A, vector<T> const& v)  
{
    vector<double> result;
    for (int i = 1; i <=  static_cast<int>(v.size()); i++)
    {
        double ris = 0;
        for (int j = 1; j <=  static_cast<int>(v.size()); j++)
        {
            ris = ris + (A.get(i, j) * v[j-1]);
        }
        result.push_back(ris);
    }
    return result;
}

//overloading vector difference
template <class T>
vector<T> operator-(vector<T> v1, vector<T> v2) { 
     vector<T> result;
     for (int i = 0; i < static_cast<int>(v1.size()); i++)
     {
        result.push_back(v1[i]-v2[i]);
     }
     return result;
}

template <class T>
double norm2(vector<T> const v) { //funzione norma quadratica
    double ris = 0;
    for (auto it = v.begin(); it != v.end(); it++)
    {
        ris += (*it)*(*it);
    }
    return sqrt(ris);
}

void Neurons::setState(std::vector<int> activationValues){
        //std::cout << "Warning: activation value should range from -1 to 1. Temporarily setting activationValue to 1";
        activationValues_ = activationValues;
}

int Neurons::getState(int i) const{
    return activationValues_[i];
}

std::vector<int> Neurons::getVector() const {
    return activationValues_;
}


void Neurons::randomFill(const int N){
    for (int i = 0; i < N; i++)
    {
        int rand = (std::rand())%(10);
    if (rand <5){
        activationValues_.push_back(1);
    } else {
        activationValues_.push_back(-1);
    }
    }
}

void Neurons::printStatus(){
    std::cout << "[";
    for (int i = 0; i < N_-1; i++)
    {
        std::cout<< activationValues_[i] << ", ";
    }
    std::cout << activationValues_[N_-1] << "]\n";
}

void Neurons::evolve(Matrix const& J){
    auto supp = J*activationValues_;
    for (int i = 0; i < N_; i++)
    {
        if (supp[i]>0)
        {
            activationValues_[i] = 1;
        } else {
            activationValues_[i] = -1;
        }
    }
    
}


double Neurons::distance2From(Neurons const& neur){
    auto a = (this->getVector())-neur.getVector();
    return norm2(a);
}