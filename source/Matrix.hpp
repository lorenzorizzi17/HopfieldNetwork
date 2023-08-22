#ifndef MATRIX
#define MATRIX


#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;


class Matrix {
    private:
        vector<vector<double>> matrix_;
    public:
        //matrix ctor via a vector/vector 
        explicit Matrix(vector<vector<double>> matrix) : matrix_{matrix} {}; 
        //matrix ctor for a homogeneous matrix (all element are equal)
        Matrix(int n, double d) {                 
            vector<vector<double>> v1;
            for (int i = 0; i < n; i++)
            {
                vector<double> v2;
                for (int j = 0; j < n; j++)
                {
                    v2.push_back(d);
                }
                v1.push_back(v2);
            }
            matrix_ = v1;
        }
        //print matrix 
        void print()            
        {
            for (auto it = matrix_.begin(); it != matrix_.end(); it++)
            {
                for (auto it1 = (*it).begin(); it1 != (*it).end(); it1++)
                {
                    std::cout << *it1 << ", ";
                }
                std::cout << '\n';
            }
        }
        //getter for the ij element
        double get(int i, int j) const   
        {
            return (matrix_[i][j]);
        }
        //setter for the ij element
        double& set(int i, int j) 
        {
            return (matrix_[i][j]);
        }
        void set(int i, int j, double element) 
        {
            matrix_[i][j] = element;
        }
        //size of the matrix
        int size() const {        
            return matrix_.size();
        } 

        double getMax() const {
            std::vector<double> v;
            int N = matrix_.size();
            for (int i = 0; i < N ; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if(std::abs(this->get(i,j)-1)>0.01){
                        v.push_back(this->get(i,j));
                    }
                }
            }
            return *std::max_element(v.begin(),v.end());
        }

        double getMin() const {
            std::vector<double> v;
            int N = matrix_.size();
            for (int i = 0; i < N ; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if(std::abs(this->get(i,j)-1)>0.01){
                        v.push_back(this->get(i,j));
                    }
                }
            }
            return *std::min_element(v.begin(),v.end());
        }
}; 



#endif