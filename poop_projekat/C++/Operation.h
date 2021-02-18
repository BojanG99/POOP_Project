#pragma once
#include"Pixel.h"

#include<vector>
#include<string>

class Operation//apstraktna klasa sa 3 apstraktne metode
{
protected:
	int konst;
public:
	Operation(int k = 0) :konst(k) {}
	virtual void izvrsi(Pixel** p) = 0;

	int Get_const()const {
		return konst;
	}
	virtual const char* Get_name()const = 0;
	virtual Operation* kopija() = 0;
};

