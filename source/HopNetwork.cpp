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

//send to ostream a vector
template <class T> 
std::ostream& operator<<(std::ostream& os, vector<T> const& v) {
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

void HopNetwork::setState(std::vector<double> activationValues){
        //std::cout << "Warning: activation value should range from -1 to 1. Temporarily setting activationValue to 1";
        activationValues_ = activationValues;
}

void HopNetwork::setState(int i, int a){
    activationValues_[i] = a;
}

double HopNetwork::getState(int i) const{
    return activationValues_[i];
}

std::vector<double> HopNetwork::getVector() const {
    return activationValues_;
}

void HopNetwork::randomFill(const double N){
    for (int i = 0; i < N; i++)
    {
        int rand = (std::rand())%(10);
    if (rand <5){
        activationValues_.push_back(1.f);
    } else {
        activationValues_.push_back(-1.f);
    }
    }
}

void HopNetwork::printStatus(){
    std::cout << "[";
    for (int i = 0; i < N_-1; i++)
    {
        std::cout<< activationValues_[i] << ", ";
    }
    std::cout << activationValues_[N_-1] << "]\n";
}

void HopNetwork::evolve(Matrix const& J){
    auto supp = J*activationValues_;
    for (int i = 0; i < N_; i++)
    {
        if (supp[i] >= 0)
        {
            activationValues_[i] = 1;
        } else {
            activationValues_[i] = -1;
        }
    }
}

void HopNetwork::evolveRandom(Matrix const& J){
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

double HopNetwork::distance2From(HopNetwork const& neur){
    auto a = (this->getVector())-neur.getVector();
    return norm2(a);
}

void HopNetwork::drawL(bool comple){
    int n = std::sqrt(N_);
    if (comple){
    for (int i = 0; i < N_; i++)
    {
        if (i>n*n-n)
        {
            activationValues_[i]=1;
        } else {
            if (i%n==0)
            {
                activationValues_[i]=1;
            }
            else {
                activationValues_[i] = -1;
            } 
        } 
    }
    } else {
    for (int i = 0; i < N_; i++)
    {
        if (i>n*n-n)
        {
            activationValues_[i]=-1;
        } else {
            if (i%n==0)
            {
                activationValues_[i]=-1;
            }
            else {
                activationValues_[i] = 1;
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
            activationValues_[i] = 1;
        } else if (row+column==n-1){
            activationValues_[i] = 1;
        } else {
            activationValues_[i] = -1;
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
        activationValues_[i] = 1;
    } else if (column == n/2) {
        activationValues_[i] = 1;
    } else {
        activationValues_[i] = -1;
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
        activationValues_[i] = 1;
    } else {
        activationValues_[i] = -1;
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
        activationValues_[i] = 1;
    } else if (row+column==n-1){
        activationValues_[i] = 1;
    } else {
        activationValues_[i] =-1;
    }
    
    }
}

void HopNetwork::evolveRandom2(Matrix const& J){
    int num = std::rand()%(N_);
    for (int i = 0; i < N_; i++)
    {
        double res=0;
        for (int j = 0; j < N_; j++)
        {
            res += J.get(num,j)*activationValues_[j];
        }
        activationValues_[num] = sign(res);
    }
}

double HopNetwork::printEnergy(Matrix const& J){
    double E = 0;
    for (int i = 0; i < N_; i++)
    {
        for (int j = 0; j < N_; j++)
        {
            E -= J.get(i,j)*(this->getState(i))*(this->getState(j));
        }
    }
    return E;
}


void HopNetwork::saveAsMemory(std::vector<HopNetwork>& memories, Matrix& J, double alpha) const {
    
    memories.push_back(*this);
    for (int i = 0; i < N_; i++){
        for (int j = 0; j < N_; j++){
            if (j != i){
                double coefficient = J.get(i,j)+alpha*this->getState(i)*this->getState(j);
                J.set(i,j, coefficient);
                } else {
                J.set(i,i,0); //self interacting term
                }
            } 
        }
}

std::vector<double> HopNetwork::distance2From(std::vector<HopNetwork> const& memories){
    std::vector<double> res;
    for (int i = 0; i < memories.size(); i++)
    {
        res.push_back((this->distance2From(memories[i])));
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, vector<double> const& v) {
    for (auto it = v.begin(); it != v.end(); it++)      //stampa a schermo il vettore
    {
        os << *it << ", ";
    };
    os << ")" << '\n';
    return os;
}

void HopNetwork::removeMemories(std::vector<HopNetwork>& memories, Matrix& J){
    J = Matrix{N_,0};
    memories.clear();
}

void HopNetwork::evolveUntilConverge(double s, Matrix const& J){
        double E = 0;
        int j = 0;
        while (j<s)
        {
            this->evolveRandom2(J);
            double deltaE = E - this->printEnergy(J);
            if (deltaE < 0.01)
            {
                j++;
            } else {
                j=0;
            }
            E = this->printEnergy(J);
        }
}