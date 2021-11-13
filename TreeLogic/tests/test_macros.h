#pragma once
#define IS_TRUE(x) { if (!(x)) {std::cout << __FUNCTION__ << " failed on line " << __LINE__ << "\n";}else{ std::cout << "Passed\n";} }
#define TEST_WARNING { std::cout << "\t Expected warning: "; }
#define TEST_ERROR { std::cout << "\t Expected error: "; }
