#include "stdafx.h"
#include "HashTable.h"
#include "item.h"
#include "pomocne.h"

int main()
{
	HashTable H;
	int key, choice;
	int poit;
	string nazit;
	float ceit;
	int x, max;
	do {
		MainMenu();
		choice = jenCislo<int>("Zadejte vyber: ");
		switch (choice) 
		{
		case 1://pridat predmet do tabulky
			do {//kontrola zda klic je jiz v zaznamech
				key = jenCislo<int>("Zadejte unikatni ID predmetu(vetsi nez 0): ");
			} while (H.IsKey(key) == true);
			cout << "Zadejte nazev predmetu: ";
			cin >> nazit;
			ceit = jenCislo<float>("Zadejte cenu predmetu(vetsi nez 0): ");
			poit = jenCislo<int>("Zadejte pocet predmetu(vetsi nez 0): ");
			H.add(key, Item(nazit, ceit, poit));
			cout << "Pridano do seznamu." << endl;
			break;
		case 2://odebrat predmet z tabulky 
			Menu2();
			switch (jenCislo<int>("Zadejte vyber: "))
			{ 
			case 1://odebrat podle klice
				key = jenCislo<int>("Zadejte ID predmetu, ktery chcete smazat: ");
				H.smaz(key, true);
				break;
			case 2://odebrat vsechny s danym poctem na skladu
				poit = jenCislo<int>("Zadejte pocet predmetu, ktery chcete smazat: ");
				H.smaz(key, false);
				break;
			default:
				cout << "Volba muze byt 1 nebo 2. Vracení do předešlého menu" << endl;
				break;
			}
			break;
		case 3://upravit polozku
			Menu3();
			x = jenCislo<int>("Zadejte vyber: ");
			key = jenCislo<int>("Zadejte ID predmetu, ktery chcete upravit: ");
			if (H.IsKey(key) == false)
			{
				cout << "Zadany klic neexistuje";
				break;
			}
			switch (x)
			{
			case 1://upravit cely predmet
				cout << "Zadejte novy nazev predmetu: ";
				cin >> nazit;
				ceit = jenCislo<float>("Zadejte novou cenu predmetu: ");
				poit = jenCislo<int>("Zadejte novy pocet predmetu: ");
				H.edit(key, nazit, ceit, poit);
				cout << "Upraveno!";
				break;
			case 2://upravit pouze nazev
				cout << "Zadejte novy nazev predmetu: ";
				cin >> nazit;
				H.editSpec(key, 0, 2, nazit);
				break;
			case 3://upravit pouze cenu
				ceit = jenCislo<float>("Zadejte novou cenu predmetu: ");
				H.editSpec(key, ceit, 3, "");
				break;
			case 4://upravit pouze pocet
				poit = jenCislo<int>("Zadejte novy pocet predmetu: ");
				H.editSpec(key, poit, 4, "");
				break;
			default:cout << "Neplatna volba. " << endl;
			}
			break;
		case 4://vystup na konzoli + vyhledavani 
			do {
				max = H.GetVel() - 2;
				Menu4();
				choice = jenCislo<int>("Zadejte vyber: ");
				switch (choice)
				{
				case 1: //vypsat dany klic
					key = jenCislo<int>("Zadejte ID predmetu: ");
					popis();
					H.printSpec(key, 0, 1);
					break;
				case 2://vypsat podle ceny
					H.NulaCurr();
					ceit = jenCislo<float>("Zadejte cenu predmetu: ");
					popis();
					do {//abychom vypsali vsechny a ne jen 1. prochazime cele a kdyz najdeme tak pokracujeme od dalsiho zaznamu 
						x = H.GetCurr();
						H.printSpec(ceit, x, choice);
					} while (x < max);
					break;
				case 3://vypsat podle mnozstvi
					H.NulaCurr();
					poit = jenCislo<int>("Zadejte pozadovane mnozstvi predmetu: ");
					x = H.GetCurr();
					popis();
					do {
						x = H.GetCurr();
						H.printSpec(poit, x, choice);
					} while (x < max);
					break;
				case 4://vypsat cele bez serazeni
					popis();
					H.print();
					break;
				case 5://vypsat cele serazene podle klice
					popis();
					H.printSort();
					break;

				default:
					cout << "Volba muze byt 1-5" << endl;
					break;
				}
			} while (choice > 5&&choice <1);
			break;
		case 5://ukladani do souboru
			Menu5();
			switch (choice = jenCislo<int>("Zadejte vyber: "))
			{
			case 1://ulozit do souboru neserazene
				H.zapis();
				break;
			case 2://ulozit vsechny s danym poctem
				poit = jenCislo<int>("Zadejte vyhledavane mnozsti predmetu: ");
				H.zapisPocet(poit);
				break;
			case 3://ulozit serazene 
				H.zapisSort();
				break;
			default:
				cout << "Volba muze byt 1-3. Vraceni do predesleho menu" << endl;
				break;
			}
			break;
		case 6: //nacist data ze souboru zbozi.txt
			H.Nacteni();
			break;
		case 7://spocitejte cenu
			Menu7();
			switch (jenCislo<int>("Zadejte vyber: "))
			{
			case 1://spocitani ceny daneho predmetu
				key = jenCislo<int>("Zadejte ID predmetu, u ktereho chcete vedet celkovou cenu: ");
				if (H.IsKey(key) == false)
				{
					cout << "Zadany klic neexistuje";
					break;
				}
				H.cenaIt(key);
				break;
			case 2://cena vsech predmetu na skladu 
				H.cenall();
				break;
			}
			break;
		case 0:	cout << "Dekujeme za pouzivani! Brzy na shledanou."; break;//ukonceni programu
		default:
			cout << "Volba musi byt od 0-7" << endl;
			break;
		}
	} while (choice  !=0);//opakovani menu do doby nez dojde k ukonceni
	return 0;
}