#pragma once
#include"Operation.h"
class Inverzija:public Operation
{
public:
	virtual void izvrsi(Pixel** p)override {
		(**p)-255;
		(**p)-255;
		(**p)-255;
	}
	virtual const char* Get_name()const override {
		return "Inv";
	}
	virtual Inverzija* kopija()override {
		return new Inverzija();
	}
};

