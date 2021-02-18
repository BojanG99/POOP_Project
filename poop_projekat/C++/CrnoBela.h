#pragma once
#include"Operation.h"
class CrnoBela:public Operation
{

public:
	virtual void izvrsi(Pixel** p)override {
		int mid = ((**p).Get_red() + (**p).Get_blue() + (**p).Get_green()) / 3;
		if (mid > 127) {
			(**p).Set_blue(255);
			(**p).Set_green(255);
			(**p).Set_red(255);
		}
		else {
			(**p).Set_blue(0);
			(**p).Set_green(0);
			(**p).Set_red(0);
		}
	}
	virtual CrnoBela* kopija()override {
		return new CrnoBela();
	}
	virtual const char* Get_name()const override {
		return "Crna";
	}
};

