#include <vector>
class Matrix {
    public:
        
        Matrix(int x, int y);

        double& loc(int i, int j);
        Image eigenvalues();

        Matrix operator*(Matrix n);
        Matrix operator*(double n);
        Matrix operator/(matrix n);
        Matrix operator/(double n);
        Matrix operator-(Matrix n);
        Matrix operator-(double n);
        Matrix operator+(Matrix n);
        Matrix operator+(double n);
    private:
        std::vector<double> m;
};
