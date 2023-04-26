#include "gtest/gtest.h"
#include "matrix.h"
#include <iostream>

class TestController : public ::testing::Test 
{
	std::streambuf* old_stdout{nullptr};
protected:
	void SetUp() 
	{
		old_stdout = std::cout.rdbuf(new_stdout.rdbuf());
	}

	void TearDown() 
	{
		old_stdout = std::cout.rdbuf(old_stdout);
	}

	std::stringstream new_stdout;
};

TEST_F(TestController, test_matrix)
{	
	Matrix<int, -1, 7> matrix;
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

	ASSERT_EQ(new_stdout.str(), "1000 999 998 997 996 995 994 7777 \n");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}