#include "bench.h"

char chararray[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890?><\"\\:{})(*&^%$#@!~/.,;'][|=-`" };

void generateRandomPairs() {

    std::ofstream output("pairtestR.txt");
    std::stringstream fileBuffer;

    generatePairsR(fileBuffer, 10);
    generatePairsR(fileBuffer, 100);
    generatePairsR(fileBuffer, 500);
    generatePairsR(fileBuffer, 1000);

    output << fileBuffer.str();
    output.close();
}

void generateSimilarPairs() {

    std::ofstream output("pairtestS.txt");
    std::stringstream fileBuffer;

    generatePairsS(fileBuffer, 10);
    generatePairsS(fileBuffer, 100);
    generatePairsS(fileBuffer, 500);
    generatePairsS(fileBuffer, 1000);

    output << fileBuffer.str();
    output.close();
}

void generatePairsR(std::stringstream& Buffer, int n) {

    std::pair<std::string, std::string> strPair;
    unsigned seed = static_cast<long unsigned int> (std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 91);

    for (size_t i = 0; i < 25000; i++)
    {
        for (int i = 0; i < n; i++)
        {
            strPair.first.push_back(chararray[(distribution(generator))]);
        }
        for (int i = 0; i < n; i++)
        {
            strPair.second.push_back(chararray[(distribution(generator))]);
        }
        Buffer << strPair.first << " " << strPair.second << std::endl;
        strPair.first.clear();
        strPair.second.clear();
    }
}

void generatePairsS(std::stringstream& Buffer, int n) {
    std::pair<std::string, std::string> strPair;
    unsigned seed = static_cast<long unsigned int> (std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 92);

    for (size_t i = 0; i < 25000; i++)
    {
        for (int i = 0; i < n; i++)
        {
            strPair.first.push_back(chararray[(distribution(generator))]);
        }

        strPair.second = strPair.first;

        char temp = chararray[distribution(generator)];
        while (strPair.second[0] == temp)
        {
            temp = chararray[distribution(generator)];
        }
        strPair.second[0] = temp;
        Buffer << strPair.first << " " << strPair.second << std::endl;
        strPair.first.clear();
        strPair.second.clear();
    }
}