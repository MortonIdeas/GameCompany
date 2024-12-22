#include<iostream>
#include<vector>
#include<random>
#include<string>

using namespace std;
#define N 6	//Ustawiam na podstawie ilu ostatnich miesiecy jest obliczana wartosc spolki
#define M 5 //Ustalam ile razy wiecej moze wynosic zadluzenie niz wartosc firmy

//Deklaracje zawodow w naszej firmie
class Pracownik
{
private:
	string imie;
	double wynagrodzenie;
public:
	Pracownik();
	string getImie();
	double getWynagrodzenie();
	virtual void print();
	void set_wynagrodzenie(double new_wynagrodzenie);
};

class Inzynier :public Pracownik
{
private:
	string wydzial;
public:
	static int l_inzynierow;
	static const int CI = 25;
	Inzynier(string nazwa_wydzialu);
	void print() override;
	string getWydzial();
};

class Magazynier :public Pracownik
{
private:
	bool uprawnienia_na_wozek;
public:
	static int l_magazynierow;
	static const int CMag = 2000;
	Magazynier(bool uprawnienia);
	void print() override;
	string is_uprawnienia();
};

class Marketer :public Pracownik
{
private:
	int liczba_obserwujacych;
public:
	static int l_marketerow;
	static const int CMkt = 400;
	Marketer(int followers);
	void print() override;
	int getFolowersy();
};

class Robotnik :public Pracownik
{
private:
	double numer_buta;
public:
	static int l_robotnikow;
	static const int CR = 1300;
	Robotnik(double r_buta);
	void print() override;
	double wielkosc_buta();
};

class Kredyt
{
private:
	double dlug;
	double rata;
	int pozostale_raty;
public:
	Kredyt(double p_dlug, int l_rat);
	double splac_rate();
	double get_rata();
	int get_pozostale_raty();
};


//Deklaracja zarzadzanej firmy
class Firma
{
private:
	int stan_konta;
	int n_kredytow;
	vector<Kredyt*> kredyty;
	vector<Pracownik*> pracownicy;
	vector<double> historia_przychodow;
	int pojemnosc_magazynu;
	int cena_produktu;
	int popyt;
	int sprzedaz;
	double zadluzenie;
public:
	int get_stan_konta();//Zwraca informacje na temat tego ile pieniedzy znajduje sie na koncie przedsiebiorstwa
	int get_liczba_pracownikow();//Zwraca informacje ile osob pracuje w firmie
	void drukuj_pracownikow();//Wypisuje informacje na temat wszystkich pracownikow
	void wez_kredyt(double kwota, int czas_splaty); //Metoda ta skutkuje zaciagnieciem kredytu na firme
	void zatrudnij(Pracownik* p);//Metoda ta zatrudnia pracownika
	void zaplac_wynagrodzenie();//Metoda ta obciaza stan konta przedsiebiorstwa wszystkimi pensjami pracownikow
	void otrzymaj_przychod();//Metoda dodaje zarobione pieniadze do stanu konta
	void splac_raty();//Metoda ta skutkuje obciazeniem stanu konta przedsiebiorstwa ratami ze wszystkich kredytow
	double wartosc_firmy();//Wylicza aktualna wartosc firmy
	double oblicz_przychod() const;//?
	void kredyt_info();
	void set_pojemnosc_magazynu(int poj);
	void set_cena_produktu(int cena);
	void set_popyt(int popyt);
	void set_sprzedaz();
	int get_pojemnosc_magazynu();
	int get_cena_produktu();
	int get_popyt();
	int get_sprzedaz();
	int get_ile_sprzedano();
	double get_zadluzenie();
	Firma();//Konstruktor
	~Firma();//Destruktor
};


// Definicja gry
class Gra
{
private:
	bool stan;
	Firma f;
public:
	Gra();
	void wypiszAkcje();
	void akcja_gracza();
	bool get_stan();
	void info();
	~Gra();
};
