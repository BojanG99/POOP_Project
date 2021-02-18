#pragma once
#include"Pixel.h"
#include<stdio.h>
#include<vector>
#include<string>

class Layer
{
public:
	std::vector < std::vector < Pixel> > mat;
	int proz;
	int v, s;
	bool activan,ucestvuje;
public:
	friend class MyFormater;
	friend class Image;
	Layer():proz(0),v(0),s(0),activan(0) {
		
	}
	
	Layer(std::vector<std::vector<Pixel>> m, int visina, int sirina, int prozirnost, bool act = true,bool uces=true) :activan(act),mat(m), v(visina), s(sirina), proz(prozirnost),ucestvuje(uces) {}
	
	int GetV()const {
		return v;
	}
	int GetS()const {
		return s;
	}
	void SetV(int v) {
		this->v = v;
	}//dohvata visinu
	void SetS(int s) {
		this->s = s;
	}//dohvata sirinu
};

