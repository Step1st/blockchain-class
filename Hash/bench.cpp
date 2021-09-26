#include "bench.h"

char chararray[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890?><\"\\:{})(*&^%$#@!~/.,;'][|=-`" };

void generateFiles() {

    std::ofstream output("pairtest.txt");
    std::stringstream fileBuffer, file2Buffer, file3Buffer, file4Buffer;
    std::pair<std::string, std::string> temp;
    unsigned seed = static_cast<long unsigned int> (std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 93);

    for (size_t i = 0; i < 25000; i++)
    {
        for (int i = 0; i < 10; i++)
        {
            temp.first.push_back(chararray[(distribution(generator))]);
        }
        for (int i = 0; i < 10; i++)
        {
            temp.second.push_back(chararray[(distribution(generator))]);
        }
        fileBuffer << temp.first << " " << temp.second << std::endl;
        temp.first.clear();
        temp.second.clear();
    }

    for (size_t i = 0; i < 25000; i++)
    {
        for (int i = 0; i < 100; i++)
        {
            temp.first.push_back(chararray[(distribution(generator))]);
        }
        for (int i = 0; i < 100; i++)
        {
            temp.second.push_back(chararray[(distribution(generator))]);
        }
        fileBuffer << temp.first << " " << temp.second << std::endl;
        temp.first.clear();
        temp.second.clear();
    }

    for (size_t i = 0; i < 25000; i++)
    {
        for (int i = 0; i < 500; i++)
        {
            temp.first.push_back(chararray[(distribution(generator))]);
        }
        for (int i = 0; i < 500; i++)
        {
            temp.second.push_back(chararray[(distribution(generator))]);
        }
        fileBuffer << temp.first << " " << temp.second << std::endl;
        temp.first.clear();
        temp.second.clear();
    }

    for (size_t i = 0; i < 25000; i++)
    {
        for (int i = 0; i < 1000; i++)
        {
            temp.first.push_back(chararray[(distribution(generator))]);
        }
        for (int i = 0; i < 1000; i++)
        {
            temp.second.push_back(chararray[(distribution(generator))]);
        }
        fileBuffer << temp.first << " " << temp.second << std::endl;
        temp.first.clear();
        temp.second.clear();
    }

    output << fileBuffer.str();
    output.close();
}