#include "stdafx.h"
#include "BackpackProblem.h"
#include <fstream>


// konstruktor domyslny
BackpackProblem::BackpackProblem()
{
	this->bag = Backpack();
	this->amount_elements = 0;
	this->elements = new Element[amount_elements]();
}


// argumenty konstruktora: s- pojemnosc plecaka, n- ilosc wszystkich przedmiotow
BackpackProblem::BackpackProblem(unsigned int s, unsigned int n)
{
	this->bag = Backpack(s);
	this->amount_elements = n;
	this->elements = new Element[amount_elements];

	srand(time(NULL));
	for (int i = 0; i < amount_elements; i++)
	{
		unsigned int a = (rand() / 1000);
		unsigned int b = (rand() / 1000);
		elements[i] = Element(a, b);
	}
}

// funkcja wyswietlajaca rezultaty dzialania algorytmu
void BackpackProblem::displayResult()
{
	bag.displayContents();
}


// odczyt danych z pliku
void BackpackProblem::readFromFile()
{
	unsigned purchaseCost, sellingPrice, availabeBudget;

	fstream file;

	try {
		file.open("ins_wp5.txt", std::ios::in);
		file >> this->amount_elements;
		file >> availabeBudget;

		this->elements = new Element[amount_elements];
		this->bag = Backpack(availabeBudget);

		for (unsigned i = 0; i < amount_elements; i++)
		{
			file >> purchaseCost;
			file >> sellingPrice;
			elements[i] = Element(purchaseCost, sellingPrice);
		}

		file.close();
	}
	catch (exception e) {
		cout << "Nie uda�o sie wczyta� pliku!";
		file.close();
	}
}

void BackpackProblem::writeToFile()
{
	fstream file;
	int N = 500;
	srand(time(NULL));

	try {
		file.open("pom.txt", std::ios::out);

		for (unsigned i = 0; i < N; i++)
		{
			unsigned int a = (rand() / 1000);
			unsigned int b = (rand() / 1000);
			file << a << " " << b << endl;
		}

		file.close();
	}
	catch (exception e)
	{
		cout << "Nie uda�o sie zapisa� do pliku!";
		file.close();
	}
}


// Algorytm oparty na programowaniu dynamicznym
void BackpackProblem::dynamicAlgorithm()
{

	//float
	float** bestTable = new float*[amount_elements + 1]; // macierz na podproblemy o wymiarach: [amount_elements+1] x [bag.get_max_capacity()+1]
	for (unsigned i = 0; i < amount_elements + 1; i++) 
	{
		bestTable[i] = new float[(unsigned)bag.getAvailabeBudget() + 1];
		//tworze iteracyjnie tabele
		for (unsigned j = 0; j <= (unsigned)bag.getAvailabeBudget(); j++)
		{
			if (i == 0 || j == 0)  // pierwsza kolumne i pierwszy wiersz wypelniamy zerami
			{
				bestTable[i][j] = 0;
			}
	
			else if ((unsigned)elements[i - 1].getSellingPrice() <= j)
			{
				float a = elements[i - 1].getProfitOnSale() + bestTable[i - 1][j - (unsigned)elements[i - 1].getPurchaseCost()];
				float b = bestTable[i - 1][j];
				bestTable[i][j] = max(a, b);
			}
			else 
			{
				bestTable[i][j] = bestTable[i - 1][j];
			} 
		}
	}

	//szukam wartosci w tablicy
	unsigned w = bag.getAvailabeBudget();

	for (unsigned i = amount_elements; i > 0; i--) 
	{
		if (bestTable[i][w] != bestTable[i - 1][w]) 
		{
			bag.addElement(&elements[i - 1]); // dodanie elementu do plecaka
			w -= (unsigned)elements[i - 1].getPurchaseCost();
		}
	} 

	// usuwanie macierzy
	for (unsigned i = 0; i < amount_elements; i++) 
	{
		delete[] bestTable[i];
	}
	delete bestTable;
}


BackpackProblem::~BackpackProblem()
{
}
