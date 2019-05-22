#include <iostream>
#include <random>

using namespace std;

int main()
{
    std::default_random_engine gen;
    gen.seed(42);
    std::binomial_distribution<unsigned int> bin(10, 0.7);
    std::cout << bin(gen) << std::endl;
    return 0;
}
