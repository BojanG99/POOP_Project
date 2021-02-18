#pragma once
#include"Image.h"

class PamFormater
{

public:
	static Layer* import(const char* ch,int p);
	static void export1(std::vector<std::vector<Pixel>>p,const char* putanja);

	
};

