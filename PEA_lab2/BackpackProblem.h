#pragma once
#include <random>
#include <stdint.h>
#include <algorithm>
#include "Element.h"
#include "Backpack.h"
#include <iostream>
#include <time.h>

using namespace std;


// Klasa reprezentująca problem plecakowy i algorytmy stworzone do jego rozwiazania
class BackpackProblem
{
private:
	Backpack bag;
	Element* elements; // tablica wszystkich elementow
	unsigned amount_elements; // liczba elementow
public:
	BackpackProblem();
	BackpackProblem(unsigned int s, unsigned int n);
	~BackpackProblem();
	void readFromFile();
	void writeToFile();
	void displayResult();
	void dynamicAlgorithm();
};



