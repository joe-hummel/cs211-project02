/*main.cpp*/

/**
  * @brief main testing harness for googletest unit tests
  *
  * @author Prof. Joe Hummel
  * @note Northwestern University
  */
  
#include <iostream>

#include "gtest/gtest.h"

using namespace std;


int main()
{
    ::testing::InitGoogleTest();

    //
    // run all the tests, returns 0 if they
    // all pass and 1 if any fail:
    //
    int test_results = RUN_ALL_TESTS();

    return test_results;
}

