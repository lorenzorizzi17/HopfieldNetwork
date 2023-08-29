#ifndef HOPNETWORK
#define HOPNETWORK

#include<assert.h>
#include <vector>
#include"Matrix.hpp"
#include"state.hpp"

class HopNetwork{
    private:
        State activationValues_;
        int N_;
        std::vector<State> storedMemories_;
        Matrix J_;
    public:
        //standard ctor
        HopNetwork(const int N): activationValues_{State(N)}, J_{Matrix(N,0)} {
            N_ = N;
        }

        int getState(int) const;

        State getVector() const;

        void setState(State);

        void setState(int, int);

        Matrix& getMatrix();

        void setMatrix(Matrix const&);

        State getMemory(int) const;

        std::vector<State> getMemories() const;

        void randomShuffle(const double);

        void evolveRandom();

        void evolveRandom2();

        double getEnergy();

        double distanceFrom(State const&);

        std::vector<double> distanceFrom(std::vector<State> const&);

        void drawL(bool const);

        void drawX();

        void drawT();

        void drawO();

        void drawZ();

        void saveAsMemory(double);

        void removeMemories();

        void evolveUntilConverge(double);

        void randomNoise(int);

        Matrix getCorrelationMatrix() const;

        void randomNoiseOnMatrix(int, double);
};


std::ostream& operator<<(std::ostream&, vector<double> const&);

#endif