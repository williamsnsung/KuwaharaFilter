#include <vector>
class Matrix {
    public:
        
        Matrix(int x, int y);
        Matrix(Matrix mtx);

        double& loc(int i, int j);
        Image eigenvalues();
        // https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading/4421719#4421719
        // Last accessed [2024-08-28]
        Matrix operator*=(Matrix n);
        Matrix operator*=(double n);
        Matrix operator/=(matrix n);
        Matrix operator/=(double n);
        Matrix operator-=(Matrix n);
        Matrix operator-=(double n);
        Matrix operator+=(Matrix n);
        Matrix operator+=(double n);

        int X, Y;
    private:
        std::vector<double> m;
};
