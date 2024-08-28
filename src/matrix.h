#include <vector>
class Matrix {
    public:
        
        Matrix(int x, int y);
        Matrix(const Matrix& mtx);

        double& loc(int i, int j);
        Matrix eigenvalues();
        // https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading/4421719#4421719
        // Last accessed [2024-08-28]
        Matrix& operator*=(const Matrix& n);
        Matrix& operator*=(const double& n);

        Matrix& operator/=(const Matrix& n);
        Matrix& operator/=(const double& n);

        Matrix& operator-=(const Matrix& n);
        Matrix& operator-=(const double& n);

        Matrix& operator+=(const Matrix& n);
        Matrix& operator+=(const double& n);


        friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
        friend Matrix operator*(const double& lhs, const Matrix& rhs);
        friend Matrix operator*(const Matrix& lhs, const double& rhs);

        friend Matrix operator/(const Matrix& lhs, const Matrix& rhs);
        friend Matrix operator/(const double& lhs, const Matrix& rhs);
        friend Matrix operator/(const Matrix& lhs, const double& rhs);

        friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
        friend Matrix operator-(const double& lhs, const Matrix& rhs);
        friend Matrix operator-(const Matrix& lhs, const double& rhs);

        friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
        friend Matrix operator+(const double& lhs, const Matrix& rhs);
        friend Matrix operator+(const Matrix& lhs, const double& rhs);

        int X, Y;
    private:
        std::vector<double> m;
};
