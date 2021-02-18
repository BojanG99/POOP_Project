#pragma once
#include"Layer.h"

class BMPFormater
{
public:
static 	Layer* Ucitaj_Sliku(const char* ch, int prov);
		BMPFormater() {}
static	void Sacuvaj_Sliku(const char*ch,std::vector<std::vector<Pixel>>l);
};

