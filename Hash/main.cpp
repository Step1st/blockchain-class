#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <map>

#include "hash.h"
#include "bench.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"

using namespace std::chrono;


int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		if (argc == 3 && strcmp(argv[1], "-hs") == 0)
		{
			std::string text = argv[2];
			std::cout << "Hash: " << hash(text) << std::endl;
		}
		else if (argc == 3 && strcmp(argv[1], "-hf") == 0)
		{
			std::fstream input;
			std::stringstream text;
			input.open(argv[2]);

			if (input.fail())
			{
				std::cout << "Failed to open file" << std::endl;
				exit(1);
			}
			text << input.rdbuf();
			input.close();
			std::cout << "Hash: " << hash(text.str()) << std::endl;
		}
		else if (argc == 3 && strcmp(argv[1], "-bench") == 0 && strcmp(argv[2], "-A") == 0)
		{
			std::cout << "Generating similar pairs..." << std::endl;
			generateSimilarPairs();
			std::fstream input;
			input.open("pairtestS.txt");
			if (input.fail())
			{
				std::cout << "Failed to open file" << std::endl;
				exit(1);
			}
			std::stringstream buffer;
			std::pair<std::string, std::string> hashes;
			std::map<int, int> count;
			double binTemp, binMin = 100, binMax = 0, binSum = 0;
			double hexTemp, hexMin = 100, hexMax = 0, hexSum = 0;
			buffer << input.rdbuf();
			input.close();
			std::cout << "Checking similar pairs..." << std::endl << std::endl;
			while (buffer) {
				if (!buffer.eof())
				{
					std::string temp;
					std::stringstream line;
					std::getline(buffer, temp);
					line << temp;
					line >> hashes.first >> hashes.second;
					int size = hashes.first.size();
					hashes.first = hash(hashes.first, true);
					hashes.second = hash(hashes.second, true);
					if (hashes.first == hashes.second)
					{
						count[size]++;
					}

					std::bitset<256> hashtemp = std::bitset<256>(hashes.first) ^ std::bitset<256>(hashes.second);
					binTemp = (double) hashtemp.count() / 256 * 100;

					if (binTemp < binMin) binMin = binTemp;
					if (binTemp > binMax) binMax = binTemp;
					binSum += binTemp;

					hashes.first = bin_to_hex(hashes.first);
					hashes.second = bin_to_hex(hashes.second);
					int hexCount = 0;
					for (size_t i = 0; i < 64; i++)
					{
						if (hashes.first[i] != hashes.second[i])
							hexCount++;
					}

					hexTemp = (double)hexCount / 64 * 100;
					if (hexTemp < hexMin) hexMin = hexTemp;
					if (hexTemp > hexMax) hexMax = hexTemp;
					hexSum += hexTemp;

					hashes.first.clear();
					hashes.second.clear();
				}
				else break;
			}
			std::cout << "Minimum binary diffirence: " << binMin << "%" << std::endl;
			std::cout << "Maximum binary diffirence: " << binMax << "%" << std::endl;
			std::cout << "Average binary diffirence: " << binSum / 100000 << "%" << std::endl;
			std::cout << std::endl;
			std::cout << "Minimum hex diffirence: " << hexMin << "%" << std::endl;
			std::cout << "Maximum hex diffirence: " << hexMax << "%" << std::endl;
			std::cout << "Average hex diffirence: " << hexSum / 100000 << "%" << std::endl;
			std::cout << std::endl;
			std::cout << "Size 10 collitions: " << count[10] << std::endl;
			std::cout << "Size 100 collitions: " << count[100] << std::endl;
			std::cout << "Size 500 collitions: " << count[500] << std::endl;
			std::cout << "Size 1000 collitions: " << count[1000] << std::endl;
		}
		else if (argc == 3 && strcmp(argv[1], "-bench") == 0 && strcmp(argv[2], "-C") == 0)
		{
			std::cout << "Generating random pairs..." << std::endl;
			generateRandomPairs();

			std::fstream input;
			input.open("pairtestR.txt");
			if (input.fail())
			{
				std::cout << "Failed to open file" << std::endl;
				exit(1);
			}

			std::stringstream buffer;
			std::pair<std::string, std::string> hashes;
			std::map<int, int> count;

			buffer << input.rdbuf();
			input.close();
			std::cout << "Checking random pairs..." << std::endl << std::endl;

			while (buffer) {
				if (!buffer.eof())
				{
					std::string tempstr;
					std::stringstream line;
					std::getline(buffer, tempstr);
					line << tempstr;
					line >> hashes.first >> hashes.second;

					if (hash(hashes.first) == hash(hashes.second))
					{
						count[hashes.first.size()]++;
					}
					hashes.first.clear();
					hashes.second.clear();
				}
				else break;
			}
			std::cout << "Size 10 collitions: " << count[10] << std::endl;
			std::cout << "Size 100 collitions: " << count[100] << std::endl;
			std::cout << "Size 500 collitions: " << count[500] << std::endl;
			std::cout << "Size 1000 collitions: " << count[1000] << std::endl;
		}
		else if (argc == 3 && strcmp(argv[1], "-spd") == 0)
		{
			std::fstream input;
			std::string fileName = argv[2];
			std::stringstream buffer;
			std::string line;

			input.open(fileName);
			if (input.fail())
			{
				std::cout << "Failed to open file" << std::endl;
				exit(1);
			}
			buffer << input.rdbuf();

			std::chrono::duration<double> md5sum(0);
			std::chrono::duration<double> sha2sum(0);
			std::chrono::duration<double> sha1sum(0);
			std::chrono::duration<double> hashsum(0);
			while (buffer)
			{
				if (!buffer.eof()) {

					std::getline(buffer, line);
					auto start = std::chrono::high_resolution_clock::now();
					hash(line);
					std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
					hashsum += diff;

					start = std::chrono::high_resolution_clock::now();
					md5(line);
					diff = std::chrono::high_resolution_clock::now() - start;
					md5sum += diff;

					start = std::chrono::high_resolution_clock::now();
					sha1(line);
					diff = std::chrono::high_resolution_clock::now() - start;
					sha1sum += diff;

					start = std::chrono::high_resolution_clock::now();
					sha256(line);
					diff = std::chrono::high_resolution_clock::now() - start;
					sha2sum += diff;
				}
				else break;
			}
			std::cout << "My hash took " << hashsum.count() << std::endl;
			std::cout << "MD5 took " << md5sum.count() << std::endl;
			std::cout << "SHA1 took " << sha1sum.count() << std::endl;
			std::cout << "SHA256 took " << sha2sum.count() << std::endl;

		}
		else {

		std::cout << "Error: bad arguments" << std::endl; 
		std::cout << "---------------------------------------" << std::endl;
		std::cout << "To hash a string: Hash -hs <text>" << std::endl;
		std::cout << "To hash a file(include extention): Hash -hf <path>" << std::endl;
		std::cout << "To test for collitions with random pairs: Hash -bench -C" << std::endl;
		std::cout << "To test the avalanche effect: Hash -bench -A" << std::endl;
		std::cout << "Speed test with selected file(include extention): Hash -spd <path>" << std::endl;

		}
	}
	else
	{
	std::cout << "To hash a string: Hash -hs <text>" << std::endl;
	std::cout << "To hash a file(include extention): Hash -hf <path>" << std::endl;
	std::cout << "To test for collitions with random pairs: Hash -bench -C" << std::endl;
	std::cout << "To test the avalanche effect: Hash -bench -A" << std::endl;
	std::cout << "Speed test with selected file(include extention): Hash -spd <path>" << std::endl;
	}

    return 0;
}
