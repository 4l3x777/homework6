#include "matrix.h"
#include <cassert>


int main(int argc, char* argv[])
{
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    // print one line
    // 100100314
    for(auto c: matrix)
    {
        for(auto value: c)
        {
            std::cout << value;
        }
        std::cout << std::endl;
    }

    // Operator's `=` canonical from
    ((matrix[100][100] = 314) = 0) = 217;

    // print one line
    // 100100217
    for(auto c: matrix)
    {
        for(auto value: c)
        {
            std::cout << value;
        }
        std::cout << std::endl;
    }

    // Clear matrix
    matrix[100][100] = -1;
    assert(matrix.size() == 0);

    // N-arn matrix (N = 7)
    matrix[1000][999][998][997][996][995][994] = 7777;

    // print one line
    // 1000 999 998 997 996 995 994 7777
    for(auto c: matrix)
    {
        for(auto value: c)
        {
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
    
    // Create matrix with default value '0'
    Matrix<int, 0> matrix2;
    for(int i = 0; i < 10; i++)
    {
        matrix2[i][i] = i;
        matrix2[i][9 - i] = 9-i;
    }

    // print one line
    std::cout << matrix2.size() << std::endl;
    for(auto c: matrix2)
    {
        if (c[0] > 0 && c[1] > 0 && c[0] < 9 && c[1] < 9) 
        {
            for(auto value: c)
            {
                std::cout << value << ' ';
            }
            std::cout << std::endl;
        }
    }

    return 0;
}