#ifndef NEURONS
#define NEURONS

#include<assert.h>
#include <vector>
#include"Matrix.hpp"


class Neurons{
    private:
        std::vector<double> activationValues_;
        int N_;
    public:
        //standard ctor
        Neurons(const int N) {
            N_ = N;
            this->randomFill(N);
        }

        Neurons(std::vector<double> ActivationValues){
            activationValues_ = ActivationValues;
            N_ = ActivationValues.size();
        }

        double getState(int) const;

        std::vector<double> getVector() const;

        void setState(std::vector<double>);

        void setState(int, int);

        void randomFill(const double);

        void printStatus();
        
        void evolve(Matrix const&);

        void evolveRandom(Matrix const&);

        void evolveRandom2(Matrix const&);

        double distance2From(Neurons const&);

        void drawL(bool const);

        void drawX();

        void drawT();

        void drawO();

        void drawZ();

        double printEnergy(Matrix const&);
};

#endif