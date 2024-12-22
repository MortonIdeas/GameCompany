#pragma once
#include"classes.hpp"

//funkcja zwracajaca losowe imie/nazwisko
string losoweImieINazwisko() {
	vector<std::string> imiona = { "Anna", "Jan", "Maria", "Piotr", "Katarzyna", "Tomasz", "Alicja", "Wojciech" };
	vector<std::string> nazwiska = { "Nowak", "Kowalski", "Wisniewski", "Wojcik", "Kowalczyk", "Lewandowski", "Kaminski", "Dabrowski" };

	random_device rd;
	mt19937 generator(rd());

	// Losowe wybieranie imienia i nazwiska
	uniform_int_distribution<int> imieDist(0, imiona.size() - 1);
	uniform_int_distribution<int> nazwiskoDist(0, nazwiska.size() - 1);

	string losoweImie = imiona[imieDist(generator)];
	string losoweNazwisko = nazwiska[nazwiskoDist(generator)];

	// Zwracanie imienia i nazwiska w postaci jednego stringa
	return losoweImie + " " + losoweNazwisko;
}


Gra::Gra()
{
	stan = true;
	srand(static_cast<unsigned>(time(0)));
	cout << "UDALO SIE ROZPOCZAC GRE!" << endl;
	cout << "_________________________________________________" << endl;
	wypiszAkcje();
	cout << "_________________________________________________" << endl;
	info();
}
void Gra::wypiszAkcje()
{
	cout << "_____________DOZWOLONE AKCJE W GRZE______________" << endl;
	cout << "1) lp - wylistuj pracownikow " << endl;
	cout << "2) zinz - zatrudnij inz." << endl;
	cout << "3) zmag - zatrudnij mag." << endl;
	cout << "4) zmkt - zatrudnij mark. " << endl;
	cout << "5) zrob - zatrudnij rob. " << endl;
	cout << "6) kred - weŸ kredyt " << endl;
	cout << "7) kt - zakoncz turê i wyswietl stan firmy na poczatku nastepnego miesiaca " << endl;
}
void Gra::akcja_gracza()
{
	string akcja;
	cout << "Wpisz akcje gracza: " << endl;
	cin >> akcja;
	if (akcja == "lp")
	{
		f.drukuj_pracownikow();
	}
	else if (akcja == "zinz")
	{
		string wydzial;
		cout << "Wprowadz nazwe wydzialu: " << endl;
		cin >> wydzial;
		Inzynier* i = new Inzynier(wydzial);
		f.zatrudnij(i);
	}
	else if (akcja == "zmag")
	{
		int uprawnienia;
		cout << "Czy magazynier ma uprawnienia na wozki widlowe?: 1-tak, 0-nie " << endl;
		cin >> uprawnienia;
		Magazynier* mag = new Magazynier(bool(uprawnienia));
		f.zatrudnij(mag);
	}
	else if (akcja == "zmkt")
	{
		unsigned int fol;
		cout << "Wprowadz liczbe obserwujacych: " << endl;
		cin >> fol;
		Marketer* mkt = new Marketer(fol);
		f.zatrudnij(mkt);
	}
	else if (akcja == "zrob")
	{
		double rozmiar;
		cout << "Wprowadz rozmiar buta: " << endl;
		cin >> rozmiar;
		Robotnik* rob = new Robotnik(rozmiar);
		f.zatrudnij(rob);
	}
	else if (akcja == "kred")
	{
		double wartosc_kredytu;
		unsigned int liczba_rat;
		cout << "Wprowadz wartosc kredytu" << endl;
		cin >> wartosc_kredytu;
		cout << "Wprowadz liczbe rat" << endl;
		cin >> liczba_rat;
		if (liczba_rat < 24)
		{
			f.wez_kredyt(wartosc_kredytu, liczba_rat);
		}
		else
		{
			cout << "Nie mozna brac kredytu na tak dlugi czas!" << endl;
		}
	}
	else if (akcja == "kt")
	{
		cout <<"_________________________________________________" << endl;
		cout << "WYDATKI: " << endl;
		f.zaplac_wynagrodzenie();
		//ustawienie nowej wartosci
		f.splac_raty();
		//Aktualizacja wartosci parametrow firmy
		f.set_pojemnosc_magazynu(Magazynier::l_magazynierow * Magazynier::CMag);
		f.set_cena_produktu(Inzynier::l_inzynierow * Inzynier::CI);
		f.set_popyt(Marketer::l_marketerow * Marketer::CMkt);
		cout << "W tym miesiacu sprzedano: " << f.get_ile_sprzedano() <<" produktow." << endl;
		f.set_sprzedaz();
		//Dodanie wartosci
		f.otrzymaj_przychod();
		cout << "Wartosc firmy po tej turze wynosi: " << f.wartosc_firmy() << endl;
		if (f.get_stan_konta() < 0.0)//Warunek porazki
		{
			stan = false;
			cout << "DOPROWADZILES FIRME DO UPADKU, PRZEGRALES" << endl;
		}
		else if (f.wartosc_firmy() - f.get_zadluzenie() > 150000)//Warunek zwyciestwa
		{
			stan = false;
			cout << "BRAWO UDALO CI SIE WYGRAC GRE!" << endl;
		}
		cout << "_________________________________________________" << endl;
		info();
	}
}
bool Gra::get_stan()
{
	return stan;
}
void Gra::info()
{
	cout << " Aktualna sytuacja firmy wyglada nastepujaco: " << endl;
	f.kredyt_info();
	cout << "1) Posiadasz: " << f.get_stan_konta() << " PLN" << endl;
	cout << "2) Zatrudniasz lacznie: " << f.get_liczba_pracownikow() << " pracownikow" << endl;
	cout << "3) W tym momencie twoja firma warta jest: " << f.wartosc_firmy() << endl;
	cout << "4)Pracuje dla ciebie " << Inzynier::l_inzynierow << " Inz." << endl;
	cout << "5)Pracuje dla ciebie " << Marketer::l_marketerow << " Mark." << endl;
	cout << "6)Pracuje dla ciebie " << Magazynier::l_magazynierow << " Magaz." << endl;
	cout << "7)Pracuje dla ciebie " << Robotnik::l_robotnikow << " Rob." << endl;
}
Gra::~Gra()
{
	cout << "Udalo sie zakonczyc gre" << endl;
}




Firma::Firma()
{
	stan_konta = 100000;
	n_kredytow = 0;
	zadluzenie = 0.0;
	Inzynier* i = new Inzynier("Meil");
	Magazynier* mag = new Magazynier(true);
	Marketer* mark = new Marketer(1000);
	Robotnik* rob = new Robotnik(33.4);
	pracownicy.push_back(i);
	pracownicy.push_back(mag);
	pracownicy.push_back(mark);
	pracownicy.push_back(rob);
}
int Firma::get_stan_konta()
{
	return stan_konta;
}
void Firma::drukuj_pracownikow()
{
	cout << "Wszyscy pracownicy" << endl;
	for (int i = 0; i < pracownicy.size(); i++)
	{
		pracownicy[i]->print();
	}
}
int Firma::get_liczba_pracownikow()
{
	return pracownicy.size();
}
double Firma::get_zadluzenie()
{
	zadluzenie = 0;
	for (auto kredyt : kredyty)
	{
		zadluzenie = zadluzenie + (kredyt->get_pozostale_raty() * kredyt->get_rata());
	}
	return zadluzenie;
}
void Firma::wez_kredyt(double kwota, int  czas_splaty)
{
	if (kwota + get_zadluzenie() > M * wartosc_firmy())
	{
		cout<<"Ze wzgledow proceduralnych nie mozna wziac kredytu"<<endl;
	}
	else
	{
		Kredyt* k = new Kredyt(kwota, czas_splaty);
		stan_konta = stan_konta + kwota;
		kredyty.push_back(k);
	}
}
void Firma::zatrudnij(Pracownik* p)
{
	pracownicy.push_back(p);
}
void Firma::zaplac_wynagrodzenie()
{
	double koszty_zatrudnienia = 0;
	for (auto pracownik : pracownicy)
	{
		koszty_zatrudnienia = koszty_zatrudnienia + pracownik->getWynagrodzenie();
	}
	cout << "Koszty zatrudnienia za miesiac wynosza: " << koszty_zatrudnienia <<endl;
	stan_konta = stan_konta - koszty_zatrudnienia;
}
void Firma::otrzymaj_przychod()
{
	stan_konta = stan_konta + sprzedaz;
	cout << "W tym miesiacu zostalo zarobione: " << sprzedaz << " zl" << endl;
	historia_przychodow.push_back(sprzedaz);
}
void Firma::splac_raty()
{
	double ceny_kredytow = 0.0;
	int numer_kredytu = 0;
	for (auto kredyt : kredyty)
	{
		if (kredyt->get_pozostale_raty() == 0)
		{
			kredyty.erase(kredyty.begin() + numer_kredytu);
		}
		else
		{
			ceny_kredytow = ceny_kredytow + double(kredyt->splac_rate());
		}
		numer_kredytu++;
	}
	cout << "Na splate kredytow w tym miesiacu zostalo wydane " << ceny_kredytow << " zl" << endl;
	stan_konta = stan_konta - ceny_kredytow;
}
double Firma::wartosc_firmy()
{
	double wartosc_firmy = 0.0;
	if (historia_przychodow.size() < N)
	{
		return wartosc_firmy;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			wartosc_firmy = wartosc_firmy + historia_przychodow[historia_przychodow.size() - i - 1];
		}
		return double(int(wartosc_firmy/6));
	}
}
double Firma::oblicz_przychod() const
{
	return 0.0;
}
Firma::~Firma()
{
	cout << "Zamknalem firme" << endl;
}
void Firma::kredyt_info()
{
	cout << "W tym momencie firma ma zaciagniete " << kredyty.size() << " kredyty" << endl;
}
void Firma::set_pojemnosc_magazynu(int pojemnosc)
{
	pojemnosc_magazynu = pojemnosc;
}
void Firma::set_cena_produktu(int cena)
{
	cena_produktu = cena;
}
void Firma::set_popyt(int p_popyt)
{
	popyt = p_popyt;
}
void Firma::set_sprzedaz()
{
	int mozliwosci_produkcyjne = Robotnik::CR * Robotnik::l_robotnikow;
	int wyprodukowane = min(mozliwosci_produkcyjne, pojemnosc_magazynu);
	int liczba_sprzedanych = min(wyprodukowane, popyt);
	sprzedaz =  liczba_sprzedanych * cena_produktu;
}
int Firma::get_pojemnosc_magazynu()
{
	return pojemnosc_magazynu;
}
int Firma::get_cena_produktu()
{
	return pojemnosc_magazynu;
}
int Firma::get_popyt()
{
	return popyt;
}
int Firma::get_sprzedaz()
{
	return sprzedaz;
}
int Firma::get_ile_sprzedano()
{
	int mozliwosci_produkcyjne = Robotnik::CR * Robotnik::l_robotnikow;
	int wyprodukowane = min(mozliwosci_produkcyjne, pojemnosc_magazynu);
	int liczba_sprzedanych = min(wyprodukowane, popyt);
	return liczba_sprzedanych;
}



Pracownik::Pracownik()
{
	imie = losoweImieINazwisko();
}
string Pracownik::getImie()
{
	return imie;
}
double Pracownik::getWynagrodzenie()
{
	return wynagrodzenie;
}
void Pracownik::print()
{
	cout << "Imie pracownika: " << getImie() << " wynagrodzenie pracownika" << getWynagrodzenie() << endl;
}
void Pracownik::set_wynagrodzenie(double new_wynagrodzenie)
{
	wynagrodzenie = new_wynagrodzenie;
}

//Metody inzyniera
int Inzynier::l_inzynierow = 0;
Inzynier::Inzynier(string nazwa_wydzialu)
{
	l_inzynierow++;
	wydzial = nazwa_wydzialu;
	set_wynagrodzenie(5000.0);
}
void Inzynier::print()
{
	cout << "Inzynier: " << getImie() << " otrzymuje wyplate: " << getWynagrodzenie() << " Skonczony wydzial " << getWydzial() << endl;
}
string Inzynier::getWydzial()
{
	return wydzial;
}



//Metody Marketera
int Marketer::l_marketerow = 0;
Marketer::Marketer(int followers)
{
	l_marketerow++;
	set_wynagrodzenie(5000.0);
	liczba_obserwujacych = followers;
}
void Marketer::print()
{
	cout << "Marketer: " << getImie() << " otrzymuje wyplate: " << getWynagrodzenie() << "posiada liczbe obserwatorow rowna: " << getFolowersy() << endl;
}
int Marketer::getFolowersy()
{
	return liczba_obserwujacych;
}



//Metody Magazynier
int Magazynier::l_magazynierow = 0;
Magazynier::Magazynier(bool uprawnienia)
{
	l_magazynierow++;
	set_wynagrodzenie(4000.0);
	uprawnienia_na_wozek = uprawnienia;
}
string Magazynier::is_uprawnienia()
{
	if (uprawnienia_na_wozek)
		return "Tak";
	else
		return "Nie";
}
void Magazynier::print()
{
	cout << "Magazynier: " << getImie() << " otrzymuje wyplate: " << getWynagrodzenie() << " Czy posiada uprawnienia na wozek: " << is_uprawnienia() << endl;
}




int Robotnik::l_robotnikow = 0;
Robotnik::Robotnik(double r_buta)
{
	l_robotnikow++;
	set_wynagrodzenie(4000.0);
	numer_buta = r_buta;
}
void Robotnik::print()
{
	cout << "Robotnik: " << getImie() << " otrzymuje wyplate: " << getWynagrodzenie() << "Robotnik posiada rozmiar buta:" << wielkosc_buta() << endl;
}
double Robotnik::wielkosc_buta()
{
	return numer_buta;
}




//Metody dotyczace Kredytu
Kredyt::Kredyt(double p_dlug, int l_rat)
{
	dlug = p_dlug;
	pozostale_raty = l_rat;
	rata = (p_dlug / l_rat) * (1.1 + l_rat * 0.01);
}

double Kredyt::splac_rate()
{
	pozostale_raty--;
		return rata;
}
int Kredyt::get_pozostale_raty()
{
	return pozostale_raty;
}
double Kredyt::get_rata()
{
	return rata;
}
