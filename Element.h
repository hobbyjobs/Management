#pragma once
/*
Klasa reprezentująca pojedynczy element wkladany do plecaka
*/
class Element
{
private:
//PurchaseCost, ProfitOnSale,  sellingPrice

	float purchaseCost;		//Koszt zakupu
	float sellingPrice;		//Cena przy sprzedaży
	float profitOnSale;		//Zarobek ze sprzedaży

public:
	Element();
	Element(float s, float v);
	~Element();

	float getPurchaseCost() const { return this->purchaseCost; }
	float getSellingPrice() const { return this->sellingPrice; }
	float getProfitOnSale() const { return this->profitOnSale; }

};



