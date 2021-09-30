#include "bench.h"

char chararray[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890?><\"\\:{})(*&^%$#@!~/.,;'][|=-`" };

void generateRandomPairs() {

    
    std::fstream test("pairtestR.txt");
    if (test.fail())
    {
        std::stringstream fileBuffer;
        std::ofstream output("pairtestR.txt");
        generatePairsR(fileBuffer, 10);
        generatePairsR(fileBuffer, 100);
        generatePairsR(fileBuffer, 500);
        generatePairsR(fileBuffer, 1000);

        output << fileBuffer.str();
        output.close();
    }
    test.close();
}

void generateSimilarPairs() {

    
    std::fstream test("pairtestS.txt");
    if (test.fail())
    {
        std::stringstream fileBuffer;
        std::ofstream output("pairtestS.txt");
        generatePairsS(fileBuffer, 10);
        generatePairsS(fileBuffer, 100);
        generatePairsS(fileBuffer, 500);
        generatePairsS(fileBuffer, 1000);

        output << fileBuffer.str();
        output.close();
    }
    test.close();
}

void generatePairsR(std::stringstream& Buffer, int n) {

    std::pair<std::string, std::string> strPair;
    unsigned seed = static_cast<long unsigned int> (std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 91);

    for (size_t i = 0; i < 25000; i++)
    {
        if (i != 0) {
            Buffer << std::endl;
        }
        for (int i = 0; i < n; i++)
        {
            strPair.first.push_back(chararray[(distribution(generator))]);
        }
        for (int i = 0; i < n; i++)
        {
            strPair.second.push_back(chararray[(distribution(generator))]);
        }
        Buffer << strPair.first << " " << strPair.second;
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
        if (i != 0) {
            Buffer << std::endl;
        }
        for (int i = 0; i < n; i++)
        {
            strPair.first.push_back(chararray[(distribution(generator))]);
        }

        strPair.second = strPair.first;

        std::bitset<8> temp = std::bitset<8>(strPair.second[0]);
        temp[0] = temp[0] ^ 1;
        strPair.second[0] = temp.to_string()[0];
        Buffer << strPair.first << " " << strPair.second;
        strPair.first.clear();
        strPair.second.clear();
    }
}

void generateFile() {
    unsigned seed = static_cast<long unsigned int> (std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 255);

    std::ofstream output("largeFile.txt");
    std::stringstream fileBuffer;

    for (size_t i = 0; i < 10000; i++)
    {
        fileBuffer << char(distribution(generator));
    }

    output << fileBuffer.str();
    output.close();
}