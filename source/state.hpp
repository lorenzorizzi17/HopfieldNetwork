#include<vector>

class State {
    private:
    std::vector<int> state_;

    public:
    State(std::vector<int> state) : state_{state}{};
    //minimal constructor
    State(int N){
        this->randomShuffle(N);
    }

    void randomShuffle(int);

    int get(int) const;

    std::vector<int> getVector() const;

    void set(int,int);

    

};