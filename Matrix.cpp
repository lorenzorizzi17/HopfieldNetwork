#include"Matrix.hpp"

//overloading operator*. Implements the product matrix-matrix
Matrix operator*(Matrix const& A, Matrix const& B)         
{
    Matrix result{A.size(),0};
    for (int i = 0; i <  A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            for (int z = 0; z < A.size(); z++) {
               result.set(i,j) += A.get(i,z)*B.get(z,j);
            }
        }
    }
    return result;
}

Matrix operator+(Matrix const& A, Matrix const& B) //overload di operator+. Implementa la somma matrice per matrice
{
    Matrix result{A.size(),0};
    for (int i = 0; i <  A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            result.set(i,j) += A.get(i,j)+B.get(i,j);
        }
    }
    return result;
}



double norm(vector<double> const v) {  //funzione norma lineare
    double ris;
    for (auto it = v.begin(); it != v.end(); it++)
    {
        ris+= (*it);
    }
    return ris;
}



/* Matrix makeDiagonal(int n, vector<double> v) {      //crea una matrice diagonale di n colonne e righe in base al vettore v
    auto result = Matrix{n,0};
    for (int i = 1; i <= n; i++)
    {
        result.set(i,i) = v[i-1];
    }
    return result;
} */

Matrix operator*(double a, Matrix const& A) {      //overload di operator*. Implementa il prodotto scalare per matrice
    Matrix result{A.size(),1};
    for (int i = 1; i <= A.size(); i++)
    {
        for (int j = 1; j <= A.size(); j++)
        {
            result.set(i,j) = A.get(i,j)*a;
        }
    }
    return result;
}

Matrix transpose(Matrix const& A) {      //effettua la trasposta
    auto result = Matrix{A.size(),0};
    for (int i = 1; i <= A.size(); i++)
    {
        for (int j = 1; j <= A.size(); j++)
        {
            result.set(i,j) = A.get(j,i);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, vector<double> const& v) {
    for (auto it = v.begin(); it != v.end(); it++)      //stampa a schermo il vettore
    {
        os << *it << ", ";
    };
    os << ")" << '\n';
    return os;
}