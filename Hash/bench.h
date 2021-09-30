#pragma once
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <map>

void generateRandomPairs();
void generateSimilarPairs();

void generateFile();

void generatePairsS(std::stringstream& buffer, int n);
void generatePairsR(std::stringstream& buffer, int n);