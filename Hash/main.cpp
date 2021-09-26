#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

#include "hash.h"
#include "bench.h"



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
		else if (argc == 3 && strcmp(argv[1], "-gen") == 0)
		{
			generateRandom(argv[2]);
		}
		else if (argc == 2 && strcmp(argv[1], "-bench") == 0)
		{

			std::fstream input1;
			std::stringstream text1;
			generateRandom("hashtest1");

			input1.open("hashtest1.txt");
			text1 << input1.rdbuf();
			std::cout << "Hash: " << hash(text1.str()) << " Lenght: " << hash(text1.str()).size() << std::endl;
			input1.close();
			text1.clear();

		}
		else if (argc == 2 && strcmp(argv[1], "-spd") == 0)
		{
			std::fstream file("konstitucija.txt");
			std::stringstream buffer;
			std::string line;
			buffer << file.rdbuf();

			std::chrono::duration<double> sum(0);
			while (buffer);
			{
				std::getline(buffer, line);
				auto start = std::chrono::high_resolution_clock::now();
				hash(line);
				std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
				sum += diff;
			}
			std::cout << "Hashing took " << sum << std::endl;

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
