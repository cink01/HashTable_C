#pragma once
#include "stdafx.h"
class Item
{
private:
	string nazev;
	float cena;
	int pocet;
public:
	Item() {}
	~Item() {}
	Item(string n, float c, int p) : nazev(n), cena(c), pocet(p) {}
	//vraceni atributu predmetu
	string GetNazev() { return nazev; }
	float GetCena() { return cena; }
	int GetPocet() { return pocet; }
	//nastaveni atributu predmetu
	void SetNazev(string nazev) { this->nazev = nazev; }
	void SetCena(float cena) { this->cena = cena; }
	void SetPocet(int pocet) { this->pocet = pocet; }
	void SetAll(string nazev,float cena,int pocet) //nasteveni vsecho naraz
	{ 
		this->nazev = nazev; 
		this->cena = cena;
		this->pocet = pocet; 
	}
	//pretezujeme operator << kvuli vypisu polozky
	friend ostream& operator<<(ostream &os, Item&i)
	{
		os<< i.GetNazev() << "\t\t" << i.GetCena() << "\t" << i.GetPocet() << endl;
		return os;
	}
};

