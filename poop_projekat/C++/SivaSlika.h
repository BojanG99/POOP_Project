#pragma once
#include"Operation.h"
class SivaSlika :public Operation
{

public:
	virtual void izvrsi(Pixel** p)override {
		int mid = ((**p).Get_red() + (**p).Get_blue() + (**p).Get_green()) / 3;
		
		(**p).Set_blue(mid);
		(**p).Set_green(mid);
		(**p).Set_red(mid);
		
	
	}
	virtual const char* Get_name()const override {
		return "Siva";
	}
	virtual SivaSlika* kopija()override {
		return new SivaSlika();
	}
};

