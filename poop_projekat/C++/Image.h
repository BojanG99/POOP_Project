#pragma once
#include"Selection.h"
#include"Layer.h"
#include"Operation.h"
#include"MyFormater.h"
#include"BMPFormater.h"
#include<map>
#include<vector>
#include<string>
#include"CompositeOperation.h"
#include<algorithm>
#include<iostream>
#include"PamFormater.h"
class Image
{


	std::map< std::string, Selection> selekcije;
	std::vector<Layer> slojevi;
	std::vector<CompositeOperation>kompoper;//vektor kompozitnih operacija
	int height, width;
	std::vector<std::vector<int>>change;
	int numSel ;
	mutable bool save = false;//da li se sacuvalo od poslednje promjene
	Image();
	static Image* imginst;
public:
	bool Get_save()const {
		return save;
	}
	static Image* Get_Image();//Pravi se samo 1 istanca klase Image
	void Aktiviraj_Selekciju(std::string sel);//Aktivira selekciju sa zadatim imenom
	void Deaktiviraj_Selekciju(std::string sel);//Deaktivira selekciju sa zadatim imenom
	void Aktiviraj_Sloj_Operation(int at);
	void Deaktiviraj_Sloj_Operation(int at);
	void Aktiviraj_Sloj_Save(int at);
	void Deaktiviraj_Sloj_Save(int at);
	friend class MyFormater;
	void Poravnaj(Layer l);//Izravnava slojeve i ubacuje zadati sloj
	int Dodaj_Sloj(std::string c, int prov);//Dodaje sloj iz zadatog fajla
	void Dodaj_Selekciju(std::string s, std::vector<Rectangle>&r, bool akt = false);//Dodaje Selekciju sa zadatim imenom i parametrima
	void Exportuj_sliku(std::string ch)const;//Cuva sliku u fajl i format zadat argumentom
	void Izvrsi_Operaciju();//Izvrsava operaciju
	std::vector<std::vector<Pixel>> Napravi_Sliku()const;//Pravi sliku od trenutnog stanja piksela i slojeva
	int d(int a)const ;//Koristimo za nalazenje susjednih piksela	
	int ux(int a)const ;//Koristimo za nalazenje susjednih piksela
	int uy(int a)const;//Koristimo za nalazenje susjednih piksela
	void Izbrisi_Sloj(int indx);
	void Dodaj_Kompozitnu_funkciju(CompositeOperation op);
};

