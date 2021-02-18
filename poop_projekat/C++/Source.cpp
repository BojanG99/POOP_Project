#include <iostream>
#include<vector>
#include"MyFormater.h"
#include <fstream>
#include"Image.h"
#include"tiny2xml.h"
#include"CompositeOperation.h"
#include"BasicOperation.h"
#include"PamFormater.h"
#include"CrnoBela.h"
#include"SivaSlika.h"
#include"Inverzija.h"
#include"Medijana.h"
using namespace std;
using namespace tinyxml2;
void meni() {
	cout << "0.Izadji\n";
	cout << "1.Dodaj sloj\n";
	cout << "2.Dodaj selekciju\n";
	cout << "3.Dodaj operaciju\n";
	cout << "4.Napravi kompozitnu funkciju\n";
	cout << "5.Sacuvaj kompozitnu funkciju\n";
	cout << "6.Aktiviraj selekciju\n";
	cout << "7.Deaktiviraj selekciju\n";
	cout << "8.Aktiviraj sloj(za operaciju)\n";
	cout << "9.Deaktiviraj sloj(za operaciju)\n";
	cout << "10.Sacuvaj sliku\n";
	cout << "11.Aktiviraj sloj(za ucestvovanje u pravljenju slike)\n";
	cout << "12.Deaktiviraj sloj(za ucestvovanje u pravljenju slike)\n";
	cout << "13.Izvrsi operacije\n";
	cout << "14.Izbrisi sloj\n";
}
void meni_Za_operacije() {
	cout << "0.Dodaj\n";
	cout << "1.Oduzmi\n";
	cout << "2.Inverzno oduzmi\n";
	cout << "3.Mnozi\n";
	cout << "4.Dijeli\n";
	cout << "5.Inverzno dijeli\n";
	cout << "6.Max\n";
	cout << "7.Min\n";
	cout << "8.Pow\n";
	cout << "9.Log\n";
	cout << "10.Medijana\n";
	cout << "11.Inverzija slike\n";
	cout << "12.Crno-bijela slika\n";
	cout << "13.Siva slika\n";
	cout << "14.Apsolutna vrijednost\n";
}
int main(int argc, char* argv[]) {
	std::cout << "***Moj format je XML***\n";
	std::cout << "NAPOMENA:Pomocni fajlovi za xml format se cuvaju u istom folderu kao i sam fajl\n";
	std::cout << "NAPOMENA:ucitavanje/cuvanje xml formata moze da potraje\n";
	std::cout << "Za pravljenje kompozitne funkcije prvo pritisnete 4,\n a zatim ako ocete da je sacuvate\n";
	std::cout << "pritisnite 5, a da je ubacite u sliku pritisnite 3\n";
	//CompositeOperation op;
	bool akt;
//	op.dodaj(new Sabiranje(50));
	//op.exportuj("kompozitna.xml");
	Image* img = Image::Get_Image();
	if (argc >2) {
		const char* ch = argv[1];
		const char* comp = argv[2];

		img->Dodaj_Sloj(ch, 100);
		CompositeOperation co(comp);
		img->Dodaj_Kompozitnu_funkciju(co);
		img->Izvrsi_Operaciju();

		img->Exportuj_sliku(ch);
		return 0;
	}
	int id;
	int opcija;
	bool run=true;
	bool haveoperation = false;
	bool havop = false;
	
	
	CompositeOperation compop;
	while (run) {
		vector<Rectangle> rec;
		string s;
		meni();
		cin >> opcija;
		switch (opcija)
		{
		case 0:
			if (img->Get_save())
			run = false;
			else {
				cout << "Slika nije sacuvan, da li ste sigurni da zelite da izadjete???(0.ne 1.da)\n";
				int opc;
				cin >> opc;
				if (opc)run = false;

			}
			break;
		case 1:cout << "Unesi putanju do slike:\n";
			const char* ch;

			cin >> s;
			
			int pr;
			cout << "Unesi providnost slike(0-100):\n";
			cin >> pr;
			img->Dodaj_Sloj(s, pr);
			break;
		case 2:
			cout << "Unesi ime selekcije\n";
			cin >> s;
			cout << "Unesi broj pravougaonih objekata\n";
			int num;
			cin >> num;
			
			for (int i = 0; i < num; i++)
			{
				int x, y, m, n;
				cout << "Unesi x i y koordinatu\n";
				cin >> x >> y;
				cout << "Unesi sirinu i duzinu \n";
				cin >> m >> n;
				Rectangle r(x, y, m, n);
				rec.push_back(r);
			}
			cout << "Da li zelite da bude aktivna(1.da 0.ne)\n";
			int i;
			cin >> i;
			 akt = ((i == 0) ? false : true);

			img->Dodaj_Selekciju(s,rec,akt);
			break;

		case 3:
			if(haveoperation)
			img->Dodaj_Kompozitnu_funkciju(compop);
			else {
				std::cout << "Niste napravili novu kompozitnu funkciju.Pritisnite 4 ako zelite novu kompozitnu\n";
			}
			haveoperation = false;
			break;

		case 4:
			int brojoperacija;
			cout << "Unesi broj operacija:\n";
			cin >> brojoperacija;
			int koja_operacija;
			haveoperation = true;
			havop = true;
			compop.obrisi();
			for (int i = 0; i < brojoperacija; i++)
			{
				meni_Za_operacije();
				cin >> koja_operacija;
				int par;
				
				switch (koja_operacija)
				{
				case 0:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new Sabiranje(par));
					break;
				case 1:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new Oduzimanje(par));
					break;
				case 2:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new IOduzimanje(par));
					break;
				case 3:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new Mnozenje(par));
					break;
				case 4:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new Dijeljenje(par));
					break;
				case 5:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new IDijeljenje(par));
					break;
				case 6:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new Max(par));
					break;
				case 7:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new Min(par));
					break;
				case 8:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new Pow(par));
					break;
				case 9:
					cout << "Unesi Parametar\n";
					cin >> par;
					compop.dodaj(new Log(par));
					break;
				case 10:
				
					compop.dodaj(new Medijana());
					break;
				case 11:
					compop.dodaj(new Inverzija());
					break;
				case 12:
					compop.dodaj(new CrnoBela());
					break;
				case 13:
					compop.dodaj(new SivaSlika());
					break;
					case 14:
						compop.dodaj(new Abs());
						break;
				default:
					cout << "Pogresan Unos";
					break;
				}
			}
			break;
		case 5:
			if (havop) {
				cout << "Unesi ime fajla\n";
				cin >> s;

				compop.exportuj(s);
			}
			else std::cout<<"Ne postoji kompozitna funkcija.Pritisnite 4 da je napravite\n";
			break;
		case 6:
			cout << "Unesi ime selekcije\n";
			cin >> s;
			
			img->Aktiviraj_Selekciju(s);
			break;
		case 7:
			cout << "Unesi ime selekcije\n";
			cin >> s;
			img->Deaktiviraj_Selekciju(s);
			break;
		case 8:
			cout << "Unesi ID sloja\n";
			
			cin >> id;
			img->Aktiviraj_Sloj_Operation(id);
			break;
		case 9:
			cout << "Unesi ID sloja\n";
			//int id;
			cin >> id;
			img->Deaktiviraj_Sloj_Operation(id);
			break;
		case 10:
			cout << "Unesi ime fajla\n";
			cin >> s;
			img->Exportuj_sliku(s);
			break;
		case 11:
			cout << "Unesi ID sloja\n";
			int id;
			cin >> id;
			img->Aktiviraj_Sloj_Save(id);
			break;
		case 12:
			cout << "Unesi ID sloja\n";
		//	int id;
			cin >> id;
			img->Deaktiviraj_Sloj_Save(id);
			break;
		case 13:
			img->Izvrsi_Operaciju();
			break;
		case 14:
			cout << "Unesi ID sloja\n";
			//	int id;
			cin >> id;
			img->Izbrisi_Sloj(id);
			break;
		default:
			break;
		}
		
	}

return 0;

	}
