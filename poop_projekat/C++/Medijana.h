#pragma once
#include"Operation.h"
class Medijana:public Operation
{

public:
	
	
	virtual void izvrsi(Pixel** p)override {
	
		int red = (p[0]->Get_red() + p[1]->Get_red() + p[2]->Get_red() + p[3]->Get_red() + p[4]->Get_red()) / 5;
		int blue = (p[0]->Get_blue() + p[1]->Get_blue() + p[2]->Get_blue() + p[3]->Get_blue() + p[4]->Get_blue()) / 5;
		int green = (p[0]->Get_green() + p[1]->Get_green() + p[2]->Get_green() + p[3]->Get_green() + p[4]->Get_green()) / 5;
		p[0]->Set_red(red);
		p[0]->Set_blue(blue);
		p[0]->Set_green(green);
	}
	virtual const char* Get_name()const override {
		return "Med";
	}
	virtual Medijana* kopija()override {
		return new Medijana();
	}
};

