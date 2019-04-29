#pragma once
#include "item.h"
//#include "pomocne.h"

struct Zaznam
{
	int key;//klic predmetu
	Item item;//predmet
	Zaznam(){}
	Zaznam(int k, Item v) : key(k), item(v) {}//konstruktor na vyvoreni pomoci klice a polozky
	Zaznam(int k, string n, float c, int p);
	int getKey() { return key; }//vraceni klice
	Item getValue() { return item; }//vraceni predmetu
	string NazevI() { return item.GetNazev(); }//vraceni nazvu predmetu
	float CenaI() { return item.GetCena(); }//vraceni ceny predmetu
	int PocetI() { return item.GetPocet(); }//vraceni poctu predmetu 
	friend ostream& operator<<(ostream &os, Zaznam&i)//pretezujeme operator << kvuli vypisu zaznamu 
	{
		Item it = i.getValue();
		os<< i.getKey() << "\t" << it;
		return os;
	}
};

class HashTable
{
private:
	Zaznam **tabulka;//dynamicke pole ukazatelu zaznamu
	int velikost;//velikost tabulky 
	void init();
	void full();
	void resize(bool full);
	int curr;//pomocna promenna 
	int kolik;//pocet zaznamu
	void SmazPozici(int k);
	Zaznam search(float hod, int vel, int jak);
	int GetHash(int key);
	int Hash(int key);
	void kolikplus() { kolik++; }//zvyseni poctu o 1
	void kolikminus() { kolik--; }//snizeni poctu o 1
	void quicksort(Zaznam **tabulka, int leva, int prava);
	void sort(Zaznam**Sorted);
public:
	HashTable();
	~HashTable();
	int GetVel() { return velikost; }
	int GetCurr() { return curr; }
	void NulaCurr() { curr = 0; }
	bool IsKey(int key);
	void add(int key, Item value);
	int smaz(int key, bool test);
	void edit(int key, string nNa, float nCe, int nPo);
	void editSpec(int key, float value, int jak, string jmeno);
	void print();
	void printSpec(float hod, int vel, int jak);
	void zapis();
	void zapisPocet(int hod);
	void zapisSort();
	void printSort();
	void Nacteni();
	void cenaIt(int key);
	void cenall();
};