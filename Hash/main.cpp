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
	//std::cout << "argc: " << argc << std::endl;
	//for (size_t i = 0; i < argc; i++)
	//{
	//	std::cout << "argv " << i << ": " << argv[i] << std::endl;
	//}
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
		else if (argc == 2 && strcmp(argv[1], "-bench") == 0)
		{
			std::cout << "Generating..." << std::endl;
			generateFiles();
			std::fstream input;
			input.open("pairtest.txt");
			if (input.fail())
			{
				std::cout << "Failed to open file" << std::endl;
				exit(1);
			}
			std::stringstream line, buffer;
			std::string temp;
			std::pair<std::string, std::string> hashes;
			std::map<int, int> count;
			buffer << input.rdbuf();
			std::cout << "Checking..." << std::endl;
			while (buffer) {
				if (!buffer.eof())
				{
					std::getline(buffer, temp);
					line << temp;
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
			std::cout << "size 10 collitions: " << count[10] << std::endl;
			std::cout << "size 100 collitions: " << count[100] << std::endl;
			std::cout << "size 500 collitions: " << count[500] << std::endl;
			std::cout << "size 1000 collitions: " << count[1000] << std::endl;


		}
		else if (argc == 2 && strcmp(argv[1], "-spd") == 0)
		{
			std::fstream file("konstitucija.txt");
			std::stringstream buffer;
			std::string line;
			buffer << file.rdbuf();

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
		else
		{


		}
	}
	else
	{
		for (size_t i = 0; i < 256; i++)
		{
			std::cout << i << " : " << char(i) << " : " << hash(std::to_string(char(i))) << " " << (hash(std::to_string(char(i))).size() == 64 ? char(251) : 'x') << std::endl;
		}

	}

    return 0;
}
