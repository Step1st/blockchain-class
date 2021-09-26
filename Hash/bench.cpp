#include "bench.h"

void generateRandom(std::string fileName) {
    std::ifstream test;
    test.open(fileName.append(".txt"));
    test.close();
    if (test.fail())
    {
        std::ofstream output(fileName);
        std::string temp;
        std::stringstream endBuffer;
        unsigned seed = static_cast<long unsigned int> (std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(0, 255);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i <= 2000; i++)
        {
            endBuffer << char(distribution(generator));
        }
        endBuffer << std::endl;

        output << endBuffer.str();
        output.close();
    }
}