#ifndef POMOCNE_H_INCLUDED
#define POMOCNE_H_INCLUDED
//tento soubor obsahuje pomocne funkce jako vypisy menu a funkci na kontrolu vstupu

template <class Typ>
Typ jenCislo(const char *const message)//kontrola zadaneho cisla
{
	Typ n;//promenna 
	do//opakujeme tak dlouho nez neni zadane kladne cislo
	{
		cout << message << flush;
		cin >> n;
		cin.clear();
		cin.ignore(1000, '\n');
	} while (cin.good() != true || n < 0);//kontrolu je se zda neni zadan znak a nebo zaporne cislo
	return n;//vratime platnou hodnotu
}

void popis()//nadpis nad tabulky 
{
	cout << endl << "ID\tNAZEV\t\tCENA\tPOCET" << endl;
}

void MainMenu()//hlavni menu programu
{
	cout << endl << "+--------------------------+" << endl;
	cout << "| 0 -	KONEC              |" << endl;
	cout << "| 1 -	PRIDAT ITEM        |" << endl;
	cout << "| 2 -	ODEBRAT ITEM       |" << endl;
	cout << "| 3 -	UPRAVIT ITEM       |" << endl;
	cout << "| 4 -	VYPSAT SEZNAM	   |" << endl;
	cout << "| 5 -	ZAPSAT DO SOUBORU  |" << endl;//sort a mozna nacitani ze souboru
	cout << "| 6 -	NACIST ZE SOUBORU  |" << endl;
	cout << "| 7 -	SPOCITEJ CENU	   |" << endl;
	cout << "+--------------------------+" << endl;
}

void Menu2()//menu programu pro bod 2
{
	cout << endl << "+--------------------------+" << endl;
	cout << "| 1 -	Smaz podle klice   |" << endl;
	cout << "| 2 -	Smaz podle poctu   |" << endl;
	cout << "+--------------------------+" << endl;
}

void Menu3()//menu programu pro bod 3
{
	cout << endl << "+-----------------------------+" << endl;
	cout << "| 1 -	Upravit cely predmet  |" << endl;
	cout << "| 2 -	Upravit nazev predmtu |" << endl;
	cout << "| 3 -	Upravit cenu predmtu  |" << endl;
	cout << "| 4 -	Upravit pocet predmtu |" << endl;
	cout << "+-----------------------------+" << endl;
}

void Menu4()//menu programu pro bod 4
{
	cout << endl << "+-----------------------------------+" << endl;
	cout << "| 1 -	Vypsat podle urciteho klice |" << endl;
	cout << "| 2 -	Vypsat podle urcite ceny    |" << endl;
	cout << "| 3 -	Vypsat podle urciteho poctu |" << endl;
	cout << "| 4 -	Vypsat vse neserazene       |" << endl;
	cout << "| 5 -	Vypsat vse serazene         |" << endl;
	cout << "+-----------------------------------+" << endl;
}

void Menu5()//menu programu pro bod 5
{
	cout << endl << "+-------------------------------+" << endl;
	cout << "| 1 -	Neserazene              |" << endl;
	cout << "| 2 -	Zapsat jen urcity pocet |" << endl;
	cout << "| 3 -	Serazeno podle klice    |" << endl;
	cout << "+-------------------------------+" << endl;
}
/*
void Menu6()//menu programu pro bod 6
{
	cout << "+---------------------------------+" << endl;
	cout << "| 1 -	Nacist defaultni hodnoty  |" << endl;
	cout << "| 2 -	Nacist hodnoty ze souboru |" << endl;
	cout << "+---------------------------------+" << endl;
}
*/
void Menu7()//menu programu pro bod 7
{
	cout << "+--------------------------------------+" << endl;
	cout << "| 1 -	Celkova cena pro uricity klic  |" << endl;
	cout << "| 2 -	Celkova cena skladu            |" << endl;
	cout << "+--------------------------------------+" << endl;
}
#endif