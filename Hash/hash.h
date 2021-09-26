#include <string>
#include <bitset>
#include <vector>
#include <random>
#include <unordered_map>
#include <algorithm>


constexpr int HashLength = 32; // Hash length in bytes
std::unordered_map<std::string, char> hexmap{
    {"0000", '0'},{"0001", '1'},{"0010", '2'},{"0011", '3'},{"0100", '4'},{"0101", '5'},{"0110", '6'},{"0111", '7'},{"1000", '8'},{"1001", '9'},{"1010", 'A'},{"1011", 'B'},{"1100", 'C'},{"1101", 'D'},{"1110", 'E'},{"1111", 'F'}
};

std::string bin_to_hex(std::string binary) {
    //std::stringstream hex;
    //for (size_t i = 0; i < text.size(); i+=4)
    //{
    //    std::bitset<4> temp(text.substr(i, 4));
    //    hex << std::hex << temp.to_ulong();
    //}
    //return hex.str();

    std::string hex;
    for (size_t i = 0; i < binary.size(); i+=4)
    {
        hex.push_back(hexmap[binary.substr(i, 4)]);
    }
    return hex;
}

std::string hash(std::string input)
{
    int offset = 0;
    for (auto& i : input)
    {
        offset = std::stoi(std::to_string(i));
    }
    std::mt19937 generator(input.size() + offset);
    std::uniform_int_distribution<int> distribution(0,255);
    while (input.size() % HashLength != 0 || input.size() == 0)
    {
        input += char(distribution(generator));
    }

    std::string temp = "";
    std::vector<std::bitset<256>> blocks;
    long long i = 1;
    std::bitset<8> c("10110101");
    std::bitset<8> temps;
    for (auto& Char : input)
    {
        temps = ((c = (std::bitset<8>(Char) << 3) ^ c) >> 1);
        c = ~c;
        temp += (temps).to_string();
        if (i % HashLength == 0 && i != 0) {
            std::rotate(temp.rbegin(), temp.rbegin() + 1, temp.rend());
            blocks.push_back(std::bitset<256>(temp));
            temp.clear();
        }
        i++;
    }

    std::bitset<256> hash = blocks[0];

    for (size_t i = 0; i < 1000; i++)
    {
        for (size_t i = 0; i < blocks.size() - 1; i++)
        {
            blocks[i] ^= blocks[i + 1];
        }
    }

    for (size_t i = 1; i < blocks.size(); i++)
    {
        hash ^= (((blocks[i]) << 19));
    }

    //for (size_t i = 0; i < hash.size() - 1; i++)
    //{
    //    hash[i] = hash[i] ^ hash[i + 1];
    //}

    for (size_t i = 0; i < 1000; i++)
    {
        for (size_t i = hash.size() - 1; i > 0; i--)
        {
            hash[i] = hash[i] ^ hash[i - 1];
        }
    }

    const std::string test = hash.to_string();
    return bin_to_hex(test.c_str());
}


