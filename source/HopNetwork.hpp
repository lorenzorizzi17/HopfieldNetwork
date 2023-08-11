#ifndef HOPNETWORK
#define HOPNETWORK

#include<assert.h>
#include <vector>
#include"Matrix.hpp"


class HopNetwork{
    private:
        std::vector<double> activationValues_;
        int N_;
    public:
        //standard ctor
        HopNetwork(const int N) {
            N_ = N;
            this->randomFill(N);
        }

        HopNetwork(std::vector<double> ActivationValues){
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

        double distance2From(HopNetwork const&);

        std::vector<double> distance2From(std::vector<HopNetwork> const&);

        void drawL(bool const);

        void drawX();

        void drawT();

        void drawO();

        void drawZ();

        double printEnergy(Matrix const&);

        void saveAsMemory(std::vector<HopNetwork>&, Matrix&, double) const;

        void removeMemories( std::vector<HopNetwork>&, Matrix&);
};

std::ostream& operator<<(std::ostream&, vector<double> const&);

#endif