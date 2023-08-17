#include "state.hpp"
#include<random>


void State::randomShuffle(int N){
    for (int i = 0; i < N; i++)
    {
        int rand = (std::rand())%(10);
    if (rand <5){
        state_.push_back(1);
    } else {
        state_.push_back(-1);
    }
    }
}

int State::get(int i) const {
    return state_[i];
}

std::vector<int> State::getVector() const {
    return state_;
}

void State::set(int i, int a){
    state_[i] = a;
}