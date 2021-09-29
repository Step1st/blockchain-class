#pragma once
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

void generateRandomPairs();
void generateSimilarPairs();

void testPairs(std::string fileName);

void generatePairsS(std::stringstream& buffer, int n);
void generatePairsR(std::stringstream& buffer, int n);