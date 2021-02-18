#include "MyFormater.h"
#include<regex>
#include <iostream>
#include <fstream>
#include"tiny2xml.h"

using namespace std;
using namespace tinyxml2;


 int t = 0;
void MyFormater::exportImage(const Image& i, const char* path) {

	string s2 = path;
	
	int poz = -1;
	for (int j = 0; j < s2.length(); j++)
	{
		if (s2[j] == '\\')poz = j;
	}
	s2.resize(poz + 1);
	
	
	FILE* file = fopen(path, "wb");
	if (!file) {
		cout << "Greska u pravljenju fajla:" << path << "\n";
		return;
	}
	tinyxml2::XMLDocument doc;
	XMLNode* node = doc.NewElement("Slika");

	doc.InsertFirstChild(node);
	XMLElement* pElement;


	pElement = doc.NewElement("Opis");
	if (pElement == nullptr) {
		cout << "Greska u fajlu";
		return ;
	}
	pElement->SetAttribute("Sirina", i.width);
	pElement->SetAttribute("Visina", i.height);
	pElement->SetAttribute("BrojSlojeva", i.slojevi.size());

	node->InsertFirstChild(pElement);

	int o = 0;
	for (auto sl : i.slojevi)// za svaki sloj pravi cvor u kome cuva osnovne podatke (providnost i aktivnosti)
	{
		o++;
		XMLElement* pElement1 = doc.NewElement("Layer");
		pElement1->SetAttribute("Providnost", sl.proz);
		pElement1->SetAttribute("Aktivanprikaz", sl.ucestvuje);
		pElement1->SetAttribute("Aktivanoperacije", sl.activan);
		ofstream izlaz;
		if (!izlaz) {
			cout << "Greska u pravljenju fajla:" << path << "\n";
		
			return;
		}
		string lay = "layer.txt";//za svaki sloj u posebnom txt fajlu cuva piksele po formatu r,g,b,a;
		string s;
		if(poz==-1)
		s= std::to_string(o) + lay;
		else 
			s= s2+std::to_string(o) + lay;
		pElement1->SetAttribute("Putanja", s.c_str());
		izlaz.open(s.c_str());
		for (auto vv : sl.mat)
		{

			for (auto v : vv)
			{
				izlaz << std::to_string(v.Get_red()) << "," << std::to_string(v.Get_green()) << "," << std::to_string(v.Get_blue()) << "," << std::to_string(v.Get_alfa()) << ";\n";
		 
		
				
			}
		}
		izlaz.close();
		pElement->InsertEndChild(pElement1);



	}
	vector<vector<Pixel>> pom=i.Napravi_Sliku();
	XMLElement* pElement1 = doc.NewElement("GlavnaSlika");//cuva glavnu sliku/kako je korisnik vidi
	

	ofstream izlaz;
	string lay1;
	if (poz == -1)
		lay1 = "glavna.txt";//u posebnom txt fajlu
	else
		lay1 = s2 + "glavna.txt";
	
	pElement1->SetAttribute("Putanja", lay1.c_str());
	izlaz.open(lay1.c_str());
	for (auto x:pom)
	{
		for (auto v: x)
		{
			izlaz << std::to_string(v.Get_red()) << "," << std::to_string(v.Get_green()) << ",";
			izlaz<< std::to_string(v.Get_blue()) << "," << std::to_string(v.Get_alfa()*255/100) << ";\n";
		}
	}
	izlaz.close();
	pElement->InsertEndChild(pElement1);

	//
	XMLElement* pSelekcije = doc.NewElement("OpisSelekcije");//cuva sve selekcije sa njihovim parametrima
	pSelekcije->SetAttribute("BrojSelekcija", i.selekcije.size());

	
	for (auto x : i.selekcije) {
		XMLElement* psel = doc.NewElement("Selekcija");
		psel->SetAttribute("Aktivna", x.second.Get_aktivnost());
		psel->SetAttribute("Ime", x.first.c_str());
		psel->SetAttribute("BrojPravougaonika", x.second.okviri.size());
		for (auto prav : x.second.okviri) {
			XMLElement* pokv = doc.NewElement("Okvir");
			pokv->SetAttribute("x", prav.Get_x());
			pokv->SetAttribute("y", prav.Get_y());
			pokv->SetAttribute("sir", prav.Get_sirina());
			pokv->SetAttribute("vis", prav.Get_visina());
			psel->InsertEndChild(pokv);
		}
		pSelekcije->InsertEndChild(psel);
}
	node->InsertEndChild(pSelekcije);/**/

	XMLElement* pKomp = doc.NewElement("Kompozitne");
	int count = 0;

	for ( auto x:i.kompoper)// i za  kompozitn funkciju eksportuje i cuva putanju do nje
	{
		count++;
		string s = "kompozitna.xml";
		string s1;

		if(poz==-1)
		s1= std::to_string(count) + s;
		else 
			s1= s2+std::to_string(count) + s;
		XMLElement* pc = doc.NewElement("Komp");
		x.exportuj(s1);
		pc->SetAttribute("Putanja", s1.c_str());
		pKomp->InsertEndChild(pc);
	}
	node->InsertEndChild(pKomp);
	doc.SaveFile(file);

	fclose(file);
}


std::vector<Layer>  MyFormater::importImage(const char* path,int prov,Image &img) {//obrnuto od ucitavanja, setuje sve podatke od slojevima, kompozitnim funkcijama i vraca vektor slojeva
	vector<Layer> retlayer;

	FILE* file = fopen(path, "rb");
	if (!file) {
		cout << "Greska u fajlu\n";
		return retlayer;
	}
	tinyxml2::XMLDocument doc;
	doc.LoadFile(file);

	XMLNode* node = doc.FirstChild();
	if (node == nullptr) {
		cout << "Greska u fajlu";
		return retlayer;
	}
	if (!node)cout << 0;
	XMLElement* el = node->FirstChildElement("Opis");
	if (el == nullptr) {
		cout << "Greska u fajlu";
		return retlayer;
	}
	int w, h, bs;
	const XMLAttribute* atr = el->FindAttribute("Sirina");
	if (atr == nullptr) {
		cout << "Greska u fajlu";
		return retlayer;
	}
    atr->QueryIntValue(&w);
	const XMLAttribute* atr1 = el->FindAttribute("Visina");
	if (atr1 == nullptr) {
		cout << "Greska u fajlu";
		return retlayer;
	}
	atr1->QueryIntValue(&h);
	const XMLAttribute* atr2 = el->FindAttribute("BrojSlojeva");
	if (atr2 == nullptr) {
		cout << "Greska u fajlu";
		return retlayer;
	}
	atr2->QueryIntValue(&bs);

	
	std::vector<Layer> niz1;
	XMLElement* el1 = el->FirstChildElement("Layer");




	while (el1 != nullptr) {
		const XMLAttribute* at = el1->FindAttribute("Providnost");
		if (at == nullptr) {
			cout << "Greska u fajlu";
			return retlayer;
		}
		int t;
		at->QueryIntValue(&t);
		bool op, pr;
		at = el1->FindAttribute("Aktivanoperacije");
		if (at == nullptr) {
			cout << "Greska u fajlu";
			return retlayer;
		}
		at->QueryBoolValue(&op);
		at = el1->FindAttribute("Aktivanprikaz");
		if (at == nullptr) {
			cout << "Greska u fajlu";
			return retlayer;
		}
		at->QueryBoolValue(&pr);
		at = el1->FindAttribute("Putanja");
		if (at == nullptr) {
			cout << "Greska u fajlu";
			return retlayer;
		}
		const char* ch = at->Value();

		ifstream ul;
		ul.open(ch);
		if (node == nullptr) {
			cout << "Greska u fajlu";
			return retlayer;
		}
		
		std::regex r1("([^;]*).*");
		string red;
		std::smatch result;
		std::regex r2("([0-9]*),([0-9]*),([0-9]*),([0-9]*).*");//presporo je ako se radi regex-om

		std::smatch rez;
	
		std::vector<std::vector<Pixel>>niz;
		char c;
		int r, g, b,alfa;
		for (int i = 0; i < h;i++)
		{
			std::vector<Pixel>niz1;
			for (int j = 0; j < w; j++)
			{
				ul >> r >> c >> g >> c >> b >> c >>alfa>>c;
				niz1.push_back(Pixel(r, g, b, alfa*255/100));
			}

			niz.push_back(niz1);

			
			
		}
		el1 = el1->NextSiblingElement("Layer");
		retlayer.push_back(Layer(niz, h, w, t, op, pr));
		ul.close();
	}

	
	XMLElement *novielem = node->FirstChildElement("OpisSelekcije");
	if (novielem == nullptr) {
		cout << "Greska u fajlu";
		return retlayer;
	}
	const XMLAttribute* atribut = novielem->FindAttribute("BrojSelekcija");
	if (atribut == nullptr) {
		cout << "Greska u fajlu";
		return retlayer;
	}
	int selnum;

	atribut->QueryIntValue(&selnum);


	if (selnum) {
		XMLElement* elem = novielem->FirstChildElement("Selekcija");
		for (int i = 0; i < selnum; i++)
		{
			vector<Rectangle>rekt;
			bool akt;
			string s;
			int numkvadrata;
			const XMLAttribute* selatr = elem->FindAttribute("Aktivna");
			selatr->QueryBoolValue(&akt);
			selatr = elem->FindAttribute("Ime");
			s = selatr->Value();
			selatr = elem->FindAttribute("BrojPravougaonika");
			selatr->QueryIntValue(&numkvadrata);
			XMLElement* pravougaonici = elem->FirstChildElement("Okvir");
			for (int j = 0; j < numkvadrata; j++)
			{
				int x, y, duz, sir;
				const XMLAttribute* rek = pravougaonici->FindAttribute("x");
				rek->QueryIntValue(&x);
				rek = pravougaonici->FindAttribute("y");
				rek->QueryIntValue(&y);
				rek = pravougaonici->FindAttribute("sir");
				rek->QueryIntValue(&sir);
				rek = pravougaonici->FindAttribute("vis");
				rek->QueryIntValue(&duz);
				rekt.push_back(Rectangle(x, y, sir, duz));
				pravougaonici = pravougaonici->NextSiblingElement("Okvir");
			}

			img.Dodaj_Selekciju(s, rekt, akt);
			elem = elem->NextSiblingElement("Selekcija");
		}

	}

	XMLElement* novielem1 = node->FirstChildElement("Kompozitne");
	if (novielem1 == nullptr) {
		cout << "Greska u fajlu";
		return retlayer;
	}
	XMLElement* kom = novielem1->FirstChildElement("Komp");
	const XMLAttribute* put;
	while (kom != nullptr) {

		put = kom->FindAttribute("Putanja");
		if (put == nullptr) {
			cout << "Greska u fajlu";
			return retlayer;
		}
		string s = put->Value();
		img.Dodaj_Kompozitnu_funkciju(CompositeOperation(s.c_str()));
		kom = kom->NextSiblingElement("Komp");
	}

		std::fclose(file);
	return retlayer;
}