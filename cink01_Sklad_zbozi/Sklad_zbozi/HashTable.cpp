#include "stdafx.h"
#include "HashTable.h"

Zaznam::Zaznam(int k, string n, float c, int p) : key(k)//Konstruktor pro zaznam pro zadani vsech parametru predmetu
{
	Item* i=new Item (n, c, p);
	this->item = *i;
}

// ------------------------------------------

void HashTable::init()	//inicializace tabulky a naplneni NULL hodnotami
{
	tabulka = new Zaznam*[velikost];
	for (int i = 0; i < velikost; i++)
		tabulka[i] = NULL;
}

HashTable::HashTable()//bezparametricky konstruktor pro Hashovaci tabulku
{
	velikost = 16;//zakladni velikost
	kolik = 0;//pocet zaznamu
	init();
}

HashTable::~HashTable()	//destruktor pro dynamicke pole 
{
	for (int i = 0; i < velikost; i++)
		if (tabulka[i] != NULL)
			delete tabulka[i];
	delete[] tabulka;
	tabulka = NULL;
}


void HashTable::resize(bool full)//zmena velikosti dynamickeho pole bool kontroluje zda se ma zvysit(true) nebo zvysit(false)
{	
	Zaznam** TMP = new Zaznam*[velikost];
	//vytvoreni pole TMP na uchovani stavajicich zaznamu
	for (int i = 0; i < velikost; i++)
		TMP[i] = tabulka[i];
	int klic;
	//zvetsovani pole
	if (full == true)
	{
		velikost *= 2;//zdvojnasobeni velikosti
		init();//zalozeni nove tabulky o nove velikosti
		for (int i = 0; i < velikost /2; i++)
		{
			if (TMP[i] != NULL) {
				klic = TMP[i]->getKey();//ziskani klice z polozky
				tabulka[Hash(klic)] = TMP[i];//prepocitani hashe a nahrani data do nove tabulky
			}
		}
	}
	//zmensovani pole 
	if(full == false)
	{
		velikost /= 2;
		init();
		for (int i = 0; i < velikost *2; i++)
		{
			if (TMP[i] != NULL) {
				klic = TMP[i]->getKey();
				tabulka[Hash(klic)] = TMP[i];
			}
		}
	}	
	delete[]TMP;TMP = NULL;//zruseni TMP pole 
}

void HashTable::full()//kontrola zda je pole plne 
{
	//konrolujeme kolik mame dat v tabulce kdyz ze priblizuje k plnemu tak se zvetsi
	if (kolik>=velikost - 2)
		resize(true);
	//kdyz je zaznamu v tabulce 3x mene nez jaka je velikost a zaroven velikost tabulky je vetsi nez 32 tak se tabulka zmensi
	if (kolik <= velikost/3 && velikost >= 32)
		resize(false);
}


int HashTable::Hash(int key)//funkce na prideleni hash
{
	int hash = (key % velikost);//vypocet hashe
	while (tabulka[hash] != NULL && tabulka[hash]->getKey() != key)//kontrola jestli je hash obsazen a zda je klic stejny jako pro vypocitane
	{
		//paklize ne tak zvetsujeme hash do doby nez nenajdeme prazdne misto v tabulce
		hash++;
		if (hash > velikost - 1)//paklize dojdeme na konec tabulky zacnema kontrolovat od zacatku
			hash = 0;
	}//tabulka nikdy neni zcela plna, proto nemusime kontrolovat zda se nezacyklíme
	return hash;
}



void HashTable::add(int key, Item value)//pridani predmetu do skladu
{
	full();//kontrola, zda li je pole plne
	int hash = Hash(key);//spocitani hashe pro zvoleny klic
	tabulka[hash] = new Zaznam(key, value);//pridani zaznamu
	kolikplus();//zvyseni poctu polozek
}

void HashTable::SmazPozici(int poz)//smazani pozice z tabulky
{
	if (tabulka[poz] != NULL)//kdyz misto na dane pozici pos neni prazdne tak se smaze 
		delete tabulka[poz];
	tabulka[poz] = NULL;
	cout << "Smazano\n";
	kolikminus();//snizeni poctu polozek
}

int HashTable::smaz(int key,bool test)//mazani polozky podle klice(test=true) nebo podle poctu(test=false)
{
	if (test == true) //mazani podle klice
	{
		int hash = (key % velikost);
		//prepocitani hashe nepouziti funkce hash(); kvuli tomu, ze potrebujeme kvuli kontrole vratit -1 nebo 1 kdyz probiha operace
		while (tabulka[hash] != NULL && tabulka[hash]->getKey() != key)
		{
			hash++;
			if (hash > velikost)
				hash = 0;
			if (hash == (key % velikost))
			{
				cout << "Zaznam neni v tabulce" << endl;
				return -1;
			}
		}
		SmazPozici(hash);
		full();//kontrola jestli neni plne pole nebo nemame malo zanamu pro velikost tabulky
		return 1;
	}
	else //mazani podle poctu
	{
		//prochazime celou tabulku a hledame zda zaznam ma stejny pocet, kdyz ma tak zaznam na pozici i smazeme
		for (int i = 0; i < velikost; i++)
			if (tabulka[i] != NULL && tabulka[i]->item.GetPocet() == key)
				SmazPozici(i);
	}
}

void HashTable::edit(int key, string nNa, float nCe, int nPo)//uprava celeho zaznamu
{
		tabulka[GetHash(key)]->item.SetAll(nNa, nCe, nPo);
}

void HashTable::editSpec(int key, float value, int jak, string jmeno)//uprava jen urciteho parametru 
//nazev(jak=2) , cena (jak=3) , pocet (jak=4)
{
		int hash = GetHash(key);//ziskame hash zadaneho klice 
		if (jak == 2)//zmenime nazev predmetu 
			tabulka[hash]->item.SetNazev(jmeno);
		if (jak == 3)//zmenime cenu predmetu 
			tabulka[hash]->item.SetCena(value);
		if (jak == 4)//zmenime pocet predmetu 
			tabulka[hash]->item.SetPocet((int)value);
}

void HashTable::print()//vytisknuti tabulky cele neserazene
{
	if (kolik == 0)//jestli je tabulka prazdna vytiskne se zprava
		cout << "Seznam je prazdny" << endl;
	else
		for (int i = 0; i < velikost; i++)//prochazeni tabulky a vypis jen tech co nejsou prazdne
			if (tabulka[i] != NULL)
				cout << *tabulka[i];
}

int HashTable::GetHash(int key)//vyhledavani hashe pro klic, kdyz klic neni v tabulce vrati se -1 jinak se vrati hash klice
{
	int hash = (key % velikost);
	while (tabulka[hash] != NULL)
	{
		if (tabulka[hash]->getKey() == key)
			return hash;
		else
		{
			hash++;
			if (hash > velikost - 1)
				hash = 0;
		}
	}
	return -1;
}

bool HashTable::IsKey(int key)//kontrola zda klic je v tabulce
{
	NulaCurr();//vynulovani pocitadla curr
	int hash = (key % velikost);//vypocet hashe
	if(tabulka[hash] == NULL)//kdyz je misto prazne vrati se false 
		return false;
	for (int i = 0; i < velikost; i++)//projiti tabulky a hledani klice v nem
		if (tabulka[i] != NULL)
			if (tabulka[i]->getKey() == key)
			{
				curr = i;//nasteveni pocitadla curr na pozici klice v tabulce
				return true;
			}
	return false;//kdyz se nenajde zadny zaznam tak se vrati false
}

Zaznam HashTable::search(float hod,int vel, int jak)//hledani zaznamu v tabulce zadavame hledanou hodnotu, z jake pozice v tabulce vyhledavame, co za parametr zadavame
//klic(jak=1) , cena(jak=2) , pocet(jak=3) ,
{
	if (jak == 1)//hledani klice
	{
		int k = (int)hod;
		if (IsKey(k) == true)//zjistime kde se klic nachazi
			return *tabulka[curr];//vratime zaznam na pozici curr, ktery nam nastavi IsKey()
		else
			cout << "Zadany klic neexistuje." << endl;//kdyz neni vypise se zaznam
	}
	if (jak == 2)//hledani ceny
	{
		float c = hod;
		Zaznam it;
		int count = 0;//pocitadlo, zda jsme nasli nejaky predmet
		if (vel > 1)//posunuti zacatku o jedna kdyz nezaciname na 0
			vel++;
		for (int i = vel; i < velikost; i++) //prochazime tabulku od pozice vel a kontrolujeme, zda cena je v tabulce
		{
			this->curr = i;//nastavime curr na pozici v tabulce, abychom pak mohli opakovat tuto funkci od teto pozice
			if (tabulka[i] != NULL)
			{
				it = *tabulka[i];
				count++;
				if (vel == 0&&i==0)//abychom predelsi zacykleni nastavujeme hodnotu curr na 1 kdyz mame pozici 0 
					this->curr = 1;
				if (it.item.GetCena() == hod)//kdyz najdeme hodnotu tak ji vratime zpet
					return it;
			}
		}
		if (count != 0 && vel== 0)//jestli se count nezmeni a pozice kde zaciname je 0 tak vime ze v tabulce neni tento zaznam
			cout << "Zadanou cenu nema zadny predmet." << endl;
		Zaznam *wrong = new Zaznam(-1, "wrong", -1, -1);//vratime zaznam, ktery nam rekne, ze neni zadny zaznam
		return *wrong;
	}
	if (jak == 3)//hledani poctu
	{	//hledani poctu probiha stejne jako u ceny jen se hod prevede z float na int
		int p = (int)hod;
		Zaznam it;
		int count = 0;
		if (vel != 0)
			vel++;
		for (int i = vel; i < velikost; i++) {
			this->curr = i;
			if (tabulka[i] != NULL)
			{
				it = *tabulka[i];
				count++;
				if (vel == 0 && i == 0)
					this->curr = 1;
				if (it.item.GetPocet() == hod)
					return it;
			}
		}
		if (count != 0 && vel==0)
			cout << "Zadany pocet nema zadny predmet." << endl;
		Zaznam *wrong = new Zaznam(-1, "wrong", -1, -1);
		return *wrong;
	}
}

void HashTable::printSpec(float hod, int vel, int jak)//vytiskne udaje, podle toho co chceme vytisknoud za specifikovane udaje 
//hod= hledana hodnota , vel=pozice, od ktere hledame, jak=co hledame (1=klic, 2=cena, 3=pocet)
{
		Zaznam i = search(hod,  vel,jak);//vyhledame 
		if (i.getKey()!=-1 && i.item.GetCena() != -1 && i.item.GetNazev()!="wrong" && i.item.GetPocet()!=-1) 
			cout << i;//kdyz se nevrati spatny zaznam, tak se zaznam vypise na konzoli
}

void HashTable:: zapis()//zapis tabulky do souboru "zbozi.txt"
{
	ofstream of("zbozi.txt");//vytoreni nebo otevreni souboru zbozi.txt
	if (of.is_open())//kdyz se podari soubor otevrit 
	{
		for (int i = 0; i < velikost; i++)//prochazime tabulku a kdyz pozice i v tabulce neni prazna zapiseme do souboru
			if (tabulka[i] != NULL)
				of << *tabulka[i];
		of.flush();	of.close();//uzavreme soubor
		cout <<endl<<"  Uspesne zapsano do souboru zbozi.txt" << endl;//vypiseme zpravu o uspechu
	}
	else
		cerr << endl << "  Chyba pri vytvareni souboru. " << endl;//paklize se naskytla nejaka chyba pri otevreni, uprave nebo vytroreni vypiseme chybovou hlasku

}

void HashTable::zapisPocet(int hod)//zapiseme do souboru zbozi.txt pouze polozky s danym poctem
{
	ofstream o("zbozi.txt");
	if (o.is_open())
	{
		Zaznam i;
		curr = 0;
		do
		{
			i = search(hod,curr,3);//hledame pocet v tabulce 
			if (i.getKey() != -1 && i.item.GetCena() != -1 && i.item.GetNazev() != "wrong" && i.item.GetPocet() != -1)
				o << i;//kdyz zaznam neni spatny zapiseme do tabulky 
		} while (curr < velikost-2);
	}
}

void HashTable::quicksort(Zaznam **tabulka, int leva, int prava) //rekuzivni funkce na serazeni pole podle klice od nejmensiho k nejvetsimu
{

	int i = leva, j = prava; Zaznam *TNP;
	int pivot = tabulka[(leva + prava) / 2]->getKey();
	while (i <= j)
	{
		while (tabulka[i]->getKey() < pivot)
			i++;
		while (tabulka[j]->getKey() > pivot)
			j--;
		if (i <= j)
		{
			TNP = tabulka[i];
			tabulka[i] = tabulka[j];
			tabulka[j] = TNP;
			i++;
			j--;
		}
	};
	if (leva < j)
		quicksort(tabulka, leva, j);
	if (i < prava)
		quicksort(tabulka, i, prava);
}

void HashTable::sort(Zaznam**Sorted)//naplnime dynamicke pole ukazatelu na zaznam Sorted hodnotami z Hashovaci tabulky a provedeme serazeni pomoci quick sort 
{
	int j = 0;
	for (int i = 0; i < velikost; i++)
		if (tabulka[i] != NULL)
			Sorted[j++] = tabulka[i];
	quicksort(Sorted, 0, kolik-1);
}

void HashTable::printSort()//vytiskneme na konzoli serazene tabulky
{
	if (kolik != 0)
	{
		Zaznam** Sorted = new Zaznam*[kolik];
		sort(Sorted);
		for (int i = 0; i < kolik - 1; i++)
			cout << *Sorted[i];
	}
	else
		cout << "Seznam je prazdny" << endl;
}

void HashTable::zapisSort()//zapiseme do souboru zbozi.txt serazene polozky tabulky podle klice
{
	if (kolik != 0)
	{
		Zaznam** Sorted = new Zaznam*[kolik];
		sort(Sorted);
		ofstream of("zbozi.txt");
		if (of.is_open())
		{
			Zaznam z;
			for (int i = 0; i < kolik; i++)
				if (Sorted[i] != NULL)
					of << *Sorted[i];
			of.flush(); of.close();
			cout << endl << "  Uspesne zapsano do souboru zbozi.txt" << endl;
		}
		else
			cerr << endl << "  Chyba pri vytvareni souboru. " << endl;
	}
	else
		cout << "Seznam je prazdny nelze zapsat." << endl;
}

void HashTable::Nacteni()//nacteni hodnot ze souboru zbozi.txt
{
	ifstream in("zbozi.txt");
	if (in.is_open())
	{
		init();
		kolik = 0;
		int key;
		string name;
		float cost;
		int number;
		int hash;
		while (in >> key >> name >> cost >> number)
			if (IsKey(key) == false)//kontrola zda klic neni 2x v souboru
				add(key, Item(name, cost, number));//pridani zaznamu
		cout << "Data uspesne nahrana ze souboru.\n";
	}
	else //kdyz vznikne problem z otevrenim souboru vypiseme chybovou hlasku
		cerr << endl << "  Chyba pri otevreni souboru souboru. " << endl;
}

void  HashTable::cenaIt(int key)//vypocitani ceny daneho zbozi
{
	Zaznam i = search(key,0,1);//vyhledame polozku
	//zapiseme si hodnotu ceny a poctu do promenne 
	float cena = i.item.GetCena();
	int pocet = i.item.GetPocet();
	//jesli je polozka v tabulce vypise se na konzoli
	if (i.getKey() != -1 && cena != -1 && i.item.GetNazev() != "wrong" && pocet != -1)
		cout << "Celkova cena predmetu s ID: " << key << " je " << cena * pocet <<" Kc"<< endl;
		
}

void  HashTable::cenall()//vypocete celkove ceny zbozi ve skladu
{
	float p=0.0;
	//prochazime tabulku a kdyz najdeme zaznam tak pro nej vynasobime pocet a cenu a seteme
	for (int i = 0; i < velikost; i++)
		if (tabulka[i] != NULL)
			p += (float)(tabulka[i]->item.GetPocet())*tabulka[i]->item.GetCena();
	cout << "Celkova cena skladu je " << p << "Kc" << endl;//vypiseme konecny vysledek
}
