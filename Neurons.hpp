#ifndef NEURONS
#define NEURONS

#include<assert.h>
#include <vector>
#include"Matrix.hpp"


class Neurons{
    private:
        std::vector<int> activationValues_;
        int N_;
    public:
        //standard ctor
        Neurons(const int N) {
            N_ = N;
            this->randomFill(N);
        }

        Neurons(std::vector<int> ActivationValues){
            activationValues_ = ActivationValues;
            N_ = ActivationValues.size();
        }

        int getState(int) const;

        std::vector<int> getVector() const;

        void setState(std::vector<int>);

        void setState(int, int);

        void randomFill(const int);

        void printStatus();
        
        void evolve(Matrix const&);

        void evolveRandom(Matrix const&);

        double distance2From(Neurons const&);

};

#endif