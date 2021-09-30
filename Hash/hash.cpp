#include "hash.h"

constexpr int HashLength = 32; // Hash length in bytes
std::unordered_map<std::string, char> hexmap{
    {"0000", '0'},{"0001", '1'},{"0010", '2'},{"0011", '3'},
    {"0100", '4'},{"0101", '5'},{"0110", '6'},{"0111", '7'},
    {"1000", '8'},{"1001", '9'},{"1010", 'A'},{"1011", 'B'},
    {"1100", 'C'},{"1101", 'D'},{"1110", 'E'},{"1111", 'F'}
};

std::string bin_to_hex(std::string binary) {
    std::string hex;
    for (size_t i = 0; i < binary.size(); i += 4)
    {
        hex.push_back(hexmap[binary.substr(i, 4)]);
    }
    return hex;
}

std::string hash(std::string input, bool bin)
{
    int seedOffset = 0;
    for (auto& i : input)
    {
        seedOffset += i;
    }
    std::mt19937 generator(input.size() + seedOffset);
    std::uniform_int_distribution<int> distribution(0, 255);
    while (input.size() % HashLength != 0 || input.size() == 0)
    {
        input += char(distribution(generator));
    }

    std::string temp = "";
    std::vector<std::bitset<256>> blocks;
    unsigned long long iteration = 1;
    std::bitset<8> c("10110101");
    for (auto& Char : input)
    {
        temp += ((c = (std::bitset<8>(Char) << 3) ^ c) >> 1).to_string();
        if (iteration % HashLength == 0 && iteration != 0) {
            blocks.push_back(std::bitset<256>(temp));
            temp.clear();
        }
        iteration++;
    }

    std::bitset<256> hash = blocks[0];

    for (size_t i = 0; i < blocks.size() - 1; i++)
    {
        blocks[i] = ((blocks[i] ^ (blocks[i + 1] << 29)));
    }

    for (size_t i = 1; i < blocks.size(); i++)
    {
        hash ^= (((blocks[i]) << 19));
    }

    for (size_t i = hash.size() - 1; i > 0; i--)
    {
        hash[i] = hash[i] ^ hash[i - 1];
    }

    const std::string hashStr = hash.to_string();
    if (bin)
    {
        return hashStr;
    }
    return bin_to_hex(hashStr.c_str());
}

