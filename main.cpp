#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "util.cpp"

#include "algo\rank.cpp"
#include "algo\berlekamp_massey.cpp"
#include "algo\dfft.cpp"

#include "test\test.cpp"
#include "test\monobit_frequency_test.cpp"
#include "test\frequency_test_within_a_block.cpp"
#include "test\poker_test.cpp"
#include "test\serial_test.cpp"
#include "test\runs_test.cpp"
#include "test\runs_distribution_test.cpp"
#include "test\test_for_the_longest_run_of_ones_in_a_block.cpp"
#include "test\binary_derivative_test.cpp"
#include "test\autocorrelation_test.cpp"
#include "test\binary_matrix_rank_test.cpp"
#include "test\cumulative_test.cpp"
#include "test\approximate_entropy_test.cpp"
#include "test\linear_complexity_test.cpp"
#include "test\Maurers_universal_test.cpp"
#include "test\Discrete_Fourier_Transform_test.cpp"

#include "testsuit.cpp"

default_random_engine generator(time(NULL));
uniform_int_distribution<int> distribution(0, 1);

vector<bool> v;
int main(int argc, char* argv[]){
    if (argc<=1){
        srand(time(NULL));
        for (int i=0;i<1000000;i++){
            v.push_back(distribution(generator));
        }


    } else {
        fstream f(argv[1]);
        char c;
        while (f>>c){
            if (c=='0') v.push_back(false);
            else if(c=='1') v.push_back(true);
            else {
                cout<< "Invalid character!"<<endl;
                return 0;
            }
        }
    }

    testSuit::initDefaultTests();
    testSuit::runTest(v);

    return 0;
}

