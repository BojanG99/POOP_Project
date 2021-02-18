#include "CompositeOperation.h"
#include"BasicOperation.h"
#include <iostream>
#include <fstream>
#include"tiny2xml.h"
#include"CrnoBela.h"
#include"SivaSlika.h"
#include"Medijana.h"
#include"Inverzija.h"
using namespace std;
using namespace tinyxml2;
CompositeOperation::CompositeOperation(const char* ch) {//prosljedimo putanju do fajla konstruktoru i on izvuce podatke o kompozitnoj funkciji
	FILE* file = fopen(ch, "rb");
	tinyxml2::XMLDocument doc;
	doc.LoadFile(file);
	XMLNode* node = doc.FirstChild();
	XMLElement* el = node->FirstChildElement();
	const XMLAttribute* at = el->FindAttribute("BrojFunkcija");
	int num ;
	at->QueryIntValue(&num);
	el = el->NextSiblingElement("fun");//dohvata prvu operaciju
	while(el!=nullptr)//dok ima operacija
	{
		int kon;
		const char* c1;
		at = el->FindAttribute("Par");
		at->QueryIntValue(&kon);
		at = el->FindAttribute("Ime");
		c1 = at->Value();
		if (strcmp(c1, "Sum") == 0) {//zavisno od imena operacije pravi novi objekat tog tipa i dodjeljuje mu parametar
			Koperacije.push_back(new Sabiranje(kon));
		}
		else if (strcmp(c1, "Sub") == 0) {
			Koperacije.push_back(new Oduzimanje(kon));
		}
		else if (strcmp(c1, "Mul") == 0) {
			Koperacije.push_back(new Mnozenje(kon));
		}
		else if (strcmp(c1, "Pow") == 0) {
			Koperacije.push_back(new Pow(kon));
		}
		else if (strcmp(c1, "Log") == 0) {
			Koperacije.push_back(new Log(kon));
		}
		else if (strcmp(c1, "Min") == 0) {
			Koperacije.push_back(new Min(kon));
		}
		else if (strcmp(c1, "Max") == 0) {
			Koperacije.push_back(new Max(kon));
		}
		else if (strcmp(c1, "Div") == 0) {
			Koperacije.push_back(new Dijeljenje(kon));
		}
		else if (strcmp(c1, "Idiv") == 0) {
			Koperacije.push_back(new IDijeljenje(kon));
		}
		else if (strcmp(c1, "Isub") == 0) {
			Koperacije.push_back(new IOduzimanje(kon));
		}
		else if (strcmp(c1, "Abs") == 0) {
			Koperacije.push_back(new Abs(kon));
		}
		else if (strcmp(c1, "Crna") == 0) {
			Koperacije.push_back(new CrnoBela());
		}
		else if (strcmp(c1, "Siva") == 0) {
			Koperacije.push_back(new SivaSlika());
		}
		else if (strcmp(c1, "Inv") == 0) {
			Koperacije.push_back(new Inverzija());
		}
		else if (strcmp(c1, "Med") == 0) {
			Koperacije.push_back(new Medijana());
		}
		else {
			std::cout << "Ne prepoznaje ovu funkciju\n"  ;
		}
		el = el->NextSiblingElement("fun");//sledeca operacija
	}
	fclose(file);

}
void CompositeOperation::exportuj(std::string ch) {
	FILE* file = fopen(ch.c_str(), "wb");

	tinyxml2::XMLDocument doc;
	XMLNode* node = doc.NewElement("KompozitnaFunkcija");

	doc.InsertFirstChild(node);
	XMLElement* pElement;
	pElement = doc.NewElement("Opis");
	pElement->SetAttribute("BrojFunkcija", Koperacije.size());
	
	node->InsertFirstChild(pElement);

	for (auto& k:Koperacije)//za svaku operaciju pravi cvor u xml fajlu i kao atribute stavlja ime i parametar
	{
		XMLElement* pElement1=doc.NewElement("fun");
			if(strcmp)
		pElement1->SetAttribute("Ime", k->Get_name());
			
				pElement1->SetAttribute("Par", k->Get_const());
			
		node->InsertEndChild(pElement1);
	}
	


	doc.SaveFile(file);
	fclose(file);

}
 void CompositeOperation::izvrsi(Pixel** p) {

	for (auto k : Koperacije)//za svaku operaciju polimorfno zove funkciju izvrsi
	{
		k->izvrsi(p);
	}

}
 CompositeOperation::~CompositeOperation() {
	 obrisi();
 }
 void CompositeOperation::obrisi() {
	 for (size_t i = 0; i < Koperacije.size(); i++)
	 {



		 Operation* o = Koperacije[i];
		 delete o;
		 Koperacije[i] = nullptr;
	 }
	 for (size_t i = 0; i < Koperacije.size(); i++)
	 {



		 Koperacije.pop_back();
	 }

 }
 CompositeOperation::CompositeOperation(const CompositeOperation& n) {
	 kopiraj(n);
	 
 }
 CompositeOperation::CompositeOperation( CompositeOperation&& n) {
	 premjesti(n);
	
	
 }
 CompositeOperation& CompositeOperation::operator=(const CompositeOperation& n) {
	 if (this != &n) {
		 obrisi();
		 kopiraj(n);
	 }
	 return *this;
 }
 CompositeOperation& CompositeOperation::operator=( CompositeOperation&& n) {
	 if (this != &n) {
		 obrisi();
		 kopiraj(n);
	 }
	 return *this;
 }
 void CompositeOperation::kopiraj(const CompositeOperation& n){
	 for (auto x : n.Koperacije)
	 {
		 Koperacije.push_back(x->kopija());
	 }
	 konst = n.konst;
 }
 void CompositeOperation::premjesti(CompositeOperation& n) {
	 Koperacije = n.Koperacije;
	 konst = n.konst;
	 n.~CompositeOperation();
 }