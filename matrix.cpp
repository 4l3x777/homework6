#include "matrix.h"
#include <cassert>


int main(int argc, char* argv[])
{
    Matrix<int, -1, 2> matrix1;
    assert(matrix1.size() == 0);
    auto a = matrix1[0][0];
    assert(a == -1);
    assert(matrix1.size() == 0);
    matrix1[100][100] = 314;
    assert(matrix1[100][100] == 314);
    assert(matrix1.size() == 1);

    // print one line
    // 100100314
    for(auto c: matrix1)
    {
        for(auto value: c)
        {
            std::cout << value;
        }
        std::cout << std::endl;
    }

    // Operator's `=` canonical form
    ((matrix1[100][100] = 314) = 0) = 217;

    // print one line
    // 100100217
    for(auto c: matrix1)
    {
        for(auto value: c)
        {
            std::cout << value;
        }
        std::cout << std::endl;
    }

    // Clear matrix
    matrix1[100][100] = -1;
    assert(matrix1.size() == 0);

    // N-arn matrix (N = 7)
    Matrix<int, -1, 7> matrix2;
    matrix2[1000][999][998][997][996][995][994] = 7777;

    // print one line
    // 1000 999 998 997 996 995 994 7777
    for(auto c: matrix2)
    {
        for(auto value: c)
        {
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }

    // Create matrix with default value '0'
    Matrix<int, 0, 2> matrix3;
    for(int i = 0; i < 10; i++)
    {
        matrix3[i][i] = i;
        matrix3[i][9 - i] = 9-i;
    }

    // print result
    std::cout << matrix3.size() << std::endl;
    for(auto c: matrix3)
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