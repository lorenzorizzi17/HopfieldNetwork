#include "Neurons.hpp"
#include<random>
#include<iostream>

//////////////////////////////////////////////
//////////// free functions //////////////////
//////////////////////////////////////////////

std::random_device rd;
std::mt19937 g(rd());


template <class T>
int sign(T a){
    if (a>0)
    {
        return 1;
    } else {
        return -1;
    }
}

//////////////////////////////////////////////
/////////// algebraic functions //////////////
//////////////////////////////////////////////

//overloading operator*. Implements the product matrix-vector
template <class T>
vector<double> operator*(Matrix const& A, vector<T> const& v)  
{
    vector<double> result;
    for (int i = 0; i <  static_cast<int>(v.size()); i++)
    {
        double ris = 0;
        for (int j = 0; j <  static_cast<int>(v.size()); j++)
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

//quadratic norm
template <class T>
double norm2(vector<T> const v) { 
    double ris = 0;
    for (auto it = v.begin(); it != v.end(); it++)
    {
        ris += (*it)*(*it);
    }
    return sqrt(ris);
}


//////////////////////////////////////////////
///////// neurons member functions ///////////
//////////////////////////////////////////////

void Neurons::setState(std::vector<int> activationValues){
        //std::cout << "Warning: activation value should range from -1 to 1. Temporarily setting activationValue to 1";
        activationValues_ = activationValues;
}

void Neurons::setState(int i, int a){
    activationValues_[i] = a;
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

void Neurons::evolveRandom(Matrix const& J){
    std::vector<int> v(N_);
    std::iota(v.begin(),v.end(), 0);
    std::shuffle(v.begin(), v.end(), g);
    for (int i = 0; i < N_; i++)
    {
        int index = v[i];
        double res=0;
        for (int j = 0; j < N_; j++)
        {
            res += J.get(index,j)*activationValues_[j];
        }
        activationValues_[index] = sign(res);
    }
}

double Neurons::distance2From(Neurons const& neur){
    auto a = (this->getVector())-neur.getVector();
    return norm2(a);
}

