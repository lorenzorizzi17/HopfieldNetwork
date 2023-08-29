#include "HopNetwork.hpp"
#include<random>
#include<iostream>

//////////////////////////////////////////////
//////////// free functions //////////////////
//////////////////////////////////////////////

std::random_device rd;
std::mt19937 g(rd());


template <class T>
int sign(T a){
    if (a>=0)
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
            ris += A.get(i, j) * v[j];
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

//absolute norm
template <class T>
double norm(vector<T> const v) { 
    double ris = 0;
    for (auto it = v.begin(); it != v.end(); it++)
    {
        ris += std::abs(*it);
    }
    return (ris);
}

//send to ostream a vector 
std::ostream& operator<<(std::ostream& os, vector<double> const& v) {
    for (auto it = v.begin(); it != v.end(); it++)   
    {
        os << *it << ", ";
    };
    os << ")" << '\n';
    return os;
}

//////////////////////////////////////////////
///////// HopNetwork member functions ///////////
//////////////////////////////////////////////

int HopNetwork::getState(int i) const{
    return activationValues_.get(i);
}

State HopNetwork::getVector() const {
    return activationValues_;
}


void HopNetwork::setState(State activationValues){
        //std::cout << "Warning: activation value should range from -1 to 1. Temporarily setting activationValue to 1";
        activationValues_ = activationValues;
}

void HopNetwork::setState(int i, int a){
    activationValues_.set(i,a);
}

Matrix& HopNetwork::getMatrix(){
    return J_;
}

void HopNetwork::setMatrix(Matrix const& J){
    J_ = J;
}

State HopNetwork::getMemory(int n) const {
    if (n < storedMemories_.size())
    {
        return storedMemories_[n];
    } else {
        std::cout << "No such memory exist";
    }
}

std::vector<State> HopNetwork::getMemories() const{
    return storedMemories_;
}

void HopNetwork::randomShuffle(const double N){
    State a = State(N);
    activationValues_= a;
}


void HopNetwork::evolveRandom(){
    std::vector<int> v(N_);
    std::iota(v.begin(),v.end(), 0);
    std::shuffle(v.begin(), v.end(), g);
    for (int i = 0; i < N_; i++)
    {
        int index = v[i];
        double res=0;
        for (int j = 0; j < N_; j++)
        {
            res += J_.get(index,j)*activationValues_.get(j);
        }
        activationValues_.set(index,sign(res));
    }
}

void HopNetwork::evolveRandom2(){
    int num = std::rand()%(N_);
    for (int i = 0; i < N_; i++)
    {
        double res=0;
        for (int j = 0; j < N_; j++)
        {
            res += J_.get(num,j)*activationValues_.get(j);
        }
        activationValues_.set(num,sign(res));
    }
}

double HopNetwork::getEnergy(){
    double E = 0;
    for (int i = 0; i < N_; i++)
    {
        for (int j = 0; j < N_; j++)
        {
            E -= J_.get(i,j)*(this->getState(i))*(this->getState(j));
        }
    }
    return E;
}

double HopNetwork::distanceFrom(State const& neur){
    auto a = (this->getVector()).getVector() - neur.getVector();
    return norm(a);
}

std::vector<double> HopNetwork::distanceFrom(std::vector<State> const& memories){
    std::vector<double> res;
    for (int i = 0; i < memories.size(); i++)
    {
        res.push_back((this->distanceFrom(memories[i])));
    }
    return res;
}

void HopNetwork::drawL(bool comple){
    int n = std::sqrt(N_);
    if (comple){
    for (int i = 0; i < N_; i++)
    {
        if (i>n*n-n)
        {
            activationValues_.set(i,1);
        } else {
            if (i%n==0)
            {
                activationValues_.set(i,1);
            }
            else {
                activationValues_.set(i,-1);
            } 
        } 
    }
    } else {
    for (int i = 0; i < N_; i++)
    {
        if (i>n*n-n)
        {
            activationValues_.set(i,-1);
        } else {
            if (i%n==0)
            {
                activationValues_.set(i,-1);
            }
            else {
                activationValues_.set(i,1);
            } 
        } 
    }
    }   
}

void HopNetwork::drawX(){
    int n = std::sqrt(N_);
    for (int i = 0; i < N_; i++)
    {
        
    int column = i%n;
    int row = (i-column)/n;
        if (row==column)
        {
            activationValues_.set(i,1);
        } else if (row+column==n-1){
            activationValues_.set(i,1);
        } else {
            activationValues_.set(i,-1);
        }
    } 
}

void HopNetwork::drawT(){
    int n = std::sqrt(N_);
    for (int i = 0; i < N_; i++)
    {
    int column = i%n;
    int row = (i-column)/n;
    if (row == 0)
    {
        activationValues_.set(i,1);
    } else if (column == n/2) {
        activationValues_.set(i,1);
    } else {
        activationValues_.set(i,-1);
    }
  }
}

void HopNetwork::drawO(){
    int n = std::sqrt(N_);
    for (int i = 0; i < N_; i++)
    {
    int column = i%n;
    int row = (i-column)/n;
    if ((row == 0)||(column == 0)||(row == n-1)||(column == n-1))
    {
        activationValues_.set(i,1);
    } else {
        activationValues_.set(i,-1);
    }
  }
}


void HopNetwork::drawZ(){
    int n = std::sqrt(N_);
    for (int i = 0; i < N_; i++) {
    int column = i%n;
    int row = (i-column)/n;
    if ((row == 0)||(row == n-1))
    {
        activationValues_.set(i,1);
    } else if (row+column==n-1){
        activationValues_.set(i,1);
    } else {
        activationValues_.set(i,-1);
    }
    
    }
}




void HopNetwork::saveAsMemory(double alpha)  {
    storedMemories_.push_back(activationValues_);
    for (int i = 0; i < N_; i++){
        for (int j = 0; j < N_; j++){
            if (j != i){
                double coefficient = J_.get(i,j)+alpha*this->getState(i)*this->getState(j);
                J_.set(i,j, coefficient);
                } else {
                J_.set(i,i,0); //self interacting term
                }
            } 
        }
}



void HopNetwork::removeMemories(){
    J_ = Matrix{N_,0};
    storedMemories_.clear();
}

void HopNetwork::evolveUntilConverge(double s){
        double E = 0;
        int j = 0;
        while (j<s)
        {
            this->evolveRandom2();
            double deltaE = E - this->getEnergy();
            if (deltaE < 0.01)
            {
                j++;
            } else {
                j=0;
            }
            E = this->getEnergy();
        }
}

void HopNetwork::randomNoise(int n){
    for (int i = 0; i < n; i++)
    {
        int a = std::rand()%N_;
        this->setState(a,this->getState(a)*(-1));
    }
}

Matrix HopNetwork::getCorrelationMatrix() const {
    int size = storedMemories_.size();
    Matrix M = Matrix{size,0};
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            double res = 0;
            for (int k =0;k< N_;k++)
            {
              res += (1/(double)N_)*storedMemories_[i].get(k)*storedMemories_[j].get(k) ;
            }
            M.set(i,j,res);
        }   
    }
    return M;
}

void HopNetwork::randomNoiseOnMatrix(int n, double value){
    for (int k = 0; k < n; k++)
    {
        int i = std::rand()%(N_);
        int j = std::rand()%(N_);
        J_.set(i,j,0);
    } 
}